<!--no-pdf-->
# Activity Examples

This folder holds the worked examples for the activities that precede Problem
Set 3, Threads, Shared State, and Synchronization. Each activity has its own
folder. Each folder holds its own `make` and `make check`.

These examples are not graded. They are not part of the work you submit. Use
them to see the mechanism before you write the code.

| Folder | Activity |
|:--|:--|
| `act11` | Threads: Shared and Private State |
| `act12` | Interleavings and Mutexes |
| `act13` | Condition Variables |
| `act14` | Semaphores |
| `act15` | Deadlock and Problem Set 3 |

Build and check one folder:

```bash
cd examples/act11
make
make check
make clean
```

`make` builds the examples. `make check` builds them and compares the output
with the recorded output. `make clean` removes the build output. Read the
`README.md` in each folder for the model and the cases.

Run these commands inside Ubuntu. The examples need Linux.
