<!--no-pdf-->
# Threads and the Thread API Example

The program creates two worker threads. A mutex protects their shared update. Each worker reads its own input value. Every result is deterministic.

## The Model

The two workers share one total. Worker A receives a record that holds 1, and worker B receives one that holds 2. Under the mutex, a worker adds its own value to the shared total, so the total ends at 3 whichever worker runs first. A worker returns its record address. The join writes that same address to the caller's pointer. The last line checks both pointers and both private values.

The check compares the program's complete output against the checked-in expected file, including its summary line and every result printed for the example's fixed workload.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
