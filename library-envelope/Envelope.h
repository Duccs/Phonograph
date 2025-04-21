#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_

#include <string>
#include "AudioTrack.h"

const std::string MAXIMUM_AMPLITUDE = "MAXIMUM-AMPLITUDE";
const std::string ATTACK_SECONDS = "ATTACK-SECONDS";
const std::string DECAY_SECONDS = "DECAY-SECONDS";
const std::string SUSTAIN_AMPLITUDE = "SUSTAIN-AMPLITUDE";
const std::string RELEASE_SECONDS = "RELEASE-SECONDS";

class Envelope {
    protected:
        std::string name;
        std::string type;
        double amplitude;

    public:
        Envelope(const std::string& name, const std::string& type_name);
        Envelope(const std::string& name, const std::string& type_name, const double amplitude);
        
        virtual ~Envelope();
        virtual void generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const = 0;

        const std::string& getName() const;
        const std::string& getTypeName() const;
        double getMaximumAmplitude() const;

        void setName(const std::string& name);
        void setTypeName(const std::string& type_name);
        void setMaximumAmplitude(const double amplitude);
};

#endif /* _ENVELOPE_H_ */