#include "menu_test_aux.h"

void menuUI(ApplicationData& app_data) {
    app_data.menuData.printActionHelp(app_data.getOutputStream());
}