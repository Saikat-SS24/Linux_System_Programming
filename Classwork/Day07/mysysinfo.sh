#!/bin/bash

# File name : sysinfo.sh
# purpose: display system information

echo "=================="
echo "System report"
echo "=================="

echo "user: $user"
echo "Uptime: $(uptime -p)"
echo "Disk usage report"
df -h / | tail -1
echo ""
echo "Memory Usage report"
echo ""
free -h | grep Mem
echo ""

