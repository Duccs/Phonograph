#ifndef _APPLICATIONDATA_H_
#define _APPLICATIONDATA_H_

#include "AudioTrack.h"
#include "WAVFile.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>


class ApplicationData {
public:
  ApplicationData(std::istream& input_stream, std::ostream& output_stream);

  int getInteger(const std::string& prompt);
  double getDouble(const std::string& prompt);
  std::string getString(const std::string& prompt);
  void promptUser(const std::string& prompt);

  std::istream& getInputStream();
  std::ostream& getOutputStream();

  AudioTrack& getAudioTrack();
  const AudioTrack& getAudioTrack() const;

  double getDoubleRegister(const unsigned int position) const;
  void setDoubleRegister(const unsigned int position, const double value);

  WAVFile& getWAVFile();
  const WAVFile& getWAVFile() const;
  std::vector<AudioTrack>& getChannels();
  const std::vector<AudioTrack>& getChannels() const;

protected:
  std::istream& mInputStream;
  std::ostream& mOutputStream;
  AudioTrack mAudioTrack;
  WAVFile mWAVFile;

  std::vector<double> doubleRegisters;
  std::vector<AudioTrack> audioTracks;

private:

};

#endif /* _APPLICATIONDATA_H_ */
