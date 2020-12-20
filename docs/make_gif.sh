#!/bin/bash

if [ -z $1 ]
then
	echo "error: missing argument <directory>"
	exit
fi

convert -delay 8 -loop 0 $1*.BMP result.gif
