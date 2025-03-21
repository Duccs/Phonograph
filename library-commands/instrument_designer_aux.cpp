#include "instrument_designer_aux.h"
#include "Waveform.h"
#include "WaveformFactory.h"
#include "Envelope.h"
#include "EnvelopeFactory.h"
#include "instrument_test_aux.h"
#include "wav_file_creator_aux.h"
#include "menu_test_aux.h"
#include <iomanip>

std::string cleanDouble(double num){
    std::stringstream ss;
    ss << std::fixed << std::setprecision(10) << num; // set a high precision to avoid rounding errors
    std::string str = ss.str();
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') str.pop_back();
    return str;
}

void listWaveformsUI(ApplicationData& app_data){
    Waveforms::const_iterator it;
    for (it = app_data.getWaveforms().begin(); it != app_data.getWaveforms().end(); ++it) {
        std::shared_ptr<Waveform> waveform = it->second;
        app_data.getOutputStream() << it->first << " : " 
        << waveform->getName() << " " << waveform->getTypeName() 
        << " " << waveform->getAmplitude() << "\n";
    }
}

void addWaveformUI(ApplicationData& app_data){
    std::string waveform_name = app_data.getString("Waveform name: ");
    std::string waveform_type = app_data.getString("Waveform type: ");
    double waveform_amplitude = app_data.getDouble("Amplitude: ");

    std::shared_ptr<Waveform> waveform = WaveformFactory::create(waveform_type, waveform_name);
    if(waveform == nullptr) { 
        app_data.getOutputStream() << "Unable to create a waveform of type '"+ waveform_type +"'.\n";
        return;
    }
    
    waveform.get()->setAmplitude(waveform_amplitude);
    waveform.get()->setTypeName(waveform_type);
    app_data.getWaveforms().addWaveform(waveform_name, waveform);
}

void editWaveformUI(ApplicationData& app_data) {
    std::string waveform_name = app_data.getString("Waveform name: ");
    std::shared_ptr<Waveform> waveform = app_data.getWaveforms().getWaveform(waveform_name);
    if (waveform == nullptr)
    {
        app_data.getOutputStream() << "Unable to find a waveform with name '" << waveform_name << "'.\n";
        return;
    }
    
    double waveform_amplitude = app_data.getDouble("Amplitude(" + cleanDouble(waveform.get()->getAmplitude()) + "): ");
    waveform.get()->setAmplitude(waveform_amplitude);
}

void listEnvelopesUI(ApplicationData& app_data){
    Envelopes::const_iterator it;
    for (it = app_data.getEnvelopes().begin(); it != app_data.getEnvelopes().end(); ++it) {
        std::shared_ptr<Envelope> envelope = it->second;
        app_data.getOutputStream() << it->first << " : " 
        << envelope->getName() << " " << envelope->getTypeName() 
        << " " << envelope->getMaximumAmplitude() << "\n";
    }
}

void addEnvelopeUI(ApplicationData& app_data){
    std::string envelope_name = app_data.getString("Envelope name: ");
    std::string envelope_type = app_data.getString("Envelope type: ");
    double envelope_amplitude = app_data.getDouble("Maximum amplitude: ");
    
    std::shared_ptr<Envelope> envelope = EnvelopeFactory::create(envelope_type, envelope_name);
    
    if(envelope == nullptr) { 
        app_data.getOutputStream() << "Unable to create an envelope of type '"+ envelope_type +"'.\n";
        return;
    }

    //shared set
    envelope.get()->setMaximumAmplitude(envelope_amplitude);
    if (envelope_type == "ADSR")
    {
        std::shared_ptr<ADSREnvelope> adsrEnvelope = std::dynamic_pointer_cast<ADSREnvelope>(envelope);

        double attack_seconds = app_data.getDouble("Attack seconds: ");
        double decay_seconds = app_data.getDouble("Decay seconds: ");
        double sustain_amplitude = app_data.getDouble("Sustain amplitude: ");
        double release_seconds = app_data.getDouble("Release seconds: ");
        if (adsrEnvelope){
            adsrEnvelope.get()->setAttackSeconds(attack_seconds);
            adsrEnvelope.get()->setDecaySeconds(decay_seconds);
            adsrEnvelope.get()->setSustainAmplitude(sustain_amplitude);
            adsrEnvelope.get()->setReleaseSeconds(release_seconds);
            
            app_data.getEnvelopes().addEnvelope(envelope_name, adsrEnvelope);
        }
        else{
            app_data.getOutputStream() << "Error creating ADSR envelope\n";
        }
        
    }
    else if (envelope_type == "AD")
    {
        std::shared_ptr<ADEnvelope> adEnvelope = std::dynamic_pointer_cast<ADEnvelope>(envelope);

        if(adEnvelope){
            double attack_seconds = app_data.getDouble("Attack seconds: ");
            adEnvelope.get()->setAttackSeconds(attack_seconds);

            app_data.getEnvelopes().addEnvelope(envelope_name, adEnvelope);
        }
        else{
            app_data.getOutputStream() << "Error creating AD envelope\n";
        }
    }
    else{
        app_data.getOutputStream() << "Envelope type '"+ envelope_type +"' is not known.\n";
    }   
}

