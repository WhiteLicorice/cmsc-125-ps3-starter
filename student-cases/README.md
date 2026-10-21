# Student Cases

Add one boundary or failure case of your own. Give it a `.case` file. Add its expected output under `expected/` with the same stem and an `.out` suffix. A failure case also needs a `.status` file and an `.err` file. A valid case needs neither.

Write `.status` as one integer followed by a newline. Write `.err` as the exact standard-error bytes. Keep `.out` empty when the command must fail. For a failure case, record the expected nonzero status and error text, so the checker can tell a planned error from a defect.

`example.case` gives a small valid counter case. Replace it with your own case before submission. Don't change `tools/check_cases.py` or the public cases.

Run `./check.sh student-cases` to check the case. Run it once against the corrected starter and once against a known defective version. Record each command, output, and exit code in `ANALYSIS.md`, with the defect the case detects.
