all: waveform_test

waveform_test: waveform_test.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a \
../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libscore.a
	g++ -L../lib -o $@ $<  -lcommands -laudiofiles -lapplication -lwaveform -lenvelope -linstrument -lscore

waveform_test.o: waveform_test.cpp ../include/waveform_test_aux.h ../include/WAVFile.h ../include/ApplicationData.h ../include/AudioTrack.h ../include/Waveform.h ../include/SineWaveform.h ../include/SquareWaveform.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o waveform_test