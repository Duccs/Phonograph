# Build the library here
all: libscore-io.a

libscore-io.a: ScoreReader.o ScoreWriter.o
	ar crus $@ $^

ScoreReader.o: ScoreReader.cpp ScoreReader.h ../include/MusicalScore.h
	g++ -I ../include -o $@ -c $<

ScoreWriter.o: ScoreWriter.cpp ScoreWriter.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libscore-io.a ../include/ScoreReader.h ../include/ScoreWriter.h

../lib/libscore-io.a: libscore-io.a
	cp $< $@

../include/ScoreReader.h: ScoreReader.h
	cp $< $@

../include/ScoreWriter.h: ScoreWriter.h
	cp $< $@
	
clean:
	-rm -f *.o libscore-io.a
