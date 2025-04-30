#include "score_editor_aux.h"
#include "ScoreReader.h"
#include "ScoreWriter.h"
#include "WavWriter.h"
#include "WaveformFactory.h"
#include "EnvelopeFactory.h"
#include "menu_test_aux.h"
#include <fstream>

void readScoreUI(ApplicationData& app){
    std::string score_name = app.getString("Score filename: ");
    std::ifstream input_stream(score_name);
    
    if(!input_stream.is_open()) {
        app.getOutputStream() << "Unable to open file '" << score_name << "'.\n";
        return;
    }

    ScoreReader reader;
    reader.readScore(input_stream, app.getScore());
}

void writeScoreUI(ApplicationData& app){
    std::string file_name = app.getString("Filename: ");
    std::ofstream output_stream(file_name);

    if (!output_stream.is_open()) {
        app.getOutputStream() << "Unable to open file '" << file_name << "' for writing.\n";
        return;
    }

    ScoreWriter writer;
    writer.writeScore(output_stream, app.getScore());
}

void renderScoreUI(ApplicationData& app){
    std::string file_name = app.getString("Filename: ");
    int samples_per_second = app.getInteger("Samples per second: ");
    int bits_per_sample = app.getInteger("Bits per sample: ");
    WavWriter writer;
    writer.writeWavFromScore(app.getScore(), samples_per_second, bits_per_sample, file_name);
}

void setScoreTimeSignatureUI(ApplicationData& app){
    int beats_per_bar = app.getInteger("Beats per bar: ");
    int beat_value = app.getInteger("Beat value: ");
    app.getScore().setTimeSignature(TimeSignature(beats_per_bar, beat_value));
}

void setScoreTempoUI(ApplicationData& app){
    double tempo = app.getDouble("Beats per minute: ");
    app.getScore().setTempo(tempo);
}

void listScoreWaveformsUI(ApplicationData& app){
    Waveforms::const_iterator it;
    for (it = app.getScore().getWaveforms().begin(); it != app.getScore().getWaveforms().end(); ++it) {
        std::shared_ptr<Waveform> waveform = it->second;
        app.getOutputStream() << it->first << " : " 
        << waveform->getName() << " " << waveform->getTypeName() 
        << " " << waveform->getAmplitude() << "\n";
    }
}

void addScoreWaveformUI(ApplicationData& app){
    std::string waveform_name = app.getString("Waveform name: ");
    std::string waveform_type = app.getString("Waveform type: ");

    std::shared_ptr<Waveform> waveform = WaveformFactory::create(waveform_type, waveform_name);
    if(waveform == nullptr) { 
        app.getOutputStream() << "Unable to create a waveform of type '"+ waveform_type +"'.\n";
        return;
    }
    double waveform_amplitude = app.getDouble("Amplitude: ");
    
    waveform.get()->setAmplitude(waveform_amplitude);
    waveform.get()->setTypeName(waveform_type);
    app.getScore().getWaveforms().addWaveform(waveform_name, waveform);
}

void editScoreWaveformUI(ApplicationData& app){
    std::string waveform_name = app.getString("Waveform name: ");
    std::shared_ptr<Waveform> waveform = app.getScore().getWaveforms().getWaveform(waveform_name);
    if (waveform == nullptr)
    {
        app.getOutputStream() << "Unable to find a waveform with name '" << waveform_name << "'.\n";
        return;
    }
    
    double waveform_amplitude = app.getDouble("Amplitude(" + app.cleanDouble(waveform.get()->getAmplitude()) + "): ");
    waveform.get()->setAmplitude(waveform_amplitude);
}

void listScoreEnvelopesUI(ApplicationData& app){
    Envelopes::const_iterator it;
    for (it = app.getScore().getEnvelopes().begin(); it != app.getScore().getEnvelopes().end(); ++it) {
        std::shared_ptr<Envelope> envelope = it->second;
        app.getOutputStream() << it->first << " : " 
        << envelope->getName() << " " << envelope->getTypeName() 
        << " " << envelope->getMaximumAmplitude() << "\n";
    }
}

