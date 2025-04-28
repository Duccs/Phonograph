#ifndef _STAFF_NOTE_H_
#define _STAFF_NOTE_H_

#include "Note.h"

class StaffNote{
    protected:
        Note note;
        double start;
    public:
        StaffNote();
        StaffNote(const Note& note, const double start);
        Note& getNote();
        const Note& getNote() const;
        double getStart() const;
        void setStart(const double start);
};

std::ostream& operator<<(std::ostream& os, const StaffNote& staff_note);

#endif /* _STAFF_NOTE_H_ */