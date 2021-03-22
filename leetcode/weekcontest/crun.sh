#!/bin/bash
set -e
g++ $1 -std=c++17 -o a.exe
./a.exe
exit