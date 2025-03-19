#include "AudioTrack.h"
#include <cmath>

AudioTrack::AudioTrack() : samplesPerSecond(0), seconds(0), values() {}

// Function to check if a value is a whole number for calculating number of entries
bool AudioTrack::isWholeNumber(double value) {
    return std::fmod(value, 1) == 0;
}

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
    if (seconds <= 0) {
        return;
    }
    this->seconds = seconds;
    resizeValues();
}

void AudioTrack::setSize(const int samplesPerSeconds, const double seconds) {
    if (samplesPerSeconds < 1 || seconds <= 0) {
        return;
    }
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
    int entries;
    if (isWholeNumber(samplesPerSecond * seconds)) {
        entries = ceil(samplesPerSecond * seconds);
    } else{
        entries = samplesPerSecond * seconds;
    }
    values.resize(entries);
    for (unsigned int i = 0; i < values.size(); i++) {
        values[i] = 0;
    }
}

AudioTrack AudioTrack::operator*(const AudioTrack& rhs) const{
    if(getSamplesPerSecond() != rhs.getSamplesPerSecond() || getSeconds() != rhs.getSeconds()){
        return AudioTrack();
    }

    AudioTrack result;
    result.setSamplesPerSecond(getSamplesPerSecond());
    result.setSeconds(getSeconds());

    for(unsigned int i = 0; i < getSize(); i++){
        result.setValue(i, getValue(i) * rhs.getValue(i));
    }

    return result;
}