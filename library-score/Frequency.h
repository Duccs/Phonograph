#ifndef _FREQUENCY_H_
#define _FREQUENCY_H_

#include <map>
#include <string>

class Frequency {
    protected:
        static double trt;
        static std::map<std::string, double> smFrequencies;
    
    public:
        static double getFrequency(const std::string& note);

    protected:
        static double computeFactor(const unsigned int& octaves, const unsigned int& keys);
        static double moveLeft(const double& frequency, const unsigned int& octaves, const unsigned int& keys);
        static double moveRight(const double& frequency, const unsigned int& octaves, const unsigned int& keys);
        static std::map<std::string, double> generateFrequencies();
        
};

#endif /* _FREQUENCY_H_ */