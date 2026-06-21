# ==============================================================
#  ECSBF  —  Makefile
# ==============================================================
#
#  FOLDER STRUCTURE
#  ─────────────────
#  inc/          header files       (.h)
#  src/          source files       (.cpp)
#  obj/          compiled objects   (.o)    ← auto-created
#  bin/          final executables          ← auto-created
#  logs/         log files                  ← auto-created
#  RPT/          Valgrind report system     ← see RPT/README.md
#  RPT/reports/  generated Valgrind output  ← auto-created by RPT scripts
#
#  COMMANDS
#  ─────────
#  make               →  build both  bin/engine  and  bin/node
#  make engine        →  build only  bin/engine
#  make node          →  build only  bin/node
#  make clean         →  delete obj/ and bin/ contents
#  make dirs          →  create all required folders
#  make valgrind      →  full Valgrind analysis  (all tools)
#  make vg-memcheck   →  memory leak analysis only
#  make vg-helgrind   →  thread / data-race analysis only
#  make vg-callgrind  →  CPU profiling only
#  make vg-massif     →  heap profiling only
#  make rpt-clean     →  wipe all reports in RPT/reports/
# ==============================================================

# ── Compiler settings ─────────────────────────────────────────
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pthread -Iinc

# ── Folders ───────────────────────────────────────────────────
BIN := bin
OBJ := obj
SRC := src
INC := inc
RPT := RPT

# ── Source files that are SHARED by both engine and node ──────
#    (everything except the two main_*.cpp files)
SHARED_SRCS := $(SRC)/logger.cpp   \
               $(SRC)/crypto.cpp   \
               $(SRC)/utils.cpp    \
               $(SRC)/registry.cpp \
               $(SRC)/session.cpp

# Convert shared .cpp paths → .o paths under obj/
#   e.g.  src/logger.cpp  →  obj/logger.o
SHARED_OBJS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SHARED_SRCS))

# ── engine also needs engine.cpp ──────────────────────────────
ENGINE_OBJS := $(SHARED_OBJS) $(OBJ)/engine.o $(OBJ)/main_engine.o

# ── node needs only shared + main_node.cpp ────────────────────
NODE_OBJS   := $(SHARED_OBJS) $(OBJ)/main_node.o

# ==============================================================
#  DEFAULT TARGET  —  build everything
# ==============================================================
all: dirs $(BIN)/engine $(BIN)/node
	@echo ""
	@echo "  Build complete!"
	@echo "  Run engine :  ./bin/engine"
	@echo "  Run node   :  ./bin/node <id> <password> [register]"
	@echo ""

# ==============================================================
#  LINK  bin/engine
# ==============================================================
$(BIN)/engine: $(ENGINE_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "  [Linked]  $@"

# ==============================================================
#  LINK  bin/node
# ==============================================================
$(BIN)/node: $(NODE_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "  [Linked]  $@"

# ==============================================================
#  COMPILE  any  src/*.cpp  →  obj/*.o
#
#  The rule  $(OBJ)/%.o : $(SRC)/%.cpp  means:
#    "to build obj/X.o, compile src/X.cpp"
#
#  $<  = the .cpp file (first prerequisite)
#  $@  = the .o  file (the target)
# ==============================================================
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "  [Compiled] $<  →  $@"

# ==============================================================
#  CREATE FOLDERS  (if they don't exist yet)
# ==============================================================
dirs:
	@mkdir -p $(BIN) $(OBJ) logs

# ==============================================================
#  INDIVIDUAL TARGETS  (convenience)
# ==============================================================
engine: dirs $(BIN)/engine

node: dirs $(BIN)/node

# ==============================================================
#  CLEAN
# ==============================================================
clean:
	rm -f $(OBJ)/*.o $(BIN)/engine $(BIN)/node
	@echo "  Cleaned obj/ and bin/"

# Tell make these are not real files
.PHONY: all engine node dirs clean

# ==============================================================
#  VALGRIND TARGETS
#  All targets rebuild in debug mode (-g -O0 -fno-inline)
#  then run RPT/run_valgrind.sh.
#  Reports are written to  RPT/reports/
# ==============================================================

# ── Full analysis (Memcheck + Helgrind + Callgrind + Massif) ──
valgrind:
	@echo ""
	@echo "  Running full Valgrind analysis (all tools)..."
	@echo "  Reports → RPT/reports/"
	@echo ""
	bash $(RPT)/run_valgrind.sh all

# ── Memory leak analysis only ─────────────────────────────────
vg-memcheck:
	bash $(RPT)/run_valgrind.sh memcheck

# ── Thread / data-race analysis only ─────────────────────────
vg-helgrind:
	bash $(RPT)/run_valgrind.sh helgrind

# ── CPU profiling only ────────────────────────────────────────
vg-callgrind:
	bash $(RPT)/run_valgrind.sh callgrind

# ── Heap profiling only ───────────────────────────────────────
vg-massif:
	bash $(RPT)/run_valgrind.sh massif

# ── Wipe all generated Valgrind reports ───────────────────────
rpt-clean:
	bash $(RPT)/run_valgrind.sh clean

.PHONY: valgrind vg-memcheck vg-helgrind vg-callgrind vg-massif rpt-clean
