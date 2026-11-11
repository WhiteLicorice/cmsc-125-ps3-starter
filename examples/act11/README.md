<!--no-pdf-->
# Activity 11 Example

The program creates two worker threads. A mutex protects their shared update. Each worker reads its own input value. Every result is deterministic.

The check compares the program's complete output against the checked-in expected file, including its summary line and every result printed for the activity's fixed workload.

Run commands in this directory. On macOS, use the Ubuntu virtual machine from Bootcamp 1, Part 4. On Windows, use WSL2 Ubuntu. On Linux, use a terminal. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
