all: wav_file_creator

wav_file_creator: wav_file_creator.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a \
../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libscore.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -lscore-io -lscore -linstrument -lenvelope -lwaveform  -laudiofiles

wav_file_creator.o: wav_file_creator.cpp ../include/wav_file_creator_aux.h ../include/WAVFile.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o wav_file_creator