#ifndef _INSTRUMENTARUM_H_
#define _INSTRUMENTARUM_H_

#include "Instrument.h"
#include <map>
#include <memory>
#include <string>

class Instrumentarium {
    protected:
        std::map<std::string, std::shared_ptr<Instrument>> instruments;
    
    public:
        typedef std::map<std::string, std::shared_ptr<Instrument>>::iterator iterator;
        typedef std::map<std::string, std::shared_ptr<Instrument>>::const_iterator const_iterator;

        Instrumentarium();
        virtual ~Instrumentarium();

        void addInstrument(const std::string& name, std::shared_ptr<Instrument> instrument);
        std::shared_ptr<Instrument> getInstrument(const std::string& name);

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

};

#endif /* _INSTRUMENTARUM_H_ */