# Project: DumpCore
# Makefile created by Dev-C++ 5.4.2

CPP      = g++ -D__DEBUG__
CC       = gcc -D__DEBUG__
OBJ      = obj/dumper.o obj/engine.o obj/main.o
LINKOBJ  = obj/dumper.o obj/engine.o obj/main.o
LIBS     = -static-libgcc -m32 -pg -g3
INCS     = -I"include"
CXXINCS  = -I"include"
BIN      = DumpCore
CXXFLAGS = $(CXXINCS) -m32 -std=c++11 -Wall -pg -g3
CFLAGS   = $(INCS) -m32 -std=c++11 -Wall -pg -g3
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

obj/dumper.o: src/dumper.cpp
	$(CPP) -c src/dumper.cpp -o obj/dumper.o $(CXXFLAGS)

obj/engine.o: src/engine.cpp
	$(CPP) -c src/engine.cpp -o obj/engine.o $(CXXFLAGS)

obj/main.o: src/main.cpp
	$(CPP) -c src/main.cpp -o obj/main.o $(CXXFLAGS)