void editEnvelopeUI(ApplicationData& app_data) {
    std::string envelope_name = app_data.getString("Envelope name: ");
    std::shared_ptr<Envelope> envelope = app_data.getEnvelopes().getEnvelope(envelope_name);

    if(envelope == nullptr) {
        app_data.getOutputStream() << "Unable to find an envelope with name '" << envelope_name << "'.\n";
        return;
    }

    double envelope_amplitude = app_data.getDouble("Maximum amplitude: ");
    //shared set
    envelope.get()->setMaximumAmplitude(envelope_amplitude);
    if (envelope->getTypeName() == "ADSR")
    {
        std::shared_ptr<ADSREnvelope> adsrEnvelope = std::dynamic_pointer_cast<ADSREnvelope>(envelope);
        if(adsrEnvelope){
            double attack_seconds = adsrEnvelope.get()->getAttackSeconds();
            attack_seconds = app_data.getDouble("Attack seconds(" + cleanDouble(attack_seconds) + "): ");
            double decay_seconds = adsrEnvelope.get()->getDecaySeconds();
            decay_seconds = app_data.getDouble("Decay seconds(" + cleanDouble(decay_seconds) + "): ");
            double sustain_amplitude = adsrEnvelope.get()->getSustainAmplitude();
            sustain_amplitude = app_data.getDouble("Sustain amplitude(" + cleanDouble(sustain_amplitude) + "): ");
            double release_seconds = adsrEnvelope.get()->getReleaseSeconds();
            release_seconds = app_data.getDouble("Release seconds(" + cleanDouble(release_seconds) + "): ");
            adsrEnvelope.get()->setAttackSeconds(attack_seconds);
            adsrEnvelope.get()->setDecaySeconds(decay_seconds);
            adsrEnvelope.get()->setSustainAmplitude(sustain_amplitude);
            adsrEnvelope.get()->setReleaseSeconds(release_seconds);
        }else{
            app_data.getOutputStream() << "Error editing ADSR envelope\n";
        }
        
    }
    else if (envelope->getTypeName() == "AD")
    {
        std::shared_ptr<ADEnvelope> adEnvelope = std::dynamic_pointer_cast<ADEnvelope>(envelope);
        double attack_seconds = adEnvelope.get()->getAttackSeconds();
        attack_seconds = app_data.getDouble("Attack seconds(" + cleanDouble(attack_seconds) + "): ");
        adEnvelope.get()->setAttackSeconds(attack_seconds);
    }
    else{
        app_data.getOutputStream() << "Envelope type '"+ envelope->getTypeName() +"' is not known.\n";
    }
}

void listInstrumentsUI(ApplicationData& app_data){
    Instrumentarium::const_iterator it;
    for (it = app_data.getInstrumentarium().begin(); it != app_data.getInstrumentarium().end(); ++it) {
        std::shared_ptr<Instrument> instrument = it->second;
        app_data.getOutputStream() << instrument->getName() << " : " 
        << instrument->getWaveform()->getName() << " " << instrument->getEnvelope()->getName() << "\n";
    }
}

