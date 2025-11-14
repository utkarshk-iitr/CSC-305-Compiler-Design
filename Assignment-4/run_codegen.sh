#!/bin/bash

# Script to run parser and code generator on all test files

if [ ! -f "src/parser" ]; then
    echo "Parser not found. Building..."
    make parser
fi

if [ ! -f "src/codegen" ]; then
    echo "Code generator not found. Building..."
    make codegen
fi

# Create x86 output directory if it doesn't exist
mkdir -p output/x86

# Process all test files
for testfile in test/*.txt; do
    filename=$(basename "$testfile" .txt)
    echo "Processing $filename..."
    
    # Run parser to generate TAC
    ./src/parser < "$testfile" > "output/${filename}_output.txt" 2>&1
    
    # Run code generator to convert TAC to x86
    if [ -f "output/output${filename#test}.txt" ]; then
        ./src/codegen "output/output${filename#test}.txt" "output/x86/${filename}_x86.asm"
    fi
done

echo "All test files processed!"
echo "Three-address code in: output/"
echo "x86 assembly code in: output/x86/"
