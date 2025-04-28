#ifndef _TIME_SIGNATURE_H_
#define _TIME_SIGNATURE_H_

class TimeSignature {
    protected:
        int beats_per_bar;
        int beat_value;

    public:
        TimeSignature();
        TimeSignature(const int beats_per_bar, const int beat_value);
        
        int getBeatsPerBar() const;
        int getBeatValue() const;
        void setBeatsPerBar(const int beats_per_bar);
        void setBeatValue(const int beat_value);
};

#endif /* _TIME_SIGNATURE_H_ */