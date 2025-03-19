# Build the library here
all: libinstrument.a

libinstrument.a: Instrument.o Instrumentarium.o
	ar crus $@ $^

Instrument.o: Instrument.cpp Instrument.h ../include/AudioTrack.h ../include/Envelope.h ../include/Waveform.h ../include/SineWaveform.h ../include/SquareWaveform.h ../include/ADEnvelope.h
	g++ -I ../include -o $@ -c $<

Instrumentarium.o: Instrumentarium.cpp Instrumentarium.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libinstrument.a ../include/Instrument.h ../include/Instrumentarium.h

../lib/libinstrument.a: libinstrument.a
	cp $< $@

../include/Instrument.h: Instrument.h
	cp $< $@

../include/Instrumentarium.h: Instrumentarium.h
	cp $< $@
	
clean:
	-rm -f *.o libinstrument.a
