#include "instrument_test_aux.h"
#include "wav_file_creator_aux.h"

#include <string>

std::shared_ptr<Waveform> choose_waveform(ApplicationData& app_data) {
    std::string waveform_style = app_data.getString("Waveform style: ");
    if (waveform_style == "sine") {
        return std::shared_ptr<SineWaveform>(new SineWaveform(""));
    } else if (waveform_style == "square") {
        return std::shared_ptr<SquareWaveform>(new SquareWaveform(""));
    } else {
        app_data.getOutputStream() << "Waveform style '"+ waveform_style +"' is not known.\n";
        return nullptr;
    }
}

std::shared_ptr<Envelope> choose_envelope(ApplicationData& app_data) {
    std::string envelope_style = app_data.getString("Envelope style: ");
    double maximum_amplitude = app_data.getDouble("Maximum amplitude: ");
    if (envelope_style == "ADSR") {
        double attack_seconds = app_data.getDouble("Attack seconds: ");
        double decay_seconds = app_data.getDouble("Decay seconds: ");
        double release_seconds = app_data.getDouble("Release seconds: ");
        double sustain_amplitude = app_data.getDouble("Sustain amplitude: ");
        return std::shared_ptr<ADSREnvelope>(new ADSREnvelope("", maximum_amplitude, attack_seconds, decay_seconds, sustain_amplitude, release_seconds));
    } else if (envelope_style == "AD") {
        double attack_seconds = app_data.getDouble("Attack seconds: ");
        return std::shared_ptr<ADEnvelope>(new ADEnvelope("", maximum_amplitude, attack_seconds));
    } else {
        app_data.getOutputStream() << "Envelope style '"+ envelope_style +"' is not known.\n";
        return nullptr;
    }
}

std::shared_ptr<Instrument> create_instrument(ApplicationData& app_data) {
    return std::shared_ptr<Instrument>(new Instrument("", choose_waveform(app_data), choose_envelope(app_data)));
}

void fill_audio_track_from_instrument(ApplicationData& app_data, std::shared_ptr<Instrument> instrument_ptr) {
    double frequency = app_data.getDoubleRegister(0);
    instrument_ptr->generateSamples(frequency, app_data.getAudioTrack().getSeconds(), app_data.getAudioTrack().getSamplesPerSecond(), app_data.getAudioTrack());
}

int instrument_test(ApplicationData& app_data) {
    configure_audio_track_and_wav_file(app_data);
    std::shared_ptr<Instrument> instrument_ptr = create_instrument(app_data);
    double frequency = app_data.getDouble("Frequency: ");
    app_data.setDoubleRegister(0, frequency);
    printf("Reached before fill\n");
    fill_audio_track_from_instrument(app_data, instrument_ptr);
    printf("Reached before channels\n");
    app_data.getChannels().resize(2);
    app_data.getChannels()[0] = app_data.getAudioTrack();
    app_data.getChannels()[1] = app_data.getAudioTrack();
    printf("Reached after channels\n");
    save_wav_file(app_data);
    return 0;

}