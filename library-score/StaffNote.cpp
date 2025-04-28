#include "StaffNote.h"

StaffNote::StaffNote() : note(), start(0.0) {}

StaffNote::StaffNote(const Note& note, const double start) : note(note), start(start) {}

Note& StaffNote::getNote() {
    return note;
}

const Note& StaffNote::getNote() const {
    return note;
}

double StaffNote::getStart() const {
    return start;
}

void StaffNote::setStart(const double start) {
    if(start > 0.0){
        this->start = start;
    }
}

std::ostream& operator<<(std::ostream& os, const StaffNote& staff_note) {
    os << staff_note.getStart() << " " 
       << staff_note.getNote().getName() << " " 
       << staff_note.getNote().getDuration();
    return os;
}
