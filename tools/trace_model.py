#!/usr/bin/env python3
"""Validate LOAD, ADD, STORE traces for the manual's two-thread model."""

from pathlib import Path
import sys


def run_trace(path: Path) -> tuple[int, str]:
    shared = 0
    registers = [None, None]
    actions = [line.split() for line in path.read_text(encoding="utf-8").splitlines()
               if line.strip() and not line.strip().startswith("#")]
    locked = any(len(parts) == 2 and parts[1] == "LOCK" for parts in actions)
    sequence = ["LOCK", "LOAD", "ADD", "STORE", "UNLOCK"] if locked else [
        "LOAD", "ADD", "STORE"
    ]
    next_action = [0, 0]
    owner = None
    for number, parts in enumerate(actions, 1):
        if len(parts) != 2 or parts[0] not in ("T0", "T1"):
            return 1, f"line {number}: expected T0|T1 LOCK|LOAD|ADD|STORE|UNLOCK"
        thread = int(parts[0][1])
        action = parts[1]
        expected = sequence[next_action[thread]] if next_action[thread] < len(sequence) else "DONE"
        if action != expected:
            return 1, f"line {number}: {parts[0]} expected {expected}"
        if locked and action == "LOCK":
            if owner is not None:
                return 1, f"line {number}: {parts[0]} cannot acquire the held mutex"
            owner = thread
        elif locked and owner != thread:
            return 1, f"line {number}: {parts[0]} does not hold the mutex"
        if action == "LOAD":
            registers[thread] = shared
            next_action[thread] += 1
        elif action == "ADD":
            if registers[thread] is None:
                return 1, f"line {number}: register is unset"
            registers[thread] += 1
            next_action[thread] += 1
        elif action == "STORE":
            if registers[thread] is None:
                return 1, f"line {number}: register is unset"
            shared = registers[thread]
            next_action[thread] += 1
        elif action == "LOCK":
            next_action[thread] += 1
        elif action == "UNLOCK":
            owner = None
            next_action[thread] += 1
    if next_action != [len(sequence), len(sequence)]:
        return 1, "trace ended before both increments completed"
    return 0, f"final x={shared} T0.r={registers[0]} T1.r={registers[1]}"


if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise SystemExit("usage: trace_model.py <trace-file>")
    status, message = run_trace(Path(sys.argv[1]))
    print(message)
    raise SystemExit(status)
