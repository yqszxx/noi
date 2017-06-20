#!/bin/bash

read PROBLEM_NUMBER < .PROBLEM_CONFIG;
if [ $? = 0 ]; then
	g++ -g -DYQSZXX_DEBUG -o $PROBLEM_NUMBER.o $PROBLEM_NUMBER.cpp;
	if [ $? = 0 ]; then
		gdbtui $PROBLEM_NUMBER.o;
	else
		echo "!!!!!!!Compile Error!!!!!!!!!";
	fi
fi

