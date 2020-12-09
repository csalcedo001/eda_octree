#!/bin/bash

if [ ! -f bin/decompress ]
then
	make
fi

./bin/decompress data/compressed/test.dat data/rgb/test.out
python3 make_image.py
