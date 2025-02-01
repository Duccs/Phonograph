#include "WAVFile.h"

WAVFile::WAVFile(int samples_per_second, int bits_per_sample)
: samplesPerSecond(0), bitsPerSample(0) {
    setSamplesPerSecond(samples_per_second);
    setBitsPerSample(bits_per_sample);
}

int WAVFile::getSamplesPerSecond() const {
    return samplesPerSecond;
}

int WAVFile::getBitsPerSample() const {
    return bitsPerSample;
}

void WAVFile::setSamplesPerSecond(const int samples_per_second) {
    if (samples_per_second < 1) {
        return;
    }
    samplesPerSecond = samples_per_second;
}

void WAVFile::setBitsPerSample(const int bits_per_sample) {
    if(bits_per_sample % 8 == 0) {
        bitsPerSample = bits_per_sample;
    }
}