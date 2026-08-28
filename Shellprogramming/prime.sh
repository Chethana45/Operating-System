#!/bin/bash

echo "Enter a number:"
read n

if [ $n -le 1 ]; then
    echo "Not Prime"
    exit
fi

flag=0

for ((i=2; i<n; i++))
do
    if [ $((n % i)) -eq 0 ]; then
        flag=1
        break
    fi
done

if [ $flag -eq 0 ]; then
    echo "Prime"
else
    echo "Not Prime"
fi
