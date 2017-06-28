all:test6

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread

Thread:test6.o
    $(CC) $(LDFLAGS) -o $@ $^

Thread.o:test6.cc
    $(CC) $(CPPFLAGS) -o $@ -c $^


.PHONY:
    clean

clean:
    rm test6.o test6