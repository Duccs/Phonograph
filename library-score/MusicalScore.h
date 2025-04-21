#ifndef _MUSICALSCORE_H_
#define _MUSICALSCORE_H_

#include "Waveforms.h"
#include "Envelopes.h"
#include "Instrumentarium.h"

class MusicalScore {

    protected:
        Waveforms waveforms;
        Envelopes envelopes;
        Instrumentarium instrumentarium;

    public:
        MusicalScore();
        Waveforms& getWaveforms();
        const Waveforms& getWaveforms() const;

        Envelopes& getEnvelopes();
        const Envelopes& getEnvelopes() const;

        Instrumentarium& getInstrumentarium();
        const Instrumentarium& getInstrumentarium() const;
};

#endif /* _MUSICALSCORE_H_ */