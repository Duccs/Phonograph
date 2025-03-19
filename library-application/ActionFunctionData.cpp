#include "ActionFunctionData.h"
#include "ApplicationData.h"

ActionFunctionData::ActionFunctionData(): name(""), function(0), description(""), prefix_length(0){}

ActionFunctionData::ActionFunctionData(const std::string& name, const ActionFunctionType& function, const std::string& description)
    : name(name), function(function), description(description), prefix_length(0) {}

ActionFunctionData::ActionFunctionData(const std::string& name, const ActionFunctionType& function, const std::string& description, const int prefix_length)
    : name(name), function(function), description(description), prefix_length(prefix_length) {}

const std::string& ActionFunctionData::getName() const { return name; }
ActionFunctionData::ActionFunctionType ActionFunctionData::getFunction() const { return function; }
const std::string& ActionFunctionData::getDescription() const { return description; }
int ActionFunctionData::getPrefixLength() const { return prefix_length; }

void ActionFunctionData::setName(const std::string& name) { this->name = name; }
void ActionFunctionData::setFunction(ActionFunctionType function) { this->function = function; }
void ActionFunctionData::setDescription(const std::string& description) { this->description = description; }
void ActionFunctionData::setPrefixLength(const int length) { this->prefix_length = length; }