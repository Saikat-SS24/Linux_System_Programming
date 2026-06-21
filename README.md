# C++ / Linux System Programming

This repository contains my coursework, projects, and reference materials for the
**C++ & Linux System Programming** training program. It is organized day-by-day
to mirror the course schedule, alongside reference materials and a capstone
project built at the end of the program.

## Repository Structure

```
.
├── Assignments/   # Daily take-home assignments (Day01 – Day43)
├── Classwork/     # In-class exercises, demos, and mini-projects
├── Materials/     # Reference PDFs, slide decks, and guides shared by instructors
├── CapStoneProject/   # Capstone project
```

### Assignments/
Daily problem sets covering C/C++ fundamentals through advanced Linux systems
programming. Each `DayNN/` folder holds that day's solutions; a few also include a
`README.md` with the assignment brief. Topics progress from arrays, strings, and
pointers, through recursion, linked lists, OOP, and into POSIX/sockets-level
systems programming (see `Day30` onward for TCP/UDP socket examples).

### Classwork/
In-class exercises and short demos written during live sessions, plus a few small
client-server mini-projects built to practice IPC concepts:

| Project | Concept demonstrated |
|---|---|
| `LibraryManagementSystem/` | Client-server architecture over sockets |
| `EmployeeRecordManagementSystem/` | Shared memory IPC |
| `RemoteDrop/`, `Test/` | Shell scripting / remote file handling |
| `LinuxHistoryAndPhilosophy/` | Notes on Linux/Unix history and philosophy |
| `ECSBF/` | Early prototype of the capstone broadcast framework |

Each mini-project includes its own `README.md` with build/run instructions
(typically `make`, then run the server before the client).

### Materials/
Instructor-provided reference material: PDFs and slide decks on Linux/Unix
internals, POSIX & System V IPC, kernel debugging, computer architecture, data
structures, software design principles/architecture, coding standards (C/C++),
shell scripting, Vim, and Git.

### Capstone Project — ECSBF
**ECSBF (Enterprise Concurrent Signal Broadcast Framework)** is a multi-threaded,
C++17 client-server broadcast system for Linux, built as the program's
capstone deliverable. A central **engine** (server) handles node registration,
authentication, and message broadcasting; multiple **node** clients connect,
authenticate, and exchange encrypted messages in real time.

The capstone folder follows a standard SDLC documentation structure:

```
24May26_SYS_CPPLinuxSysProg_CapStone_4026593-ECSBF/
├── CUT/      # Code under test — the ECSBF source tree, plus Unit/Integration test plans & reports
├── Design/   # Design document
├── MOM/      # Minutes of meeting
├── Plan/     # Schedule plan
├── PPT/      # Project presentation
├── RTM/      # Requirements Traceability Matrix
└── SRS/      # Software Requirements Specification
```

The actual source code lives under `CUT/ECSBF/`, which has its own detailed
`README.md` covering the folder layout, prerequisites, and build/run steps
(`make`, then run `bin/engine` followed by `bin/node`).

## Tech Stack

- **Languages:** C, C++ (C++17 for the capstone)
- **Platform:** Linux (POSIX APIs, sockets, threads, shared memory)
- **Build tooling:** `make` / `g++`
- **Debugging/QA:** Valgrind (see `ECSBF/RPT/`)

## Getting Started

Most sub-projects are self-contained and build independently:

```bash
cd <project-folder>
make
```

Then follow the instructions in that folder's `README.md` (where present) to run
the resulting binaries — typically starting a server/engine process first and a
client/node process second, each in its own terminal.

## Notes

- `Assignments/` and `Classwork/` are organized chronologically by training day,
  not by topic — see each day's files/README for what was covered.
- `Materials/` is reference-only and not required to build any project.
