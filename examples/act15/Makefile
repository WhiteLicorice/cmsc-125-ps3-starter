CC=cc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pthread

all: example
example: example.c
	$(CC) $(CFLAGS) -o $@ $<
check: example
	@./example > actual.txt
	@diff -u expected/run.txt actual.txt
	@echo "1 of 1 outputs match"
clean:
	rm -f example actual.txt
.PHONY: all check clean
