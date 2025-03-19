# Build the library here
all: libenvelope.a

libenvelope.a: Envelope.o ADSREnvelope.o ADEnvelope.o Envelopes.o EnvelopeFactory.o
	ar crus $@ $^

Envelope.o: Envelope.cpp Envelope.h ../include/AudioTrack.h
	g++ -I ../include -o $@ -c $<

ADSREnvelope.o: ADSREnvelope.cpp ADSREnvelope.h
	g++ -I ../include -o $@ -c $<

ADEnvelope.o: ADEnvelope.cpp ADEnvelope.h
	g++ -I ../include -o $@ -c $<

Envelopes.o: Envelopes.cpp Envelopes.h
	g++ -I ../include -o $@ -c $<

EnvelopeFactory.o: EnvelopeFactory.cpp EnvelopeFactory.h 
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libenvelope.a ../include/Envelope.h ../include/ADSREnvelope.h ../include/ADEnvelope.h ../include/Envelopes.h ../include/EnvelopeFactory.h

../lib/libenvelope.a: libenvelope.a
	cp $< $@

../include/Envelope.h: Envelope.h
	cp $< $@

../include/ADSREnvelope.h: ADSREnvelope.h
	cp $< $@

../include/ADEnvelope.h: ADEnvelope.h
	cp $< $@

../include/Envelopes.h: Envelopes.h
	cp $< $@

../include/EnvelopeFactory.h: EnvelopeFactory.h
	cp $< $@

clean:
	-rm -f *.o libenvelope.a
