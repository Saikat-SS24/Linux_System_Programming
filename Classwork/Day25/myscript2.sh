#!/usr/bin/env bash
# NAME="Saikat"
# EMPTY=""

# # ── Basic expansion ────────────────────────────────────────────────
# echo "$NAME"           # Saikat

# # ── Default values ─────────────────────────────────────────────────
# echo "${NAME:-Unknown}"       # Saikat (NAME is set)
# echo "${EMPTY:-Unknown}"      # Unknown (EMPTY is empty)
# echo "${UNDEFINED:-Unknown}"  # Unknown (not set)

# # Assign default AND use it:
# echo "${NAME:=DefaultName}"   # Saikat (NAME already set, no change)
# echo "${EMPTY:=NewValue}"     # NewValue (EMPTY was empty, now set!)
# echo "$EMPTY"                 # NewValue (it was actually assigned!)

NAME="Saikat"

var1='My Name is ${NAME}'
var2="My Name is ${NAME}" 
echo "${var1}"
echo "${var2}"


