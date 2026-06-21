# ECSBF — Enterprise Concurrent Signal Broadcast Framework
### C++17 | Linux | Multi-threaded Client-Server

---

## What is ECSBF?

ECSBF is a multi-threaded client-server broadcast system written in C++17.
A central **engine** (server) manages node registration, authentication, and
message broadcasting. Multiple **nodes** (clients) connect, register or log in,
and exchange encrypted messages in real time.

---

## Folder Structure

```
ECSBF/
├── Makefile
├── inc/                  ← header files
│   ├── protocol.h        frame format and protocol constants
│   ├── engine.h          central engine class
│   ├── registry.h        node identity registry
│   ├── session.h         active session manager
│   ├── crypto.h          encrypt / decrypt
│   ├── logger.h          multi-level logger
│   └── utils.h           SHA-256, split, send_line, recv_line
├── src/                  ← source files
│   ├── main_engine.cpp   engine entry point
│   ├── main_node.cpp     node entry point
│   ├── engine.cpp
│   ├── registry.cpp
│   ├── session.cpp
│   ├── crypto.cpp
│   ├── logger.cpp
│   └── utils.cpp
├── obj/                  ← compiled .o files  (auto-created)
├── bin/                  ← executables        (auto-created)
│   ├── engine
│   └── node
├── logs/                 ← log files          (auto-created)
└── RPT/                  ← Valgrind report system
    ├── run_valgrind.sh
    └── reports/
```

---

## Prerequisites

Make sure you have the following installed before building:

```bash
# Check g++
g++ --version

# Check make
make --version

# Install if missing
sudo apt update && sudo apt install g++ build-essential
```

---

## Build Instructions

### Step 1 — Go into the project folder
```bash
cd ECSBF
```

### Step 2 — Build both engine and node
```bash
make
```

This compiles all `.cpp` files into `obj/` and links:
- `bin/engine`  — the server
- `bin/node`    — the client

### Step 3 — Build individually (optional)
```bash
make engine      # build only the engine
make node        # build only the node
```

---

## Clean and Rebuild

Use this whenever you modify source files and want a fresh build.

### Clean
```bash
make clean
```
Removes all compiled `.o` files from `obj/` and deletes `bin/engine` and `bin/node`.

### Rebuild from scratch
```bash
make clean && make
```

This is the recommended way to recompile after any code change.

---

## How to Run

You need **at least 2 terminal windows** open — one for the engine, one or more for nodes.
Always start the engine first.

---

### Terminal 1 — Start the Engine
```bash
./bin/engine
```

Expected output:
```
  ╔══════════════════════════════════════════╗
  ║    ECSBF Engine  —  Online               ║
  ║    Ready  (Ctrl+C to stop)               ║
  ╚══════════════════════════════════════════╝
```

The engine is now running and waiting for nodes to connect.

---

### Terminal 2 — Start a Node
```bash
./bin/node
```

You will see:
```
  ╔══════════════════════════════════════════╗
  ║         ECSBF  —  Node Client            ║
  ╚══════════════════════════════════════════╝

  [1]  Register  (new account)
  [2]  Login     (existing account)
  [0]  Exit

  Select an option:
```

---

## Features and How to Check Them

---

### Feature 1 — Register a New Node

Run `./bin/node` and select `[1] Register`.

```
  Select an option: 1

  Node ID  : alice
  Password : mypassword
```

Expected output:
```
  [OK]  Registered:alice
  Welcome alice

  Type a message + Enter to send.  Type  quit  to exit.
  >
```

On the engine terminal you will see:
```
  [+] 'alice' connected  (active: 1)
```

---

### Feature 2 — Login with an Existing Account

Run `./bin/node` in another terminal and select `[2] Login`.

```
  Select an option: 2

  Node ID  : alice
  Password : mypassword
```

Expected output:
```
  [OK]  Authenticated:alice
  Welcome alice
  >
```

---

### Feature 3 — Register a Second Node

Open a third terminal and run `./bin/node`, select `[1] Register`:

```
  Node ID  : bob
  Password : bobsecret
```

Engine will show:
```
  [+] 'bob' connected  (active: 2)
```

---

### Feature 4 — Broadcast a Message

In alice's terminal type a message and press Enter:
```
> Hello from alice!
```

Bob's terminal will receive:
```
  ╔══ Message from 'alice' ══
  ║  Hello from alice!
  ╚════════════════════════════
```

The sender's node ID is always shown alongside the message.

---

### Feature 5 — Encrypted Communication

All credentials and messages are encrypted before being sent over the network.
The encryption uses two steps:

```
ENCRYPT:
  "hello"
    → Caesar shift +13  →  "uryyb"
    → Base-64 encode    →  "dXJ5eWI="

DECRYPT:
  "dXJ5eWI="
    → Base-64 decode    →  "uryyb"
    → Caesar shift -13  →  "hello"
```

Passwords are also hashed using SHA-256 before being stored, so plain
passwords are never saved anywhere.

---

### Feature 6 — Log Files

All events are written to log files in `logs/` with four levels:
DEBUG, INFO, WARNING, and FATAL.

```bash
# Watch the engine log live
tail -f logs/engine.log

# Watch a node log live
tail -f logs/node_alice.log
```

Sample log output:
```
2026-05-23 08:33:01 [INFO   ] Node 'alice' starting
2026-05-23 08:33:01 [INFO   ] Node registered: 'alice'
2026-05-23 08:33:01 [INFO   ] 'alice' broadcast: Hello from alice!
```

---

### Feature 7 — Clean Disconnect

In any node terminal type:
```
> quit
```

The node disconnects cleanly. The engine shows:
```
  [-] 'alice' disconnected  (active: 1)
```

---

### Feature 8 — Duplicate Node ID

Try registering a node with an ID that already exists:
```
  Node ID  : alice
  Password : anypassword
  Select an option: 1  (Register)
```

Expected response:
```
  [!] Node ID 'alice' already exists
```

---

### Feature 9 — Wrong Password

Try logging in with the correct ID but wrong password:
```
  Select an option: 2  (Login)
  Node ID  : alice
  Password : wrongpassword
```

Expected response:
```
  [!] Login failed for 'alice'
```

---

## Valgrind Memory Analysis

### Run full analysis
```bash
make valgrind
```

### Run specific checks
```bash
make vg-memcheck     # memory leaks only
make vg-helgrind     # thread race conditions only
make vg-callgrind    # CPU profiling only
make vg-massif       # heap profiling only
```

### Clean Valgrind reports
```bash
make rpt-clean
```

Reports are saved as plain `.txt` files in `RPT/reports/`.

---

## Quick Reference

| Command | Description |
|---|---|
| `make` | Build engine and node |
| `make clean` | Remove all compiled files |
| `make clean && make` | Full clean rebuild |
| `make engine` | Build engine only |
| `make node` | Build node only |
| `./bin/engine` | Start the server |
| `./bin/node` | Start a client node |
| `tail -f logs/engine.log` | Watch engine logs live |
| `make valgrind` | Full Valgrind analysis |
| `make rpt-clean` | Clear Valgrind reports |

---

## Important Notes

- Always start `./bin/engine` before `./bin/node`
- Register once per node ID — use Login for all subsequent sessions
- Multiple nodes can be connected at the same time in separate terminals
- All log files are appended across sessions — delete them manually if needed
- The engine runs until you press `Ctrl+C`
