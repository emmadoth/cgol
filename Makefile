WARN = -Wall -Wextra -Wconversion
LINK = -lncurses

default:
	$(CC) $(WARN) $(LINK)     main.c -o cgol

debug:
	$(CC) $(WARN) $(LINK) -g3 main.c -o cgol

run: default
	./cgol
