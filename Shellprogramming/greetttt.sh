#!/bin/bash

greet()
{
    echo "Hello, $1"
}

echo "Enter your name:"
read name

greet "$name"
