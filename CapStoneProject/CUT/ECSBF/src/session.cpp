/*
 * ============================================================
 *  ECSBF  —  Session Manager
 *  Tracks active node sessions in memory.
 *  On disconnect, closes the socket and removes the entry.
 * ============================================================
 */

#include "../inc/session.h"
#include "../inc/logger.h"

#include <mutex>
#include <ctime>
#include <unistd.h>

/* ── Constructor ────────────────────────────────────────── */
SessionManager::SessionManager()
{
    LOG_INFO("SessionManager ready");
}

/* ============================================================
 *  create()
 *  Adds or replaces a session for node_id.
 *  If the node reconnects, the old socket is closed first.
 * ============================================================ */
void SessionManager::create(const std::string& node_id,
                              int socket_fd,
                              const std::string& ip_address)
{
    std::lock_guard<std::mutex> guard(lock_);

    if (sessions_.count(node_id) > 0) {
        /* Do NOT close the old fd here.  The old handle_client thread
         * already owns that fd and will close it via remove() when its
         * recv_line returns empty.  Closing it here races with the OS
         * recycling the same fd number for the brand-new connection,
         * which instantly kills the reconnecting node.            */
        LOG_INFO("Session restored for '%s'", node_id.c_str());
    }

    Session s;
    s.node_id      = node_id;
    s.socket_fd    = socket_fd;
    s.ip_address   = ip_address;
    s.connected_at = now();

    sessions_[node_id] = s;

    LOG_INFO("Session started: '%s'  (active: %d)",
             node_id.c_str(), (int)sessions_.size());
}

/* ============================================================
 *  remove()
 *  Closes the socket and erases the session entry.
 *  Takes the caller's fd so a stale thread can't evict a
 *  newer session that reused the same node_id.
 * ============================================================ */
void SessionManager::remove(const std::string& node_id, int caller_fd)
{
    std::lock_guard<std::mutex> guard(lock_);

    if (sessions_.count(node_id) == 0) {
        /* Session was already superseded and cleaned up — just
         * close our own fd and leave.                          */
        close(caller_fd);
        LOG_WARNING("remove() — no session found for '%s' (fd already replaced)",
                    node_id.c_str());
        return;
    }

    if (sessions_[node_id].socket_fd != caller_fd) {
        /* A newer session for the same node_id is active.
         * Only close our own (old) fd; leave the new session alone. */
        close(caller_fd);
        LOG_INFO("remove() — old session for '%s' cleaned up (new session active)",
                 node_id.c_str());
        return;
    }

    close(caller_fd);
    sessions_.erase(node_id);

    LOG_INFO("Session ended: '%s'  (active: %d)",
             node_id.c_str(), (int)sessions_.size());
}

/* ── get_all() — snapshot for broadcast ────────────────── */
std::vector<Session> SessionManager::get_all() const
{
    std::lock_guard<std::mutex> guard(lock_);
    std::vector<Session> out;
    for (const auto& pair : sessions_)
        out.push_back(pair.second);
    return out;
}

/* ── count() ────────────────────────────────────────────── */
int SessionManager::count() const
{
    std::lock_guard<std::mutex> guard(lock_);
    return (int)sessions_.size();
}

/* ── now() ──────────────────────────────────────────────── */
std::string SessionManager::now() const
{
    time_t t = time(nullptr);
    struct tm* ti = localtime(&t);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ti);
    return std::string(buf);
}
