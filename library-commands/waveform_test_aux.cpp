#include "waveform_test_aux.h"
#include "wav_file_creator_aux.h"
#include "Waveform.h"
#include "SineWaveform.h"
#include "SquareWaveform.h"

void fill_audio_track_with_waveform(ApplicationData& app_data){
    std::string waveform_style = app_data.getString("Waveform style: ");
    double amplitude = app_data.getDouble("Amplitude: ");
    double frequency = app_data.getDouble("Frequency: ");
    AudioTrack& audio_track = app_data.getAudioTrack();

    if(waveform_style == "sine"){
        SineWaveform sineWaveform = SineWaveform("SineWaveform");
        sineWaveform.setAmplitude(amplitude);
        sineWaveform.generateSamples(frequency, audio_track.getSeconds(), audio_track.getSamplesPerSecond(), audio_track);
    } else if(waveform_style == "square"){
        SquareWaveform squareWaveform = SquareWaveform("SquareWaveform");
        squareWaveform.setAmplitude(amplitude);
        squareWaveform.generateSamples(frequency, audio_track.getSeconds(), audio_track.getSamplesPerSecond(), audio_track);
    } else {
        app_data.getOutputStream() << "Waveform style " + waveform_style + "' is not known.\n";
    }
}

void fill_channels_with_waveforms(ApplicationData& app_data){
    app_data.getChannels().resize(2);

    app_data.getOutputStream() << "Left Channel" << std::endl;
    fill_audio_track_with_waveform(app_data);
    app_data.getChannels()[0] = app_data.getAudioTrack();

    app_data.getOutputStream() << "Right Channel" << std::endl;
    fill_audio_track_with_waveform(app_data);
    app_data.getChannels()[1] = app_data.getAudioTrack();
}


int waveform_test(ApplicationData& app_data){
    configure_audio_track_and_wav_file(app_data);
    fill_channels_with_waveforms(app_data);
    save_wav_file(app_data);
    return 0;
}