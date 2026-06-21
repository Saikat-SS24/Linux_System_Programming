/*
 * ============================================================
 *  ECSBF  —  Endpoint Node  (Client)
 * ============================================================
 *
 *  HOW TO USE
 *  ───────────
 *  ./bin/node
 *  → Choose [1] Register  (first time)
 *  → Choose [2] Login     (returning)
 *  → Enter your Node ID
 *  → Enter your Password
 *  → Type a message + Enter to broadcast to all nodes
 *  → Type  quit  to disconnect
 * ============================================================
 */

#include "../inc/logger.h"
#include "../inc/protocol.h"
#include "../inc/crypto.h"
#include "../inc/utils.h"

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <csignal>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/* ── Global state ───────────────────────────────────────── */
static int               g_fd    = -1;
static std::atomic<bool> g_alive { true };

/* ============================================================
 *  listen_thread()
 *  Receives frames from the engine and prints messages.
 * ============================================================ */
static void listen_thread()
{
    while (g_alive) {

        std::string line = recv_line(g_fd);

        if (line.empty()) {
            if (g_alive) {
                std::cout << "\n  [!] Connection lost.\n";
                g_alive = false;
            }
            break;
        }

        std::vector<std::string> parts = split(line, FRAME_SEP);
        std::string type = parts[0];

        /* ── Incoming broadcast ─────────────────────────── */
        if (type == MSG_BROADCAST && parts.size() == 3) {
            std::string sender_id   = parts[1];
            std::string enc_payload = parts[2];

            std::string payload;
            try   { payload = crypto_decrypt(enc_payload); }
            catch (...) { payload = enc_payload; }

            std::cout << "\n"
                      << "  ╔══ Message from '" << sender_id << "' ══\n"
                      << "  ║  " << payload << "\n"
                      << "  ╚════════════════════════════\n"
                      << "> " << std::flush;

            LOG_INFO("Received from '%s': %s",
                     sender_id.c_str(), payload.c_str());
        }

        /* ── ACK (heartbeat reply etc.) — silent ────────── */
        else if (type == MSG_ACK) {
            /* intentionally no output */
        }

        /* ── Error from engine ──────────────────────────── */
        else if (type == MSG_ERROR) {
            std::cout << "\n  [!] "
                      << (parts.size() > 1 ? parts[1] : line) << "\n";
            LOG_WARNING("Engine error: %s",
                        parts.size() > 1 ? parts[1].c_str() : line.c_str());
        }
    }
}

/* ============================================================
 *  keepalive_thread()
 *  Silently pings the engine every 20 s. No output.
 * ============================================================ */
static void keepalive_thread()
{
    while (g_alive) {
        for (int i = 0; i < 20 && g_alive; i++)
            std::this_thread::sleep_for(std::chrono::seconds(1));
        if (g_alive)
            send_line(g_fd, MSG_HEARTBEAT);
    }
}

/* ============================================================
 *  prompt()
 *  Reads a non-empty value from stdin.
 * ============================================================ */
static std::string prompt(const std::string& label)
{
    std::string value;
    while (value.empty()) {
        std::cout << "  " << label << ": ";
        std::getline(std::cin, value);
        if (value.empty())
            std::cout << "  [!] This field cannot be empty.\n";
    }
    return value;
}

/* ============================================================
 *  main()
 * ============================================================ */
int main()
{
    signal(SIGPIPE, SIG_IGN);

    /* ── Banner ─────────────────────────────────────────── */
    std::cout << "\n"
              << "  ╔══════════════════════════════════════════╗\n"
              << "  ║         ECSBF  —  Node Client            ║\n"
              << "  ╚══════════════════════════════════════════╝\n\n"
              << "  [1]  Register  (new account)\n"
              << "  [2]  Login     (existing account)\n"
              << "  [0]  Exit\n\n";

    /* ── Menu ───────────────────────────────────────────── */
    std::string choice;
    bool do_register = false;

    while (true) {
        std::cout << "  Select an option: ";
        std::getline(std::cin, choice);
        if (choice == "1") { do_register = true;  break; }
        if (choice == "2") { do_register = false; break; }
        if (choice == "0") { std::cout << "\n  Goodbye!\n\n"; return 0; }
        std::cout << "  [!] Enter 1, 2, or 0.\n";
    }

    std::cout << "\n";

    /* ── Credentials ────────────────────────────────────── */
    std::string node_id  = prompt("Node ID");
    std::string password = prompt("Password");

    std::cout << "\n";

    /* ── Logger ─────────────────────────────────────────── */
    Logger::init("logs/node_" + node_id + ".log");
    LOG_INFO("Node '%s' starting", node_id.c_str());

    /* ── Connect ────────────────────────────────────────── */
    g_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (g_fd < 0) { LOG_FATAL("socket() failed"); return 1; }

    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port   = htons(DEFAULT_PORT);
    inet_pton(AF_INET, DEFAULT_HOST, &server.sin_addr);

    if (connect(g_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cout << "  [!] Cannot reach engine. Start it first:  ./bin/engine\n\n";
        return 1;
    }

    /* ── Handshake ──────────────────────────────────────── */
    send_line(g_fd, HANDSHAKE_HELLO);
    if (recv_line(g_fd) != HANDSHAKE_READY) {
        std::cout << "  [!] Handshake failed.\n";
        close(g_fd);
        return 1;
    }

    /* ── Send credentials ───────────────────────────────── */
    std::string enc_id = crypto_encrypt(node_id);
    std::string enc_pw = crypto_encrypt(password);
    std::string msg_type = do_register ? MSG_REGISTER : MSG_AUTH;
    send_line(g_fd, msg_type + FRAME_SEP + enc_id + FRAME_SEP + enc_pw);

    /* ── Auth response ──────────────────────────────────── */
    std::string resp = recv_line(g_fd);
    std::vector<std::string> rp = split(resp, FRAME_SEP);

    if (rp[0] == MSG_ERROR) {
        std::cout << "  [!] " << (rp.size() > 1 ? rp[1] : resp) << "\n\n";
        close(g_fd);
        return 1;
    }

    /* ── Welcome — the ACK frame itself is the welcome ──── */
    std::cout << "  " << (rp.size() > 1 ? rp[1] : resp) << "\n\n";

    /* ── Start background threads ───────────────────────── */
    std::thread(listen_thread).detach();
    std::thread(keepalive_thread).detach();

    /* ── Input loop ─────────────────────────────────────── */
    std::cout << "  Type a message + Enter to send.  Type  quit  to exit.\n\n";

    while (g_alive) {
        std::cout << "> ";
        std::string input;
        if (!std::getline(std::cin, input) || !g_alive) break;
        if (input.empty()) continue;

        if (input == "quit") {
            send_line(g_fd, MSG_DISCONNECT);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            break;
        }

        std::string enc_payload = crypto_encrypt(input);
        send_line(g_fd, std::string(MSG_BROADCAST) + FRAME_SEP + enc_payload);
        LOG_INFO("'%s' sent a message", node_id.c_str());
    }

    g_alive = false;
    close(g_fd);
    std::cout << "\n  Disconnected. Goodbye!\n\n";
    return 0;
}
