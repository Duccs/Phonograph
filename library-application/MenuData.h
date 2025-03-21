#ifndef _MENU_DATA_H_
#define _MENU_DATA_H_

#include <map>
#include <string>

class ActionFunctionData;

class MenuData {
    protected:
        std::map<std::string, ActionFunctionData> actions;

        bool actionExistsAux(const std::string& name) const;
        const std::string actionPrefix(const std::string& name) const;

    public:
        MenuData();
        void addAction(const ActionFunctionData& function);
        bool actionExists(const std::string& name) const;
        const ActionFunctionData& getAction(const std::string& name);
        void printActionHelp(std::ostream& out) const;
};

#endif /* _MENU_DATA_H_ */