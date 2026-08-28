#!/bin/bash

echo "Enter main string:"
read str

echo "Enter substring:"
read sub

if [[ "$str" == *"$sub"* ]]; then
    echo "Substring found"
else
    echo "Substring not found"
fi
