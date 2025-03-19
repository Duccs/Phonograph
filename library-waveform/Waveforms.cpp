#include "Waveforms.h"

Waveforms::Waveforms(){}

Waveforms::~Waveforms(){}

void Waveforms::addWaveform(const std::string& name, std::shared_ptr<Waveform> waveform){
    waveforms[name] = waveform;
}

std::shared_ptr<Waveform> Waveforms::getWaveform(const std::string& name){
    const_iterator it = waveforms.find(name);
    return (it != waveforms.end()) ? it->second : nullptr;
}

Waveforms::iterator Waveforms::begin() {
    return waveforms.begin();
}

Waveforms::const_iterator Waveforms::begin() const {
    return waveforms.begin();
}

Waveforms::iterator Waveforms::end() {
    return waveforms.end();
}

Waveforms::const_iterator Waveforms::end() const {
    return waveforms.end();
}