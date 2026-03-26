#!/bin/bash

echo "Pre-Building - Checking by \`libsdl3-dev\` installation."

if dpkg-query -W -f='${Status}' libsdl3-0 2>/dev/null | grep -q "ok installed" ; then
	
	echo "You have \`libsdl3-dev\` installed. Continuing..."
	
else
	
	echo "You do not have \`libsdl3-dev\` installed. Aborting..."
	
	exit 1
	
fi

if test -d ./build ; then
	
	echo "Removing and remaking - Build directory."
	
	rm -rf ./build
	mkdir ./build
	
else
	
	echo "Making - Build directory."
	
	mkdir ./build
	
fi

echo "Building - Main System and Register."

if [ "$1" = "debug" ] ; then
	
	gcc -Wall \
	    -Wextra \
	    -std=c23 \
	    -g \
	    $(find ./source/c -name "*.c") \
	    -I./source/h \
	    $(pkg-config --cflags --libs sdl3) \
	    -o ./build/multiverse-cards
	
elif [ "$1" = "release" ] ; then
	
	gcc -Wall \
	    -Wextra \
	    -std=c23 \
	    -O2 \
	    -s \
	    $(find ./source/c -name "*.c") \
	    -I./source/h \
	    $(pkg-config --cflags --libs sdl3) \
	    -o ./build/multiverse-cards
	
fi

if test -d build/multiverse-cards ; then
	
	echo "Multiverse Cards - Build successful!"
	
	build/multiverse-cards
	
fi
