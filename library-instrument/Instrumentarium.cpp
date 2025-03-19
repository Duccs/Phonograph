#include "Instrumentarium.h"

Instrumentarium::Instrumentarium() {}

Instrumentarium::~Instrumentarium() {}

void Instrumentarium::addInstrument(const std::string& name, std::shared_ptr<Instrument> instrument) {
    instruments[name] = instrument;
}

std::shared_ptr<Instrument> Instrumentarium::getInstrument(const std::string& name) {
    const_iterator it = instruments.find(name);
    return (it != instruments.end()) ? it->second : nullptr;
}

Instrumentarium::iterator Instrumentarium::begin() { return instruments.begin(); }

Instrumentarium::const_iterator Instrumentarium::begin() const { return instruments.begin(); }

Instrumentarium::iterator Instrumentarium::end() { return instruments.end(); }

Instrumentarium::const_iterator Instrumentarium::end() const { return instruments.end(); }