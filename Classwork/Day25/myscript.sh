#!/usr/bin/env bash
# system_info.sh — Display comprehensive system information
set -euo pipefail

# ── Color codes for pretty output ──────────────────────────────────
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
BOLD='\033[1m'
RESET='\033[0m'

# ── Helper function for section headers ────────────────────────────
print_header() {
    echo -e "\n${BLUE}${BOLD}═══ $1 ═══${RESET}"
}

print_info() {
    echo -e "  ${GREEN} ${RESET} $1: ${YELLOW}$2${RESET}"
}

# ── Main script ────────────────────────────────────────────────────
echo -e "${BOLD}╔══════════════════════════════════╗${RESET}"
echo -e "${BOLD}║     SYSTEM INFORMATION REPORT    ║${RESET}"
echo -e "${BOLD}╚══════════════════════════════════╝${RESET}"

print_header "Operating System"
print_info "Distribution" "$(grep PRETTY_NAME /etc/os-release | cut -d= -f2 | tr -d '\"')"
print_info "Kernel" "$(uname -r)"
print_info "Architecture" "$(uname -m)"
print_info "Hostname" "$(hostname)"


print_header "Hardware"
print_info "CPU" "$(grep 'model name' /proc/cpuinfo | head -1 | cut -d: -f2 | xargs)"
print_info "CPU Cores" "$(nproc)"
print_info "Total RAM" "$(free -h | awk '/^Mem:/{print $2}')"
print_info "Free RAM" "$(free -h | awk '/^Mem:/{print $4}')"

print_header "Storage"
df -h | grep -E '^/dev' | while read -r fs size used avail pct mnt; do
    print_info "Mount: $mnt" "$used / $size ($pct used)"
done

print_header "Network"
ip -4 addr show | grep 'inet ' | while read -r line; do
    ip_addr=$(echo "$line" | awk '{print $2}')
    iface=$(echo "$line" | awk '{print $NF}')
    print_info "Interface: $iface" "$ip_addr"
done

print_header "System Load"
print_info "Uptime" "$(uptime -p)"
print_info "Load Average" "$(cat /proc/loadavg | awk '{print $1, $2, $3}')"
print_info "Running Processes" "$(ps aux | wc -l)"

echo ""
echo -e "${GREEN}Report generated: $(date)${RESET}"