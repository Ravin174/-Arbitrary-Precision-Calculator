#!/bin/bash

# Function to run a test case
# Usage: run_test <operand1> <operator> <operand2> <expected_output>
run_test() {
    local op1=$1
    local operator=$2
    local op2=$3
    local expected=$4

    echo -n "Testing: $op1 $operator $op2 ... "
    
    # Capture the output of the apc program
    # Note: Use quotes around operator to handle '*' correctly
    result=$(./a.out "$op1" "$operator" "$op2")

    if [ "$result" == "$expected" ]; then
        echo "PASS (Result: $result)"
    else
        echo "FAIL (Expected $expected, but got $result)"
    fi
}

echo "--- Starting APC Test Suite ---"

# --- Case 1: Addition ---
run_test "10" "+" "20" "30"
run_test "-10" "+" "-10" "-20"
run_test "-10" "+" "20" "10"
run_test "10" "+" "-20" "-10"

# --- Case 2: Subtraction ---
run_test "20" "-" "10" "10"
run_test "10" "-" "20" "-10"
run_test "-10" "-" "-20" "10"
run_test "-20" "-" "10" "-30"

# --- Case 3: Multiplication ---
run_test "10" "*" "10" "100"
run_test "-10" "*" "-10" "100"
run_test "-10" "*" "10" "-100"
run_test "0" "*" "500" "0"

# --- Case 4: Division ---
run_test "10" "/" "5" "2"
run_test "-10" "/" "-5" "2"
run_test "-10" "/" "5" "-2"
run_test "1" "/" "10" "0"

# --- Large Numbers ---
run_test "10000000000000000000" "+" "1" "10000000000000000001"

echo "--- Tests Completed ---"