void addInstrumentUI(ApplicationData& app_data){
    std::string instrument_name = app_data.getString("Instrument name: ");
    std::string waveform_name = app_data.getString("Waveform name: ");
    std::string envelope_name = app_data.getString("Envelope name: ");

    std::shared_ptr<Waveform> waveform = app_data.getWaveforms().getWaveform(waveform_name);
    std::shared_ptr<Envelope> envelope = app_data.getEnvelopes().getEnvelope(envelope_name);

    if (waveform == nullptr)
    {
        app_data.getOutputStream() << waveform_name << " does not name a waveform in this application.\n";
        return;
    }
    if (envelope == nullptr)
    {
        app_data.getOutputStream() << envelope_name << " does not name an envelope in this application.\n";
        return;
    }

    std::shared_ptr<Instrument> instrument = std::make_shared<Instrument>(instrument_name, waveform, envelope);
    app_data.getInstrumentarium().addInstrument(instrument_name, instrument);
}

void editInstrumentUI(ApplicationData& app_data){
    std::string instrument_name = app_data.getString("Instrument name: ");
    std::shared_ptr<Instrument> instrument = app_data.getInstrumentarium().getInstrument(instrument_name);
    std::string waveform_name = app_data.getString("Waveform name: ");
    std::string envelope_name = app_data.getString("Envelope name: ");

    std::shared_ptr<Waveform> waveform = app_data.getWaveforms().getWaveform(waveform_name);
    std::shared_ptr<Envelope> envelope = app_data.getEnvelopes().getEnvelope(envelope_name);

    if (instrument == nullptr)
    {
        app_data.getOutputStream() << instrument_name << " does not name a instrument in this application.\n";
        return;
    }
    if (waveform == nullptr)
    {
        app_data.getOutputStream() << waveform_name << " does not name a waveform in this application.\n";
        return;
    }
    if (envelope == nullptr)
    {
        app_data.getOutputStream() << envelope_name << " does not name an envelope in this application.\n";
        return;
    }

    instrument.get()->setWaveform(waveform);
    instrument.get()->setEnvelope(envelope);
}

void put_frequency_in_register(ApplicationData& app_data){
    double frequency = app_data.getDouble("Frequency: ");
    app_data.setDoubleRegister(0, frequency);
}

void recordInstrumentNoteUI(ApplicationData& app_data){
    std::string instrument_name = app_data.getString("Instrument name: ");
    std::shared_ptr<Instrument> instrument = app_data.getInstrumentarium().getInstrument(instrument_name);

    if (instrument == nullptr)
    {
        app_data.getOutputStream() << instrument_name << " does not name a instrument in this application.\n";
        return;
    }
    
    put_frequency_in_register(app_data);

    fill_audio_track_from_instrument(app_data, instrument);

    app_data.getChannels().resize(2);
    app_data.getChannels()[0] = app_data.getAudioTrack();
    app_data.getChannels()[1] = app_data.getAudioTrack();

    save_wav_file(app_data);
}

int register_instrument_designer_commands(ApplicationData& app_data){
    register_menu_test_commands(app_data);
    app_data.addAction(ActionFunctionData("list-waveforms", listWaveformsUI, "List waveforms in the inventory."));
    app_data.addAction(ActionFunctionData("add-waveform", addWaveformUI, "Add waveform to the inventory."));
    app_data.addAction(ActionFunctionData("edit-waveform", editWaveformUI, "Edit waveform in the inventory."));
    app_data.addAction(ActionFunctionData("list-envelopes", listEnvelopesUI, "List envelopes in the inventory."));
    app_data.addAction(ActionFunctionData("add-envelope", addEnvelopeUI, "Add envelope to the inventory."));
    app_data.addAction(ActionFunctionData("edit-envelope", editEnvelopeUI, "Edit envelope in the inventory."));
    app_data.addAction(ActionFunctionData("list-instruments", listInstrumentsUI, "List instruments in the inventory."));
    app_data.addAction(ActionFunctionData("add-instrument", addInstrumentUI, "Add instrument to the inventory."));
    app_data.addAction(ActionFunctionData("edit-instrument", editInstrumentUI, "Edit instrument in the inventory."));
    app_data.addAction(ActionFunctionData("record-instrument-note", recordInstrumentNoteUI, "Record a note for an instrument to a WAV file."));
    app_data.addAction(ActionFunctionData("configure-audio-track-and-wav-file", configure_audio_track_and_wav_file, "Configure meta data for the audio track and WAV file."));

    return 0;
}

int instrument_designer(ApplicationData& app_data){
    register_instrument_designer_commands(app_data);
    app_data.mainLoop();
    return 0;
}