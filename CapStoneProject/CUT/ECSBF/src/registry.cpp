/*
 * ============================================================
 *  ECSBF  —  Global Identity Registry
 *  Tracks all registered nodes in memory.
 *  Handles registration (provision) and login (verify).
 * ============================================================
 */

#include "../inc/registry.h"
#include "../inc/logger.h"

#include <mutex>
#include <ctime>

/* ── Constructor ────────────────────────────────────────── */
Registry::Registry()
{
    LOG_INFO("Registry ready");
}

/* ============================================================
 *  provision()
 *  Registers a new node.
 *  Returns false if the node ID is already taken.
 * ============================================================ */
bool Registry::provision(const std::string& node_id,
                          const std::string& password_hash,
                          const std::string& ip_address)
{
    std::lock_guard<std::mutex> guard(lock_);

    if (registry_.count(node_id) > 0) {
        LOG_WARNING("Registration failed — '%s' already exists", node_id.c_str());
        return false;
    }

    NodeRecord rec;
    rec.node_id       = node_id;
    rec.password_hash = password_hash;
    rec.ip_address    = ip_address;
    rec.registered_at = now();
    rec.last_seen     = "";

    registry_[node_id] = rec;

    LOG_INFO("Node registered: '%s'", node_id.c_str());
    return true;
}

/* ============================================================
 *  verify()
 *  Checks credentials for login.
 *  On success, updates last_seen.
 * ============================================================ */
bool Registry::verify(const std::string& node_id,
                       const std::string& password_hash,
                       const std::string& ip_address)
{
    std::lock_guard<std::mutex> guard(lock_);

    if (registry_.count(node_id) == 0) {
        LOG_WARNING("Login failed — unknown node '%s'", node_id.c_str());
        return false;
    }

    if (registry_[node_id].password_hash != password_hash) {
        LOG_WARNING("Login failed — wrong password for '%s'", node_id.c_str());
        return false;
    }

    registry_[node_id].last_seen  = now();
    registry_[node_id].ip_address = ip_address;

    LOG_INFO("Node logged in: '%s'", node_id.c_str());
    return true;
}

/* ── exists() ───────────────────────────────────────────── */
bool Registry::exists(const std::string& node_id) const
{
    std::lock_guard<std::mutex> guard(lock_);
    return registry_.count(node_id) > 0;
}

/* ============================================================
 *  resolve_ip()
 *  Returns all node IDs previously seen from a given IP.
 * ============================================================ */
std::vector<std::string> Registry::resolve_ip(const std::string& ip) const
{
    std::lock_guard<std::mutex> guard(lock_);

    std::vector<std::string> matches;
    for (const auto& pair : registry_) {
        if (pair.second.ip_address == ip)
            matches.push_back(pair.first);
    }
    return matches;
}

/* ── all_nodes() ────────────────────────────────────────── */
std::vector<NodeRecord> Registry::all_nodes() const
{
    std::lock_guard<std::mutex> guard(lock_);

    std::vector<NodeRecord> result;
    for (const auto& pair : registry_)
        result.push_back(pair.second);
    return result;
}

/* ── now() ──────────────────────────────────────────────── */
std::string Registry::now() const
{
    time_t t = time(nullptr);
    struct tm* tm_info = localtime(&t);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    return std::string(buf);
}
