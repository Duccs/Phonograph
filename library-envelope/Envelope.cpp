#include "Envelope.h"

Envelope::Envelope(const std::string& name, const std::string& type_name): name(name), type(type_name), amplitude(1.0) {}

Envelope::Envelope(const std::string& name, const std::string& type_name, const double amplitude): name(name), type(type_name), amplitude(amplitude) {}

Envelope::~Envelope() {}

const std::string& Envelope::getName() const { return name; }

const std::string& Envelope::getTypeName() const { return type; }

double Envelope::getMaximumAmplitude() const { return amplitude; }

void Envelope::setName(const std::string& name) { this->name = name; }

void Envelope::setTypeName(const std::string& type_name) { type = type_name; }

void Envelope::setMaximumAmplitude(const double amplitude) { 
    if(amplitude > 0.0){
        this->amplitude = amplitude; 
    }
}