<!--no-pdf-->
# Semaphores Example

A child thread posts a named semaphore. Its parent waits before continuing. Every run prints the same three lines in the same order.

## The Model

The parent creates the named semaphore with count zero and prints its first line. The child prints its line and posts the semaphore, which raises the count to one. The parent's wait then returns. It prints the last line. The child can post before the parent reaches its wait. In that order, the wait finds the count already at one and returns at once. The three lines keep their order on every run because the parent prints its last line only after the wait returns. The parent joins the child, closes the handle, and unlinks the semaphore name before it exits.

The `check` target runs the program and compares its complete output with `expected/run.txt`. A change to any single printed line fails the check.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
