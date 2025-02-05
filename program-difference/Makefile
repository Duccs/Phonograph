all: difference

difference: difference.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a
	g++ -L../lib -o $@ $< -lapplication -lcommands -laudiofiles

difference.o: difference.cpp ../include/difference_aux.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o difference