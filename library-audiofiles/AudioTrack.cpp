#include "AudioTrack.h"
#include <cmath>

AudioTrack::AudioTrack() : samplesPerSecond(0), seconds(0), values() {}

int AudioTrack::getSamplesPerSecond() const {
    return samplesPerSecond;
}

double AudioTrack::getSeconds() const {
    return seconds;
}

unsigned int AudioTrack::getSize() const {
    return values.size();
}

void AudioTrack::setSamplesPerSecond(const int samplesPerSecond) {
    if (samplesPerSecond < 1) {
        return;
    }
    this->samplesPerSecond = samplesPerSecond;
    resizeValues();
}

void AudioTrack::setSeconds(const double seconds) {
    if (seconds < 0) {
        return;
    }
    this->seconds = seconds;
    resizeValues();
}

void AudioTrack::setSize(const int samplesPerSeconds, const double seconds) {
    setSamplesPerSecond(samplesPerSeconds);
    setSeconds(seconds);
}

bool AudioTrack::indexValid(const unsigned int index) const {
    return index < values.size();
}

double AudioTrack::getValue(const unsigned int index) const {
    if (!indexValid(index)) {
        return -INFINITY;
    }
    return values[index];
}

void AudioTrack::setValue(const unsigned int index, const double value) {
    if (!indexValid(index)) {
        return;
    }
    values[index] = value;
}

void AudioTrack::resizeValues() {
    values.resize(samplesPerSecond * seconds);
    for (unsigned int i = 0; i < values.size(); i++) {
        values[i] = 0;
    }
}