all: instrument_designer

instrument_designer: instrument_designer.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a \
../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libscore.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -lscore-io -lscore -linstrument -lenvelope -lwaveform  -laudiofiles

instrument_designer.o: instrument_designer.cpp ../include/instrument_designer_aux.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o instrument_designer