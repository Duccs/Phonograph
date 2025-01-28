all: audio_track_creator

audio_track_creator: audio_track_creator.o ../lib/libaudio.a ../lib/libapplication.a ../lib/libcommands.a
	g++ -L../lib -o $@ $< -lcommands -lapplication

audio_track_creator.o: audio_track_creator.cpp ../include/audio_track_creator_aux.h  ../include/AudioTrack.h ../include/ApplicationData.h 
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o audio_track_creator