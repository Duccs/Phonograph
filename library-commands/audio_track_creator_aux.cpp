#include "AudioTrack.h"
#include "audio_track_creator_aux.h"

void rampup_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double seconds = audio_track.getSeconds();
    int samples_per_second = audio_track.getSamplesPerSecond();
    double value = 0.0;
    int entires = samples_per_second * seconds;
    double increment = 0.0 + (1.0 - 0.0) * 1.0 / (entires - 1);
    for (int i = 0; i < samples_per_second * seconds -1; i++) {
        audio_track.setValue(i, value);
        value += increment;
    }
}

void rampdown_fill_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double seconds = audio_track.getSeconds();
    int samples_per_second = audio_track.getSamplesPerSecond();
    double value = 1.0;
    int entires = samples_per_second * seconds;
    double decrement = 0.0 + (1.0 - 0.0) * 1.0 / (entires - 1);
    for (int i = 0; i < samples_per_second * seconds -1; i++) {
        audio_track.setValue(i, value);
        value -= decrement;
    }
}

void display_audio_track(ApplicationData& app_data) {
    AudioTrack& audio_track = app_data.getAudioTrack();
    double seconds = audio_track.getSeconds();
    int samples_per_second = audio_track.getSamplesPerSecond();
    app_data.getOutputStream() << "\n";
    app_data.getOutputStream() << "\nsample_number,amplitude\n";
    app_data.getOutputStream() << samples_per_second * seconds << "\n";
    for (int i = 0; i < samples_per_second * seconds -1; i++) {
        app_data.getOutputStream() << i << "," << audio_track.getValue(i) << std::endl;
    }
}

void fill_audio_track(ApplicationData& app_data) {
    std::string fill_style;
    app_data.promptUser("Fill style: ");
    std::cin >> fill_style;

    if (fill_style == "rampup") {
        rampup_fill_audio_track(app_data);
    } else if (fill_style == "rampdown") {
        rampdown_fill_audio_track(app_data);
    } else {
        app_data.promptUser("Fill style '" + fill_style + "' is not allowed.\n");
    }
}

int audio_track_creator(ApplicationData& app_data) {
    int samples_per_second;
    double seconds;

    app_data.promptUser("Samples/Second: ");
    std::cin >> samples_per_second;

    app_data.promptUser("Seconds: ");
    std::cin >> seconds;

    if (samples_per_second > 0 && seconds > 0) {
        AudioTrack& audio_track = app_data.getAudioTrack();
        audio_track.setSamplesPerSecond(samples_per_second);
        audio_track.setSeconds(seconds);
        fill_audio_track(app_data);
        display_audio_track(app_data);
        return audio_track.getSize();
    } else {
        app_data.promptUser("Positive values expected for samples per second and seconds.\n");
        return 0;
    }
}