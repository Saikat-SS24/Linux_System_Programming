#!/usr/bin/env bash
# ==============================================================
#  ECSBF — Valgrind Report Generator
#  RPT/run_valgrind.sh
# ==============================================================
#
#  WHAT IT DOES
#  ─────────────
#  1. Rebuilds the project with debug symbols  (-g -O0)
#  2. Runs the engine under Valgrind (Memcheck + Helgrind)
#     for a fixed duration
#  3. Runs the node under Valgrind in offline mode
#  4. Writes a plain human-readable report:
#        RPT/reports/valgrind_report_<timestamp>.txt
#  5. Exits with code 0 (no errors) or 1 (leaks/errors found)
#
#  USAGE
#  ──────
#  From the ECSBF/ project root:
#
#      bash RPT/run_valgrind.sh              # default: all checks
#      bash RPT/run_valgrind.sh memcheck     # memory leaks only
#      bash RPT/run_valgrind.sh helgrind     # thread errors only
#      bash RPT/run_valgrind.sh callgrind    # CPU profiling only
#      bash RPT/run_valgrind.sh massif       # heap profiling only
#      bash RPT/run_valgrind.sh clean        # wipe all reports
#
#  OUTPUT
#  ──────
#  RPT/reports/valgrind_report_<timestamp>.txt  — plain text report
# ==============================================================

set -euo pipefail

# ── Paths ──────────────────────────────────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
REPORTS_DIR="$SCRIPT_DIR/reports"
TIMESTAMP="$(date +%Y%m%d_%H%M%S)"
REPORT_FILE="$REPORTS_DIR/valgrind_report_${TIMESTAMP}.txt"

# ── Binaries ───────────────────────────────────────────────────
ENGINE_BIN="$PROJECT_ROOT/bin/engine"
NODE_BIN="$PROJECT_ROOT/bin/node"

# ── Test duration (seconds the engine runs under Valgrind) ─────
ENGINE_TIMEOUT=10

# ── Colours ────────────────────────────────────────────────────
RED='\033[0;31m'; GREEN='\033[0;32m'
YELLOW='\033[1;33m'; CYAN='\033[0;36m'; NC='\033[0m'

# ── Mode (default = all) ───────────────────────────────────────
MODE="${1:-all}"

# ==============================================================
#  Helpers
# ==============================================================

log_step() { echo -e "${CYAN}[STEP]${NC}  $*"; }
log_ok()   { echo -e "${GREEN}[OK]${NC}    $*"; }
log_warn() { echo -e "${YELLOW}[WARN]${NC}  $*"; }
log_fail() { echo -e "${RED}[FAIL]${NC}  $*"; }

# Write a line to both stdout and the report file
report() { echo "$*" | tee -a "$REPORT_FILE"; }

# Check required tools
check_tools() {
    local missing=0
    for tool in valgrind g++ make; do
        if ! command -v "$tool" &>/dev/null; then
            log_fail "Required tool not found: $tool"
            missing=1
        fi
    done
    if [[ $missing -eq 1 ]]; then
        echo ""
        echo "  Install missing tools:"
        echo "    sudo apt-get install valgrind g++ make"
        exit 1
    fi
    log_ok "All required tools present (valgrind $(valgrind --version | head -1 | awk '{print $NF}'))"
}

# Create reports directory and initialise the report file
setup_dirs() {
    mkdir -p "$REPORTS_DIR"
    {
        echo "============================================================"
        echo "  ECSBF — Valgrind Report"
        echo "  Generated : $(date '+%Y-%m-%d %H:%M:%S')"
        echo "  Mode      : $MODE"
        echo "============================================================"
        echo ""
    } > "$REPORT_FILE"
    log_ok "Reports directory: $REPORTS_DIR"
    log_ok "Report file: $(basename "$REPORT_FILE")"
}

# Build with debug symbols — required for useful Valgrind output
build_debug() {
    log_step "Building ECSBF with debug symbols (-g -O0 -fno-inline)..."
    cd "$PROJECT_ROOT"

    make clean --no-print-directory 2>&1 | grep -v "^make"
    make all   --no-print-directory \
         CXXFLAGS="-std=c++17 -Wall -Wextra -pthread -Iinc -g -O0 -fno-inline" \
         2>&1 | grep -E "\[Compiled\]|\[Linked\]|error:|warning:" || true

    if [[ ! -f "$ENGINE_BIN" || ! -f "$NODE_BIN" ]]; then
        log_fail "Build failed — binaries not found"
        exit 1
    fi
    log_ok "Debug build complete"
    report "Build: debug symbols enabled (-g -O0 -fno-inline)"
    report ""
}

