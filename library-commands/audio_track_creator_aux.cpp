#include "AudioTrack.h"
#include "audio_track_creator_aux.h"
#include <cmath> 

int numberOfSamples(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double seconds = audio_track.getSeconds();
    int samples_per_second = audio_track.getSamplesPerSecond();
    int entries;
    if (audio_track.isWholeNumber(samples_per_second * seconds)) {
        entries = ceil(samples_per_second * seconds);
    } else{
        entries = samples_per_second * seconds;
    }
    return entries;   
}

void rampup_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double value = 0.0;
    int entries = numberOfSamples(app_data);
    double increment = 1.0 / (entries - 1);
    for (int i = 0; i < entries; i++) {
        audio_track.setValue(i, value);
        value += increment;
    }
    audio_track.setValue(entries - 1, 1.0); // Set the final value explicitly to 1.0
}

void rampdown_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double value = 1.0;
    int entries = numberOfSamples(app_data);
    double decrement = 1.0 / (entries - 1);
    for (int i = 0; i < entries; i++) {
        audio_track.setValue(i, value);
        value -= decrement;
    }
    audio_track.setValue(entries - 1, 0.0); // Set the last sample to 0
}

void display_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    int entries = numberOfSamples(app_data);;
    app_data.getOutputStream() << "\nsample_number,amplitude\n";
    for (int i = 0; i < entries; i++) {
        app_data.getOutputStream() << i << "," << audio_track.getValue(i) << std::endl;
    }
}

void fill_audio_track(ApplicationData& app_data) {
    std::string fill_style = app_data.getString("Fill style: ");

    if (fill_style == "rampup") {
        rampup_fill_audio_track(app_data);
    } else if (fill_style == "rampdown") {
        rampdown_fill_audio_track(app_data);
    } else if (fill_style == "sine") {
        double frequency = app_data.getDouble("Frequency: ");
        app_data.setDoubleRegister(0, frequency);
        sine_fill_audio_track(app_data);
    } else if (fill_style == "sawtooth") {
        double frequency = app_data.getDouble("Frequency: ");
        app_data.setDoubleRegister(0, frequency);
        sawtooth_fill_audio_track(app_data);
    } else {
        app_data.getOutputStream() << "Fill style '" + fill_style + "' is not allowed.\n";
        exit(0);
    }
}

int audio_track_creator(ApplicationData& app_data) {
    int samples_per_second;
    double seconds;

    samples_per_second = app_data.getInteger("Samples/Second: ");

    seconds = app_data.getDouble("Seconds: ");

    if (samples_per_second > 0 && seconds > 0) {
        AudioTrack& audio_track = app_data.getAudioTrack();
        audio_track.setSamplesPerSecond(samples_per_second);
        audio_track.setSeconds(seconds);
        fill_audio_track(app_data);
        display_audio_track(app_data);
        return audio_track.getSize();
    } else {
        app_data.getOutputStream() << "Positive values expected for samples per second and seconds.\n";
        exit(0);
    }
}

void sine_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    int samples_per_second = audio_track.getSamplesPerSecond();
    double frequency = app_data.getDoubleRegister(0);
    double angle;
    double amplitude;
    int entries = numberOfSamples(app_data);
    for (int i = 0; i < entries; i++) {

        angle = (6.28 * i * frequency) / samples_per_second;
        amplitude = std::sin(angle);
        audio_track.setValue(i, amplitude);

        if ( i == 1229) { 
            std::cout << "Reached 1229" << std::endl;
            std::cout << "Angle: " << angle << std::endl;
            std::cout << "Amplitude: " << amplitude << std::endl;
        }
    }
    std::cout << "Entry 1229: " << audio_track.getValue(1229) << std::endl;
}

void sawtooth_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double seconds = audio_track.getSeconds();
    int samples_per_second = audio_track.getSamplesPerSecond();
    double frequency = app_data.getDoubleRegister(0);
    int cycle_size = samples_per_second/frequency;
    double j;
    double angle;
    double amplitude;
    int entries = numberOfSamples(app_data);
    for (int i = 0; i < entries; i++) {
        j = i % cycle_size;
        amplitude = -1.0 + (2.0 * j) / (cycle_size - 1);
        audio_track.setValue(i, amplitude);
        samples_per_second = amplitude;
    }
}
