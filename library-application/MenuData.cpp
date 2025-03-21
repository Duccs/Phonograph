#include "MenuData.h"
#include "ActionFunctionData.h"
#include "ApplicationData.h"

bool MenuData::actionExistsAux(const std::string& name) const{
    return actions.find(name) != actions.end();
}

const std::string MenuData::actionPrefix(const std::string& name) const{
    for (const auto& action : actions) {
        if (name.substr(0, action.second.getPrefixLength()) == action.first) {
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
    if(actionExistsAux(name)) return true;
    std::string prefix = actionPrefix(name);
    if(!prefix.empty() && actionExistsAux(prefix)) return true;
    return false;
}

const ActionFunctionData& MenuData::getAction(const std::string& name){
    std::string prefix = actionPrefix(name);
    if (!prefix.empty()) {
        auto it = actions.find(prefix);
        if (it != actions.end()) {
            return it->second;
        }
    }

    static ActionFunctionData defaultAction;
    auto it = actions.find(name);
    return (it != actions.end()) ? it->second : defaultAction;
}

void MenuData::printActionHelp(std::ostream& out) const{
    out << "Options are:\n";
    for (const auto& action : actions) {
        out << "  " << action.first << " - " << action.second.getDescription() << "\n";
    }
    out << "\n";
}