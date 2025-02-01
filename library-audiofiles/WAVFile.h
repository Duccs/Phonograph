#ifndef _WAVFILE_H_
#define _WAVFILE_H_

class WAVFile {
    protected:
        int samplesPerSecond;
        int bitsPerSample;
    public:
        WAVFile(int samples_per_second, int bits_per_sample);
        int getSamplesPerSecond() const;
        int getBitsPerSample() const;
        void setSamplesPerSecond(const int samples_per_second);
        void setBitsPerSample(const int bits_per_sample);

};

#endif /* _WAVFILE_H_ */