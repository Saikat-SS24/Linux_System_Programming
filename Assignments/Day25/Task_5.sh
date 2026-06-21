#!/bin/bash

echo "Creating test file: data.txt"
cat << EOF > data.txt
Zebra
Apple
Banana
Apple
Cherry
Banana
EOF

SEARCH_TERM="Apple"

check_file(){
    local target=$1
    echo "Processing $target.."

    if [ -f "$target" ]; then
        RESULT=$(grep "$SEARCH_TERM" "$target" | sort)

        if [ -z "$RESULT" ]; then
            echo "Result: No matches found for '$SEARCH_TERM'."
        else
            echo "Result (Sorted):"
            echo "$RESULT"
        fi
    else
        echo "Error: $target not found."
    fi
}

echo "======Starting Loop======"
for item in "data.txt" "noneexistent.txt; do
    check_file "$item"
    echo "================"
done