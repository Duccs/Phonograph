#include "MusicalStaff.h"

MusicalStaff::MusicalStaff() : name(""), instrument(nullptr), notes() {}

MusicalStaff::MusicalStaff(std::shared_ptr<Instrument> instrument) 
    : name(""), instrument(instrument), notes() {}

MusicalStaff::MusicalStaff(const std::string& name, std::shared_ptr<Instrument> instrument) 
    : name(name), instrument(instrument), notes() {}

MusicalStaff::MusicalStaff(const MusicalStaff& src) 
    : name(src.name), instrument(src.instrument), notes(src.notes) {}

MusicalStaff::~MusicalStaff() {}

std::string MusicalStaff::toString() const 
    { return name + " " + instrument->getName(); }

const std::string& MusicalStaff::getName() const{ return name;}

void MusicalStaff::setName(const std::string& name) { this->name = name; }

std::shared_ptr<Instrument> MusicalStaff::getInstrument() { return instrument; }

std::shared_ptr<const Instrument> MusicalStaff::getInstrument() const { return instrument; }

void MusicalStaff::setInstrument(std::shared_ptr<Instrument> instrument) { this->instrument = instrument; }

void MusicalStaff::addNote(const StaffNote& note) { 
    notes.push_back(note); 
}

const std::vector<StaffNote>& MusicalStaff::getNotes() const { return notes; }

double MusicalStaff::getDurationInWholeNotes() const {
    double max_finish = 0.0;
    for (const StaffNote& sn : notes) {
        double finish = sn.getStart() + sn.getNote().getDuration();
        if (finish > max_finish) {
            max_finish = finish;
        }
    }
    return max_finish;
}

void MusicalStaff::render(const TimeSignature& time_signature, const double tempo, const int samples_per_second, AudioTrack& track) const {
    // 1. Calculate seconds per whole note and total seconds needed
    double seconds_per_whole_note = time_signature.getBeatValue() * 60.0 / tempo;
    double total_seconds = getDurationInWholeNotes() * seconds_per_whole_note;

    // 2. Resize the aggregator track
    track.setSize(samples_per_second, total_seconds);

    // 3. For each note, generate and add samples
    for (const StaffNote& sn : notes) {
        double note_start_seconds = sn.getStart() * seconds_per_whole_note;
        double note_duration_seconds = sn.getNote().getDuration() * seconds_per_whole_note;

        // Generate samples for this note
        AudioTrack temp_track;
        instrument->generateSamples(
            sn.getNote().getFrequency(),
            note_duration_seconds,
            samples_per_second,
            temp_track
        );

        // Add samples to main track at correct offset using addAt
        track.addAt(temp_track, note_start_seconds);
    }
}

std::ostream& operator<<(std::ostream& output_stream, const MusicalStaff& staff) {
    output_stream << staff.toString();
    return output_stream;
}