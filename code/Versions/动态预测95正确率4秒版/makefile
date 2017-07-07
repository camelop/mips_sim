CC = g++
CFLAGS = -Wall -std=c++11 -O2 -m32

################!! MODIFY HERE !!####################
_OBJ = mips_sim.o
_DEPS = Pack.hpp line.hpp program.hpp CPU.hpp oracle.hpp
#####################################################

ODIR = obj
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

IDIR = .
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.c* $(DEPS)
	$(shell mkdir -p bin)
	$(shell mkdir -p obj)
	$(CC) -c -o $@ $< $(CFLAGS)

mips: $(OBJ)
	$(CC) -o bin/mips $^ $(CFLAGS)

.PHONY: clean all rebuild

clean:
	rm -f $(ODIR)/*
	rm -f bin/*

all:
	mips

rebuild: clean all
