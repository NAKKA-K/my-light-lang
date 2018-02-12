all:
	gcc -std=c11 -o bin/lightang src/lightang.c

test:
	tests/runtest

clean:
	rm -f bin/lightang
