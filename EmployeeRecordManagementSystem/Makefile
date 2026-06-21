# ─────────────────────────────────────────────────────────────────────────────
#  Employee Record Management System — Makefile
#  Uses: POSIX Shared Memory, POSIX Semaphores, POSIX Threads
# ─────────────────────────────────────────────────────────────────────────────

CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -g -std=c11 -D_GNU_SOURCE -Wno-unused-result -Wno-stringop-truncation
LDFLAGS := -lpthread -lrt       # -lrt for shm_open/shm_unlink on older Linux

SERVER  := server
CLIENT  := client

SERVER_SRCS := server.c shm_helper.c
CLIENT_SRCS := client.c shm_helper.c

SERVER_OBJS := $(SERVER_SRCS:.c=.o)
CLIENT_OBJS := $(CLIENT_SRCS:.c=.o)

# ── default ───────────────────────────────────────────────────────────────────
.PHONY: all
all: $(SERVER) $(CLIENT)
	@echo ""
	@echo "  ✔  Build successful!"
	@echo ""
	@echo "  Terminal 1:  ./server"
	@echo "  Terminal 2:  ./client"
	@echo ""

# ── link ──────────────────────────────────────────────────────────────────────
$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "  [linked]  $@"

$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "  [linked]  $@"

# ── compile ───────────────────────────────────────────────────────────────────
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "  [compiled] $<"

# ── convenience ───────────────────────────────────────────────────────────────
.PHONY: run-server
run-server: $(SERVER)
	./$(SERVER)

.PHONY: run-client
run-client: $(CLIENT)
	./$(CLIENT)

# Remove stale POSIX shared memory left from a crashed run
.PHONY: clean-shm
clean-shm:
	@rm -f /dev/shm/emp_shm 2>/dev/null || true
	@echo "  Shared memory cleaned."

.PHONY: clean
clean: clean-shm
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER) $(CLIENT)
	@echo "  Build artifacts cleaned."

.PHONY: help
help:
	@echo ""
	@echo "  make               — Build server and client"
	@echo "  make run-server    — Start server (creates shared memory)"
	@echo "  make run-client    — Start client (attaches to shared memory)"
	@echo "  make clean-shm     — Remove leftover shared memory"
	@echo "  make clean         — Remove all compiled files + shared memory"
	@echo ""
