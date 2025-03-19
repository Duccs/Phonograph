#ifndef _WAVEFORM_FACTORY_H_
#define _WAVEFORM_FACTORY_H_

#include <vector>
#include <string>
#include <memory>
#include "Waveform.h"
#include "SineWaveform.h"
#include "SquareWaveform.h"

class WaveformFactory {
    public:
        const static std::vector<std::string> WaveformName;

        enum WaveformId {WF_SINE, WF_SQUARE, WF_ERROR};

        static std::unique_ptr<Waveform> create(WaveformId id, const std::string& name);

        static std::unique_ptr<Waveform> create(const std::string& id, const std::string& name);

        static WaveformId stringToWaveformId(const std::string& id);

        static bool validStringId(const std::string& id);

        virtual ~WaveformFactory() = default;
};

#endif /* _WAVEFORM_FACTORY_H_ */