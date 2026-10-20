<!--no-pdf-->
# CMSC 125 Problem Set 3 Starter

This C17 project is the starter for the CMSC 125 Problem Set 3 concurrent
queue and lock-order graph. A counter measures lost updates. A bounded queue
carries items between producers and consumers through a condition variable or
POSIX semaphores. A lock-order graph reports whether a cycle can stop every
thread. This README gives the repository map, the commands, the starting state,
and the three host routes.

This project runs on Linux, on macOS, and on Windows through WSL2 Ubuntu. It
uses POSIX threads and, on macOS, named POSIX semaphores.

## Pair

Enter two names below. An assigned trio adds one entry.

- Full Name (`@github-username`)
- Full Name (`@github-username`)

## Files You May Change

You may change only these files and folders:

- `src/counter.c`
- `src/buffer.c`
- `src/deadlock.c`
- `ANALYSIS.md`, which you create
- The Pair section of `README.md`
- `student-cases/`, which holds the one case of your own

Everything else is fixed. `include/ps3.h` and `src/main.c` are given to you
complete. `cases/`, `tools/check_cases.py`, and the workflow are the grading
corpus and its runner. The manual states every rule these files follow.

## Layout

```
include/ps3.h         fixed interface: limits, structures, prototypes
src/main.c            complete: the case reader, the command line, the exit codes
src/counter.c         yours: the shared counter and the lost-update measurement
src/buffer.c          yours: the bounded queue, the condition variable, the semaphores
src/deadlock.c        yours: the lock-order graph cycle search
cases/                the complete public corpus
student-cases/        the one boundary or failure case of your own
tools/check_cases.py  the runner that grades the corpus
ANALYSIS.md           the joint analysis that you create
Makefile run check.sh  the run contract
```

## Commands

```bash
make                      # build build/ps3
make clean                # remove the build directory
./run cases/mutex.case
./run counter 4 100000
./check.sh                # build, then run every published case in cases/
./check.sh student-cases  # build, then run the cases in student-cases/
```

`./run` passes its arguments to the binary. It accepts one case file, or
`counter WORKERS INCREMENTS` for a direct measurement.

`check.sh` is the complete public automated check. No hidden suite exists. Read
`tools/check_cases.py` before you trust a green run. The rubric separately
assesses the joint analysis and the collaboration history.

## Exit Codes

| Code | Meaning |
|---|---|
| 0 | The case ran and every check in it passed. |
| 1 | A case check failed, or the case content was refused. |
| 2 | The command line or the case file path was refused. |

## The First Run

A fresh clone builds without warnings. It passes 13 of the 39 cases and exits
1. The 13 passing cases test invalid input. They need no completed module: the
stubs return failure as required.

The other 26 cases need `src/counter.c`, `src/buffer.c`, and `src/deadlock.c`.
The workflow in the Actions tab is red for the same reason. That state is
correct for a starter. Your fork passes after you implement the three files.

Enable workflows in the Actions tab after you fork the repository. GitHub
disables them on forks. The workflow run is part of the submission.

## Hosts

### Linux

```bash
sudo apt update
sudo apt install -y build-essential make python3
```

### macOS

The Xcode command line tools carry the compiler and `make`.

```bash
xcode-select --install
```

Check the Python 3 version. macOS ships Python 3 with the command line tools.

```bash
python3 --version
```

The semaphore implementation uses named POSIX semaphores on macOS. The
interface keeps that platform choice inside `src/buffer.c`.

### Windows through WSL2 Ubuntu

Install WSL2 with Ubuntu from PowerShell.

```powershell
wsl --install -d Ubuntu
```

Open the Ubuntu terminal and install the tools inside it.

```bash
sudo apt update
sudo apt install -y build-essential make python3
```

Work in the Ubuntu file system under your home directory. A checkout under
`/mnt/c` works but it is slower, and file permissions there behave differently.

### Check

```bash
cc --version
make --version
python3 --version
```

## The Corpus

The 39 cases under `cases/` are the cases the instructor grades with. Each
`.case` file holds one workload and its limits. A valid case has an `.out` file
with the exact expected output. An invalid case also has `.err` and `.status`
files.

The runner compares standard output, standard error, and the exit status of
every case byte for byte. It stops a case after 15 seconds. A valid case
requires exit code zero and empty standard error.

Several cases apply the same producer and consumer workload to both queue
implementations. Their exact counts and sums are comparable under identical
inputs.

The one case your pair writes lives under `student-cases/`. That folder holds a
short README and an example in the same form. Run it with
`./check.sh student-cases`.

