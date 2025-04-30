all: instrument_test

instrument_test: instrument_test.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a ../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libscore.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -lscore-io -lscore -linstrument -lenvelope -lwaveform  -laudiofiles

instrument_test.o: instrument_test.cpp ../include/instrument_test_aux.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o questions3