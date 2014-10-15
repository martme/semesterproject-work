PORTAUDIO=/usr/local/lib/libportaudio.a
LIBSNDFILE=/usr/local/lib/libsndfile.a /usr/local/lib/libvorbis.a /usr/local/lib/libogg.a /usr/local/lib/libvorbisfile.a /usr/local/lib/libvorbisenc.a /usr/local/lib/libflac.a
FFTW=/usr/local/lib/libfftw3f.a
FRAMEWORKS=-framework Carbon -framework CoreServices -framework AudioUnit -framework AudioToolbox -framework CoreAudio
DEPENDENCIES=$(FRAMEWORKS) $(PORTAUDIO) $(LIBSNDFILE) $(FFTW) -I /usr/local/include/
LINUX_DEPENDENCIES=-lm -lfftw3f -lsndfile


all: bin/main

clean:
	rm -rf bin

bin:
	mkdir -p bin

bin/main: src/*.c | bin
	cc $+ $(LINUX_DEPENDENCIES) -o $@

.PHONY: all
