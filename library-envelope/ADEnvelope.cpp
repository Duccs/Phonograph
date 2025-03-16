#include "ADEnvelope.h"

ADEnvelope::ADEnvelope(const std::string& name) : ADSREnvelope(name, "AD", 1.0, 0.0, 0.0, 0.0, 0.0) {}

ADEnvelope::ADEnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds) : ADSREnvelope(name, "AD", maximum_amplitude, attack_seconds, 0.0, 0.0, 0.0) {}

ADEnvelope::~ADEnvelope() {}

void ADEnvelope::generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const {
    if (seconds < attack) {
        return;
    }

    track.setSize(samples_per_second, seconds);

    int attackSamples = static_cast<int>(attack * samples_per_second);
    int decaySamples = track.getSize() - attackSamples;
    double maximum_amplitude = getMaximumAmplitude();

    assignAttackAmplitudes(0, attackSamples, track, 0.0, maximum_amplitude);
    assignDecayAmplitudes(attackSamples, track.getSize(), track, maximum_amplitude, 0.0);
}