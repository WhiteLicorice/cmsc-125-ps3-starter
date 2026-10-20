#!/usr/bin/env sh
set -eu
root=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
make -C "$root"
cd "$root"
case_dir=${1:-cases}
set -- "$root/$case_dir"/*.case
case_count=$#
if [ ! -f "$1" ]; then
    case_count=0
fi
echo "Checking $case_count cases in $case_dir."
python3 tools/check_cases.py "$case_dir"
