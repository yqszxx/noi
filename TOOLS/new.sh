#!/bin/bash

mkdir $1
cd $1
echo $1 > .PROBLEM_CONFIG
cp ~/TOOLS/base.cpp $1.cpp
vim $1.cpp
