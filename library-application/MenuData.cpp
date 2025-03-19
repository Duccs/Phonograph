#include "MenuData.h"

bool MenuData::actionExistsAux(const std::string& name) const{
    return actions.find(name) != actions.end();
}

const std::string MenuData::actionPrefix(const std::string& name) const{
    for (const auto& action : actions) {
        if (name.find(action.first) == 0 && action.first.length() == action.second.getPrefixLength()) {
            return action.first;
        }
    }
    return "";
}

MenuData::MenuData() {}

void MenuData::addAction(const ActionFunctionData& function) {
    if(!actionExistsAux(function.getName())) {
        actions[function.getName()] = function;
    }
}

bool MenuData::actionExists(const std::string& name) const {
    return actionExistsAux(name) || !actionPrefix(name).empty();
}

const ActionFunctionData& MenuData::getAction(const std::string& name){
    auto it = actions.find(name);
    return (it != actions.end()) ? it->second : ActionFunctionData();
}

void MenuData::printActionHelp(std::ostream& out) const{
    out << "Options are:\n";
    for (const auto& action : actions) {
        out << "  " << action.first << " - " << action.second.getDescription() << ".\n";
    }
}