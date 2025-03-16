# Build the library here
all: libenvelope.a

libenvelope.a: Envelope.o ADSREnvelope.o ADEnvelope.o
	ar crus $@ $^

Envelope.o: Envelope.cpp Envelope.h ../include/AudioTrack.h
	g++ -I ../include -o $@ -c $<

ADSREnvelope.o: ADSREnvelope.cpp ADSREnvelope.h
	g++ -I ../include -o $@ -c $<

ADEnvelope.o: ADEnvelope.cpp ADEnvelope.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libenvelope.a ../include/Envelope.h ../include/ADSREnvelope.h ../include/ADEnvelope.h

../lib/libenvelope.a: libenvelope.a
	cp $< $@

../include/Envelope.h: Envelope.h
	cp $< $@

../include/ADSREnvelope.h: ADSREnvelope.h
	cp $< $@

../include/ADEnvelope.h: ADEnvelope.h
	cp $< $@

clean:
	-rm -f *.o libenvelope.a
