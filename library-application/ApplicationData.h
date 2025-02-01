#ifndef _APPLICATIONDATA_H_
#define _APPLICATIONDATA_H_

#include "AudioTrack.h"
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

protected:
  std::istream& mInputStream;
  std::ostream& mOutputStream;
  AudioTrack mAudioTrack;

  std::vector<double> doubleRegisters;

private:

};

#endif /* _APPLICATIONDATA_H_ */
