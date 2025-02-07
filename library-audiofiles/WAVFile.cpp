#include "WAVFile.h"
#include "endian_io.h"
#include <iostream>
#include <fstream>
#include <cmath>

WAVFile::WAVFile(int samples_per_second, int bits_per_sample)
: samplesPerSecond(0), bitsPerSample(0), NumberOfChannels(2) {
    setSamplesPerSecond(samples_per_second);
    setBitsPerSample(bits_per_sample);
}

int WAVFile::getSamplesPerSecond() const {
    return samplesPerSecond;
}

int WAVFile::getBitsPerSample() const {
    return bitsPerSample;
}

int WAVFile::getNumberOfChannels() const {
    return NumberOfChannels;
}

void WAVFile::setSamplesPerSecond(const int samples_per_second) {
    if (samples_per_second < 1) {
        return;
    }
    samplesPerSecond = samples_per_second;
}

void WAVFile::setBitsPerSample(const int bits_per_sample) {
    // Accepts 8, 16, 24, and 32 only
    if(bits_per_sample > 0 && bits_per_sample % 8 == 0 
        && (bits_per_sample == 8 || bits_per_sample == 16 
        || bits_per_sample == 24 || bits_per_sample == 32)){
        bitsPerSample = bits_per_sample;
    }
}

void WAVFile::setNumberOfChannels(const int number_of_channels) {
    if (number_of_channels < 1) {
        return;
    }
    NumberOfChannels = number_of_channels;
}

void WAVFile::open(const std::string& filename, std::ofstream& output_stream) {
    output_stream.open(filename, std::ios::binary);
}

void WAVFile::writeRIFFHeader(std::ostream& output_stream){
    output_stream.write("RIFF", 4);
    little_endian_io::write_4_bytes(output_stream, 0);
    output_stream.write("WAVE", 4);
}

void WAVFile::writeFMTSubchunk(std::ostream& output_stream) {
    // SubchunkID
    output_stream.write("fmt ", 4);

    // SubchunkSize
    // The number of bytes in this subchunk that follow this field
    little_endian_io::write_4_bytes(output_stream, 16);

    // AudioFormat
    // For PCM formats, the value should be 1.
    little_endian_io::write_2_bytes(output_stream, 1);

    // NumChannels
    // The number of channels, 1 for mono, 2 for stereo.
    little_endian_io::write_2_bytes(output_stream, NumberOfChannels);

    // SamplesRate
    // The number of samples per second. (44100 for “CD Quality”)
    little_endian_io::write_4_bytes(output_stream, samplesPerSecond);

    // ByteRate
    // The number of bytes per second.
    // SampleRate * NumChannels * BitsPerSample/8.
    little_endian_io::write_4_bytes(output_stream, samplesPerSecond * NumberOfChannels * (bitsPerSample / 8));

    // BlockAlign
    // The number of bytes per sample, including all channels.
    // NumberOfChannels * BitsPerSample/8.
    little_endian_io::write_2_bytes(output_stream, NumberOfChannels * (bitsPerSample / 8));
    
    // BitsPerSample
    // The number of bits per sample, per channel.
    little_endian_io::write_2_bytes(output_stream, bitsPerSample);
}

void WAVFile::writeDataSubchunkHeader(std::ostream& output_stream){
    // SubchunkID
    output_stream.write("data", 4);

    // Data position
    dataSubchunkPosition = output_stream.tellp();

    // SubchunkSize
    // the number of bytes in the file that follow this field.
    // In other words, the number of bytes in the file minus 44.
    little_endian_io::write_4_bytes(output_stream, 0);
}

void WAVFile::writeOneTrackData(std::ostream& output_stream, const double track_data, int maximum_amplitude, int bytes_per_sample){
    int value = static_cast<int>(track_data * maximum_amplitude);
    switch (bytes_per_sample)
    {
    case 1:
        little_endian_io::write_1_bytes(output_stream, value);
        break;
    case 2:
        little_endian_io::write_2_bytes(output_stream, value);
        break;
    case 3:
        little_endian_io::write_3_bytes(output_stream, value);
        break;
    case 4:
        little_endian_io::write_4_bytes(output_stream, value);
        break;
    default:
        break;
    }
    
}

void WAVFile::writeTracks(std::ostream& output_stream, const std::vector<AudioTrack>& tracks){
    if (tracks.size() != NumberOfChannels) {
        return; // do nothing if tracks are not valid
    }

    for (size_t i = 0; i < tracks.size(); i++)
    {
        if (tracks[i].getSize() != tracks[0].getSize()) {
            return; // do nothing if track sizes are not valid
        }
    }

    int bytesPerSample = bitsPerSample / 8;
    int maximumAmplitude = (int)pow(2, bitsPerSample - 1) - 1;

    for (unsigned int i = 0; i < tracks[0].getSize(); i++) {
        for (size_t j = 0; j < tracks.size(); j++)
        {
            writeOneTrackData(output_stream, tracks[j].getValue(i), maximumAmplitude, bytesPerSample);
        }
    }
}

void WAVFile::writeSizes(std::ostream& output_stream){
    // Store current position, doubles as the total file size
    int fileSize = static_cast<int>(output_stream.tellp());

    // Move to 4 bytes after RIFF  identifier, which is RIFF chunk size
    output_stream.seekp(4);

    // Write the RIFF chunck size
    int riffChunkSize = fileSize - 8;
    little_endian_io::write_4_bytes(output_stream, riffChunkSize);

    // Move to where the data subchunck size should be written
    output_stream.seekp(dataSubchunkPosition);

    // Write the data subchunk size
    int dataSubchunkSize = fileSize - 44;
    little_endian_io::write_4_bytes(output_stream, dataSubchunkSize);
}

void WAVFile::close(std::ofstream& output_stream){
    if (output_stream.is_open()) {
        output_stream.close();
    }    
}

void WAVFile::writeFile(const std::string& filename, const std::vector<AudioTrack>& tracks){
    std::ofstream output_stream;
    open(filename, output_stream);
    writeFile(output_stream, tracks);
    close(output_stream);
}

void WAVFile::writeFile(std::ostream& output_stream, const std::vector<AudioTrack>& tracks){
    dataSubchunkPosition = 0;
    writeRIFFHeader(output_stream);
    writeFMTSubchunk(output_stream);
    writeDataSubchunkHeader(output_stream);
    writeTracks(output_stream, tracks);
    writeSizes(output_stream);
}