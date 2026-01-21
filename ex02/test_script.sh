#!/bin/bash

for i in $(seq 1 50);
do
  shuf -i 1-10000 -n $i | tr "\n" " " | xargs ./PmergeMe
done

shuf -i 1-10000 -n 3000 | tr "\n" " " | xargs ./PmergeMe
shuf -i 1-10000 -n 30000 | tr "\n" " " | xargs ./PmergeMe