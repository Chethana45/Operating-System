#!/bin/bash

echo "Enter a string:"
read str

reverse=""

for ((i=${#str}-1; i>=0; i--))
do
    reverse="$reverse${str:i:1}"
done

echo "Reversed string: $reverse"
