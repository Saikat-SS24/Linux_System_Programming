#!/bin/bash

grep "Failed password" /var/log/auth.log \
| sed -E 's/invalid user //' \
| awk '{user=$(NF-5); print "User:", user, "| Message:", $0}' \
> login_attempt.txt

