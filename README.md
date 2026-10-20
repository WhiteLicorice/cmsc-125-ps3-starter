# CMSC 125 Problem Set 3 Starter

This repository holds a POSIX threads exercise. Complete the TODO blocks in `src/counter.c`, `src/buffer.c`, and `src/deadlock.c`. Keep the public interface and cases unchanged.

## Requirements

The project uses C17, POSIX threads, Make, Git, and Python 3.9 or newer. It has no third-party package dependencies.

## Build and Run

On Linux, install the compiler and tools with `sudo apt install build-essential make git python3`.

On macOS, install the Xcode command line tools with `xcode-select --install`. Install Python with `brew install python` if your version is older than 3.9.

On Windows, install WSL2 Ubuntu from PowerShell with `wsl --install -d Ubuntu`. Then install the Linux tools inside Ubuntu.

Run these commands on Linux, native macOS, or WSL2 Ubuntu:

```sh
make
./run cases/mutex.case
./check.sh
```

The starter builds with failure stubs. Its public check reports `13/39 cases passed` and exits 1 until you complete the modules. The invalid-input cases pass because the stubs return failure as required.

The TODO comments split the implementation into reviewable tasks. Each comment marks one task in a worker, queue operation, or graph search.

Run a counter measurement with `time ./run counter 4 100000`. The program prints the total. The shell prints elapsed time.

The semaphore implementation uses named POSIX semaphores on macOS. The interface keeps that platform choice inside `src/buffer.c`.

## Cases

`cases/` holds 39 exact-output cases. They check the counter limits, both queue paths, queue boundaries, and lock-order graph boundaries. Valid cases have an `.out` file and require exit code zero with empty standard error. Invalid cases also have `.status` and `.err` files. The checker compares all three results byte for byte and stops a case after 15 seconds.

Several cases apply the same producer and consumer workload to both queue implementations, so their exact counts and sums can be compared under identical inputs.

## The Pair

Record both partners' names and GitHub accounts in `ANALYSIS.md`. The instructor assigns pairs at random. Keep commits that show each partner's work. Both partners must explain the queue invariant and one trace.

## TODOs

Each TODO block states one implementation task. Preserve the fixed interface in `include/ps3.h`. Implement queue operations under the mutex. Don't treat a racy counter result as a required output.
