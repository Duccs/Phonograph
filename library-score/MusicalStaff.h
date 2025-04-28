#ifndef _MUSICAL_STAFF_H_
#define _MUSICAL_STAFF_H_

#include <string>
#include <vector>
#include <memory>
#include "Instrument.h"
#include "TimeSignature.h"
#include "StaffNote.h"

class MusicalStaff {
    protected:
        std::string name;
        std::shared_ptr<Instrument> instrument;
        std::vector<StaffNote> notes;
    public:
        MusicalStaff();
        MusicalStaff(std::shared_ptr<Instrument> instrument);
        MusicalStaff(const std::string& name, std::shared_ptr<Instrument> instrument);
        MusicalStaff(const MusicalStaff& src);
        virtual ~MusicalStaff();

        MusicalStaff& operator=(const MusicalStaff& rhs) = default;
        virtual std::string toString() const;

        const std::string& getName() const;
        void setName(const std::string& name);

        std::shared_ptr<Instrument> getInstrument();
        std::shared_ptr<const Instrument> getInstrument() const;
        void setInstrument(std::shared_ptr<Instrument> instrument);

        void addNote(const StaffNote& note);
        const std::vector<StaffNote>& getNotes() const;

        double getDurationInWholeNotes() const;

        void render(const TimeSignature& time_signature, const double tempo, const int samples_per_second, AudioTrack& track) const;
};

std::ostream& operator<<(std::ostream& output_stream, const MusicalStaff& staff);

#endif /* _MUSICAL_STAFF_H_ */