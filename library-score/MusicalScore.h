#ifndef _MUSICALSCORE_H_
#define _MUSICALSCORE_H_

#include "Waveforms.h"
#include "Envelopes.h"
#include "Instrumentarium.h"
#include "TimeSignature.h"

class MusicalScore {

    protected:
        Waveforms waveforms;
        Envelopes envelopes;
        Instrumentarium instrumentarium;
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
};

#endif /* _MUSICALSCORE_H_ */