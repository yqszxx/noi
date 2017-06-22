#!/bin/bash

read OLD_NUMBER < ./$1/.PROBLEM_CONFIG;
if [ $? = 0 ]; then
	mv $1 $2;
	cd $2;
	rm .PROBLEM_CONFIG;
	for OLD_FILE in $(find .) do
		echo $OLD_FILE | sed "s/$OLD_NUMBER/$2/" | xargs mv $OLD_FILE;
	done
	echo $2 > .PROBLEM_CONFIG;
	cd ..;
	echo "DONE";
fi
