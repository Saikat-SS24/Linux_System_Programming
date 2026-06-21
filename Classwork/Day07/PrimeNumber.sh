#!/bin/bash

echo "==========Prime Number Checker"
read -p "Enter a number: " n

if [ $n -lt 2 ]; then
	echo "$n is not prime"
	exit
fi

for ((i=2 ; i*i<=n; i++))
do
	if [ $((n%i)) -eq 0 ]; then
		echo "$n is not a prime number"
		exit
	fi
done

echo "$n is prime number"

