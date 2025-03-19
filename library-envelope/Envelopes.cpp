#include "Envelopes.h"

Envelopes::Envelopes() {}

Envelopes::~Envelopes(){}

void Envelopes::addEnvelope(const std::string& name, std::shared_ptr<Envelope> envelope) { 
    envelopes[name] = envelope; 
}

std::shared_ptr<Envelope> Envelopes::getEnvelope(const std::string& name) { 
    const_iterator it = envelopes.find(name); 
    return (it != envelopes.end()) ? it->second : nullptr; 
}

Envelopes::iterator Envelopes::begin() { return envelopes.begin(); }

Envelopes::const_iterator Envelopes::begin() const { return envelopes.begin(); }

Envelopes::iterator Envelopes::end() { return envelopes.end(); }

Envelopes::const_iterator Envelopes::end() const { return envelopes.end(); }