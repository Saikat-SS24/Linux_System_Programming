#pragma once
/*
 * ============================================================
 *  ECSBF  —  Utility Functions
 *  Small helpers used by both engine and node.
 * ============================================================
 */

#include <string>
#include <vector>

/*
 *  sha256(text)
 *  ─────────────
 *  Returns a 64-character hex string — the SHA-256 hash.
 *  Used to store passwords safely.  One-way: you cannot
 *  reverse it back to the original password.
 *
 *  Example:
 *      sha256("hello") → "2cf24dba5fb0a30e26e83b2ac5b9e29e..."
 */
std::string sha256(const std::string& input);

/*
 *  split(str, separator)
 *  ──────────────────────
 *  Breaks a string into pieces at every occurrence of separator.
 *
 *  Example:
 *      split("REGISTER||alice||pass", "||")
 *      → { "REGISTER", "alice", "pass" }
 */
std::vector<std::string> split(const std::string& str,
                                const std::string& sep);

/*
 *  send_line(socket_fd, message)
 *  ──────────────────────────────
 *  Sends  message + '\n'  over the given TCP socket.
 *  Returns true on success, false if the socket broke.
 */
bool send_line(int socket_fd, const std::string& message);

/*
 *  recv_line(socket_fd)
 *  ──────────────────────
 *  Reads characters from the socket until '\n' is found.
 *  Returns the line WITHOUT the '\n'.
 *  Returns ""  if the connection was closed or an error occurred.
 */
std::string recv_line(int socket_fd);
