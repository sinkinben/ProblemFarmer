#!/bin/bash
set -e
str=$1
str=${str%.*}
g++ $1 -o a.out
./a.out
exit