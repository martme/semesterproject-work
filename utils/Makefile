all: bin/main

clean:
	rm -rf bin

bin:
	mkdir -p bin

bin/main: src/*.c | bin
	cc $+ -o $@

.PHONY: all
