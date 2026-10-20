#!/usr/bin/env python3
"""Check the invariants outside the published case corpus.

`check.sh` runs these checks after the public cases. Each one exercises a claim
that the case corpus cannot state on its own:

1. The lost-update paper trace follows the model and ends at x=1.
2. The mutex paper trace follows the model and ends at x=2.
3. Four workers with 100,000 increments each report a total of 400000.
4. An acyclic lock order reports no cycle.
5. A cyclic lock order reports a cycle.
"""

from pathlib import Path
import subprocess
import sys

from trace_model import run_trace


def main() -> int:
    root = Path(sys.argv[1]).resolve()
    checks = 0
    failures = []
    trace = Path(__file__).resolve().parent / "traces" / "counter-lost-update.trace"
    status, result = run_trace(trace)
    checks += 1
    if status != 0 or result != "final x=1 T0.r=1 T1.r=1":
        failures.append(f"paper trace did not match model: {result}")
    locked = Path(__file__).resolve().parent / "traces" / "counter-locked.trace"
    status, result = run_trace(locked)
    checks += 1
    if status != 0 or result != "final x=2 T0.r=1 T1.r=2":
        failures.append(f"mutex trace did not match model: {result}")
    expected_total = "counter total=400000\n"
    stress = subprocess.run([str(root / "run"), "counter", "4", "100000"],
                            text=True, capture_output=True, check=False)
    checks += 1
    if stress.returncode != 0 or stress.stdout != expected_total:
        failures.append("counter stress run did not report 400000")
    safe = root / "cases" / "deadlock-safe.case"
    safe_output = subprocess.run([str(root / "run"), str(safe)],
                                 text=True, capture_output=True, check=False)
    checks += 1
    if safe_output.stdout != "lock-order cycle=no\n":
        failures.append("acyclic lock order was rejected")
    empty = root / "cases" / "deadlock-cycle.case"
    cycle_output = subprocess.run([str(root / "run"), str(empty)],
                                  text=True, capture_output=True, check=False)
    checks += 1
    if cycle_output.stdout != "lock-order cycle=yes\n":
        failures.append("cyclic lock order was missed")
    for failure in failures:
        print(f"FAIL {failure}")
    print(f"{checks - len(failures)}/{checks} invariant checks passed")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
