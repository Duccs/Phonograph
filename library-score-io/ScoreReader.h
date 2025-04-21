#ifndef _SCORE_READER_H_
#define _SCORE_READER_H_

#include "MusicalScore.h"
#include <istream>

class ScoreReader {

    public:
        ScoreReader();
        virtual ~ScoreReader();

        void readScore(std::istream& input_stream, MusicalScore& score) const;
        
        std::shared_ptr<Waveform> readWaveform(std::istream& input_stream, MusicalScore& score) const;
        std::shared_ptr<Envelope> readEnvelope(std::istream& is, MusicalScore& score) const;
        std::shared_ptr<Instrument> readInstrument(std::istream& is, MusicalScore& score) const;
};

#endif /* _SCORE_READER_H_ */