void addScoreEnvelopeUI(ApplicationData& app){
    std::string envelope_name = app.getString("Envelope name: ");
    std::string envelope_type = app.getString("Envelope type: ");
    
    std::shared_ptr<Envelope> envelope = EnvelopeFactory::create(envelope_type, envelope_name);
    
    if(envelope == nullptr) { 
        app.getOutputStream() << "Unable to create an envelope of type '"+ envelope_type +"'.\n";
        return;
    }

    //shared set
    double envelope_amplitude = app.getDouble("Maximum amplitude: ");
    envelope.get()->setMaximumAmplitude(envelope_amplitude);
    if (envelope_type == "ADSR")
    {
        std::shared_ptr<ADSREnvelope> adsrEnvelope = std::dynamic_pointer_cast<ADSREnvelope>(envelope);

        double attack_seconds = app.getDouble("Attack seconds: ");
        double decay_seconds = app.getDouble("Decay seconds: ");
        double sustain_amplitude = app.getDouble("Sustain amplitude: ");
        double release_seconds = app.getDouble("Release seconds: ");
        if (adsrEnvelope){
            adsrEnvelope.get()->setAttackSeconds(attack_seconds);
            adsrEnvelope.get()->setDecaySeconds(decay_seconds);
            adsrEnvelope.get()->setSustainAmplitude(sustain_amplitude);
            adsrEnvelope.get()->setReleaseSeconds(release_seconds);
            
            app.getScore().getEnvelopes().addEnvelope(envelope_name, adsrEnvelope);
        }
        else{
            app.getOutputStream() << "Error creating ADSR envelope\n";
        }
        
    } else if (envelope_type == "AD") {

        std::shared_ptr<ADEnvelope> adEnvelope = std::dynamic_pointer_cast<ADEnvelope>(envelope);

        double attack_seconds = app.getDouble("Attack seconds: ");
        if(adEnvelope){
            adEnvelope.get()->setAttackSeconds(attack_seconds);

            app.getScore().getEnvelopes().addEnvelope(envelope_name, adEnvelope);
        }
        else{
            app.getOutputStream() << "Error creating AD envelope\n";
        }
    }
    else{
        app.getOutputStream() << "Envelope type '"+ envelope_type +"' is not known.\n";
    }   
}

void editScoreEnvelopeUI(ApplicationData& app) {
    std::string envelope_name = app.getString("Envelope name: ");
    std::shared_ptr<Envelope> envelope = app.getScore().getEnvelopes().getEnvelope(envelope_name);

    if(envelope == nullptr) {
        app.getOutputStream() << "Unable to find an envelope with name '" << envelope_name << "'.\n";
        return;
    }

    double envelope_amplitude = envelope.get()->getMaximumAmplitude();
    envelope_amplitude = app.getDouble("Maximum amplitude(" + app.cleanDouble(envelope_amplitude) + "): ");
    //shared set
    envelope.get()->setMaximumAmplitude(envelope_amplitude);
    if (envelope->getTypeName() == "ADSR")
    {
        std::shared_ptr<ADSREnvelope> adsrEnvelope = std::dynamic_pointer_cast<ADSREnvelope>(envelope);
        if(adsrEnvelope){
            double attack_seconds = adsrEnvelope.get()->getAttackSeconds();
            attack_seconds = app.getDouble("Attack seconds(" + app.cleanDouble(attack_seconds) + "): ");
            double decay_seconds = adsrEnvelope.get()->getDecaySeconds();
            decay_seconds = app.getDouble("Decay seconds(" + app.cleanDouble(decay_seconds) + "): ");
            double sustain_amplitude = adsrEnvelope.get()->getSustainAmplitude();
            sustain_amplitude = app.getDouble("Sustain amplitude(" + app.cleanDouble(sustain_amplitude) + "): ");
            double release_seconds = adsrEnvelope.get()->getReleaseSeconds();
            release_seconds = app.getDouble("Release seconds(" + app.cleanDouble(release_seconds) + "): ");
            adsrEnvelope.get()->setAttackSeconds(attack_seconds);
            adsrEnvelope.get()->setDecaySeconds(decay_seconds);
            adsrEnvelope.get()->setSustainAmplitude(sustain_amplitude);
            adsrEnvelope.get()->setReleaseSeconds(release_seconds);
        }else{
            app.getOutputStream() << "Error editing ADSR envelope\n";
        }
        
    }
    else if (envelope->getTypeName() == "AD")
    {
        std::shared_ptr<ADEnvelope> adEnvelope = std::dynamic_pointer_cast<ADEnvelope>(envelope);
        double attack_seconds = adEnvelope.get()->getAttackSeconds();
        attack_seconds = app.getDouble("Attack seconds(" + app.cleanDouble(attack_seconds) + "): ");
        adEnvelope.get()->setAttackSeconds(attack_seconds);
    }
    else{
        app.getOutputStream() << "Envelope type '"+ envelope->getTypeName() +"' is not known.\n";
    }
}

void listScoreInstrumentsUI(ApplicationData& app) {
    Instrumentarium::const_iterator it;
    for (it = app.getScore().getInstrumentarium().begin(); it != app.getScore().getInstrumentarium().end(); ++it) {
        Instrument instrument = *it->second;
        app.getOutputStream() << it->first << " : " << instrument.getName() << " : ";
        
        app.getOutputStream() << instrument.getWaveform()->getName() << " ";
        app.getOutputStream() << instrument.getEnvelope()->getName() << "\n";
    }
}

