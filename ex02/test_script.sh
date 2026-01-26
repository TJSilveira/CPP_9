#!/bin/bash

for i in $(seq 1 50);
do
  shuf -i 1-10000 -n $i | tr "\n" " " | xargs ./PmergeMe
done

shuf -i 1-10000 -n 3000 | tr "\n" " " | xargs ./PmergeMe
shuf -i 1-10000 -n 10000 | tr "\n" " " | xargs ./PmergeMe

# error testing
echo
echo "========== [ERROR SECTION] =========="

./PmergeMe 1a 6 2 6 8
./PmergeMe "" 6 2 6 8
./PmergeMe "" "" "" ""
./PmergeMe "1.2      5" 3 5 4
./PmergeMe "1      5" 3 5 4
./PmergeMe "1," 3 5 4
./PmergeMe "1,    " 3 5 4
./PmergeMe "1 5 3 4"