#include "ScoreReader.h"
#include "WaveformFactory.h"
#include "EnvelopeFactory.h"
#include <string>
#include <memory>

ScoreReader::ScoreReader() {}
ScoreReader::~ScoreReader() {}

void ScoreReader::readScore(std::istream& input_stream, MusicalScore& score) const{
    std::string keyword;
    input_stream >> keyword;

    if(keyword != "SCORE"){
        return;
    }

    while(input_stream >> keyword){
        if(keyword == "SCORE-END"){
            break;
        } else if (keyword == "WAVEFORM"){
            std::shared_ptr<Waveform> waveform = readWaveform(input_stream, score);
        } else if (keyword == "ENVELOPE"){
            std::shared_ptr<Envelope> envelope = readEnvelope(input_stream, score);
        } else if (keyword == "INSTRUMENT"){
            std::shared_ptr<Instrument> instrument = readInstrument(input_stream, score);
        }
        // Future keywords will go here ↓↓

    }
    
    if(input_stream.eof()){
        return;
    }
}

std::shared_ptr<Waveform> ScoreReader::readWaveform(std::istream& input_stream, MusicalScore& score) const{
    std::string keyword;
    std::string waveform_name;
    std::string waveform_type;
    double amplitude = 1.0;

    input_stream >> waveform_name;

    std::shared_ptr<Waveform> waveform = score.getWaveforms().getWaveform(waveform_name);
    if (waveform){
        while (keyword != "WAVEFORM-END"){
            input_stream >> keyword;
        }
        return waveform;
    }

    input_stream >> waveform_type;

    // Create a new waveform using the WaveformFactory
    waveform = WaveformFactory::create(waveform_type, waveform_name);

    while(input_stream >> keyword){
        if(keyword == "WAVEFORM-END"){
            break;
        } else if (keyword == "AMPLITUDE") {
            input_stream >> amplitude;
            if (input_stream.fail()) {
                // Input is not a valid number
                return nullptr;
            }
            if (amplitude < 0.0 || amplitude > 1.0)
            {
                return nullptr;
            }
            waveform->setAmplitude(amplitude);
        } else {
            // Any other keyword causes the function to immediately return
            return nullptr;
        }
    }

    if (input_stream.eof()) {
        return nullptr;
    }

    score.getWaveforms().addWaveform(waveform_name, waveform);
    return waveform;
}

std::shared_ptr<Envelope> ScoreReader::readEnvelope(std::istream& is, MusicalScore& score) const{
    
    std::string keyword;
    std::string envelope_name;
    std::string envelope_type;
    double amplitude = 1.0;
    double attack_seconds = 0.0;
    double decay_seconds = 0.0;
    double sustain_amplitude = 1.0;
    double release_seconds = 0.0;

    is >> envelope_name;

    std::shared_ptr<Envelope> envelope = score.getEnvelopes().getEnvelope(envelope_name);
    if (envelope){
        while (keyword != "ENVELOPE-END"){
            is >> keyword;
        }
        return envelope;
    }

    is >> envelope_type;

    // Create a new waveform using the WaveformFactory
    envelope = EnvelopeFactory::create(envelope_type, envelope_name);

    while(is >> keyword){

        if(keyword == "ENVELOPE-END"){
            break;
        } else if (keyword == MAXIMUM_AMPLITUDE) {
            // Read the amplitude value
            is >> amplitude;
            if (is.fail()) {
                // Input is not a valid number
                return nullptr;
            }
        } else if (keyword == ATTACK_SECONDS) {
            is >> attack_seconds;
            if (is.fail()) {
                // Input is not a valid number
                return nullptr;
            }
        } else if (keyword == DECAY_SECONDS) {
            is >> decay_seconds;
            if (is.fail()) {
                // Input is not a valid number
                return nullptr;
            }
        } else if (keyword == SUSTAIN_AMPLITUDE) {
            if (is.fail()) {
                // Input is not a valid number
                return nullptr;
            }
            is >> sustain_amplitude;
        } else if (keyword == RELEASE_SECONDS) {
            is >> release_seconds;
            if (is.fail()) {
                // Input is not a valid number
                return nullptr;
            }
        } else {
            // Any other keyword causes the function to immediately return
            return nullptr;
        }
        if( amplitude < 0.0 || attack_seconds < 0.0 || decay_seconds < 0.0 || release_seconds < 0.0 || sustain_amplitude < 0.0){
            return nullptr;
        }
    }

    if (is.eof()) {
        return nullptr;
    }

    // Place values in pointer
    envelope->setMaximumAmplitude(amplitude);
    if (envelope_type == "ADSR"){
        std::shared_ptr<ADSREnvelope> adsrEnvelope = std::dynamic_pointer_cast<ADSREnvelope>(envelope);
        adsrEnvelope->setAttackSeconds(attack_seconds);
        adsrEnvelope->setDecaySeconds(decay_seconds);
        adsrEnvelope->setSustainAmplitude(sustain_amplitude);
        adsrEnvelope->setReleaseSeconds(release_seconds);

        score.getEnvelopes().addEnvelope(envelope_name, adsrEnvelope);
    } else if (envelope_type == "AD"){
        std::shared_ptr<ADEnvelope> adEnvelope = std::dynamic_pointer_cast<ADEnvelope>(envelope);
        adEnvelope->setAttackSeconds(attack_seconds);

        score.getEnvelopes().addEnvelope(envelope_name, adEnvelope);
    }

    return envelope;
}

std::shared_ptr<Instrument> ScoreReader::readInstrument(std::istream& is, MusicalScore& score) const{
    std::string keyword;
    std::string instrument_name;
    std::shared_ptr<Waveform> waveform;
    std::shared_ptr<Envelope> envelope;

    is >> instrument_name;

    std::shared_ptr<Instrument> instrument = score.getInstrumentarium().getInstrument(instrument_name);
    if (instrument){
        while (keyword != "INSTRUMENT-END"){
            is >> keyword;
        }
        return instrument;
    }

    while(is >> keyword){
        if(keyword == "INSTRUEMENT-END"){
            break;
        } else if (keyword == "WAVEFORM") {
            waveform = readWaveform(is, score);
        } else if (keyword == "ENVELOPE") {
            envelope = readEnvelope(is, score);
        } else {
            // Any other keyword causes the function to immediately return
            return nullptr;
        }
    }

    if (waveform == nullptr || envelope == nullptr) {
        return nullptr;
    }

    if (is.eof()) {
        return nullptr;
    }

    std::shared_ptr<Instrument> instrument_ptr = std::shared_ptr<Instrument>(new Instrument(instrument_name, waveform, envelope));
    score.getInstrumentarium().addInstrument(instrument_name, instrument_ptr);
    return instrument_ptr;
}