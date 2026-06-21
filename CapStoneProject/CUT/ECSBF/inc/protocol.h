#pragma once
/*
 * ============================================================
 *  ECSBF  —  Protocol Constants
 *  Shared by engine AND node.  Never put logic here, only
 *  constants that both sides must agree on.
 * ============================================================
 *
 *  FRAME FORMAT  (every message is one text line ending with \n)
 *  ─────────────────────────────────────────────────────────────
 *  Fields are separated by  "||"
 *
 *  Examples
 *  ────────
 *  Handshake      :  ECSBF_HELLO
 *  Engine reply   :  ECSBF_READY
 *  Register node  :  REGISTER||<enc_node_id>||<enc_password>
 *  Auth node      :  AUTH||<enc_node_id>||<enc_password>
 *  Send signal    :  BROADCAST||<enc_payload>
 *  Engine fwd     :  BROADCAST||<sender_id>||<enc_payload>
 *  Keep-alive     :  HEARTBEAT
 *  Leave cleanly  :  DISCONNECT
 *  OK reply       :  ACK||<message>
 *  Error reply    :  ERROR||<reason>
 */

/* ── Network ─────────────────────────────────────────────── */
#define DEFAULT_HOST   "127.0.0.1"
#define DEFAULT_PORT    9090
#define BUFFER_SIZE     4096

/* ── Handshake tokens  (Req-1) ───────────────────────────── */
#define HANDSHAKE_HELLO  "ECSBF_HELLO"
#define HANDSHAKE_READY  "ECSBF_READY"

/* ── Message-type tokens ─────────────────────────────────── */
#define MSG_REGISTER    "REGISTER"    /* Req-2  new node */
#define MSG_AUTH        "AUTH"        /* Req-3  existing node */
#define MSG_BROADCAST   "BROADCAST"   /* Req-6  send / receive signal */
#define MSG_HEARTBEAT   "HEARTBEAT"   /* Req-4  keep session alive */
#define MSG_DISCONNECT  "DISCONNECT"  /* Req-8  clean leave */
#define MSG_ACK         "ACK"         /* generic OK */
#define MSG_ERROR       "ERROR"       /* generic error */

/* ── Frame field separator ───────────────────────────────── */
#define FRAME_SEP  "||"

/* ── Crypto shift  (Req-10 / Req-11) ────────────────────── */
#define CRYPTO_SHIFT  13
