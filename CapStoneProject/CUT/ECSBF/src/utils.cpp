/*
 * ============================================================
 *  ECSBF  —  Utility Functions  (Very Basic / Beginner Version)
 * ============================================================
 *
 *  This file has 4 helper functions used all across the project:
 *
 *  1. sha256()     — Turns a password into a scrambled string.
 *                    We store the scrambled version, not the
 *                    real password, so it stays secret.
 *
 *  2. split()      — Breaks a string into pieces at a separator.
 *                    Example: "REGISTER||alice||pass"
 *                    → { "REGISTER", "alice", "pass" }
 *
 *  3. send_line()  — Sends a text message over a network socket.
 *
 *  4. recv_line()  — Receives a text message from a network socket.
 *
 * ============================================================
 */

#include "../inc/utils.h"
#include <sstream>      /* ostringstream — used to build strings */
#include <iomanip>      /* setw, setfill — used for formatting numbers */
#include <sys/socket.h> /* send(), recv() — Linux network functions */


/* ============================================================
 *  sha256() — HASH A PASSWORD INTO A SCRAMBLED STRING
 * ============================================================
 *
 *  WHAT IS A HASH?
 *  ───────────────
 *  A hash takes a word like "hello" and turns it into a long
 *  scrambled string like "a94a8fe5cc...". This is called a
 *  "fingerprint" of the word.
 *
 *  Key rules of a hash:
 *    - Same input  → always same output.
 *    - You CANNOT go backwards from the output to get the input.
 *    - "hello" and "Hello" produce completely different outputs.
 *
 *  WHY WE USE IT:
 *    We never save the real password in our registry.
 *    We save hash("password") instead.
 *    When a user logs in, we hash what they type and compare.
 *    So even if someone steals our registry file, they cannot
 *    read the real passwords.
 *
 *  NOTE: This is a simplified hash (djb2-style) for learning.
 *  Real SHA-256 is more complex, but this works the same way
 *  conceptually and is much easier to understand as a fresher.
 *
 * ============================================================ */
std::string sha256(const std::string& password)
{
    /*
     *  We use a simple technique called djb2 hashing.
     *
     *  Start with a big starting number (called the "seed").
     *  Then for every character in the password:
     *      new_hash = old_hash * 33 + ascii_value_of_character
     *
     *  Why multiply by 33? It's a small prime number that
     *  spreads the bits around nicely. Tried and tested.
     *
     *  We do this in multiple "passes" with different seeds
     *  to make the final result longer (more like a real hash).
     */

    /* These are our starting seed numbers for each pass.
     * They are just large odd numbers — nothing special about them.
     * Using different seeds gives us different scrambled results
     * that we can join together into one long string. */
    unsigned long long seeds[8] = {
        5381ULL,
        52711ULL,
        100003ULL,
        999983ULL,
        1299709ULL,
        15485863ULL,
        179424673ULL,
        999999937ULL
    };

    /* We will run 8 separate passes, each producing one number.
     * Then we combine all 8 numbers into one hex string. */
    std::ostringstream result;

    for (int pass = 0; pass < 8; pass++)
    {
        unsigned long long hash_value = seeds[pass];

        /* Go through every character in the password */
        for (int i = 0; i < (int)password.size(); i++)
        {
            /* Get the ASCII number of this character.
             * Example: 'A' = 65, 'a' = 97, '0' = 48 */
            unsigned char letter = (unsigned char)password[i];

            /* Mix the character into our running hash value.
             * hash * 33 + letter  is the djb2 formula.
             * The result wraps around automatically because
             * unsigned long long has a maximum value. */
            hash_value = hash_value * 33 + letter;
        }

        /* Also mix in the pass number so each pass gives
         * a different result even for the same password */
        hash_value = hash_value * 33 + (unsigned long long)pass;

        /* Convert hash_value to an 8-character hex string.
         * std::hex    → print as hexadecimal (base 16)
         * setw(8)     → always use 8 characters wide
         * setfill('0') → pad with zeros if shorter than 8 chars
         * Example: 255 → "000000ff" */
        result << std::hex << std::setw(8) << std::setfill('0')
               << (unsigned int)(hash_value & 0xFFFFFFFF);
        /* We take only the bottom 32 bits with & 0xFFFFFFFF
         * so each chunk is exactly 8 hex digits */
    }

    /* 8 passes × 8 hex chars = 64 character string total
     * This looks just like a real SHA-256 output in length */
    return result.str();
}


