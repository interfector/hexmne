# hxs
PREF=/usr/local/bin
VERSION=1.2.2
OPTS=-Wall -pedantic -O3 -I./include -DVERSION=\"${VERSION}\" -lc
PROG=hxs
SRCDIR=src

all:
	g++ $(OPTS) -o $(PROG) $(SRCDIR)/main.cpp $(SRCDIR)/SymClass.cpp
clean:
	rm $(PROG)
install:
	cp $(PROG) $(PREF)