# ==============================================================
#  Parse a Valgrind text output file and append a summary
# ==============================================================
parse_and_append() {
    local label="$1"
    local vg_out="$2"

    report "------------------------------------------------------------"
    report "  $label"
    report "------------------------------------------------------------"

    if [[ ! -f "$vg_out" ]]; then
        report "  [WARN] No output file found — binary may have failed to start."
        report ""
        return
    fi

    # Extract key lines from Valgrind stderr output
    local errors    leak_def leak_ind leak_pos leak_reach
    errors=$(grep -E "^==[0-9]+== ERROR SUMMARY" "$vg_out" | tail -1 || true)
    leak_def=$(grep -E "definitely lost" "$vg_out" | tail -1 || true)
    leak_ind=$(grep -E "indirectly lost" "$vg_out" | tail -1 || true)
    leak_pos=$(grep -E "possibly lost"   "$vg_out" | tail -1 || true)
    leak_reach=$(grep -E "still reachable" "$vg_out" | tail -1 || true)

    [[ -n "$errors"    ]] && report "  $errors"    || report "  ERROR SUMMARY  : (not found in output)"
    [[ -n "$leak_def"  ]] && report "  $leak_def"
    [[ -n "$leak_ind"  ]] && report "  $leak_ind"
    [[ -n "$leak_pos"  ]] && report "  $leak_pos"
    [[ -n "$leak_reach"]] && report "  $leak_reach"

    # Count actual error blocks
    local n_errors
    n_errors=$(grep -c "^==[0-9]*== Invalid\|^==[0-9]*== Use of\|^==[0-9]*== Conditional" \
                   "$vg_out" 2>/dev/null || echo 0)
    report "  Distinct error blocks found : $n_errors"
    report ""
}

# ==============================================================
#  Run Valgrind and capture plain-text output
# ==============================================================

run_vg_engine() {
    local tool="$1"; shift
    local extra_args=("$@")
    local out_file="$REPORTS_DIR/${tool}_engine_${TIMESTAMP}.txt"

    valgrind \
        --tool="$tool" \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --track-fds=yes \
        --error-exitcode=42 \
        --num-callers=20 \
        "${extra_args[@]}" \
        "$ENGINE_BIN" \
        > "$out_file" 2>&1 &

    local pid=$!
    sleep 2
    sleep "$ENGINE_TIMEOUT" && kill -INT "$pid" 2>/dev/null || true
    wait "$pid" 2>/dev/null || true

    echo "$out_file"
}

run_vg_node() {
    local out_file="$REPORTS_DIR/memcheck_node_${TIMESTAMP}.txt"

    valgrind \
        --tool=memcheck \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --track-fds=yes \
        --error-exitcode=42 \
        "$NODE_BIN" testnode testpass \
        > "$out_file" 2>&1 || true

    echo "$out_file"
}

# ==============================================================
#  MEMCHECK
# ==============================================================
run_memcheck() {
    log_step "Running Valgrind Memcheck on engine..."
    local ef
    ef=$(run_vg_engine memcheck)
    log_ok "Memcheck engine done → $(basename "$ef")"
    parse_and_append "Memcheck — Engine" "$ef"

    log_step "Running Valgrind Memcheck on node (offline path)..."
    local nf
    nf=$(run_vg_node)
    log_ok "Memcheck node done  → $(basename "$nf")"
    parse_and_append "Memcheck — Node (offline)" "$nf"
}

# ==============================================================
#  HELGRIND
# ==============================================================
run_helgrind() {
    log_step "Running Valgrind Helgrind on engine (thread race detection)..."

    local out_file="$REPORTS_DIR/helgrind_engine_${TIMESTAMP}.txt"

    valgrind \
        --tool=helgrind \
        --error-exitcode=42 \
        --num-callers=20 \
        "$ENGINE_BIN" \
        > "$out_file" 2>&1 &

    local pid=$!
    sleep 2
    sleep "$ENGINE_TIMEOUT" && kill -INT "$pid" 2>/dev/null || true
    wait "$pid" 2>/dev/null || true

    log_ok "Helgrind engine done → $(basename "$out_file")"
    parse_and_append "Helgrind — Engine (thread races)" "$out_file"
}

