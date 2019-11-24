#
# CSF Assignment 5 Makefile
# You shouldn't need to modify this.
# Use "make solution.zip" to prepare a zipfile that
# you can submit to Gradescope.
#

# Executables to build for the "all" target
EXES = hex hexTest

# C source files
C_SRCS = hexTest.c tctest.c

# Assembler source files
ASM_SRCS = hex.S hexFuncs.S

# Files to be submitted
SUBMIT_FILES = $(shell ls *.c) $(shell ls *.S) $(shell ls *.h) Makefile

# C compiler flags
CFLAGS = -Og -Wall -no-pie

# Flags to use when assembling
ASMFLAGS = -no-pie

# Flags to use when linking an executable
LDFLAGS = -no-pie

# Rule for assembling a .S file to produce a .o file
%.o : %.S
	gcc -c $(ASMFLAGS) $*.S -o $*.o

# Rule for compiling and assembling a .c file to produce a .o file
%.o : %.c
	gcc $(CFLAGS) -c $*.c -o $*.o

# Default target: build all executables
all : $(EXES)

# hex program
hex : hex.o hexFuncs.o
	gcc -o $@ $(LDFLAGS) hex.o hexFuncs.o

# Unit test program for assembly language functions
hexTest : hexTest.o hexFuncs.o tctest.o
	gcc -o $@ $(LDFLAGS) hexTest.o hexFuncs.o tctest.o

# This target creates a zipfile (solution.zip) that can be uploaded
# to Gradescope.
solution.zip : $(SUBMIT_FILES)
	rm -f $@
	zip -9r $@ $(SUBMIT_FILES)

# Clean up generated files (such as object files and executables)
clean :
	rm -f *.s *.o $(EXES) depend.mak solution.zip

depend.mak :
	touch $@

# This target generates C header file dependencies (so that C modules
# get recompiled whenever their source or included header files get
# modified).
depend :
	gcc -M $(CFLAGS) $(C_SRCS) >> depend.mak

include depend.mak
