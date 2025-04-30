#include "MusicalStaves.h"

MusicalStaves::MusicalStaves() {}
MusicalStaves::~MusicalStaves() {}

void MusicalStaves::addStaff(const std::string& name, const MusicalStaff& staff) { mStaves[name] = staff; }

MusicalStaff& MusicalStaves::getStaff(const std::string& name) { 
    if (mStaves.count(name) == 0) { 
        static MusicalStaff defaultStaff;
        return defaultStaff;
    }
    return mStaves[name];
}

const MusicalStaff& MusicalStaves::getStaff(const std::string& name) const { 
    if (mStaves.count(name) == 0) { 
        static MusicalStaff defaultStaff;
        return defaultStaff;
    }
    return mStaves.at(name);
}

unsigned int MusicalStaves::size() const { return mStaves.size(); }

MusicalStaves::iterator MusicalStaves::begin(){
    return mStaves.begin();
}

MusicalStaves::const_iterator MusicalStaves::begin() const{
    return mStaves.begin();
}

MusicalStaves::iterator MusicalStaves::end(){
    return mStaves.end();
}

MusicalStaves::const_iterator MusicalStaves::end() const{
    return mStaves.end();
}