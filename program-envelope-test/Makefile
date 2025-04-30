all: envelope_test

envelope_test: envelope_test.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a \
../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libscore.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -lscore-io -lscore -linstrument -lenvelope -lwaveform  -laudiofiles

envelope_test.o: envelope_test.cpp ../include/envelope_test_aux.h ../include/ApplicationData.h ../include/AudioTrack.h ../include/Envelope.h ../include/ADSREnvelope.h ../include/ADEnvelope.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o envelope_test