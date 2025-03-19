#ifndef _INSTRUMENT_H_
#define _INSTRUMENT_H_

#include "Waveform.h"
#include "Envelope.h"
#include <SineWaveform.h>
#include <SquareWaveform.h>
#include <ADEnvelope.h>
#include <string>
#include <memory>

class Instrument {
    protected:
        std::string name;
        std::shared_ptr<Waveform> waveform;
        std::shared_ptr<Envelope> envelope;

    public:
        Instrument();
        Instrument(const std::string& name, std::shared_ptr<Waveform> waveform, std::shared_ptr<Envelope> envelope); 
        
        virtual ~Instrument();
        
        const std::string& getName() const;
        std::shared_ptr<Waveform> getWaveform() const;
        std::shared_ptr<Envelope> getEnvelope() const;

        void setName(const std::string& name);
        void setWaveform(std::shared_ptr<Waveform> waveform);
        void setEnvelope(std::shared_ptr<Envelope> envelope);
        void generateSamples(const double frequency, const double seconds, const int samples_per_second, AudioTrack& track) const;
};


#endif /* _INSTRUMENT_H_ */