#!/bin/bash

echo "Building - Main System and Register."

gcc -Wall \
	-Wextra \
	-std=c23 \
	-g \
	./source/c/MCards/MCards_Register.c \
	./source/c/MCards/MCards_Localizations.c \
	./source/c/Main.c \
	-I./source/h \
	-o build/multiverse-cards.out

echo "Multiverse Cards - Build successful!"
