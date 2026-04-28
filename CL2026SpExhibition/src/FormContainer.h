#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ns{
    class FormContainer{
    public:
        FormContainer();
        FormContainer(std::string Name, std::string Number, int projID, int groupSize, int msgID);

        std::string getFullName() const;
        std::string getPrimaryNumber() const;
        int getProjectID() const;
        int getGroupSize() const;
        int getMsgID() const;

        std::string _fullName;
        std::string _primaryPhoneNumber;
        int _groupSize;
        int _projectID;
        int _msgID;
    };

    void to_json(json& j, const FormContainer& fc);
    void from_json(const json& j, FormContainer& p);
}

#endif
