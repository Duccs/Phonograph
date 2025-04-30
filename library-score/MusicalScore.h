#ifndef _MUSICALSCORE_H_
#define _MUSICALSCORE_H_

#include "Waveforms.h"
#include "Envelopes.h"
#include "Instrumentarium.h"
#include "MusicalStaves.h"
#include "TimeSignature.h"

class MusicalScore {

    protected:
        Waveforms waveforms;
        Envelopes envelopes;
        Instrumentarium instrumentarium;
        MusicalStaves staves;
        TimeSignature time_signature;
        double tempo;

    public:
        MusicalScore();
        MusicalScore(const TimeSignature& time_signature, const double tempo);

        TimeSignature& getTimeSignature();
        const TimeSignature& getTimeSignature() const;
        double getTempo() const;
        void setTempo(const double tempo);
        void setTimeSignature(const TimeSignature& time_signature);

        Waveforms& getWaveforms();
        const Waveforms& getWaveforms() const;

        Envelopes& getEnvelopes();
        const Envelopes& getEnvelopes() const;

        Instrumentarium& getInstrumentarium();
        const Instrumentarium& getInstrumentarium() const;

        void addStaff(const MusicalStaff& staff);
        MusicalStaff& getStaff(const std::string& name);
        const MusicalStaff& getStaff(const std::string& name) const;

        MusicalStaves& getStaves();
        const MusicalStaves& getStaves() const;

        void renderStaff(const MusicalStaff& staff, const int samples_per_second, AudioTrack& track) const; 
        void renderStaves(const int samples_per_second, std::map<std::string, AudioTrack>& tracks) const;
        void renderWavChannels(const int samples_per_second, std::vector<AudioTrack>& channels) const;
};

#endif /* _MUSICALSCORE_H_ */