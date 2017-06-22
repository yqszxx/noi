#!/bin/bash

read PROBLEM_NUMBER < .PROBLEM_CONFIG;
if [ $? = 0 ]; then
	vim $PROBLEM_NUMBER.cpp;
fi
