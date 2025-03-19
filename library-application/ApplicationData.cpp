#include "ApplicationData.h"
#include "AudioTrack.h"
#include <string>
#include <iostream>
#include <cmath>

ApplicationData::ApplicationData(std::istream& input_stream, std::ostream& output_stream) 
	: mInputStream(input_stream), mOutputStream(output_stream), mAudioTrack(), mWAVFile(1, 8), doubleRegisters(), audioTracks(){
	doubleRegisters.resize(5);
	audioTracks.resize(0);
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

AudioTrack& ApplicationData::getAudioTrack() {
	return mAudioTrack;
}

const AudioTrack& ApplicationData::getAudioTrack() const {
	return mAudioTrack;
}

double ApplicationData::getDoubleRegister(const unsigned int position) const {
	if (position >= doubleRegisters.size()) {
	return -INFINITY;
	}
	return doubleRegisters[position];
}

void ApplicationData::setDoubleRegister(const unsigned int position, const double value) {
	if (position >= doubleRegisters.size()) {
	return;
	}
	doubleRegisters[position] = value;
}

WAVFile& ApplicationData::getWAVFile() {
	return mWAVFile;
}

const WAVFile& ApplicationData::getWAVFile() const {
	return mWAVFile;
}

std::vector<AudioTrack>& ApplicationData::getChannels() {
	return audioTracks;
}

const std::vector<AudioTrack>& ApplicationData::getChannels() const {
	return audioTracks;
}

// void ApplicationData::addAction(const ActionFunctionData& action){
// 	menuData.addAction(action);
// }

// void ApplicationData::setDone(bool done){
// 	this->done = done;
// }

// void ApplicationData::printActionHelp(){
// 	menuData.printActionHelp(mOutputStream);
// }

// void ApplicationData::clearToEOL(){
// 	char c;
//     while (mInputStream.get(c) && c != '\n') {
//         // discard the character
//     }
// }

// void ApplicationData::takeAction(const std::string& choice){
// 	if (menuData.actionExists(choice)) {
//         const ActionFunctionData& action = menuData.getAction(choice);
//         action.getFunction();
//     } else {
// 		//Unknown action 'commentthis'. Use 'help' for a list of valid actions
//         mOutputStream << "Unknown action '" << choice << "'. Use 'help' for a list of valid actions\n";
//         clearToEOL();
//     }
// }

// void ApplicationData::mainLoop(){
// 	while (mInputStream.good() && !done) {
//         promptUser("Choice? ");
//         std::string choice;
//         mInputStream >> choice;
//         takeAction(choice);
//     }
// }