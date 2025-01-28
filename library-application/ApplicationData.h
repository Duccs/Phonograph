#ifndef _APPLICATIONDATA_H_
#define _APPLICATIONDATA_H_

#include "AudioTrack.h"
#include <iostream>
#include <string>
#include <map>


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

protected:
  std::istream& mInputStream;
  std::ostream& mOutputStream;
  AudioTrack mAudioTrack;

private:

};

#endif /* _APPLICATIONDATA_H_ */
