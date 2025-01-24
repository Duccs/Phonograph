# Build the library here
all: libcommands.a

libcommands.a: questions3_aux.o
	ar crus $@ $^

questions3_aux.o: questions3_aux.cpp questions3_aux.h ../include/ApplicationData.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libcommands.a ../include/questions3_aux.h

../lib/libcommands.a: libcommands.a
	cp $< $@

../include/questions3_aux.h: questions3_aux.h
	cp $< $@

clean:
	-rm -f *.o libcommands.a

