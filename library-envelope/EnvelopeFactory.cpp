#include "EnvelopeFactory.h"

const std::vector<std::string> EnvelopeFactory::EnvelopeName = {"AD", "ADSR", "error"};

std::unique_ptr<Envelope> EnvelopeFactory::create(EnvelopeId id, const std::string& name){
    std::unique_ptr<Envelope> p;
    switch (id) {
        case EN_AD:
            p = std::make_unique<ADSREnvelope>(name);
            break;
        case EN_ADSR:
            p = std::make_unique<ADEnvelope>(name);
            break;
        case EN_ERROR:
            //fall through
        default:
            p = nullptr;
            break;
    }
    return p;
}

std::unique_ptr<Envelope> EnvelopeFactory::create(const std::string& id, const std::string& name){
    EnvelopeId envelopeId = stringToEnvelopeId(id);
    return create(envelopeId, name);
}

EnvelopeFactory::EnvelopeId EnvelopeFactory::stringToEnvelopeId(const std::string& id){
    int envelope_id;
    for(envelope_id = EN_AD; envelope_id < EN_ERROR; envelope_id++) {
        if(id == EnvelopeName[envelope_id]) {
        break;
        }
    }
    return static_cast<EnvelopeId>(envelope_id);
}

bool EnvelopeFactory::validStringId(const std::string& id) {
    return stringToEnvelopeId(id) != EN_ERROR;
}