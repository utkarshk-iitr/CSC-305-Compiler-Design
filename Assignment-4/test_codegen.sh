#!/bin/bash

# Test script for code generator
# This script compiles the code generator and tests it on sample TAC files

echo "======================================"
echo "Code Generator Test Script"
echo "======================================"
echo ""

# Check if we're in the right directory
if [ ! -d "src" ] || [ ! -d "test" ]; then
    echo "Error: Please run this script from the Assignment-4 directory"
    exit 1
fi

# Build the code generator
echo "[1/4] Building code generator..."
make codegen
if [ $? -ne 0 ]; then
    echo "Error: Failed to build code generator"
    exit 1
fi
echo "✓ Code generator built successfully"
echo ""

# Create output directory for x86 code
mkdir -p output/x86

# Test on the first output file
echo "[2/4] Testing code generator on output1.txt..."
if [ ! -f "output/output1.txt" ]; then
    echo "Warning: output/output1.txt not found. Run the parser first."
    echo "Attempting to generate TAC..."
    if [ -f "src/parser" ]; then
        ./src/parser < test/test1.txt > output/output1.txt 2>&1
    else
        echo "Error: Parser not found. Please run 'make parser' first."
        exit 1
    fi
fi

./src/codegen output/output1.txt output/x86/test1.asm
if [ $? -eq 0 ]; then
    echo "✓ Successfully generated x86 assembly"
    echo ""
else
    echo "✗ Failed to generate x86 assembly"
    exit 1
fi

# Display the generated assembly (first 50 lines)
echo "[3/4] Preview of generated x86 assembly:"
echo "----------------------------------------"
head -n 50 output/x86/test1.asm
echo "----------------------------------------"
echo "(Showing first 50 lines. See output/x86/test1.asm for full output)"
echo ""

# Try to assemble with NASM (if available)
echo "[4/4] Testing assembly with NASM..."
if command -v nasm &> /dev/null; then
    nasm -f elf32 output/x86/test1.asm -o output/x86/test1.o 2>&1
    if [ $? -eq 0 ]; then
        echo "✓ Successfully assembled with NASM"
        
        # Try to link with GCC (if available)
        if command -v gcc &> /dev/null; then
            gcc -m32 output/x86/test1.o -o output/x86/test1 2>&1
            if [ $? -eq 0 ]; then
                echo "✓ Successfully linked executable"
                echo ""
                echo "You can run the program with: ./output/x86/test1"
            else
                echo "Note: Linking may require 32-bit libraries (lib32gcc, libc6-i386)"
            fi
        else
            echo "Note: GCC not found, skipping linking step"
        fi
    else
        echo "Note: NASM assembly failed. This might be due to external function dependencies."
    fi
else
    echo "Note: NASM not found. Install with: sudo apt-get install nasm"
fi

echo ""
echo "======================================"
echo "Test Complete!"
echo "======================================"
echo ""
echo "Generated files:"
echo "  - x86 assembly: output/x86/test1.asm"
echo ""
echo "To process all test files, run: ./run_codegen.sh"
