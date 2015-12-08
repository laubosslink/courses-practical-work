#!/bin/bash

echo "Compilation..."

gcc $1.c -o $1

echo "Execution..."
echo 

./$1
