#!/bin/bash

echo "Enter old file name:"
read old

echo "Enter new file name:"
read new

if [ -f "$old" ]; then

    mv "$old" "$new"

    echo "File renamed successfully"

else
    echo "File does not exist"
fi
