#include "WaveformFactory.h"

const std::vector<std::string> WaveformFactory::WaveformName = {"sine", "square", "error"};

std::unique_ptr<Waveform> WaveformFactory::create(WaveformId id, const std::string& name){
    std::unique_ptr<Waveform> p;
    switch (id) {
        case WF_SINE:
            p = std::make_unique<SineWaveform>(name);
            break;
        case WF_SQUARE:
            p =  std::make_unique<SquareWaveform>(name);
            break;
        case WF_ERROR:
            //fall through
        default:
            p =  nullptr;
            break;
    }
    return p;
}

std::unique_ptr<Waveform> WaveformFactory::create(const std::string& id, const std::string& name){
    WaveformId waveformId = stringToWaveformId(id);
    return create(waveformId, name);
}

WaveformFactory::WaveformId WaveformFactory::stringToWaveformId(const std::string& id){
    int waveform_id;
    for(waveform_id = WF_SINE; waveform_id < WF_ERROR; waveform_id++) {
        if(id == WaveformName[waveform_id]) {
        break;
        }
    }
    return static_cast<WaveformId>(waveform_id);
}

bool WaveformFactory::validStringId(const std::string& id) {
    return stringToWaveformId(id) != WF_ERROR;
}

