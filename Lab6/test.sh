#!/usr/bin/env bash

g++ main.cpp
cat in.txt | ./a.out > out.txt
cat in.txt
echo ''
diff -y out-true.txt out.txt
