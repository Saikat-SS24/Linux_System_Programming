#pragma once
/*
 * ============================================================
 *  ECSBF  —  Central Engine
 *  Requirement-1  : TCP/IP handshake
 *  Requirement-2  : node provisioning
 *  Requirement-3  : identity verification
 *  Requirement-4  : persistent sessions
 *  Requirement-5  : multi-threaded concurrency
 *  Requirement-6  : broadcast to all nodes with source ID
 *  Requirement-7  : owns the global identity registry
 *  Requirement-8  : session cleanup on disconnect
 *  Requirement-9  : IP resolution logging
 *  Requirement-10 : decrypts incoming frames
 *  Requirement-12 : logs everything
 * ============================================================
 */

#include "registry.h"
#include "session.h"
#include <string>

class Engine
{
public:
    Engine(const std::string& host, int port);

    /* Bind socket, start accept loop (blocks until stopped) */
    void run();

private:
    std::string host_;
    int         port_;
    int         server_fd_;   /* listening TCP socket */

    Registry       registry_;   /* Req-7  */
    SessionManager sessions_;   /* Req-4/8 */

    /* ── Per-connection worker (runs in its own thread) ── */
    void handle_client(int client_fd, std::string client_ip);

    /* ── Step functions called from handle_client ──────── */
    bool        do_handshake  (int fd, const std::string& ip);
    std::string do_auth       (int fd, const std::string& ip);
    void        do_message_loop(int fd, const std::string& node_id);

    /* ── Req-6 : broadcast plaintext to every live node ── */
    void broadcast(const std::string& sender_id,
                   const std::string& plaintext);
};
