all: score_editor

score_editor: score_editor.o ../lib/libapplication.a ../lib/libcommands.a ../lib/libaudiofiles.a \
../lib/libwaveform.a ../lib/libenvelope.a ../lib/libinstrument.a ../lib/libscore.a ../lib/libscore-io.a
	g++ -L../lib -o $@ $< -lcommands -lapplication -lscore-io -lscore -linstrument -lenvelope -lwaveform  -laudiofiles

score_editor.o: score_editor.cpp ../include/score_editor_aux.h ../include/ApplicationData.h ../include/Instrument.h
	g++ -I../include -o $@ -c $<

clean:
	-rm -f *.o score_editor