void addScoreInstrumentUI(ApplicationData& app){
    std::string instrument_name = app.getString("Instrument name: ");
    std::string waveform_name = app.getString("Waveform name: ");
    std::string envelope_name = app.getString("Envelope name: ");
    std::shared_ptr<Waveform> waveform = app.getScore().getWaveforms().getWaveform(waveform_name);
    std::shared_ptr<Envelope> envelope = app.getScore().getEnvelopes().getEnvelope(envelope_name);
    if(waveform == nullptr){
        app.getOutputStream() << "Unable to find a waveform with name '" << waveform_name << "'.\n";
        return;
    }
    if(envelope == nullptr){
        app.getOutputStream() << "Unable to find an envelope with name '" << envelope_name << "'.\n";
        return;
    }

    std::shared_ptr<Instrument> instrument = std::make_unique<Instrument>(instrument_name, waveform, envelope);
    app.getScore().getInstrumentarium().addInstrument(instrument_name, instrument);
}

void editScoreInstrumentUI(ApplicationData& app){
    std::string instrument_name = app.getString("Instrument name: ");
    std::shared_ptr<Instrument> instrument = app.getScore().getInstrumentarium().getInstrument(instrument_name);
    if (instrument == nullptr)
    {
        app.getOutputStream() << "Unable to find instrument with name '" << instrument_name << "'.\n";
        return;
    }
    
    std::string waveform_name = app.getString("Waveform name: ");
    std::string envelope_name = app.getString("Envelope name: ");
    std::shared_ptr<Waveform> waveform = app.getScore().getWaveforms().getWaveform(waveform_name);
    std::shared_ptr<Envelope> envelope = app.getScore().getEnvelopes().getEnvelope(envelope_name);
    if(waveform == nullptr){
        app.getOutputStream() << "Unable to find a waveform with name '" << waveform_name << "'.\n";
        return;
    }
    if(envelope == nullptr){
        app.getOutputStream() << "Unable to find an envelope with name '" << envelope_name << "'.\n";
        return;
    }

    instrument->setWaveform(waveform);
    instrument->setEnvelope(envelope);
}

void setStaffInstrumentUI(ApplicationData& app){
    std::string staff_name = app.getString("Staff name: ");
    MusicalStaff& staff = app.getScore().getStaff(staff_name);

    // Check for staff if it exists??
    //

    std::string instrument_name = app.getString("Instrument name: ");
    std::shared_ptr<Instrument> instrument = app.getScore().getInstrumentarium().getInstrument(instrument_name);
    if (instrument == nullptr)
    {
        app.getOutputStream() << "Unable to find instrument with name '" << instrument_name << "'.\n";
        return;
    }
    staff.setInstrument(instrument);
}

void listScoreStavesUI(ApplicationData& app){
    MusicalStaves::const_iterator it;
    for (it = app.getScore().getStaves().begin(); it != app.getScore().getStaves().end(); ++it) {
        MusicalStaff staff = it->second;
        //app.getOutputStream() << it->second.getName() << " " << staff.getInstrument()->getName() << std::endl;
        app.getOutputStream() << it->second << std::endl;
    }
}

void addStaffUI(ApplicationData& app){
    std::string staff_name = app.getString("Staff name: ");
    std::string instrument_name = app.getString("Instrument name: ");
    std::shared_ptr<Instrument> instrument = app.getScore().getInstrumentarium().getInstrument(instrument_name);
    if (instrument == nullptr)
    {
        app.getOutputStream() << "Unable to find instrument with name '" << instrument_name << "'.\n";
        return;
    }
    app.getScore().addStaff(MusicalStaff(staff_name, instrument));
}

void showStaffUI(ApplicationData& app){
    std::string staff_name = app.getString("Staff name: ");
    MusicalStaff& staff = app.getScore().getStaff(staff_name);
    app.getOutputStream() << staff.toString() << std::endl;
    for (const auto& note : staff.getNotes()) {
        app.getOutputStream() << note.getStart() << " " << note.getNote().getDuration() << " " << note.getNote().getName() << std::endl;
    }
    app.getOutputStream() << std::endl;
}

void addStaffNoteUI(ApplicationData& app){
    std::string staff_name = app.getString("Staff name: ");
    MusicalStaff& staff = app.getScore().getStaff(staff_name);
    double start = app.getDouble("Start: ");
    std::string duration = app.getString("Duration: ");
    std::string note = app.getString("Note: ");
    staff.addNote(StaffNote(Note(note, duration), start));
}

