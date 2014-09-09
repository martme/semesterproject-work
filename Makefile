all: bin/main

clean: 
	rm -rf bin

# For linux, something like this
# bin/main: src/*.c | bin
# 	cc $+ -lrt -ljack -lasound -lpthread /usr/local/lib/libportaudio.a -I/usr/local/include/ -o $@


bin:
	mkdir -p bin

bin/main: src/*.c | bin
	cc $+ -framework Carbon -framework CoreServices -framework AudioUnit -framework AudioToolbox -framework CoreAudio /usr/local/lib/libportaudio.a -I/usr/local/include/ -o $@

.PHONY: all
