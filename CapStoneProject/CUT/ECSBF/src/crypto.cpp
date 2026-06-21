/*
 * ============================================================
 *  ECSBF  —  Crypto Implementation  (Beginner-Friendly Version)
 *  Requirement-10 : encryption
 *  Requirement-11 : decryption
 * ============================================================
 *
 *  HOW ENCRYPTION WORKS (step by step):
 *  ─────────────────────────────────────
 *  Imagine you want to send a secret message "Hi".
 *
 *  STEP 1 — Caesar Cipher (shift each letter forward)
 *      'H' (ASCII 72)  +  13  =  'U' (ASCII 85)
 *      'i' (ASCII 105) +  13  =  'v' (ASCII 118)
 *      So "Hi" becomes "Uv" after the Caesar shift.
 *
 *  STEP 2 — Base-64 Encoding (make it safe to send over network)
 *      Base-64 takes any bytes and converts them into
 *      only these safe characters:  A-Z  a-z  0-9  +  /
 *      This is important because our network protocol uses "||"
 *      as a separator, so the message must not contain special chars.
 *      "Uv" → base64 → "VXY="   (something like that)
 *
 *  DECRYPTION is the exact reverse:
 *      STEP 1 — Base-64 Decode  (undo the encoding)
 *      STEP 2 — Caesar Backward (shift each letter back by 13)
 *
 * ============================================================
 */

#include "../inc/crypto.h"
#include "../inc/protocol.h"   /* gives us CRYPTO_SHIFT = 13 */
#include <string>
#include <stdexcept>

/* ─────────────────────────────────────────────────────────────
 *  BASE-64 ALPHABET
 *  ─────────────────────────────────────────────────────────────
 *  Base-64 uses exactly 64 characters to represent any data.
 *  Index 0 = 'A', Index 1 = 'B', ..., Index 63 = '/'
 * ───────────────────────────────────────────────────────────── */
static const std::string BASE64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/* ─────────────────────────────────────────────────────────────
 *  BASE-64 ENCODE
 *  ─────────────────────────────────────────────────────────────
 *  Base-64 works by reading 3 bytes at a time (3 × 8 = 24 bits)
 *  and splitting them into 4 groups of 6 bits each.
 *  Each 6-bit group (value 0–63) becomes one character in BASE64_CHARS.
 *
 *  Why 3 bytes → 4 chars?
 *      3 bytes = 24 bits
 *      24 bits ÷ 6 = 4 groups  →  4 characters
 *
 *  Example: bytes [77, 97, 110] → "TWFu"
 *
 *  If the input isn't a multiple of 3, we pad with '=' at the end.
 * ───────────────────────────────────────────────────────────── */
static std::string base64_encode(const std::string& input)
{
    std::string result;

    /* We will read the input 3 bytes at a time */
    int total_bytes = (int)input.size();
    int i = 0;   /* current position in input */

    while (i < total_bytes)
    {
        /* ── Read up to 3 bytes from the input ── */
        unsigned char byte1 = 0, byte2 = 0, byte3 = 0;
        int bytes_read = 0;

        byte1 = (unsigned char)input[i++];   bytes_read = 1;
        if (i < total_bytes) { byte2 = (unsigned char)input[i++]; bytes_read = 2; }
        if (i < total_bytes) { byte3 = (unsigned char)input[i++]; bytes_read = 3; }

        /* ── Split 3 bytes (24 bits) into 4 groups of 6 bits ── */
        /*
         *  byte1        byte2        byte3
         *  76543210  |  76543210  |  76543210
         *  ──────────────────────────────────
         *  group1: bits 23-18  =  top 6 bits of byte1
         *  group2: bits 17-12  =  bottom 2 bits of byte1 + top 4 bits of byte2
         *  group3: bits 11-6   =  bottom 4 bits of byte2 + top 2 bits of byte3
         *  group4: bits  5-0   =  bottom 6 bits of byte3
         */
        unsigned char g1 = (byte1 >> 2);                              /* 6 bits from byte1 */
        unsigned char g2 = ((byte1 & 0x03) << 4) | (byte2 >> 4);     /* 2 bits + 4 bits   */
        unsigned char g3 = ((byte2 & 0x0F) << 2) | (byte3 >> 6);     /* 4 bits + 2 bits   */
        unsigned char g4 = (byte3 & 0x3F);                            /* 6 bits from byte3 */

        /* ── Look up each 6-bit value in the Base-64 alphabet ── */
        result += BASE64_CHARS[g1];
        result += BASE64_CHARS[g2];

        /* Only add g3 and g4 if we actually had those bytes */
        if (bytes_read >= 2) result += BASE64_CHARS[g3]; else result += '=';
        if (bytes_read >= 3) result += BASE64_CHARS[g4]; else result += '=';
    }

    return result;
}


/* ─────────────────────────────────────────────────────────────
 *  BASE-64 DECODE
 *  ─────────────────────────────────────────────────────────────
 *  This is the reverse of base64_encode.
 *  We read 4 Base-64 characters at a time, look up their 6-bit
 *  values, then pack them back into 3 bytes.
 *
 *  '=' padding characters at the end mean fewer than 3 bytes
 *  were in the last group, so we stop early.
 * ───────────────────────────────────────────────────────────── */
