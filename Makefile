SRC    = main.c terminal.c display.c fileio.c cursor.c editor.c
TARGET = mango
CFLAGS = -Wall -Wextra -O2

ifeq ($(OS),Windows_NT)
    CC     = gcc
    EXT    = .exe
    RM     = del
else
    CC     = x86_64-w64-mingw32-gcc
    EXT    = .exe
    RM     = rm -f
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET)$(EXT) $(SRC) -luser32

clean:
	$(RM) $(TARGET)$(EXT)

run: $(TARGET)
	./$(TARGET)$(EXT)