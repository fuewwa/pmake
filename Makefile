CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = pmake

ifeq ($(OS),Windows_NT)
BIN := pmake.exe
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ifeq ($(OS),Windows_NT)
install: $(BIN)
	copy $(BIN) C:\Windows\pmake.exe
clean:
	del /Q src\*.o $(BIN)
else
install: $(BIN)
	install -m 755 $(BIN) /usr/local/bin/pmake
clean:
	rm -f src/*.o $(BIN)
endif

.PHONY: all install clean
