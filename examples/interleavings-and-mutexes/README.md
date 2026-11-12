<!--no-pdf-->
# Interleavings and Mutexes Example

The program starts two threads that increment a shared counter under one mutex. It checks the final value after both threads join. Every result is deterministic.

The check compares the program's complete output against the checked-in expected file, including the one line the program prints for this example's fixed workload.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