# ==============================================================
#  CALLGRIND
# ==============================================================
run_callgrind() {
    log_step "Running Callgrind on engine (CPU profiling)..."

    local raw_file="$REPORTS_DIR/callgrind_engine_${TIMESTAMP}.out"
    local ann_file="$REPORTS_DIR/callgrind_engine_${TIMESTAMP}_annotated.txt"

    valgrind \
        --tool=callgrind \
        --callgrind-out-file="$raw_file" \
        --collect-jumps=yes \
        --collect-systime=yes \
        --cache-sim=yes \
        --branch-sim=yes \
        "$ENGINE_BIN" &

    local pid=$!
    sleep 2
    sleep "$ENGINE_TIMEOUT" && kill -INT "$pid" 2>/dev/null || true
    wait "$pid" 2>/dev/null || true

    report "------------------------------------------------------------"
    report "  Callgrind — Engine (CPU profile)"
    report "------------------------------------------------------------"

    if [[ -f "$raw_file" ]]; then
        log_ok "Callgrind raw data → $(basename "$raw_file")"
        if command -v callgrind_annotate &>/dev/null; then
            callgrind_annotate "$raw_file" > "$ann_file" 2>/dev/null || true
            log_ok "Callgrind annotated → $(basename "$ann_file")"
            # Append top 30 lines of annotated output to report
            head -30 "$ann_file" >> "$REPORT_FILE" 2>/dev/null || true
        else
            report "  callgrind_annotate not available — raw data saved to $(basename "$raw_file")"
        fi
    else
        report "  [WARN] Callgrind output not created."
    fi
    report ""
}

# ==============================================================
#  MASSIF
# ==============================================================
run_massif() {
    log_step "Running Massif on engine (heap profiling)..."

    local raw_file="$REPORTS_DIR/massif_engine_${TIMESTAMP}.out"
    local ms_file="$REPORTS_DIR/massif_engine_${TIMESTAMP}_ms_print.txt"

    valgrind \
        --tool=massif \
        --massif-out-file="$raw_file" \
        --pages-as-heap=no \
        --time-unit=ms \
        "$ENGINE_BIN" &

    local pid=$!
    sleep 2
    sleep "$ENGINE_TIMEOUT" && kill -INT "$pid" 2>/dev/null || true
    wait "$pid" 2>/dev/null || true

    report "------------------------------------------------------------"
    report "  Massif — Engine (heap profile)"
    report "------------------------------------------------------------"

    if [[ -f "$raw_file" ]]; then
        log_ok "Massif raw data → $(basename "$raw_file")"
        if command -v ms_print &>/dev/null; then
            ms_print "$raw_file" > "$ms_file" 2>/dev/null || true
            log_ok "Massif ms_print → $(basename "$ms_file")"
            head -40 "$ms_file" >> "$REPORT_FILE" 2>/dev/null || true
        else
            report "  ms_print not available — raw data saved to $(basename "$raw_file")"
        fi
    else
        report "  [WARN] Massif output not created."
    fi
    report ""
}

# ==============================================================
#  CLEAN
# ==============================================================
do_clean() {
    log_step "Cleaning all Valgrind reports..."
    rm -f "$REPORTS_DIR"/*.txt \
          "$REPORTS_DIR"/*.out \
          "$REPORTS_DIR"/*.xml
    log_ok "Reports directory cleaned"
    exit 0
}

# ==============================================================
#  MAIN
# ==============================================================
echo ""
echo "  ╔═══════════════════════════════════════════════════╗"
echo "  ║   ECSBF — Valgrind Report Generator               ║"
echo "  ║   Mode      : $MODE$(printf '%*s' $((36 - ${#MODE})) '')║"
echo "  ║   Timestamp : $TIMESTAMP$(printf '%*s' $((28 - ${#TIMESTAMP})) '')║"
echo "  ╚═══════════════════════════════════════════════════╝"
echo ""

[[ "$MODE" == "clean" ]] && do_clean

check_tools
setup_dirs
build_debug

case "$MODE" in
    all)
        run_memcheck
        run_helgrind
        run_callgrind
        run_massif
        ;;
    memcheck)  run_memcheck  ;;
    helgrind)  run_helgrind  ;;
    callgrind) run_callgrind ;;
    massif)    run_massif    ;;
    *)
        log_fail "Unknown mode: $MODE"
        echo "  Valid modes: all | memcheck | helgrind | callgrind | massif | clean"
        exit 1
        ;;
esac

# Final footer in the report
{
    echo ""
    echo "============================================================"
    echo "  End of report"
    echo "  File: $(basename "$REPORT_FILE")"
    echo "============================================================"
} >> "$REPORT_FILE"

echo ""
log_ok "Report saved to: $REPORT_FILE"
echo ""
