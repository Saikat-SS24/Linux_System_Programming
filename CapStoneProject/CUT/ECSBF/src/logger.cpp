/*
 * ============================================================
 *  ECSBF  —  Logger Implementation       (Requirement-12)
 * ============================================================
 *  Levels:  DEBUG  INFO  WARNING  FATAL
 *  Output:  terminal  +  logs/ecsbf.log
 * ============================================================
 */

#include "../inc/logger.h"

#include <cstdio>
#include <ctime>
#include <cstdarg>
#include <mutex>
#include <string>

/* ── Static member definitions ──────────────────────────── */
FILE*       Logger::file_ = nullptr;
std::mutex  Logger::mtx_;

/* ============================================================
 *  Logger::init()
 *  Call once at program start.
 *  Opens (or creates) the log file in append mode.
 * ============================================================ */
void Logger::init(const std::string& filepath)
{
    std::lock_guard<std::mutex> guard(mtx_);

    file_ = fopen(filepath.c_str(), "a");   /* "a" = append */

    if (!file_) {
        /* Can't open file — log to stderr so we know */
        fprintf(stderr,
                "[Logger] WARNING: cannot open log file '%s' — "
                "file logging disabled.\n",
                filepath.c_str());
    }
}

/* ============================================================
 *  Logger::write()
 *  Called by LOG_DEBUG / LOG_INFO / LOG_WARNING / LOG_FATAL.
 *  Do NOT call this directly — use the macros.
 *
 *  Output line format:
 *    [2026-05-21 10:00:00] [INFO   ] Engine started on port 9090
 * ============================================================ */
void Logger::write(int         /*level*/,
                   const char* level_str,
                   const char* fmt, ...)
{
    /* ── Build timestamp ────────────────────────────────── */
    time_t     now_t = time(nullptr);
    struct tm* t     = localtime(&now_t);
    char       ts[32];
    strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", t);

    /* ── Expand format string with the variadic arguments ── */
    char msg[2048];
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg, sizeof(msg), fmt, args);
    va_end(args);

    /* ── Compose full line ──────────────────────────────── */
    /* Format:  [timestamp] [LEVEL  ] message               */
    char line[2200];
    snprintf(line, sizeof(line), "[%s] [%s] %s\n", ts, level_str, msg);

    /* ── Write (thread-safe) ────────────────────────────── */
    std::lock_guard<std::mutex> guard(mtx_);

    /* to terminal */
    fputs(line, stdout);
    fflush(stdout);

    /* to log file */
    if (file_) {
        fputs(line, file_);
        fflush(file_);
    }
}
