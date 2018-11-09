#!/bin/sh

if [ -z "$commands" ]; then
    commands="tests/in/commands"
fi

RED='\033[0;31m'
GRN='\033[0;32m'
BLU='\033[0;34m'
END='\033[0m'

 in="./tests/in"
out="./tests/out"

passed=0
failed=0
failnm=""

echo -e "\n================ START TEST ================\n"
echo -e "[ ${BLU}MISC${END} ] Creating proper test archive... "

mkdir "$out" &> /dev/null

echo -e "[ ${BLU}MISC${END} ] Creating proper test archive... Done.\n"

while IFS='' read -r cmd; do
    eval $cmd > "$out"/my_stdout 2> "$out"/my_stderr
    eval $cmd > "$out"/rf_stdout 2> "$out"/rf_stderr
    diff -u "$out"/my_stdout "$out"/rf_stdout > "$out"/diff_stdout
    diff -u "$out"/my_stderr "$out"/rf_stderr > "$out"/diff_stderr
    my_count=$(cat "$out"/my_stderr | wc -l)
    rf_count=$(cat "$out"/rf_stderr | wc -l)

    if [ ! -s "$out"/diff_stdout ] && [ "$my_count" -eq "$rf_count" ]; then
        echo -e "[ ${GRN}PASS${END} ] '$cmd'"
        passed=$((passed + 1))
    else
        echo -e "[ ${RED}FAIL${END} ] '$cmd'"
        failed=$((failed + 1))
        failnm="$failnm\n'$cmd'"
        [ ! -z "$output" ] && cat "$out"/diff_stdout
    fi

    [ ! -z "$errput" ] && cat "$out"/diff_stderr
done < "$commands"

echo -e "\n[ ${BLU}MISC${END} ] Removing created archive..."

rm -r "$out"

echo -e "[ ${BLU}MISC${END} ] Removing created archive... Done."
echo -e "\n=============== TEST SUMMARY ===============\n"
echo -e "Passed: ${GRN}$passed${END}"
echo -e "Failed: ${RED}$failed${END}"
echo -e " Total: $((passed + failed))"

if [ $failed -gt 0 ]; then
    echo -e "\nThe following tests were failed:$failnm"
fi

echo -e "\n================  END TEST  ================\n"
