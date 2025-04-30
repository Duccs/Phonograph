all: multi_track_creator

multi_track_creator: multi_track_creator.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a \
../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libscore.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -lscore-io -lscore -linstrument -lenvelope -lwaveform  -laudiofiles

multi_track_creator.o: multi_track_creator.cpp ../include/multi_track_creator_aux.h ../include/WAVFile.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o multi_track_creator