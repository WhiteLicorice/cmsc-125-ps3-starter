<!--no-pdf-->
# Unit 2 Example Programs

This folder holds one worked example for each Unit 2 subtopic that Problem Set
3 uses: "Threads and the Thread API", "Interleavings and Mutexes", "Condition
Variables", "Semaphores", and "Deadlock". Each subtopic has its own folder.
Each folder holds its own `make` and `make check`.

These examples aren't graded. They aren't part of the work you submit. Use them
to see the mechanism before you write the code.

| Folder | Subtopic |
|:--|:--|
| `threads-and-the-thread-api` | "Threads and the Thread API" |
| `interleavings-and-mutexes` | "Interleavings and Mutexes" |
| `condition-variables` | "Condition Variables" |
| `semaphores` | "Semaphores" |
| `deadlock` | "Deadlock" |

Build and check one folder:

```bash
cd examples/threads-and-the-thread-api
make
make check
make clean
```

`make` builds the example. `make check` builds it and compares its output with
the recorded output. `make clean` removes the build output. Read the `README.md`
in each folder for the model and the cases.

Run these commands in a terminal. You need a C compiler and `make`.
