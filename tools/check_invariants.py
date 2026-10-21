#!/usr/bin/env python3
"""Check the invariants outside the published case corpus.

`check.sh` runs these checks after the public cases. Each one exercises a claim
that the case corpus cannot state on its own:

1. The lost-update paper trace follows the model and ends at x=1.
2. The mutex paper trace follows the model and ends at x=2.
3. Four workers with 100,000 increments each report a total of 400000.
4. An acyclic lock order reports no cycle.
5. A cyclic lock order reports a cycle.

Each program run stops after 30 seconds. A module that hangs fails its check,
and the checks after it still run.
"""

from pathlib import Path
import subprocess
import sys

from trace_model import run_trace


INVARIANT_TIMEOUT_SECONDS = 30


def run_bounded(command: list[str]) -> tuple:
    """Run one program check. Return its result, or the timeout reason."""
    try:
        result = subprocess.run(command, text=True, capture_output=True,
                                check=False,
                                timeout=INVARIANT_TIMEOUT_SECONDS)
    except subprocess.TimeoutExpired:
        return None, f"timed out after {INVARIANT_TIMEOUT_SECONDS} seconds"
    return result, ""


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
    stress, problem = run_bounded([str(root / "run"), "counter", "4", "100000"])
    checks += 1
    if problem:
        failures.append(f"counter stress run {problem}")
    elif stress.returncode != 0 or stress.stdout != expected_total:
        failures.append("counter stress run did not report 400000")
    safe = root / "cases" / "deadlock-safe.case"
    safe_output, problem = run_bounded([str(root / "run"), str(safe)])
    checks += 1
    if problem:
        failures.append(f"acyclic lock order {problem}")
    elif safe_output.stdout != "lock-order cycle=no\n":
        failures.append("acyclic lock order was rejected")
    empty = root / "cases" / "deadlock-cycle.case"
    cycle_output, problem = run_bounded([str(root / "run"), str(empty)])
    checks += 1
    if problem:
        failures.append(f"cyclic lock order {problem}")
    elif cycle_output.stdout != "lock-order cycle=yes\n":
        failures.append("cyclic lock order was missed")
    for failure in failures:
        print(f"FAIL {failure}")
    print(f"{checks - len(failures)}/{checks} invariant checks passed")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
