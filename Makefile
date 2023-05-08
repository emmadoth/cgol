WARN = -Wall -Wextra -Wconversion -Wvla

default:
	$(CC) $(WARN) main.c -o cgol

debug:
	$(CC) $(WARN) -g3 main.c -o cgol

run: default
	./cgol
