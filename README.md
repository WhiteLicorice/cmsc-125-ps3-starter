<!--no-pdf-->
# CMSC 125 Problem Set 3 Starter

This C17 project is the starter for the CMSC 125 Problem Set 3 concurrent
queue and lock-order graph. A mutex-protected counter sums concurrent
increments. A bounded queue carries items between producers and consumers
through two condition variables or POSIX semaphores. The lock-order search finds
cycles in the supplied graph. A cycle shows a possible deadlock among the
threads that take those locks. This README gives the repository map,
the commands, the starting state, and the three host routes.

This project runs on Linux, on macOS, and on Windows through WSL2 Ubuntu. It
uses POSIX threads and named POSIX semaphores on every platform.

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
src/counter.c         yours: the mutex-protected shared counter
src/buffer.c          yours: the bounded queue, the two condition variables, the semaphores
src/deadlock.c        yours: the lock-order graph cycle search
cases/                the complete public corpus
examples/             one worked example per Unit 2 subtopic
student-cases/        the one boundary or failure case of your own
tools/check_cases.py  the runner that grades the corpus
tools/check_invariants.py  invariant checker that check.sh runs
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
assesses Implementation Correctness, Structure and Synchronization, Joint
Analysis, and Collaboration.

## Exit Codes

| Code | Meaning |
|---|---|
| 0 | The case ran and every check in it passed, or a `counter` run printed its total. |
| 1 | A case check failed, the case content was refused, or the counter run failed. |
| 2 | The command line, the case file path, or a `counter` argument was refused. |

## The First Run

A fresh clone builds without warnings. It reports `14/40 cases passed` and
exits 1. Two of the 5 invariant checks pass: the two paper traces. The three
program checks wait for your modules. All 14 passing cases are invalid-input
refusals. They need no completed module. The stubs return failure as required.

The other 26 cases need `src/counter.c`, `src/buffer.c`, and `src/deadlock.c`.
The workflow in the Actions tab is red for the same reason. That state is
correct for a starter. Your fork passes after you implement the three files. A
complete submission reports `40/40 cases passed` and `5/5 invariant checks
passed`, then exits 0.

Enable workflows in the Actions tab after you fork the repository. GitHub
disables them on forks. The workflow run is part of the submission.

## Hosts

### Linux

```bash
sudo apt update
sudo apt install -y build-essential make git python3
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

The semaphore implementation uses named POSIX semaphores on every platform.
The interface keeps that choice inside `src/buffer.c`.

### Windows Through WSL2 Ubuntu

Use Windows 10 version 2004 or later, or Windows 11. Open PowerShell as an
administrator, then install the Ubuntu 24.04 release.

```powershell
wsl --install -d Ubuntu-24.04
```

The `-d` flag selects the release, so this installs Ubuntu 24.04.

Restart Windows when the installer asks. After restart, **Ubuntu 24.04 LTS**
opens from the Start menu for the first launch. Create the Linux account and
password it asks for. On later days, start the same distribution from
PowerShell.

```powershell
wsl -d Ubuntu-24.04
```

Install the tools inside the Ubuntu terminal.

```bash
sudo apt update
sudo apt install -y build-essential make git python3
```

Work in the Ubuntu file system under your home directory. A checkout under
`/mnt/c` works but it's slower, and file permissions there behave differently.

### Check

```bash
cc --version
make --version
git --version
python3 --version
```

## The Corpus

The 40 cases under `cases/` are the cases the instructor grades with. Each
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

`check.sh` runs the five invariant checks after the public cases. They cover the
two paper traces, the counter stress run, and both lock-order results. The
checks are part of the same command, so no hidden suite exists.
