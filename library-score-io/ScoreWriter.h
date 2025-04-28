#ifndef _SCORE_WRITER_H
#define _SCORE_WRITER_H

#include "MusicalScore.h"
#include "Note.h"
#include "StaffNote.h"
#include "MusicalStaff.h"

class ScoreWriter {
    public:
        ScoreWriter();
        virtual ~ScoreWriter();

        void writeScore(std::ostream& output_stream, const MusicalScore& score) const;
        void writeInstrument(std::ostream& output_stream, const MusicalScore& score, const Instrument& instrument) const;
        void writeEnvelope(std::ostream& output_stream, const MusicalScore& score, const Envelope& envelope) const;
        void writeWaveform(std::ostream& output_stream, const MusicalScore& score, const Waveform& waveform) const;

        void writeStaff(std::ostream& os, const MusicalScore& score, const MusicalStaff& staff) const;
        void writeStaffNote(std::ostream& os, const MusicalScore& score, const StaffNote& staff_note) const;
        std::string getDurationLetter(const double duration) const;
        std::string formatNote(const Note& note) const;
};

#endif /* _SCORE_WRITER_H */