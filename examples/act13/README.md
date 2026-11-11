<!--no-pdf-->
# Activity 13 Example

A producer places one item in a one-slot buffer. A consumer waits on a condition variable until the buffer holds that item. The program prints one line. It's the same on every run.

The check compares the program's complete output against the checked-in expected file.

Run commands in this directory. On macOS, use the Ubuntu virtual machine from Bootcamp 1, Part 4. On Windows, use WSL2 Ubuntu. On Linux, use a terminal. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
