CC=g++
CPPFLAGS=-c -g -Wall
LDFLAGS=-lm

OBJ = ./obj
INC = ./inc
BIN = ./bin
SRC = ./src
ETC = ./etc

all: calc2

#Target: dependcies
#	cmd to get the traget using dependencies

calc2: $(OBJ)/calcMain.o $(OBJ)/add.o $(OBJ)/sub.o $(OBJ)/mul.o
	$(CC) -o calc2 $(OBJ)/calcMain.o $(OBJ)/add.o $(OBJ)/sub.o $(OBJ)/mul.o
	mv calc2 $(BIN)/

$(OBJ)/calcMain.o: $(SRC)/calcMain.cpp
	$(CC) $(CPPFLAGS) $(SRC)/calcMain.cpp -o $(OBJ)/calcMain.o -I$(INC)/

$(OBJ)/add.o: $(SRC)/add.cpp
	$(CC) $(CPPFLAGS) $(SRC)/add.cpp -o $(OBJ)/add.o -I$(INC)/

$(OBJ)/sub.o: $(SRC)/sub.cpp
	$(CC) $(CPPFLAGS) $(SRC)/sub.cpp -o $(OBJ)/sub.o -I$(INC)/

$(OBJ)/mul.o: $(SRC)/mul.cpp
	$(CC) $(CPPFLAGS) $(SRC)/mul.cpp -o $(OBJ)/mul.o -I$(INC)/

clean:
	@echo "Cleaning is in progress"
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*
	rm -f a.out
	@echo "Cleaning Done!"


