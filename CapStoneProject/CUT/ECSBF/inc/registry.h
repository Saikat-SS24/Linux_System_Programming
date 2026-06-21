#pragma once
/*
 * ============================================================
 *  ECSBF  —  Global Identity Registry
 *  Requirement-7 : track all provisioned nodes
 *  Requirement-9 : resolve IP address → node_id(s)
 * ============================================================
 *
 *  STORAGE  (easy, no files needed)
 *  ─────────────────────────────────
 *  We use a single  std::map<string, NodeRecord>
 *  which is just like a dictionary / lookup table:
 *
 *      registry["alice"] = { pw_hash, ip, registered_at, last_seen }
 *      registry["bob"]   = { pw_hash, ip, registered_at, last_seen }
 *
 *  A std::map keeps entries sorted by key and lets us look up
 *  any entry in O(log n) time using registry["key"].
 *
 *  The data lives in RAM while the engine runs.
 *  When the engine stops, data is cleared (in-memory only).
 *
 *  THREAD SAFETY
 *  ─────────────
 *  Multiple client threads read/write the map at the same time.
 *  We use a std::mutex (a lock) so only ONE thread touches the
 *  map at a time — preventing data corruption.
 *
 *  FUNCTIONS
 *  ─────────
 *      provision()   → add a new node          (Req-2)
 *      verify()      → check login credentials  (Req-3)
 *      exists()      → is this node registered?
 *      resolve_ip()  → which nodes came from IP? (Req-9)
 *      all_nodes()   → list all nodes            (Req-7)
 * ============================================================
 */

#include <string>
#include <map>
#include <vector>
#include <mutex>

/* ── One node's stored record ───────────────────────────── */
struct NodeRecord
{
    std::string node_id;         /* e.g. "alice"            */
    std::string password_hash;   /* sha256 hex of password  */
    std::string ip_address;      /* last known IP           */
    std::string registered_at;   /* time of first register  */
    std::string last_seen;       /* time of last login      */
};

/* ── Registry class ─────────────────────────────────────── */
class Registry
{
public:
    Registry();

    /* Req-2 : add new node — returns false if name taken */
    bool provision(const std::string& node_id,
                   const std::string& password_hash,
                   const std::string& ip_address);

    /* Req-3 : check credentials — returns true if OK */
    bool verify(const std::string& node_id,
                const std::string& password_hash,
                const std::string& ip_address);

    /* returns true if node_id is in the map */
    bool exists(const std::string& node_id) const;

    /* Req-9 : return all node_ids registered from ip_address */
    std::vector<std::string> resolve_ip(const std::string& ip_address) const;

    /* Req-7 : return every record (for diagnostics / admin) */
    std::vector<NodeRecord> all_nodes() const;

private:
    /* ── THE REGISTRY ──────────────────────────────────────
     *  key   = node_id  (string)
     *  value = NodeRecord (struct above)
     *
     *  std::map automatically keeps entries sorted by key.
     *  Access: registry_["alice"]  — returns NodeRecord.
     * ─────────────────────────────────────────────────── */
    std::map<std::string, NodeRecord> registry_;

    /* lock_ protects registry_ from concurrent modification */
    mutable std::mutex lock_;

    /* helper — returns current time as "YYYY-MM-DD HH:MM:SS" */
    std::string now() const;
};
