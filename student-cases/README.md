# Student Cases

Add one boundary or failure case of your own. Give it a `.case` file. Add its expected output under `expected/` with the same stem and an `.out` suffix. Invalid cases also need a `.status` file and an `.err` file.

Run `./check.sh student-cases` to check it. State the defect your case detects in `ANALYSIS.md`. Show the result from the defective version and the corrected version.

For a valid case, leave status and error files out. For a failure case, record the expected nonzero status and error text so the checker can distinguish a planned error from a defect.

Write `.status` as one integer followed by a newline. Write `.err` as the exact standard-error bytes. Keep `.out` empty when the command must fail.

`example.case` gives a small counter boundary. Replace it with your own case before submission. Don't change `tools/check_cases.py` or the public cases.

The supplied example checks a valid counter result. Replace its input and expected output together, then confirm that the corrected program and the known defect produce different results.

Before submission, run the case with both the corrected starter and the known defective version, then record each command, output, and exit code in `ANALYSIS.md`.
