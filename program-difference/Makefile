all: difference

difference: difference.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a \
../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a
	g++ -L../lib -o $@ $< -lapplication -lcommands -laudiofiles -lwaveform -lenvelope -linstrument

difference.o: difference.cpp ../include/difference_aux.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o difference