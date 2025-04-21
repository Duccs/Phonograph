# Build the library here
all: libscore.a

libscore.a: MusicalScore.o
	ar crus $@ $^

MusicalScore.o: MusicalScore.cpp MusicalScore.h ../include/Waveforms.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libscore.a ../include/MusicalScore.h

../lib/libscore.a: libscore.a
	cp $< $@

../include/MusicalScore.h: MusicalScore.h
	cp $< $@
	
clean:
	-rm -f *.o libscore.a
