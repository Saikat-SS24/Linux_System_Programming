#pragma once
/*
 * ============================================================
 *  ECSBF  —  Logger                          (Requirement-12)
 * ============================================================
 *  Supports four verbosity levels:
 *      DEBUG    lowest — detailed tracing
 *      INFO     normal operational messages
 *      WARNING  something unexpected but recoverable
 *      FATAL    unrecoverable error
 *
 *  Every message is written to:
 *      • stdout  (your terminal)
 *      • logs/ecsbf.log  (file on disk)
 *
 *  HOW TO USE
 *  ──────────
 *      Logger::init("logs/ecsbf.log");   // call once at startup
 *      LOG_INFO   ("Engine started on port %d", 9090);
 *      LOG_WARNING("Unknown node tried to connect");
 *      LOG_DEBUG  ("Heartbeat from '%s'", node_id.c_str());
 *      LOG_FATAL  ("Cannot bind socket on port %d", port);
 * ============================================================
 */

#include <string>
#include <mutex>
#include <cstdio>

/* ── Log-level codes ─────────────────────────────────────── */
#define LOG_LEVEL_DEBUG    0
#define LOG_LEVEL_INFO     1
#define LOG_LEVEL_WARNING  2
#define LOG_LEVEL_FATAL    3

/* ── Convenience macros ──────────────────────────────────── */
#define LOG_DEBUG(fmt, ...)   Logger::write(LOG_LEVEL_DEBUG,   "DEBUG  ", fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)    Logger::write(LOG_LEVEL_INFO,    "INFO   ", fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) Logger::write(LOG_LEVEL_WARNING, "WARNING", fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)   Logger::write(LOG_LEVEL_FATAL,   "FATAL  ", fmt, ##__VA_ARGS__)

/* ── Logger class ────────────────────────────────────────── */
class Logger
{
public:
    /*
     *  Call once before any LOG_* macro.
     *  Opens the log file in append mode.
     */
    static void init(const std::string& filepath);

    /*
     *  Internal function — do NOT call directly.
     *  Use the macros above instead.
     */
    static void write(int level,
                      const char* level_str,
                      const char* fmt, ...);

private:
    static FILE*        file_;   /* open log file handle          */
    static std::mutex   mtx_;    /* protects concurrent writes    */
};
