<!--no-pdf-->
# Deadlock Example

The program prints one deadlocked state. It reports each thread's held lock and its wait. It then traces the cycle from A through L2, B, and L1 and back to A. It ends with the lock order that prevents the cycle. The output is fixed. The program starts no threads.

## The Model

Thread A holds L1 and asks for L2. Thread B holds L2 and asks for L1. Each thread waits for a lock the other holds, so neither can release its own, and the wait never ends. The cycle runs A to L2 to B to L1 and back to A. If every thread takes L1 before L2, no cycle can form. The program prints that state, so its output stays fixed.

`make check` compares those four lines against the checked-in expected file. It prints `1 of 1 outputs match` when they agree.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
