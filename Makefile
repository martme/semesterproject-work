all: bin/main

clean: 
	rm -rf bin

bin:
	mkdir -p bin

bin/main: src/*.c | bin
	cc $+ -framework Carbon -framework CoreServices -framework AudioUnit -framework AudioToolbox -framework CoreAudio /usr/local/lib/libportaudio.a -I/usr/local/include/ -o $@

.PHONY: all

