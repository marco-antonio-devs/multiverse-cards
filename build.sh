#!/bin/bash

echo "Building Main.c/MCards_Register.c - Main System and Register."

gcc -Wall \
	-Wextra \
	-std=c23 \
	-g \
	./source/c/MCards/MCards_Register.c \
	./source/c/Main.c \
	-I./source/h \
	-o build/multiverse-cards.out

echo "Multiverse Cards - Build successful!"
