#include "TimeSignature.h"

TimeSignature::TimeSignature() : beats_per_bar(4), beat_value(4) {}

TimeSignature::TimeSignature(const int beats_per_bar, const int beat_value) : beats_per_bar(beats_per_bar), beat_value(beat_value) {}

int TimeSignature::getBeatsPerBar() const { return beats_per_bar; }

int TimeSignature::getBeatValue() const { return beat_value; }

void TimeSignature::setBeatsPerBar(const int beats_per_bar) { 
    if(beats_per_bar <= 0) { return; }
    this->beats_per_bar = beats_per_bar; 
}

void TimeSignature::setBeatValue(const int beat_value){
    if(beat_value <= 0) { return; }
    this->beat_value = beat_value;
}