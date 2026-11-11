<!--no-pdf-->
# Activity 12 Example

The program starts two threads that increment a shared counter under one mutex. It checks the final value after both threads join. Every result is deterministic.

The check compares the program's complete output against the checked-in expected file, including the one line the program prints for this activity's fixed workload.

Run commands in this directory. On macOS, use the Ubuntu virtual machine from Bootcamp 1, Part 4. On Windows, use WSL2 Ubuntu. On Linux, use a terminal. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
