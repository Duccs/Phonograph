#include "Instrument.h"

Instrument::Instrument() {}

Instrument::Instrument(const std::string& name, std::shared_ptr<Waveform> waveform, std::shared_ptr<Envelope> envelope) 
    : name(name), waveform(waveform), envelope(envelope) {}

Instrument::~Instrument() {}

const std::string& Instrument::getName() const { return name; }

std::shared_ptr<Waveform> Instrument::getWaveform() const { return waveform; }

std::shared_ptr<Envelope> Instrument::getEnvelope() const { return envelope; }

void Instrument::setName(const std::string& name) { this->name = name; }

void Instrument::setWaveform(std::shared_ptr<Waveform> waveform) { this->waveform = waveform; }

void Instrument::setEnvelope(std::shared_ptr<Envelope> envelope) { this->envelope = envelope; }

void Instrument::generateSamples(const double frequency, const double seconds, const int samples_per_second, AudioTrack& track) const {
    AudioTrack waveform_track, envelope_track;
    waveform->generateSamples(frequency, seconds, samples_per_second, waveform_track);
    envelope->generateAmplitudes(seconds, samples_per_second, envelope_track);

    printf("Waveform track size: %d\n", waveform_track.getSize());
    printf("Envelope track size: %d\n", envelope_track.getSize());
    track = waveform_track * envelope_track;
}