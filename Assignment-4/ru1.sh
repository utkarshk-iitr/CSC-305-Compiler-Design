#!/bin/bash

# Build parser if missing
if [ ! -f "src/parser" ]; then
    echo "Parser not found. Building..."
    make parser
fi

# Build code generator if missing
if [ ! -f "src/codegen" ]; then
    echo "Code generator not found. Building..."
    make codegen
fi

# Ensure output folders exist
mkdir -p output/x86

echo "Processing test1..."

# 1. Run parser → TAC
./src/parser < test/test1.txt > output/test1_output.txt 2>&1

# 2. Run code generator → x86
if [ -f "output/test1_output.txt" ]; then
    ./src/codegen output/test1_output.txt output/x86/test1_x86.asm
else
    echo "Error: TAC file not generated for test1"
fi

echo "Done!"
echo "TAC: output/test1_output.txt"
echo "x86: output/x86/test1_x86.asm"
