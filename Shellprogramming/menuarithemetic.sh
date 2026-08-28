#!/bin/bash

while true
do
    echo "1. Add"
    echo "2. Subtract"
    echo "3. Multiply"
    echo "4. Exit"

    echo "Enter your choice:"
    read choice

    case $choice in

        1)
            echo "Enter two numbers:"
            read a b
            echo "Result = $((a + b))"
            ;;

        2)
            echo "Enter two numbers:"
            read a b
            echo "Result = $((a - b))"
            ;;

        3)
            echo "Enter two numbers:"
            read a b
            echo "Result = $((a * b))"
            ;;

        4)
            echo "Exiting..."
            exit
            ;;

        *)
            echo "Invalid choice"
            ;;
    esac
done