/* ============================================================
 *  split() — BREAK A STRING INTO PIECES
 * ============================================================
 *
 *  Takes a string and a separator, returns a list of pieces.
 *
 *  Example:
 *      split("REGISTER||alice||pass", "||")
 *      → returns a vector: { "REGISTER", "alice", "pass" }
 *
 *  How it works step by step:
 *      text     = "REGISTER||alice||pass"
 *      separator = "||"
 *
 *      Loop 1: find "||" at position 8
 *              cut out "REGISTER"  (position 0 to 8)
 *              move start to position 10  (after "||")
 *
 *      Loop 2: find "||" at position 15
 *              cut out "alice"  (position 10 to 15)
 *              move start to position 17
 *
 *      No more "||" found.
 *      Add the last piece "pass"  (position 17 to end)
 *
 * ============================================================ */
std::vector<std::string> split(const std::string& text, const std::string& separator)
{
    std::vector<std::string> pieces;  /* this will hold all the parts */

    int start = 0;  /* where we start searching from */

    while (true)
    {
        /* Look for the separator starting from 'start' */
        int found_at = (int)text.find(separator, start);

        /* If not found, std::string::npos is returned */
        if (found_at == (int)std::string::npos)
            break;  /* no more separators — exit loop */

        /* Cut out the piece from 'start' up to where separator begins */
        std::string piece = text.substr(start, found_at - start);
        pieces.push_back(piece);

        /* Move start to just after the separator */
        start = found_at + (int)separator.size();
    }

    /* Add the last remaining piece (after the final separator) */
    pieces.push_back(text.substr(start));

    return pieces;
}


/* ============================================================
 *  send_line() — SEND A MESSAGE OVER THE NETWORK
 * ============================================================
 *
 *  Takes a socket (a network connection) and a message string.
 *  Adds '\n' at the end (so the receiver knows the message ended).
 *  Sends it all byte by byte until done.
 *
 *  Why the while loop?
 *  Sometimes the network only sends PART of your message at once.
 *  So we keep track of how many bytes were sent, and loop until
 *  every single byte has been sent.
 *
 *  Returns true if everything was sent OK, false if there was an error.
 *
 *  Example:
 *      send_line(fd, "AUTH||alice||secret")
 *      actually sends → "AUTH||alice||secret\n"
 *
 * ============================================================ */
bool send_line(int socket_fd, const std::string& message)
{
    /* Add newline at the end — this is how the receiver knows
     * where the message ends */
    std::string full_message = message + "\n";

    int total_bytes   = (int)full_message.size();  /* total bytes to send */
    int bytes_sent    = 0;                          /* how many we have sent so far */

    /* Keep looping until every byte has been sent */
    while (bytes_sent < total_bytes)
    {
        /* How many bytes are still left to send? */
        int bytes_left = total_bytes - bytes_sent;

        /* Try to send the remaining bytes.
         * send() returns how many bytes it actually managed to send.
         * MSG_NOSIGNAL = don't crash if the other side disconnects */
        int sent_now = (int)send(
            socket_fd,
            full_message.c_str() + bytes_sent,  /* start where we left off */
            (size_t)bytes_left,
            MSG_NOSIGNAL
        );

        /* If sent_now is 0 or negative, something went wrong */
        if (sent_now <= 0)
            return false;  /* connection failed */

        /* Add to our count of bytes sent */
        bytes_sent += sent_now;
    }

    return true;  /* all bytes sent successfully */
}


/* ============================================================
 *  recv_line() — RECEIVE A MESSAGE FROM THE NETWORK
 * ============================================================
 *
 *  Reads characters one by one from the socket.
 *  Stops when it sees '\n' (which marks end of the message).
 *  Returns the message without the '\n'.
 *
 *  Why one character at a time?
 *  We don't know in advance how long the message will be.
 *  Reading one character at a time lets us stop exactly
 *  when we hit the '\n'.
 *
 *  Returns the received line, or "" (empty string) if the
 *  connection was closed or something went wrong.
 *
 *  Example:
 *      If the other side called send_line(fd, "ACK||welcome")
 *      then recv_line() returns "ACK||welcome"
 *
 * ============================================================ */
std::string recv_line(int socket_fd)
{
    std::string line;  /* we'll build the message here, character by character */
    char one_char;     /* holds one character read from the socket */

    while (true)
    {
        /* Read exactly 1 byte from the socket */
        int bytes_read = (int)recv(socket_fd, &one_char, 1, 0);

        /* If 0 or negative, the connection was closed or had an error */
        if (bytes_read <= 0)
            return "";  /* return empty string to signal the problem */

        /* If we got the newline, the message is complete — stop */
        if (one_char == '\n')
            break;

        /* Otherwise add this character to our growing message */
        line += one_char;
    }

    return line;  /* the full message, without the '\n' at the end */
}
