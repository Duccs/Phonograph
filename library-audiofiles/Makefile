# Build the library here
all: libaudiofiles.a

libaudiofiles.a: AudioTrack.o
	ar crus $@ $^

AudioTrack.o: AudioTrack.cpp AudioTrack.h
	g++ -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libaudiofiles.a ../include/AudioTrack.h

../lib/libaudiofiles.a: libaudiofiles.a
	cp $< $@

../include/AudioTrack.h: AudioTrack.h
	cp $< $@


clean:
	-rm -f *.o libaudiofiles.a