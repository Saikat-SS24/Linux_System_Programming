#!/bin/bash

count_lines(){
    local file=$1
    if [[ -f "$file" ]]; then
        line_count=$(wc -l < "$file")
        echo "File '$file' has $line_count lines."
    else
        echo "Error: '$file' not found."
    fi
}

files=("file1.txt" "file2.txt" "file3.txt")

for f in "${file[@]}"; do
    count_lines "$f"
done