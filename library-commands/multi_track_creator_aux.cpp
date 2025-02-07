#include "multi_track_creator_aux.h"

void multi_track_configure_audio_track_and_wav_file(ApplicationData& app_data) {
    configure_audio_track_and_wav_file(app_data);

    int NumberOfChannels = app_data.getInteger("Number of Channels: ");
    WAVFile& wavfile = app_data.getWAVFile();
    wavfile.setNumberOfChannels(NumberOfChannels);
}

void multi_track_fill_channels(ApplicationData& app_data) {
    std::vector<AudioTrack>& channels = app_data.getChannels();
    channels.resize(app_data.getWAVFile().getNumberOfChannels());

    for (int i = 0; i < channels.size(); i++)
    {
        app_data.getOutputStream() << "Channel " << i << std::endl;
        fill_audio_track(app_data);
        channels[i] = app_data.getAudioTrack();
    }
}

int multi_track_creator(ApplicationData& app_data) {
    multi_track_configure_audio_track_and_wav_file(app_data);
    AudioTrack& audioTrack = app_data.getAudioTrack();

    if (audioTrack.getSize() > 0) {
        multi_track_fill_channels(app_data);
        save_wav_file(app_data);
    } else {
        app_data.getOutputStream() << "Positive values expected for samples per second and seconds.\n";
    }
    app_data.getOutputStream().flush();
    return audioTrack.getSize();
}