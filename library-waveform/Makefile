# Build the library here
all: libwaveform.a

libwaveform.a: Waveform.o SineWaveform.o SquareWaveform.o Waveforms.o
	ar crus $@ $^ 

Waveform.o: Waveform.cpp Waveform.h ../include/AudioTrack.h
	g++ -I ../include -o $@ -c $<

SineWaveform.o: SineWaveform.cpp SineWaveform.h
	g++ -I ../include -o $@ -c $<

SquareWaveform.o: SquareWaveform.cpp SquareWaveform.h
	g++ -I ../include -o $@ -c $<

Waveforms.o: Waveforms.cpp Waveforms.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libwaveform.a ../include/Waveform.h ../include/SineWaveform.h ../include/SquareWaveform.h ../include/Waveforms.h

../lib/libwaveform.a: libwaveform.a
	cp $< $@

../include/Waveform.h: Waveform.h
	cp $< $@

../include/SineWaveform.h: SineWaveform.h
	cp $< $@

../include/SquareWaveform.h: SquareWaveform.h
	cp $< $@

../include/Waveforms.h: Waveforms.h
	cp $< $@

clean:
	-rm -f *.o libwaveform.a
