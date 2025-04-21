#include "MusicalScore.h"

MusicalScore::MusicalScore(): waveforms(), envelopes(), instrumentarium() {}

Waveforms& MusicalScore::getWaveforms() { return waveforms; }
const Waveforms& MusicalScore::getWaveforms() const { return waveforms; }

Envelopes& MusicalScore::getEnvelopes() { return envelopes; }
const Envelopes& MusicalScore::getEnvelopes() const { return envelopes; }

Instrumentarium& MusicalScore::getInstrumentarium() { return instrumentarium; }
const Instrumentarium& MusicalScore::getInstrumentarium() const { return instrumentarium; }