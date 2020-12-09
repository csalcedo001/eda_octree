#!/bin/bash

if [ ! -f bin/compress ]
then
	make
fi

python3 process_image_input.py data/image/input.png data/rgb/test.in
./bin/compress data/compressed/test.dat 100 < data/rgb/test.in