void buildScoreInstrumentFromWaveformAndEnvelopePair(ApplicationData& app, std::shared_ptr<Waveform> w, std::shared_ptr<Envelope> e){
    std::string instrument_name = (w->getName() + "/" + e->getName());
    std::shared_ptr<Instrument> instrument = std::make_unique<Instrument>(instrument_name, w, e);
    app.getScore().getInstrumentarium().addInstrument(instrument_name, instrument);
}

void buildScoreAllPossibleInstrumentsUI(ApplicationData& app){
    Waveforms::const_iterator w;
    Envelopes::const_iterator e;
    for (w = app.getScore().getWaveforms().begin(); w != app.getScore().getWaveforms().end(); ++w) {
        for (e = app.getScore().getEnvelopes().begin(); e != app.getScore().getEnvelopes().end(); ++e) {
            buildScoreInstrumentFromWaveformAndEnvelopePair(app, w->second, e->second);
        }
    }
}

void addStaffNoteRunUI(ApplicationData& app){
    std::string staff_name = app.getString("Staff name: ");
    MusicalStaff& staff = app.getScore().getStaff(staff_name);
    double start = app.getDouble("Start: ");
    std::string duration = app.getString("Duration: ");
    std::string note = app.getString("First note: ");

    // First Note
    Note first_note = Note(note, duration);
    staff.addNote(StaffNote(first_note, start));

    // Second Note
    std::string second_note = first_note.relativeNoteNameFlat(4);
    staff.addNote(StaffNote(Note(second_note, duration), start + first_note.getDuration()));

    // Third Note
    std::string third_note = first_note.relativeNoteNameFlat(7);
    staff.addNote(StaffNote(Note(third_note, duration), start + (first_note.getDuration() * 2)));
}

int register_score_editor_commands(ApplicationData& app_data){
    register_menu_test_commands(app_data);
    app_data.addAction(ActionFunctionData("score-read", readScoreUI, "Read score from file."));
    app_data.addAction(ActionFunctionData("score-write", writeScoreUI, "Write score to score file."));
    app_data.addAction(ActionFunctionData("score-list-waveforms", listScoreWaveformsUI, "List waveforms in the score."));
    app_data.addAction(ActionFunctionData("score-add-waveform", addScoreWaveformUI, "Add waveform to the score."));
    app_data.addAction(ActionFunctionData("score-edit-waveform", editScoreWaveformUI, "Edit waveform in the score."));
    app_data.addAction(ActionFunctionData("score-list-envelopes", listScoreEnvelopesUI, "List envelopes in the score."));
    app_data.addAction(ActionFunctionData("score-add-envelope", addScoreEnvelopeUI, "Add envelope to the score."));
    app_data.addAction(ActionFunctionData("score-edit-envelope", editScoreEnvelopeUI, "Edit envelope in the score."));
    app_data.addAction(ActionFunctionData("score-list-instruments", listScoreInstrumentsUI, "List instruments in the score."));
    app_data.addAction(ActionFunctionData("score-add-instrument", addScoreInstrumentUI, "Add instrument to the score."));
    app_data.addAction(ActionFunctionData("score-edit-instrument", editScoreInstrumentUI, "Edit instrument in the score."));
    app_data.addAction(ActionFunctionData("score-set-time-signature", setScoreTimeSignatureUI, "Edit the time signature of a score."));
    app_data.addAction(ActionFunctionData("score-set-tempo", setScoreTempoUI, "Edit the tempo of a score."));
    app_data.addAction(ActionFunctionData("score-staff-set-instrument", setStaffInstrumentUI, "Change instrument assigned to a staff in the score."));
    app_data.addAction(ActionFunctionData("score-list-staves", listScoreStavesUI, "List staves in the score."));
    app_data.addAction(ActionFunctionData("score-add-staff", addStaffUI, "Add a staff to the score."));
    app_data.addAction(ActionFunctionData("score-show-staff", showStaffUI, "Display staff details."));
    app_data.addAction(ActionFunctionData("score-staff-add-note", addStaffNoteUI, "Add a note to a staff."));
    app_data.addAction(ActionFunctionData("score-render", renderScoreUI, "Render score to wav file."));
    app_data.addAction(ActionFunctionData("score-build-all-instruments", buildScoreAllPossibleInstrumentsUI, "Build an instrument for each waveform/envelope pair in the score."));
    app_data.addAction(ActionFunctionData("score-staff-add-note-run", addStaffNoteRunUI, "Add a run of notes to a staff."));
    
    return 0;
}

int score_editor(ApplicationData& app_data){
    register_score_editor_commands(app_data);
    app_data.mainLoop();
    return 0;
}