#include "menu_test_aux.h"

void menuUI(ApplicationData& app_data) {
    app_data.printActionHelp();
}

void commentUI(ApplicationData& app_data) {
    app_data.clearToEOL();
}

void echoUI(ApplicationData& app_data){
    std::string input;
    std::getline(app_data.getInputStream(), input);
    app_data.getOutputStream() << input << std::endl;
}

void quitUI(ApplicationData& app_data){
    app_data.setDone(true);
}

int register_menu_test_commands(ApplicationData& app_data){
    app_data.addAction(ActionFunctionData("#", commentUI, "Skip to end of line (comment).", 1));
    app_data.addAction(ActionFunctionData("comment", commentUI, "Skip to end of line (comment)."));
    app_data.addAction(ActionFunctionData("echo", echoUI, "Echo back the arguments given."));
    app_data.addAction(ActionFunctionData("help", menuUI, "Display help message."));
    app_data.addAction(ActionFunctionData("menu", menuUI, "Display help message."));
    app_data.addAction(ActionFunctionData("quit", quitUI, "Terminate the program."));

    return 0;
}

int menu_test(ApplicationData& app_data) {
    register_menu_test_commands(app_data);
    app_data.mainLoop();
    return 0;
}