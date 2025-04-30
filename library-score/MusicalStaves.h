#ifndef _MUSICAL_STAVES_H_
#define _MUSICAL_STAVES_H_

#include <map>
#include "MusicalStaff.h"

class MusicalStaves {
    protected:
        std::map<std::string, MusicalStaff> mStaves;

    public:
        typedef std::map<std::string, MusicalStaff>::iterator iterator;
        typedef std::map<std::string, MusicalStaff>::const_iterator const_iterator;

        MusicalStaves();
        virtual ~MusicalStaves();
        
        void addStaff(const std::string& name, const MusicalStaff& staff);
        MusicalStaff& getStaff(const std::string& name);
        const MusicalStaff& getStaff(const std::string& name) const;
        
        unsigned int size() const;
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        

};

#endif /* _MUSICAL_STAVES_H_ */