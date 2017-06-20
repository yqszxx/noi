#!/bin/bash

if [ $# -gt 0 ]; then
	if [ $# -gt 1 ]; then
		echo "/home/hby/noi/Week$1/problem/" > /home/hby/TOOLS/.goto_history
		cd /home/hby/noi/Week$1/problem/
	else
		echo "/home/hby/noi/Week$1/" > /home/hby/TOOLS/.goto_history
		cd /home/hby/noi/Week$1/
	fi
else
	read LAST_GOTO < /home/hby/TOOLS/.goto_history
	cd "$LAST_GOTO"
fi

