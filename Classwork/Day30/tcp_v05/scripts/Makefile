CC = g++
CPPFLAGS = -c -g -Wall
LDFLAGS = -o

INC = ./inc
SRC = ./src
OBJ = ./obj
BIN = ./bin

all: $(BIN)/Server $(BIN)/Client

$(BIN)/Server: $(OBJ)/mainServer.o $(OBJ)/common.o
	$(CC) $(LDFLAGS) $(BIN)/Server $(OBJ)/mainServer.o $(OBJ)/common.o


$(OBJ)/mainServer.o: $(SRC)/mainServer.cpp
	$(CC) $(CPPFLAGS) $(SRC)/mainServer.cpp -I $(INC)
	mv *.o $(OBJ)/

$(OBJ)/common.o: $(SRC)/common.cpp
	$(CC) $(CPPFLAGS) $(SRC)/common.cpp -I $(INC)
	mv *.o $(OBJ)/

$(BIN)/Client: $(OBJ)/mainClient.o $(OBJ)/common.o
	$(CC) $(LDFLAGS) $(BIN)/Client $(OBJ)/mainClient.o $(OBJ)/common.o


$(OBJ)/mainClient.o: $(SRC)/mainClient.cpp
	$(CC) $(CPPFLAGS) $(SRC)/mainClient.cpp -I $(INC)
	mv *.o $(OBJ)/


clean:
	@echo "Cleaning started"
	rm -f a.out Server Client
	rm -f $(BIN)/*
	rm -f $(OBJ)/*.o
	rm -f *.o
	@echo "Cleaning Done!"



