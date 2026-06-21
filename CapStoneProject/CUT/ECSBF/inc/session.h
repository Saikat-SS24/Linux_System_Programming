#pragma once
/*
 * ============================================================
 *  ECSBF  —  Session Manager
 *  Requirement-4 : maintain active sessions; restore on reconnect
 *  Requirement-8 : purge session on disconnect
 * ============================================================
 *
 *  WHAT IS A SESSION?
 *  ──────────────────
 *  A session = one connected, authenticated node.
 *  It holds:
 *      • node_id    — who the node is
 *      • socket_fd  — the open TCP socket to that node
 *      • ip_address — where they connected from
 *      • connected_at — timestamp
 *
 *  STORAGE
 *  ───────
 *  Same idea as the Registry — a plain std::map:
 *
 *      sessions_["alice"] = { socket_fd=5, ip="127.0.0.1", ... }
 *      sessions_["bob"]   = { socket_fd=7, ip="127.0.0.1", ... }
 *
 *  FUNCTIONS
 *  ─────────
 *      create()      → add/replace a session  (Req-4 restore)
 *      remove()      → close socket, erase     (Req-8 purge)
 *      get_all()     → list all sessions       (used for broadcast)
 *      count()       → how many nodes connected?
 * ============================================================
 */

#include <string>
#include <map>
#include <vector>
#include <mutex>

/* ── One live session ───────────────────────────────────── */
struct Session
{
    std::string node_id;
    int         socket_fd;
    std::string ip_address;
    std::string connected_at;
};

/* ── Session Manager class ──────────────────────────────── */
class SessionManager
{
public:
    SessionManager();

    /* Req-4 : create or replace session for node_id */
    void create(const std::string& node_id,
                int   socket_fd,
                const std::string& ip_address);

    /* Req-8 : close socket and erase session */
    void remove(const std::string& node_id, int caller_fd);

    /* return copy of all sessions (used by broadcast) */
    std::vector<Session> get_all() const;

    /* number of currently connected nodes */
    int count() const;

private:
    /* ── THE SESSION TABLE ─────────────────────────────────
     *  key   = node_id
     *  value = Session struct
     * ─────────────────────────────────────────────────── */
    std::map<std::string, Session> sessions_;
    mutable std::mutex lock_;

    std::string now() const;
};
