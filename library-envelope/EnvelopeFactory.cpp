#include "EnvelopeFactory.h"

std::unique_ptr<Envelope> EnvelopeFactory::create(EnvelopeId id, const std::string& name){
    switch (id) {
        case EN_AD:
            return std::make_unique<ADSREnvelope>(name);
        case EN_ADSR:
            return std::make_unique<ADEnvelope>(name);
        case EN_ERROR:
            //fall through
        default:
            return nullptr;
    }

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

