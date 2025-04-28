#include "ScoreWriter.h"
#include <ostream>
#include <cmath>

ScoreWriter::ScoreWriter() {}
ScoreWriter::~ScoreWriter() {}

void ScoreWriter::writeScore(std::ostream& output_stream, const MusicalScore& score) const {
    // Write SCORE keyword to start the score section
    output_stream << "SCORE" << std::endl;

    // Write time signature
    output_stream << "  TIME-SIGNATURE " << score.getTimeSignature().getBeatsPerBar() << " " << score.getTimeSignature().getBeatValue() << std::endl;
    
    // Write tempo
    output_stream << "  TEMPO " << score.getTempo() << std::endl;
    output_stream << "" << std::endl;
    
    // Write all waveforms
    Waveforms::const_iterator waveform_it;
    for (waveform_it = score.getWaveforms().begin(); waveform_it != score.getWaveforms().end(); ++waveform_it) {
        writeWaveform(output_stream, score, *waveform_it->second);
    }
    
    // Write all envelopes
    Envelopes::const_iterator envelope_it;
    for (envelope_it = score.getEnvelopes().begin(); envelope_it != score.getEnvelopes().end(); ++envelope_it) {
        writeEnvelope(output_stream, score, *envelope_it->second);
    }
    
    // Write all instruments
    Instrumentarium::const_iterator instrument_it;
    for (instrument_it = score.getInstrumentarium().begin(); instrument_it != score.getInstrumentarium().end(); ++instrument_it) {
        writeInstrument(output_stream, score, *instrument_it->second);
    }
    
    // Write SCORE-END keyword to end the score section
    output_stream << "SCORE-END" << std::endl;
}

void ScoreWriter::writeWaveform(std::ostream& output_stream, const MusicalScore& /*score*/, const Waveform& waveform) const {
    output_stream << "    WAVEFORM " << waveform.getName() << " " << waveform.getTypeName() << std::endl;
    output_stream << "      AMPLITUDE " << waveform.getAmplitude() << std::endl;
    output_stream << "    WAVEFORM-END" << std::endl;
    output_stream << "" << std::endl;
}

void ScoreWriter::writeEnvelope(std::ostream& output_stream, const MusicalScore& /*score*/, const Envelope& envelope) const {
    output_stream << "    ENVELOPE " << envelope.getName() << " " << envelope.getTypeName() << std::endl;

    // Try ADSR
    if (envelope.getTypeName() == "ADSR") {
        const ADSREnvelope* adsr = dynamic_cast<const ADSREnvelope*>(&envelope);
        output_stream << "      MAXIMUM-AMPLITUDE " << adsr->getMaximumAmplitude() << std::endl;
        output_stream << "      ATTACK-SECONDS " << adsr->getAttackSeconds() << std::endl;
        output_stream << "      DECAY-SECONDS " << adsr->getDecaySeconds() << std::endl;
        output_stream << "      SUSTAIN-AMPLITUDE " << adsr->getSustainAmplitude() << std::endl;
        output_stream << "      RELEASE-SECONDS " << adsr->getReleaseSeconds() << std::endl;
    }
    // Try AD
    else if (envelope.getTypeName() == "AD") {
        const ADEnvelope* ad = dynamic_cast<const ADEnvelope*>(&envelope);
        output_stream << "      MAXIMUM-AMPLITUDE " << ad->getMaximumAmplitude() << std::endl;
        output_stream << "      ATTACK-SECONDS " << ad->getAttackSeconds() << std::endl;
    }

    output_stream << "    ENVELOPE-END" << std::endl;
    output_stream << "" << std::endl;

}

void ScoreWriter::writeInstrument(std::ostream& output_stream, const MusicalScore& score, const Instrument& instrument) const{
    output_stream << "  INSTRUMENT " << instrument.getName() << std::endl;

    writeWaveform(output_stream, score, *instrument.getWaveform());
    writeEnvelope(output_stream, score, *instrument.getEnvelope());

    output_stream << "  INSTRUMENT-END" << std::endl;
    output_stream << "" << std::endl;
}

std::string ScoreWriter::getDurationLetter(const double duration) const {
    // Standard durations and their corresponding letters
    static const struct {
        double value;
        const char* letter;
    } duration_map[] = {
        {1.0 / 16.0, "s"},
        {1.0 / 8.0,  "e"},
        {1.0 / 4.0,  "q"},
        {1.0 / 2.0,  "h"},
        {1.0,        "w"}
    };

    double min_diff = std::abs(duration - duration_map[0].value);
    const char* result = duration_map[0].letter;

    for (size_t i = 1; i < sizeof(duration_map) / sizeof(duration_map[0]); ++i) {
        double diff = std::abs(duration - duration_map[i].value);
        if (diff < min_diff) {
            min_diff = diff;
            result = duration_map[i].letter;
        }
    }
    return std::string(result);
}

std::string ScoreWriter::formatNote(const Note& note) const{
    return getDurationLetter(note.getDuration()) + note.getName();
}

void ScoreWriter::writeStaffNote(std::ostream& os, const MusicalScore& score, const StaffNote& staff_note) const{
    os << "    " << staff_note.getStart() << " " << formatNote(staff_note.getNote()) << std::endl;
}

void ScoreWriter::writeStaff(std::ostream& os, const MusicalScore& score, const MusicalStaff& staff) const{
    os << "  STAFF " << staff.getName() << std::endl;
    for (const StaffNote& staff_note : staff.getNotes()) {
        writeStaffNote(os, score, staff_note);
    }
    os << "  END-STAFF" << std::endl;
    os << "" << std::endl;
}
