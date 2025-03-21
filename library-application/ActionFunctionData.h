#ifndef _ACTION_FUNCTION_DATA_H_
#define _ACTION_FUNCTION_DATA_H_

#include <string>

class ApplicationData;

class ActionFunctionData {
    public:
        typedef void (*ActionFunctionType)(ApplicationData&);

    protected:
        std::string name;
        ActionFunctionType function;
        std::string description;
        int prefix_length;
    
    public:
        ActionFunctionData();
        ActionFunctionData(const std::string& name, const ActionFunctionType& function, const std::string& description);
        ActionFunctionData(const std::string& name, const ActionFunctionType& function, const std::string& description, const int prefix_length);

        const std::string& getName() const;
        ActionFunctionType getFunction() const;
        const std::string& getDescription() const;
        int getPrefixLength() const;

        void setName(const std::string& name);
        void setFunction(ActionFunctionType function); 
        void setDescription(const std::string& description); 
        void setPrefixLength(const int length);
};

#endif /* _ACTION_FUNCTION_DATA_H_ */