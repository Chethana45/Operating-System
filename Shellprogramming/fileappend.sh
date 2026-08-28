#!/bin/bash

echo "Enter file name:"
read file

if [ -f "$file" ]; then

    echo "Enter text to append:"
    read text

    echo "$text" >> "$file"

    echo "Text appended successfully"

else
    echo "File does not exist"
fi
