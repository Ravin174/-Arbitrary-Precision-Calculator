Overview:   The Arbitrary Precision Calculator is a command-line tool written in C that performs arithmetic operations on integers
of virtually unlimited size.By bypassing the constraints of standard 64-bit integer types (like long long int), this calculator can
handle numbers with hundreds or even thousands of digitsusing a custom Doubly Linked List implementation.

Key Features:
              Infinite Precision: Supports numbers limited only by the system's available RAM.
              Doubly Linked List Architecture: Each node stores a single digit, allowing for efficient bidirectional traversal (essential for "carry" and "borrow" operations).
              Full Signed Arithmetic: Correctly handles positive and negative integers through advanced sign-logic handling.

Mathematical Operations:

Addition (+): Manual carry propagation.
Subtraction (-): Manual borrow handling and magnitude comparison.
Multiplication (*): Repeated addition logic or digit-by-digit distribution.
Division (/): Successive subtraction/quotient calculation.

Memory Management: 
Robust cleanup routines to prevent memory leaks during complex calculations.

Technical Implementation:

Data Structure: Dlist (Doubly Linked List).
Input Handling: Parses command-line arguments and converts strings into linked list nodes.

Algorithm Logic:

Sign Extraction: Separates the sign from the magnitude before processing.
Comparison: Uses a custom list_compare function to determine the larger operand for subtraction and division.
Traversal: Digits are processed from the tail (least significant digit) to the head (most significant digit).

Usage
Compile the project using gcc and run it via the terminal:
