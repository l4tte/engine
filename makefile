COMP=g++
COMPARGS=-Wall -std=c++17 
OUTPUT=rl
LIBS=-lsdl

LIBDIR=Lib/
INCLUDEDIR=Include/

compile:
	$(COMP) -L$(LIBDIR) -I$(INCLUDEDIR) $(LIBS) $(COMPARGS) -o $(OUTPUT) src/*.cpp
