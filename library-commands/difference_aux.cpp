#include "difference_aux.h"

#include <cmath>

int difference(ApplicationData& app_data) {
    double Minuend = app_data.getDouble("Minuend: ");
    double Subtrahend = app_data.getDouble("Subtrahend: ");
    double Difference = Minuend - Subtrahend;
    app_data.getOutputStream() << "Difference " << Difference << std::endl;
    if (Difference < 0) {
        return 1;
    } else if (Difference > 0) {
        return 2;
    }
    return 0;
}