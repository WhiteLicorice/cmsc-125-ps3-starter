<!--no-pdf-->
# Interleavings and Mutexes Example

The program starts two threads that increment a shared counter under one mutex. It checks the final value after both threads join. Every result is deterministic.

## The Model

Each thread repeats 10,000 increments. An increment reads the shared counter, adds one, and writes it back. Without a lock, two threads can read the same value before either writes. One increment is then lost. The mutex lets one thread finish the read, the add, and the write before the other enters. Both threads run 10,000 increments, so the count is always 20,000. The program checks that value and exits 0 when it matches.

The check compares the program's complete output against the checked-in expected file, including the one line the program prints for this example's fixed workload.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
