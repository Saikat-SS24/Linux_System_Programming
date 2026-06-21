#!/bin/bash

read -p "Enter number for multiplication table: " num

echo "================while==============="
i=1
while [ $i -le 10 ]; do
	echo "$num * $i = $((num*i))"
	(( i++ ))
done

echo "===============until================"
i=1
until [ $i -gt 10 ]; do
	echo "$num * $i = $((num*i))"
	(( i++ ))
done
