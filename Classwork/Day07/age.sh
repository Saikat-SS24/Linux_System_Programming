#!/bin/bash

read -p "Enter your age: " age

if [ ${age} -lt 0 ] || [ ${age} -gt 120 ]; then
	echo "Enter the age between 0-120"
	exit 0
fi

if [ ${age} -lt 18 ]; then
	echo "you are minor"
elif [ ${age} -lt 65 ]; then
	echo "You are an adult"
else
	echo "you are a seniour"
fi

echo "End of the program"
echo ""
