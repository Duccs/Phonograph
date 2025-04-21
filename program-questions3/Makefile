all: questions3

questions3: questions3.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a \
../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libscore.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -laudiofiles -lwaveform -lenvelope -linstrument -lscore

questions3.o: questions3.cpp ../include/questions3_aux.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o questions3