<!--no-pdf-->
# Deadlock Example

The program prints one deadlocked state. It reports each thread's held lock and its wait. It then traces the cycle from A through L2, B, and L1 and back to A. It ends with the lock order that prevents the cycle. The output is fixed. The program starts no threads.

`make check` compares those four lines against the checked-in expected file. It prints `1 of 1 outputs match` when they agree.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
