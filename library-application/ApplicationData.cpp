#include "ApplicationData.h"
#include <string>
#include <iostream>

ApplicationData::ApplicationData(std::istream& input_stream, std::ostream& output_stream) 
  : mInputStream(input_stream), mOutputStream(output_stream) {
}

int ApplicationData::getInteger(const std::string& prompt) {
  int value{};
  promptUser(prompt);
  mInputStream >> value;
  return value;
}

double ApplicationData::getDouble(const std::string& prompt) {
  double value{};
  promptUser(prompt);
  mInputStream >> value;
  return value;
}

std::string ApplicationData::getString(const std::string& prompt) {
  std::string value;
  promptUser(prompt);
  mInputStream >> value;
  return value;
}

void ApplicationData::promptUser(const std::string& prompt) {
  mOutputStream << prompt;
}

std::istream& ApplicationData::getInputStream() {
  return mInputStream;
}
std::ostream& ApplicationData::getOutputStream() {
  return mOutputStream;
}
