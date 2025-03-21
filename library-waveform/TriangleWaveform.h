#ifndef _TRIANGLEWAVEFORM_H_
#define _TRIANGLEWAVEFORM_H_

#include "Waveform.h"

class TriangleWaveform : public Waveform {
    public:
        TriangleWaveform(const std::string& name);
        virtual ~TriangleWaveform();
        virtual double generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const;
};

#endif /* _TRIANGLEWAVEFORM_H_ */