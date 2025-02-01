# Build the library here
all: libaudiofiles.a

libaudiofiles.a: AudioTrack.o endian_io.o WAVFile.o
	ar crus $@ $^

AudioTrack.o: AudioTrack.cpp AudioTrack.h
	g++ -o $@ -c $<

endian_io.o: endian_io.cpp endian_io.h
	g++ -o $@ -c $<

WAVFile.o: WAVFile.cpp WAVFile.h
	g++ -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libaudiofiles.a ../include/AudioTrack.h ../include/endian_io.h ../include/WAVFile.h

../lib/libaudiofiles.a: libaudiofiles.a
	cp $< $@

../include/AudioTrack.h: AudioTrack.h
	cp $< $@

../include/AudioTrack.h: endian_io.h
	cp $< $@

../include/AudioTrack.h: WAVFile.h
	cp $< $@

clean:
	-rm -f *.o libaudiofiles.a