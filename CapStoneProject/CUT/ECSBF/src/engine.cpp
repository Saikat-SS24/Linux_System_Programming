/*
 * ============================================================
 *  ECSBF  —  Central Engine  (Server)
 * ============================================================
 *  Handles node connections, registration, authentication,
 *  broadcasting, and session cleanup.
 * ============================================================
 */

#include "../inc/engine.h"
#include "../inc/logger.h"
#include "../inc/protocol.h"
#include "../inc/crypto.h"
#include "../inc/utils.h"

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <csignal>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/* ── Constructor ────────────────────────────────────────── */
Engine::Engine(const std::string& host, int port)
    : host_(host), port_(port), server_fd_(-1)
{
    LOG_INFO("Engine ready");
}

/* ============================================================
 *  run()
 *  Binds, listens, and spawns one thread per connected node.
 * ============================================================ */
void Engine::run()
{
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ < 0) {
        LOG_FATAL("Failed to create server socket");
        return;
    }

    int opt = 1;
    setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port_);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        LOG_FATAL("bind() failed — is port %d already in use?", port_);
        close(server_fd_);
        return;
    }

    if (listen(server_fd_, 128) < 0) {
        LOG_FATAL("listen() failed");
        close(server_fd_);
        return;
    }

    LOG_INFO("Engine is online");

    std::cout << "\n"
              << "  ╔══════════════════════════════════════════╗\n"
              << "  ║    ECSBF Engine  —  Online               ║\n"
              << "  ║    Ready  (Ctrl+C to stop)               ║\n"
              << "  ╚══════════════════════════════════════════╝\n\n";

    while (true) {
        struct sockaddr_in client_addr{};
        socklen_t          client_len = sizeof(client_addr);

        int client_fd = accept(server_fd_,
                               (struct sockaddr*)&client_addr,
                               &client_len);
        if (client_fd < 0) {
            LOG_WARNING("accept() error — continuing");
            continue;
        }

        std::string client_ip = inet_ntoa(client_addr.sin_addr);
        std::thread t(&Engine::handle_client, this, client_fd, client_ip);
        t.detach();
    }
}

/* ============================================================
 *  handle_client()
 *  Runs in its own thread: handshake → auth → message loop.
 * ============================================================ */
void Engine::handle_client(int client_fd, std::string client_ip)
{
    std::string node_id;

    if (!do_handshake(client_fd, client_ip)) {
        close(client_fd);
        return;
    }

    node_id = do_auth(client_fd, client_ip);
    if (node_id.empty()) {
        close(client_fd);
        return;
    }

    sessions_.create(node_id, client_fd, client_ip);

    std::cout << "  [+] '" << node_id << "' connected"
              << "  (active: " << sessions_.count() << ")\n";

    do_message_loop(client_fd, node_id);

    sessions_.remove(node_id, client_fd);
    std::cout << "  [-] '" << node_id << "' disconnected"
              << "  (active: " << sessions_.count() << ")\n";
}

/* ============================================================
 *  do_handshake()
 *  Verifies the initial HELLO/READY exchange.
 * ============================================================ */
bool Engine::do_handshake(int fd, const std::string& ip)
{
    std::string hello = recv_line(fd);
    if (hello != HANDSHAKE_HELLO) {
        LOG_WARNING("Bad handshake");
        send_line(fd, std::string(MSG_ERROR) + FRAME_SEP + "Bad handshake");
        return false;
    }
    send_line(fd, HANDSHAKE_READY);
    return true;
}

/* ============================================================
 *  do_auth()
 *  Handles REGISTER or AUTH frame.
 *  Returns node_id on success, "" on failure.
 * ============================================================ */
