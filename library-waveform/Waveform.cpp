#include "Waveform.h"
#include <cmath>

const double two_pi = 6.283185307179586476925286766559;

Waveform::Waveform(const std::string& name, const std::string& type_name) : name(name), type(type_name), amplitude(1.0) {}

Waveform::~Waveform() {}

const std::string& Waveform::getName() const { return name; }

const std::string& Waveform::getTypeName() const { return type; }

double Waveform::getAmplitude() const { return amplitude; }

void Waveform::setName(const std::string& name) { this->name = name; }

void Waveform::setTypeName(const std::string& type_name) { type = type_name; }

void Waveform::setAmplitude(const double amplitude) { 
    if(amplitude < 0.0 || amplitude > 1.0) { return; }
    this->amplitude = amplitude; 
}

double Waveform::computeSampleAngle(const double frequency, const double sample_number, const int samples_per_second) const{
    double angle = two_pi * sample_number * frequency / samples_per_second;
    return angle;
}

double Waveform::computeSampleCyclePosition(const double frequency, const double sample_number, const int samples_per_second) const{
    double angle = computeSampleAngle(frequency, sample_number, samples_per_second);
    double remining_angle = std::fmod(angle, two_pi);
    double cycle_position = remining_angle / two_pi;
    return cycle_position;
}

void Waveform::generateSamples(const double frequency, const double seconds, const int samples_per_second, AudioTrack& track) const{
    track.setSize(samples_per_second, seconds);
    for (int i = 0; i < track.getSize(); i++) {
        double sample = generateOneSample(frequency, i, samples_per_second);
        track.setValue(i, sample);
    }
}