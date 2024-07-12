#!/bin/bash

CC=gcc

if ! [ -f "miniaudio.h" ]; then
	wget "https://github.com/mackron/miniaudio/raw/master/miniaudio.h" --continue
fi

$CC main.c -o noise_cancelling -lpthread -ldl -lm

