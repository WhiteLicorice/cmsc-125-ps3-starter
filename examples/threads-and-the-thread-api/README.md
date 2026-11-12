<!--no-pdf-->
# Threads and the Thread API Example

The program creates two worker threads. A mutex protects their shared update. Each worker reads its own input value. Every result is deterministic.

The check compares the program's complete output against the checked-in expected file, including its summary line and every result printed for the example's fixed workload.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
