#include "ApplicationData.h"
#include "audio_track_creator_aux.h"

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return audio_track_creator(app_data);
}