CC=gcc
CFLAGS=-Wall -g -O3

prog = \
       test_uv \
       test_uv_r \
       # end

.PHONY: all clean
all: $(prog)

clean:
	rm -fr $(prog)

test_uv: test_uv.c
	$(CC) $(CFLAGS) -o $@ $^ -I../../src/lib/ -lpthread -lhiredis -luv -L../../build/src/lib -lhiproxy

test_uv_r: test_uv_r.c
	$(CC) $(CFLAGS) -o $@ $^ -lpthread -lhiredis -luv
