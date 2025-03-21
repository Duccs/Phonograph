# Build the library here
all: libapplication.a

libapplication.a: ApplicationData.o ActionFunctionData.o MenuData.o
	ar crus $@ $^

ApplicationData.o: ApplicationData.cpp ApplicationData.h ../include/AudioTrack.h
	g++ -I ../include -o $@ -c $<

ActionFunctionData.o: ActionFunctionData.cpp ActionFunctionData.h
	g++ -I ../include -o $@ -c $<

MenuData.o: MenuData.cpp MenuData.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libapplication.a ../include/ApplicationData.h ../include/ActionFunctionData.h ../include/MenuData.h

../lib/libapplication.a: libapplication.a
	cp $< $@

../include/ApplicationData.h: ApplicationData.h
	cp $< $@

../include/ActionFunctionData.h: ActionFunctionData.h
	cp $< $@

../include/MenuData.h: MenuData.h
	cp $< $@

clean:
	-rm -f *.o libapplication.a
