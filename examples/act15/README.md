<!--no-pdf-->
# Activity 15 Example

The program prints one deadlocked state. It reports each thread's held lock and its wait, then traces the cycle from A through L2, B, and L1 and back to A, then states the lock order that prevents it. The output is fixed. The program starts no threads.

`make check` compares those four lines against the checked-in expected file. It prints `1 of 1 outputs match` when they agree.

Run commands in this directory. On macOS, use the Ubuntu virtual machine from Bootcamp 1, Part 4. On Windows, use WSL2 Ubuntu. On Linux, use a terminal. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
