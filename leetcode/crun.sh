#!/bin/bash
set -e
str=$1
str=${str%.*}
g++ $1 -o a.out -std=c++17
./a.out
exit
