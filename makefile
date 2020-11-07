# Main target
all:nsm

# Forged target
.PHONY:clean

# Variables
CC=g++
HEADER=inc
CFLAGS=-Wall -g -std=gnu++11 -I$(HEADER)	# Complier use this option to find the header.

# cpp file path
vpath %.cpp src

# Header file path
vpath %.h inc		# make use this enviornment setting to checking if the depended file had existed.

# Static synstax
.SUFFIXES: .cpp .o
.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<

nsm:nsm_main.o nsm.o
	$(CC) $(CFLAGS) -o $@ $^
	install $@ bin/
	unlink $@

# Automatically derive
nsm_main.o:nsm_main.cpp nsm.h

# Automatically derive
nsm.o:nsm.cpp nsm.h

# Clear
clean:
	rm -f *.o

# Revise log
# 	1> Change target name hsm to nsm.
