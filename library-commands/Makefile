# Build the library here
all: libcommands.a

libcommands.a: questions3_aux.o audio_track_creator_aux.o wav_file_creator_aux.o difference_aux.o multi_track_creator_aux.o waveform_test_aux.o envelope_test_aux.o instrument_test_aux.o
	ar crus $@ $^ 

wav_file_creator_aux.o: wav_file_creator_aux.cpp wav_file_creator_aux.h ../include/AudioTrack.h ../include/WAVFile.h ../include/ApplicationData.h
	g++ -I ../include -o $@ -c $<

audio_track_creator_aux.o: audio_track_creator_aux.cpp audio_track_creator_aux.h ../include/AudioTrack.h ../include/ApplicationData.h
	g++ -I ../include -o $@ -c $<

questions3_aux.o: questions3_aux.cpp questions3_aux.h ../include/ApplicationData.h
	g++ -I ../include -o $@ -c $<

difference_aux.o: difference_aux.cpp difference_aux.h ../include/ApplicationData.h
	g++ -I ../include -o $@ -c $<

multi_track_creator_aux.o: multi_track_creator_aux.cpp multi_track_creator_aux.h ../include/AudioTrack.h ../include/ApplicationData.h ../include/WAVFile.h
	g++ -I ../include -o $@ -c $<

waveform_test_aux.o: waveform_test_aux.cpp waveform_test_aux.h ../include/AudioTrack.h ../include/ApplicationData.h ../include/WAVFile.h ../include/Waveform.h ../include/SineWaveform.h ../include/SquareWaveform.h
	g++ -I ../include -o $@ -c $<

envelope_test_aux.o: envelope_test_aux.cpp envelope_test_aux.h ../include/AudioTrack.h ../include/ApplicationData.h ../include/Envelope.h ../include/ADSREnvelope.h ../include/ADEnvelope.h
	g++ -I ../include -o $@ -c $<

instrument_test_aux.o: instrument_test_aux.cpp instrument_test_aux.h ../include/AudioTrack.h ../include/ApplicationData.h ../include/Instrument.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libcommands.a ../include/questions3_aux.h ../include/audio_track_creator_aux.h ../include/wav_file_creator_aux.h ../include/difference_aux.h ../include/multi_track_creator_aux.h ../include/waveform_test_aux.h ../include/envelope_test_aux.h ../include/instrument_test_aux.h

../lib/libcommands.a: libcommands.a
	cp $< $@

../include/questions3_aux.h: questions3_aux.h
	cp $< $@

../include/audio_track_creator_aux.h: audio_track_creator_aux.h
	cp $< $@

../include/wav_file_creator_aux.h: wav_file_creator_aux.h
	cp $< $@

../include/difference_aux.h: difference_aux.h
	cp $< $@

../include/multi_track_creator_aux.h: multi_track_creator_aux.h
	cp $< $@

../include/waveform_test_aux.h: waveform_test_aux.h
	cp $< $@

../include/envelope_test_aux.h: envelope_test_aux.h
	cp $< $@

../include/instrument_test_aux.h: instrument_test_aux.h
	cp $< $@

clean:
	-rm -f *.o libcommands.a

