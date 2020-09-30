# Copyright (c) 2020, Ari Eythorsson
# See LICENSE.txt for more information

COMP=g++
COMPARGS=-Wall -std=c++17 -O1 -pthread
OUTPUT=rl
LIBS=-lsdl2

LIBDIR=Lib/
INCLUDEDIR=Include/

compile:
	$(COMP) -L$(LIBDIR) -I$(INCLUDEDIR) $(LIBS) $(COMPARGS) -o $(OUTPUT) src/*.cpp
