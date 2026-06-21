#!/bin/bash

user_name="Saikat"
user_score=85

if [ $user_score -ge 70 ]; then
    echo "Hello $user_name, you passed with a score of $user_score!"
else
    echo "Hello $user_name, you did not meet the required score."
fi