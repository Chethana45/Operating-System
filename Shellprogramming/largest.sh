#!/bin/bash

echo "Enter first number:"
read a

echo "Enter second number:"
read b

if [ $a -gt $b ]; then
    echo "$a is largest"
elif [ $b -gt $a ]; then
    echo "$b is largest"
else
    echo "Both numbers are equal"
fi
