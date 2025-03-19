#ifndef _AUDIOTRACK_H_
#define _AUDIOTRACK_H_

#include <vector>

class AudioTrack {
    public:
        // Tool method used across app
        bool isWholeNumber(double value);

        AudioTrack();
        int getSamplesPerSecond() const;
        double getSeconds() const;
        unsigned int getSize() const;
        
        void setSamplesPerSecond(int samplesPerSecond);
        void setSeconds(const double seconds);
        void setSize(const int samplesPerSecond, const double seconds);

        bool indexValid(const unsigned int index) const;
        double getValue(const unsigned int index) const;

        void setValue(const unsigned int index, const double value);

        AudioTrack operator*(const AudioTrack& rhs) const;

    protected:
        int samplesPerSecond;
        double seconds;
        std::vector<double> values;

        void resizeValues();

};

#endif /* _AUDIOTRACK_H_ */