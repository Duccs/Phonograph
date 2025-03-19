#ifndef _ENVELOPES_H_
#define _ENVELOPES_H_

#include "Envelope.h"
#include <map>
#include <memory>
#include <string>

class Envelopes{
    protected:
        std::map<std::string, std::shared_ptr<Envelope>> envelopes;

    public:
        typedef std::map<std::string, std::shared_ptr<Envelope>>::iterator iterator;
        typedef std::map<std::string, std::shared_ptr<Envelope>>::const_iterator const_iterator;

        Envelopes();
        virtual ~Envelopes();

        void addEnvelope(const std::string& name, std::shared_ptr<Envelope> envelope);
        std::shared_ptr<Envelope> getEnvelope(const std::string& name);

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
};

#endif /* _ENVELOPES_H_ */