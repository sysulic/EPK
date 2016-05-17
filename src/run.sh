#!/bin/bash

test_cases_file1="../epddl/test_cases(BFS)"
test_cases_file2="../epddl/test_cases(DFS)"
test_cases_file3="../epddl/test_cases(Heu)"
program="./start"


echo "++++++++++++++++++++++++++++++++++ BFS ++++++++++++++++++++++++++++++++++"

cat $test_cases_file1 | while read oneline
do
    $program $oneline
    echo
done

echo "++++++++++++++++++++++++++++++++++ DFS ++++++++++++++++++++++++++++++++++"

cat $test_cases_file2 | while read oneline
do
    $program $oneline
    echo
done

echo "++++++++++++++++++++++++++++++++++ Heu ++++++++++++++++++++++++++++++++++"

cat $test_cases_file3 | while read oneline
do
    $program $oneline
    echo
done

exit 0
