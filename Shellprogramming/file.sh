#!/bin/bash

echo "Enter file name:"
read file

if [ -f "$file" ]; then
    echo "File exists"
    echo "File contents:"
    cat "$file"
else
    echo "File does not exist"
fi