std::string Engine::do_auth(int fd, const std::string& ip)
{
    std::string frame = recv_line(fd);
    if (frame.empty()) return "";

    std::vector<std::string> parts = split(frame, FRAME_SEP);
    if (parts.size() != 3) {
        send_line(fd, std::string(MSG_ERROR) + FRAME_SEP + "Malformed auth frame");
        return "";
    }

    std::string msg_type     = parts[0];
    std::string enc_node_id  = parts[1];
    std::string enc_password = parts[2];

    std::string node_id, password;
    try {
        node_id  = crypto_decrypt(enc_node_id);
        password = crypto_decrypt(enc_password);
    }
    catch (...) {
        send_line(fd, std::string(MSG_ERROR) + FRAME_SEP + "Decryption failed");
        return "";
    }

    std::string pw_hash = sha256(password);

    /* ── REGISTER ───────────────────────────────────────── */
    if (msg_type == MSG_REGISTER) {
        if (!registry_.provision(node_id, pw_hash, ip)) {
            send_line(fd, std::string(MSG_ERROR) + FRAME_SEP +
                      "Node ID '" + node_id + "' already exists");
            return "";
        }
        send_line(fd, std::string(MSG_ACK) + FRAME_SEP +
                  "Registered:" + node_id);
        return node_id;
    }

    /* ── LOGIN ──────────────────────────────────────────── */
    if (msg_type == MSG_AUTH) {
        if (!registry_.verify(node_id, pw_hash, ip)) {
            send_line(fd, std::string(MSG_ERROR) + FRAME_SEP +
                      "Login failed for '" + node_id + "'");
            return "";
        }
        send_line(fd, std::string(MSG_ACK) + FRAME_SEP +
                  "Authenticated:" + node_id);
        return node_id;
    }

    send_line(fd, std::string(MSG_ERROR) + FRAME_SEP + "Unknown message type");
    return "";
}

/* ============================================================
 *  do_message_loop()
 *  Reads frames from the authenticated node in a loop.
 *  BROADCAST  → forward to all nodes
 *  HEARTBEAT  → silent ACK (no log)
 *  DISCONNECT → clean exit
 * ============================================================ */
void Engine::do_message_loop(int fd, const std::string& node_id)
{
    while (true) {

        std::string line = recv_line(fd);
        if (line.empty()) {
            LOG_INFO("'%s' disconnected", node_id.c_str());
            break;
        }

        std::vector<std::string> parts = split(line, FRAME_SEP);
        std::string type = parts[0];

        /* ── BROADCAST ───────────────────────────────────── */
        if (type == MSG_BROADCAST) {
            if (parts.size() < 2) continue;

            std::string payload;
            try {
                payload = crypto_decrypt(parts[1]);
            }
            catch (...) {
                payload = parts[1];
            }

            std::cout << "  [>] '" << node_id << "': " << payload << "\n";
            LOG_INFO("'%s' broadcast: %s", node_id.c_str(), payload.c_str());
            broadcast(node_id, payload);
        }

        /* ── HEARTBEAT — silent, no console/log output ───── */
        else if (type == MSG_HEARTBEAT) {
            send_line(fd, std::string(MSG_ACK) + FRAME_SEP + "PONG");
        }

        /* ── DISCONNECT ──────────────────────────────────── */
        else if (type == MSG_DISCONNECT) {
            send_line(fd, std::string(MSG_ACK) + FRAME_SEP + "Goodbye");
            LOG_INFO("'%s' disconnected cleanly", node_id.c_str());
            break;
        }

        /* ── Unknown ─────────────────────────────────────── */
        else {
            send_line(fd, std::string(MSG_ERROR) + FRAME_SEP +
                      "Unknown command: " + type);
            LOG_WARNING("Unknown command from '%s': '%s'",
                        node_id.c_str(), type.c_str());
        }
    }
}

/* ============================================================
 *  broadcast()
 *  Encrypts the message and sends it to every active node.
 * ============================================================ */
void Engine::broadcast(const std::string& sender_id,
                        const std::string& plaintext)
{
    std::string enc = crypto_encrypt(plaintext);
    std::string frame = std::string(MSG_BROADCAST)
                      + FRAME_SEP + sender_id
                      + FRAME_SEP + enc;

    std::vector<Session> all = sessions_.get_all();
    for (const Session& s : all) {
        if (!send_line(s.socket_fd, frame)) {
            LOG_WARNING("Broadcast failed to '%s'", s.node_id.c_str());
        }
    }
}
