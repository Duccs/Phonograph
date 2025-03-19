#include "instrument_test_aux.h"
#include <iostream>

int main() {
  ApplicationData app_data(std::cin, std::cout);
  return instrument_test(app_data);
}