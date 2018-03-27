#!/usr/bin/env bash
cat in.txt | cmake-build-debug/Lab5 > out.txt
cat in.txt
echo ''
diff -y out_good.txt out.txt
