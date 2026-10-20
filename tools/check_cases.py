#!/usr/bin/env python3
"""Run case files and compare each result with its expected output."""

from pathlib import Path
import subprocess
import sys

CASE_TIMEOUT_SECONDS = 15


def compare(actual: bytes, expected: bytes, returncode: int,
            stderr: bytes = b"", expected_returncode: int = 0,
            expected_stderr: bytes = b"") -> list[str]:
    problems = []
    if returncode != expected_returncode:
        problems.append(f"exit code was {returncode}, expected {expected_returncode}")
    if actual != expected:
        problems.append("standard output did not match")
    if stderr != expected_stderr:
        problems.append("standard error did not match")
    return problems


def run_cases(root: Path, case_dir: Path) -> tuple[int, int, list[str]]:
    cases = sorted(case_dir.glob("*.case"))
    passed = 0
    failures = []
    for case in cases:
        expected_path = case_dir / "expected" / f"{case.stem}.out"
        if not expected_path.is_file():
            failures.append(f"{case.name}: expected output is missing")
            continue
        status_path = expected_path.with_suffix(".status")
        error_path = expected_path.with_suffix(".err")
        try:
            expected_status = int(status_path.read_text().strip()) if status_path.exists() else 0
        except ValueError:
            failures.append(f"{case.name}: expected status is invalid")
            continue
        if expected_status < 0 or expected_status > 255:
            failures.append(f"{case.name}: expected status is outside 0..255")
            continue
        expected_error = error_path.read_bytes() if error_path.exists() else b""
        try:
            result = subprocess.run([str(root / "run"), str(case)],
                                    stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE, check=False,
                                    timeout=CASE_TIMEOUT_SECONDS)
        except subprocess.TimeoutExpired:
            failures.append(
                f"{case.name}: process timed out after "
                f"{CASE_TIMEOUT_SECONDS} seconds")
            continue
        problems = compare(result.stdout, expected_path.read_bytes(),
                           result.returncode, result.stderr, expected_status,
                           expected_error)
        if problems:
            failures.append(f"{case.name}: {', '.join(problems)}")
        else:
            passed += 1
    return passed, len(cases), failures


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: check_cases.py <case-directory>", file=sys.stderr)
        return 2
    root = Path(__file__).resolve().parents[1]
    case_dir = Path(sys.argv[1]).resolve()
    passed, total, failures = run_cases(root, case_dir)
    for failure in failures:
        print(f"FAIL {failure}")
    print(f"{passed}/{total} cases passed")
    return 0 if passed == total and total > 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
