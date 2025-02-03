#include "wav_file_creator_aux.h"
#include "audio_track_creator_aux.h"

void configure_audio_track_and_wav_file(ApplicationData& app_data){
    int samples_per_second = app_data.getInteger("Samples/Second: ");
    double seconds = app_data.getDouble("Seconds: ");
    int bits_per_sample = app_data.getInteger("Bits/Sample[8,16,24,32]: ");

    WAVFile& wavfile = app_data.getWAVFile();
    AudioTrack& audioTrack = app_data.getAudioTrack();
    wavfile.setSamplesPerSecond(samples_per_second);
    wavfile.setBitsPerSample(bits_per_sample);

    audioTrack.setSamplesPerSecond(samples_per_second);
    audioTrack.setSeconds(seconds);
}

void fill_channels(ApplicationData& app_data){
    std::vector<AudioTrack>& channels = app_data.getChannels();
    channels.resize(2);

    app_data.getOutputStream() << "Left Channel" << std::endl;
    fill_audio_track(app_data);
    channels[0] = app_data.getAudioTrack();
            
    app_data.getOutputStream() << "Right Channel" << std::endl;
    fill_audio_track(app_data);
    channels[1] = app_data.getAudioTrack();
}

void save_wav_file(ApplicationData& app_data){
    std::string filename = app_data.getString("WAV filename: ");
    WAVFile& wavfile = app_data.getWAVFile();
    wavfile.writeFile(filename, app_data.getChannels());
}

int wav_file_creator(ApplicationData& app_data){
    configure_audio_track_and_wav_file(app_data);
    AudioTrack& audioTrack = app_data.getAudioTrack();

    if (audioTrack.getSize() > 0) {
        fill_channels(app_data);
        save_wav_file(app_data);
    } else {
        app_data.getOutputStream() << "Positive values expected for samples per second and seconds.\n";
    }
    app_data.getOutputStream().flush();
    return audioTrack.getSize();
}