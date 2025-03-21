#include "TriangleWaveform.h"

TriangleWaveform::TriangleWaveform(const std::string& name) : Waveform(name, "triangle"){}

TriangleWaveform::~TriangleWaveform(){}

double TriangleWaveform::generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const {
    double cycle_position = computeSampleCyclePosition(frequency, sample_number, samples_per_second);
    double result;
    
    if (cycle_position < 0.25){
        result = (4.0 * (cycle_position - 0.0) + 0.0) * amplitude;
    }
    else if (cycle_position < 0.75){
        result = (-4.0 * (cycle_position - 0.25) + 1.0) * amplitude;

    }
    else{
        result = (4.0 * (cycle_position - 0.75) - 1.0) * amplitude;

    }
    return result;
}