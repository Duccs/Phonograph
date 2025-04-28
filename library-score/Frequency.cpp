#include "Frequency.h"
#include <cmath>
#include <vector>
#include <iostream>

double Frequency::trt = std::pow(2.0, 1.0 / 12.0);
std::map<std::string, double> Frequency::smFrequencies = generateFrequencies();

double Frequency::getFrequency(const std::string& note) {
    if (smFrequencies.count(note) > 0) {
        return smFrequencies[note];
    }
    return 0.0;
}

double Frequency::computeFactor(const unsigned int& octaves, const unsigned int& keys) {
    return std::pow(2.0, static_cast<double>(octaves)) * std::pow(trt, static_cast<double>(keys));
    // return std::pow(2.0, static_cast<double>(octaves) + static_cast<double>(keys) / 12.0);
}

double Frequency::moveLeft(const double& frequency, const unsigned int& octaves, const unsigned int& keys){
    return frequency / computeFactor(octaves, keys);
}

double Frequency::moveRight(const double& frequency, const unsigned int& octaves, const unsigned int& keys){
    return frequency * computeFactor(octaves, keys);
}

std::map<std::string, double> Frequency::generateFrequencies(){
    static const std::vector<std::vector<std::string>> noteNames = {
        {"C"},
        {"C#", "Db"},
        {"D"},
        {"D#", "Eb"},
        {"E"},
        {"F"},
        {"F#", "Gb"},
        {"G"},
        {"G#", "Ab"},
        {"A"},
        {"A#", "Bb"},
        {"B"}
    };

    std::map<std::string, double> frequencies;

    // C0 is 4 octaves and 9 keys below A4
    double c0 = moveLeft(440.0, 4, 9);

    // For each octave and each note, compute frequency
    for (unsigned int octave = 0; octave <= 9; ++octave) {
        for (size_t key = 0; key < noteNames.size(); ++key) {
            double freq = moveRight(c0, octave, static_cast<unsigned int>(key));
            for (const auto& name : noteNames[key]) {
                std::string note = name + std::to_string(octave);
                frequencies[note] = freq;
            }
        }
    }

    return frequencies;
}