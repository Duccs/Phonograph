#ifndef _WAVEFORMS_H_
#define _WAVEFORMS_H_

#include <string>
#include <map>
#include <memory>
#include "Waveform.h"

class Waveforms{
    protected:
        std::map<std::string, std::shared_ptr<Waveform>> waveforms;

    public:
        typedef std::map<std::string, std::shared_ptr<Waveform>>::iterator iterator;
        typedef std::map<std::string, std::shared_ptr<Waveform>>::const_iterator const_iterator;

        Waveforms();
        virtual ~Waveforms();

        void addWaveform(const std::string& name, std::shared_ptr<Waveform> waveform);
        std::shared_ptr<Waveform> getWaveform(const std::string& name);

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

};

#endif /* _WAVEFORMS_H_ */