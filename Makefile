PORTAUDIO=/usr/local/lib/libportaudio.a
FFTW=/usr/local/lib/libfftw3f.a
FRAMEWORKS=-framework Carbon -framework CoreServices -framework AudioUnit -framework AudioToolbox -framework CoreAudio

all: bin/main

clean:
	rm -rf bin

bin:
	mkdir -p bin

bin/main: src/*.c | bin
	cc $+ $(FRAMEWORKS) $(PORTAUDIO) $(FFTW) -I/usr/local/include/ -o $@

.PHONY: all


