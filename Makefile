CC ?= cc
CFLAGS ?= -std=c17 -Wall -Wextra -Werror -pedantic -O2
THREAD_FLAGS ?= -pthread
SOURCES = src/main.c src/counter.c src/buffer.c src/deadlock.c

.PHONY: all clean
all: build/ps3

build/ps3: $(SOURCES) include/ps3.h | build
	$(CC) $(CFLAGS) $(THREAD_FLAGS) -Iinclude $(SOURCES) -o $@

build:
	mkdir -p build

clean:
	rm -f build/ps3
	rmdir build 2>/dev/null || true
