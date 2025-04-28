# Build the library here
all: libscore.a

libscore.a: MusicalScore.o TimeSignature.o Frequency.o Note.o StaffNote.o MuiscalStaff.o
	ar crus $@ $^

MusicalScore.o: MusicalScore.cpp MusicalScore.h ../include/Waveforms.h
	g++ -I ../include -o $@ -c $<

TimeSignature.o: TimeSignature.cpp TimeSignature.h
	g++ -I ../include -o $@ -c $<

Frequency.o: Frequency.cpp Frequency.h
	g++ -I ../include -o $@ -c $<

Note.o: Note.cpp Note.h
	g++ -I ../include -o $@ -c $<

StaffNote.o: StaffNote.cpp StaffNote.h
	g++ -I ../include -o $@ -c $<

MuiscalStaff.o: MusicalStaff.cpp MusicalStaff.h
	g++ -I ../include -o $@ -c $<

# Install the library for other parts of the project to use
install: ../lib/libscore.a ../include/MusicalScore.h ../include/TimeSignature.h ../include/Frequency.h \
../include/Note.h ../include/StaffNote.h ../include/MusicalStaff.h

../lib/libscore.a: libscore.a
	cp $< $@

../include/MusicalScore.h: MusicalScore.h
	cp $< $@

../include/TimeSignature.h: TimeSignature.h
	cp $< $@
	
../include/Frequency.h: Frequency.h
	cp $< $@

../include/Note.h: Note.h
	cp $< $@

../include/StaffNote.h: StaffNote.h
	cp $< $@

../include/MusicalStaff.h: MusicalStaff.h
	cp $< $@

clean:
	-rm -f *.o libscore.a
