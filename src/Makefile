CC=gcc
BIN=pomodoro

all:
	$(CC) $(CFLAGS) pomodoro.c -o $(BIN)

install:
	cp $(BIN) /usr/bin

uninstall:
	$(RM) /usr/bin/$(BIN)

clean:
	$(RM) $(BIN)
