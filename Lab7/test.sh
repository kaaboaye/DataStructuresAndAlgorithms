#!/usr/bin/env bash

g++ main.cpp
cat in.txt | ./a.out > out.txt
rm ./a.out
cat in.txt
echo ''
diff -y out-true.txt out.txt
