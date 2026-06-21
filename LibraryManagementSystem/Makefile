# ─────────────────────────────────────────────────────────────────────────────
#  Library Management System — Makefile
# ─────────────────────────────────────────────────────────────────────────────

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDFLAGS  := -lpthread

# Output binaries
SERVER   := server
CLIENT   := client

# Source files
SERVER_SRCS := server.cpp book_database.cpp
CLIENT_SRCS := client.cpp

# Object files
SERVER_OBJS := $(SERVER_SRCS:.cpp=.o)
CLIENT_OBJS := $(CLIENT_SRCS:.cpp=.o)

# ── default: build everything ─────────────────────────────────────────────────
.PHONY: all
all: $(SERVER) $(CLIENT)
	@echo ""
	@echo "  ✔  Build complete!"
	@echo "     Run ./server in one terminal"
	@echo "     Run ./client in another terminal"
	@echo ""

# ── link server ───────────────────────────────────────────────────────────────
$(SERVER): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "  [linked] $@"

# ── link client ───────────────────────────────────────────────────────────────
$(CLIENT): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "  [linked] $@"

# ── compile .cpp → .o ─────────────────────────────────────────────────────────
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "  [compiled] $<"

# ── convenience targets ───────────────────────────────────────────────────────
.PHONY: run-server
run-server: $(SERVER)
	./$(SERVER)

.PHONY: run-client
run-client: $(CLIENT)
	./$(CLIENT)

.PHONY: clean
clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER) $(CLIENT)
	@echo "  Cleaned build artifacts."

.PHONY: help
help:
	@echo ""
	@echo "Usage:"
	@echo "  make            — Build both server and client"
	@echo "  make run-server — Start the server"
	@echo "  make run-client — Start the client (server must be running)"
	@echo "  make clean      — Remove all compiled files"
	@echo ""
