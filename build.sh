#!/bin/bash

if test -d ./build ; then
	
	echo "Removing and remaking - Build directory."
	
	rm -rf ./build
	mkdir ./build
	
else
	
	echo "Making - Build directory."
	
	mkdir ./build
	
fi

echo "Building - Main System and Register."

gcc -Wall \
    -Wextra \
    -std=c23 \
    -g \
    ./source/c/MCards/MCards_Localization.c \
    ./source/c/MCards/MCards_Register.c \
    ./source/c/Main.c \
    -I./source/h \
    -o ./build/multiverse-cards.out

echo "Multiverse Cards - Build successful!"
