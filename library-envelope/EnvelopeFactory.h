#ifndef _ENVELOPE_FACTORY_H_
#define _ENVELOPE_FACTORY_H_

#include <vector>
#include <string>
#include <memory>
#include "Envelope.h"
#include "ADEnvelope.h"

class EnvelopeFactory {
    public:
        const static std::vector<std::string> EnvelopeName;

        enum EnvelopeId {EN_AD, EN_ADSR, EN_ERROR};

        static std::unique_ptr<Envelope> create(EnvelopeId id, const std::string& name);

        static std::unique_ptr<Envelope> create(const std::string& id, const std::string& name);

        static EnvelopeId stringToEnvelopeId(const std::string& id);

        static bool validStringId(const std::string& id);

        virtual ~EnvelopeFactory() = default;
};

#endif /* _ENVELOPE_FACTORY_H_ */