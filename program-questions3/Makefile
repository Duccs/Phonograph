all: questions3

questions3: questions3.o ../lib/libapplication.a ../lib/libcommands.a
	g++ -L../lib -o $@ $< -lcommands -lapplication

questions3.o: questions3.cpp ../include/questions3_aux.h ../include/ApplicationData.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o questions3