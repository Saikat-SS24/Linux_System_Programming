#!/bin/bash

grep "Failed Password" /var/log/auth.log \
| sed -E 's/invalid user //' \
| awk '{user=$(NF-5); print "User:", user, "| Message:", $0}' \
> Login_Attempts.txt
