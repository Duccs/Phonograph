#include "ADSREnvelope.h"

ADSREnvelope::ADSREnvelope(const std::string& name, const std::string& type_name): Envelope(name, type_name), attack(0.0), decay(0.0), sustain(0.5), release(0.0) {}

ADSREnvelope::ADSREnvelope(const std::string& name, const std::string& type_name, const double maximum_amplitude, const double attack_seconds, const double decay_seconds, const double sustain_amplitude, const double release_seconds):
    Envelope(name, type_name, maximum_amplitude), attack(attack_seconds), decay(decay_seconds), sustain(sustain_amplitude), release(release_seconds) {}

ADSREnvelope::ADSREnvelope(const std::string& name): Envelope(name, "ADSR"), attack(0.0), decay(0.0), sustain(0.5), release(0.0) {}

ADSREnvelope::ADSREnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds, const double decay_seconds, const double sustain_amplitude, const double release_seconds):
    Envelope(name, "ADSR", maximum_amplitude), attack(attack_seconds), decay(decay_seconds), sustain(sustain_amplitude), release(release_seconds) {}

ADSREnvelope::~ADSREnvelope() {}

double ADSREnvelope::getAttackSeconds() const { return attack; }
double ADSREnvelope::getDecaySeconds() const { return decay; }
double ADSREnvelope::getSustainAmplitude() const { return sustain; }
double ADSREnvelope::getReleaseSeconds() const { return release; }

void ADSREnvelope::setAttackSeconds(const double attack_seconds) { if(attack_seconds > 0.0) {attack = attack_seconds;} }
void ADSREnvelope::setDecaySeconds(const double decay_seconds) { if(decay_seconds > 0.0) {decay = decay_seconds;} }
void ADSREnvelope::setSustainAmplitude(const double sustain_amplitude) { if(sustain_amplitude > 0.0) {sustain = sustain_amplitude;} }
void ADSREnvelope::setReleaseSeconds(const double release_seconds) { if(release_seconds > 0.0) {release = release_seconds;} }

void ADSREnvelope::generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const{
    if (seconds < (attack + decay + release)) {
        return;
    }

    track.setSize(samples_per_second, seconds);

    int attackSamples = static_cast<int>(attack * samples_per_second);
    int decaySamples = static_cast<int>(decay * samples_per_second);
    int releaseSamples = static_cast<int>(release * samples_per_second);
    int sustainSamples = track.getSize() - attackSamples - decaySamples - releaseSamples;
    double maximum_amplitude = getMaximumAmplitude();

    assignAttackAmplitudes(0, attackSamples, track, 0.0, maximum_amplitude);
    assignDecayAmplitudes(attackSamples, attackSamples + decaySamples, track, maximum_amplitude, sustain);
    assignSustainAmplitudes(attackSamples + decaySamples, attackSamples + decaySamples + sustainSamples, track, sustain);
    assignReleaseAmplitudes(attackSamples + decaySamples + sustainSamples, track.getSize(), track, sustain, 0.0);

}

void assignLinearRamp(const int begin, const int end, AudioTrack& track, const double a0, const double a1) {
    double dbegin = begin;
    double dend = end;
    double delta = (a1 - a0) / (dend - dbegin);
    for (int i = dbegin; i < dend; i++) {
        double amplitude = a0 + (delta * (i - dbegin));
        track.setValue(i, amplitude);
    }
}

void ADSREnvelope::assignAttackAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const{
    assignLinearRamp(begin, end, track, a0, a1);
}



void ADSREnvelope::assignDecayAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const {
    assignLinearRamp(begin, end, track, a0, a1);
}

void ADSREnvelope::assignSustainAmplitudes(const int begin, const int end, AudioTrack& track, const double a0) const {
    for (int i = begin; i < end; i++) {
        track.setValue(i, a0);
    }
}

void ADSREnvelope::assignReleaseAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const {
    assignLinearRamp(begin, end, track, a0, a1);
}