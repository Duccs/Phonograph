#include "multi_track_creator_aux.h"
#include <iostream>

int main() {
    ApplicationData app_data(std::cin, std::cout);
    return multi_track_creator(app_data);
}