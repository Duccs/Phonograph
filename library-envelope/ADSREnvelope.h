#ifndef _ASDRENVELOPE_H_
#define _ADSRENVELOPE_H_

#include "Envelope.h"

class ADSREnvelope : public Envelope{
    protected:
        double attack;
        double decay;
        double sustain;
        double release;

    public:
        ADSREnvelope(const std::string& name, const std::string& type_name);
        ADSREnvelope(const std::string& name, const std::string& type_name, const double maximum_amplitude, const double attack_seconds, const double decay_seconds, const double sustain_amplitude, const double release_seconds);
        ADSREnvelope(const std::string& name);
        ADSREnvelope(const std::string& name, const double maximum_amplitude, const double attack_seconds, const double decay_seconds, const double sustain_amplitude, const double release_seconds);
        
        virtual ~ADSREnvelope();

        double getAttackSeconds() const;
        double getDecaySeconds() const;
        double getSustainAmplitude() const;
        double getReleaseSeconds() const;

        void setAttackSeconds(const double attack_seconds);
        void setDecaySeconds(const double decay_seconds);
        void setSustainAmplitude(const double sustain_amplitude);
        void setReleaseSeconds(const double release_seconds);

        virtual void generateAmplitudes(const double seconds, const int samples_per_second, AudioTrack& track) const;
        
        void assignAttackAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const;
        void assignDecayAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const;
        void assignSustainAmplitudes(const int begin, const int end, AudioTrack& track, const double a0) const;
        void assignReleaseAmplitudes(const int begin, const int end, AudioTrack& track, const double a0, const double a1) const;
};

#endif /* _ASDRENVELOPE_H_ */