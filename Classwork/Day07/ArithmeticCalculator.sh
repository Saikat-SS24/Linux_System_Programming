#!/bin/bash

echo "Simple Calculator"

echo "Enter first number:"
read a

echo "Enter second number:"
read b

echo "Choose operation:"
echo "1. Add"
echo "2. Subtract"
echo "3. Multiply"
echo "4. Divide"
read choice

if [ $choice -eq 1 ]
then
	echo "Result = $((a+b))"

elif [ $choice -eq 2 ]
then
	echo "Result = $((a-b))"

elif [ $choice -eq 3 ]
then
	echo "Result = $((a*b))"

elif [ $choice -eq 4 ]
then
	echo "Result = $((a/b))"

else
	echo "Invalid choice"
fi
