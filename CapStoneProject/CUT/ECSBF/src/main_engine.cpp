/*
 * ============================================================
 *  ECSBF  —  Engine Entry Point
 *  Compile:  see Makefile
 *  Run:      ./bin/engine          (uses port 9090)
 *            ./bin/engine 8080     (custom port)
 * ============================================================
 */

#include "../inc/logger.h"
#include "../inc/protocol.h"
#include "../inc/engine.h"

#include <iostream>
#include <csignal>
#include <cstdlib>

int main(int argc, char* argv[])
{
    /* Ignore SIGPIPE so the engine doesn't crash when a
     * client disconnects mid-send */
    signal(SIGPIPE, SIG_IGN);

    /* ── Logger — Req-12 ────────────────────────────────── */
    Logger::init("logs/engine.log");
    LOG_INFO("=== ECSBF Engine starting ===");

    /* ── Port (default or command-line override) ────────── */
    int port = DEFAULT_PORT;
    if (argc > 1) {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            LOG_FATAL("Invalid port: %s", argv[1]);
            return 1;
        }
    }

    /* ── Create and run the engine ──────────────────────── */
    Engine engine(DEFAULT_HOST, port);
    engine.run();   /* blocks forever (Ctrl+C to stop) */

    return 0;
}
