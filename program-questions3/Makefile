all: questions3

questions3: questions3.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -laudiofiles

questions3.o: questions3.cpp ../include/questions3_aux.h ../include/ApplicationData.h ../include/AudioTrack.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o questions3