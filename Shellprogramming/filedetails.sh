#!/bin/bash

echo "Enter file name:"
read file

if [ -f "$file" ]; then

    echo "Lines:"
    wc -l "$file"

    echo "Words:"
    wc -w "$file"

    echo "Characters:"
    wc -m "$file"

else
    echo "File does not exist"
fi
