IDIR=src/include
CFBHDR=$(wildcard $(IDIR)/*.h)
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -Wall

ODIR=out

all: out/ieot out/cfb

out/ieot: samples/IEOpenedTabParser/openedtab.cpp samples/IEOpenedTabParser/IEOpenedTabParser.h $(CFBHDR)
	mkdir -p out
	$(CC) -o $@ $< $(CFLAGS)

out/cfb: samples/cfb/cfb.cpp $(CFBHDR)
	mkdir -p out
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf out
