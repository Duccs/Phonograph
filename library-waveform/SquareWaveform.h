#ifndef _SQUAREWAVEFORM_H_
#define _SQUAREWAVEFORM_H_

#include "Waveform.h"

class SquareWaveform : public Waveform{
    public:
        SquareWaveform(const std::string& name);
        virtual ~SquareWaveform();
        virtual double generateOneSample(const double frequency, const int sample_number, const double samples_per_second) const;
};

#endif /* _SQUAREWAVEFORM_H_ */