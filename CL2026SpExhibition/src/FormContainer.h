#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ns{
    class FormContainer{
    public:
        FormContainer();
        FormContainer(std::string Name, std::string Number, int projID, int groupSize, int msgID);
        /* 
            note to self: do not make a constructor within the obj type you want to deserialize a json into
            this is because nlohmann::json calls the default constructor  upon a line like 
                ns::FormConstructor fc; 
            because you have written a parametrized constructor, cpp does not include any default constructor (recall from basic cs103)
            OTHERWISE, ensure you have included a default constructor like the one above.

        cite:https://github.com/nlohmann/json#arbitrary-types-conversions
            When using get<your_type>(), your_type MUST be DefaultConstructible. (There is a way to bypass this requirement described later.)
        */

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
    
    //to serialize json obj/strings into your own types,
    //place json conversions within the same namespace as the type definition, do this for the function implementations as well
    void to_json(json& j, const FormContainer& fc);
    void from_json(const json& j, FormContainer& p);


    
}
