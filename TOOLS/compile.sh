#!/bin/bash

read PROBLEM_NUMBER < .PROBLEM_CONFIG
g++ -Wall -O2 -o $PROBLEM_NUMBER.o $PROBLEM_NUMBER.cpp
if (($?)); then
	echo "!!!!!!!Compile Error!!!!!!!!!"
else
	echo "####Successfully Compiled####"
	time ./$PROBLEM_NUMBER.o
fi