static std::string base64_decode(const std::string& input)
{
    std::string result;

    int total_chars = (int)input.size();
    int i = 0;

    while (i < total_chars && input[i] != '=')
    {
        /* ── Read 4 Base-64 characters ── */
        unsigned char c1 = 0, c2 = 0, c3 = 0, c4 = 0;
        int chars_read = 0;

        /* For each character, find its index (0–63) in BASE64_CHARS */
        auto find_index = [&](char ch) -> unsigned char {
            size_t pos = BASE64_CHARS.find(ch);
            if (pos == std::string::npos)
                throw std::runtime_error("base64_decode: invalid character found");
            return (unsigned char)pos;
        };

        if (i < total_chars && input[i] != '=') { c1 = find_index(input[i++]); chars_read = 1; }
        if (i < total_chars && input[i] != '=') { c2 = find_index(input[i++]); chars_read = 2; }
        if (i < total_chars && input[i] != '=') { c3 = find_index(input[i++]); chars_read = 3; }
        if (i < total_chars && input[i] != '=') { c4 = find_index(input[i++]); chars_read = 4; }

        /* ── Reassemble 4 × 6 bits back into 3 bytes ── */
        /*
         *  c1 (6 bits) + c2 (6 bits) + c3 (6 bits) + c4 (6 bits) = 24 bits = 3 bytes
         *
         *  byte1 = all 6 bits of c1, plus top 2 bits of c2
         *  byte2 = bottom 4 bits of c2, plus top 4 bits of c3
         *  byte3 = bottom 2 bits of c3, plus all 6 bits of c4
         */
        unsigned char byte1 = (c1 << 2) | (c2 >> 4);
        unsigned char byte2 = ((c2 & 0x0F) << 4) | (c3 >> 2);
        unsigned char byte3 = ((c3 & 0x03) << 6) | c4;

        result += (char)byte1;
        if (chars_read >= 3) result += (char)byte2;
        if (chars_read >= 4) result += (char)byte3;
    }

    return result;
}


/* ─────────────────────────────────────────────────────────────
 *  CAESAR CIPHER — FORWARD (encrypt)
 *  ─────────────────────────────────────────────────────────────
 *  Shifts every byte in the string FORWARD by CRYPTO_SHIFT (13).
 *
 *  Think of it like a circular number line from 0 to 255.
 *  Adding 13 moves each byte forward by 13 positions.
 *  The % 256 wraps around if we go past 255.
 *
 *  Example with CRYPTO_SHIFT = 13:
 *      'A' (65)  →  65 + 13 = 78  →  'N'
 *      'z' (122) →  122 + 13 = 135  →  some non-printable byte (that's fine)
 * ───────────────────────────────────────────────────────────── */
static std::string caesar_forward(const std::string& text)
{
    std::string shifted = text;   /* make a copy to modify */

    for (int i = 0; i < (int)shifted.size(); i++)
    {
        /* Cast to unsigned so we work with values 0–255, not –128 to 127 */
        unsigned char original_byte = (unsigned char)shifted[i];

        /* Shift forward by CRYPTO_SHIFT, wrap around at 256 */
        unsigned char shifted_byte = (original_byte + CRYPTO_SHIFT) % 256;

        shifted[i] = (char)shifted_byte;
    }

    return shifted;
}


/* ─────────────────────────────────────────────────────────────
 *  CAESAR CIPHER — BACKWARD (decrypt)
 *  ─────────────────────────────────────────────────────────────
 *  Reverses the forward shift — subtracts CRYPTO_SHIFT from each byte.
 *
 *  The + 256 before % 256 prevents negative numbers.
 *  For example: 5 - 13 = -8, which is wrong.
 *               5 - 13 + 256 = 248, then 248 % 256 = 248. Correct!
 *
 *  Example with CRYPTO_SHIFT = 13:
 *      'N' (78)  →  78 - 13 = 65  →  'A'   (reversed correctly)
 * ───────────────────────────────────────────────────────────── */
static std::string caesar_backward(const std::string& text)
{
    std::string unshifted = text;

    for (int i = 0; i < (int)unshifted.size(); i++)
    {
        unsigned char shifted_byte = (unsigned char)unshifted[i];

        /* Subtract CRYPTO_SHIFT, add 256 first to avoid negative values */
        unsigned char original_byte = (shifted_byte - CRYPTO_SHIFT + 256) % 256;

        unshifted[i] = (char)original_byte;
    }

    return unshifted;
}


/* ─────────────────────────────────────────────────────────────
 *  PUBLIC API — crypto_encrypt()
 *  ─────────────────────────────────────────────────────────────
 *  Requirement-10
 *
 *  Takes a plain text string and returns an encrypted string.
 *  The encrypted string is safe to send over the network.
 *
 *  Process:
 *      plaintext  →  caesar_forward()  →  base64_encode()  →  ciphertext
 *
 *  Usage example:
 *      std::string secret = crypto_encrypt("mypassword");
 *      // secret is now something like "bnlwYXNzd29yZA=="
 * ───────────────────────────────────────────────────────────── */
std::string crypto_encrypt(const std::string& plaintext)
{
    /* Step 1: shift each byte forward by CRYPTO_SHIFT */
    std::string caesar_shifted = caesar_forward(plaintext);

    /* Step 2: encode to Base-64 to make it network-safe */
    std::string encoded = base64_encode(caesar_shifted);

    return encoded;
}


/* ─────────────────────────────────────────────────────────────
 *  PUBLIC API — crypto_decrypt()
 *  ─────────────────────────────────────────────────────────────
 *  Requirement-11
 *
 *  Takes an encrypted string (ciphertext) and returns the original.
 *
 *  Process (exact reverse of encrypt):
 *      ciphertext  →  base64_decode()  →  caesar_backward()  →  plaintext
 *
 *  Usage example:
 *      std::string plain = crypto_decrypt("bnlwYXNzd29yZA==");
 *      // plain is now "mypassword" again
 * ───────────────────────────────────────────────────────────── */
std::string crypto_decrypt(const std::string& ciphertext)
{
    /* Step 1: decode from Base-64 back to raw shifted bytes */
    std::string decoded = base64_decode(ciphertext);

    /* Step 2: shift each byte backward to get original text */
    std::string original = caesar_backward(decoded);

    return original;
}
