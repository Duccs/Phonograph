#include "MusicalScore.h"

MusicalScore::MusicalScore(): waveforms(), envelopes(), instrumentarium(), time_signature(), tempo(100) {}
MusicalScore::MusicalScore(const TimeSignature& time_signature, const double tempo) : 
    waveforms(), envelopes(), instrumentarium(), time_signature(time_signature), tempo(tempo) {}

TimeSignature& MusicalScore::getTimeSignature() { return time_signature; }
const TimeSignature& MusicalScore::getTimeSignature() const { return time_signature; }
double MusicalScore::getTempo() const { return tempo; }
void MusicalScore::setTempo(const double tempo) { 
    if (tempo > 0)
    { this->tempo = tempo; }
}
void MusicalScore::setTimeSignature(const TimeSignature& time_signature) { this->time_signature = time_signature; }

Waveforms& MusicalScore::getWaveforms() { return waveforms; }
const Waveforms& MusicalScore::getWaveforms() const { return waveforms; }

Envelopes& MusicalScore::getEnvelopes() { return envelopes; }
const Envelopes& MusicalScore::getEnvelopes() const { return envelopes; }

Instrumentarium& MusicalScore::getInstrumentarium() { return instrumentarium; }
const Instrumentarium& MusicalScore::getInstrumentarium() const { return instrumentarium; }