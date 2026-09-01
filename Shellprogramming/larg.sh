#!/bin/bash

read -p "Enter N: " n

read -p "Enter number: " max

for ((i=2; i<=n; i++))
do
    read -p "Enter number: " x

    if [ $x -gt $max ]; then
        max=$x
    fi
done

echo "Largest = $max"
