all: menu_test

menu_test: menu_test.o ../lib/libapplication.a ../lib/libcommands.a \
../lib/libaudiofiles.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libwaveform.a ../lib/libscore.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -lscore-io -lscore -linstrument -lenvelope -lwaveform  -laudiofiles

menu_test.o: menu_test.cpp ../include/menu_test_aux.h ../include/ApplicationData.h \
../include/AudioTrack.h ../include/MenuData.h ../include/ActionFunctionData.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o menu_test