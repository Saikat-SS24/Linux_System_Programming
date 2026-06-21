#pragma once
/*
 * ============================================================
 *  ECSBF  —  Crypto Module
 *  Requirement-10 : encrypt credentials & payloads
 *  Requirement-11 : decrypt incoming payloads
 * ============================================================
 *
 *  ALGORITHM  (basic string encryption — fresher-friendly)
 *  ────────────────────────────────────────────────────────────
 *  ENCRYPT
 *      Step-1  Caesar cipher  — shift every byte forward by
 *              CRYPTO_SHIFT (13) positions.
 *              Example:  'A'(65) → 'N'(78)
 *      Step-2  Base-64 encode — turn the shifted bytes into
 *              a safe printable string (A-Z a-z 0-9 + /).
 *              This avoids any special characters that could
 *              break the "||" frame separator.
 *
 *  DECRYPT  (exact reverse)
 *      Step-1  Base-64 decode
 *      Step-2  Caesar reverse — shift every byte back by
 *              CRYPTO_SHIFT positions.
 *
 *  HOW TO USE
 *  ──────────
 *      std::string cipher = crypto_encrypt("hello");
 *      std::string plain  = crypto_decrypt(cipher);
 *      // plain == "hello"
 * ============================================================
 */

#include <string>

/* Encrypt plaintext  →  base64( caesar_shift( plaintext ) ) */
std::string crypto_encrypt(const std::string& plaintext);

/* Decrypt ciphertext →  caesar_unshift( base64_decode( ciphertext ) ) */
std::string crypto_decrypt(const std::string& ciphertext);
