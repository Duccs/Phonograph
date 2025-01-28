#include "AudioTrack.h"
#include "audio_track_creator_aux.h"

void rampup_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double seconds = audio_track.getSeconds();
    int samples_per_second = audio_track.getSamplesPerSecond();
    double value = 0.0;
    double increment = 0.0;
    for (int i = 0; i < samples_per_second * seconds; i++) {
        value += increment;
        audio_track.setValue(i, value);
        increment += 1.0 / (samples_per_second * seconds);
    }
}

void rampdown_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double seconds = audio_track.getSeconds();
    int samples_per_second = audio_track.getSamplesPerSecond();
    double value = 0.0;
    double decrement = 0.0;
    for (int i = 0; i < samples_per_second * seconds; i++) {
        value -= decrement;
        audio_track.setValue(i, value);
        decrement += 1.0 / (samples_per_second * seconds);
    }
}

void display_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double seconds = audio_track.getSeconds();
    int samples_per_second = audio_track.getSamplesPerSecond();
    for (int i = 0; i < samples_per_second * seconds; i++) {
        app_data.getOutputStream() << audio_track.getValue(i) << std::endl;
    }
}

void fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    int samples_per_second = audio_track.getSamplesPerSecond();
    double seconds = audio_track.getSeconds();
    double value = 0.0;
    for (int i = 0; i < samples_per_second * seconds; i++) {
        audio_track.setValue(i, value);
    }
}

int audio_track_creator(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    int samples_per_second = audio_track.getSamplesPerSecond();
    double seconds = audio_track.getSeconds();
    int value = 0;
    return value;
}