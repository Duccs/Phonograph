#include "envelope_test_aux.h" 
#include "wav_file_creator_aux.h"
#include "audio_track_creator_aux.h"
#include "ADEnvelope.h"
#include <string>

void fill_audio_track_with_envelope(ApplicationData& app_data){
    std::string envelope_style = app_data.getString("Envelope style: ");
    double maximum_amplitude = app_data.getDouble("Maximum amplitude: ");
    AudioTrack& audio_track = app_data.getAudioTrack();

    if(envelope_style == "ADSR"){
        double attack_seconds = app_data.getDouble("Attack seconds: ");
        double decay_seconds = app_data.getDouble("Decay seconds: ");
        double release_seconds = app_data.getDouble("Release seconds: ");
        double sustain_amplitude = app_data.getDouble("Sustain amplitude: ");
        
        ADSREnvelope adsrenvelope("ADSREnvelope", "ADSR", maximum_amplitude, attack_seconds, decay_seconds, sustain_amplitude, release_seconds);
        adsrenvelope.generateAmplitudes(audio_track.getSeconds(), audio_track.getSamplesPerSecond(), audio_track);
    }
    else if(envelope_style == "AD"){
        double attack_seconds = app_data.getDouble("Attack seconds: ");

        ADEnvelope adenvelope("ADEnvelope", maximum_amplitude, attack_seconds);
        adenvelope.generateAmplitudes(audio_track.getSeconds(), audio_track.getSamplesPerSecond(), audio_track);
    }else{
        app_data.getOutputStream() << "Envelope style "+ envelope_style +" is not known.\n";
    }
}

int envelope_test(ApplicationData& app_data) {
    configure_audio_track(app_data);
    fill_audio_track_with_envelope(app_data);
    display_audio_track(app_data);

    return 0;
}