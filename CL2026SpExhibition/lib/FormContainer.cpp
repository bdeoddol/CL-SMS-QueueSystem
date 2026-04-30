#include "FormContainer.h"

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

namespace ns{
    //cite https://github.com/nlohmann/json#arbitrary-types-conversions
    /*
    Those methods MUST be in your type's namespace (which can be the global namespace), 
    or the library will not be able to locate them (in this example, they are in namespace ns, where person is defined).

    Those methods MUST be available (e.g., proper headers must be included) everywhere you use these conversions. Look at issue 1108 for errors that may occur otherwise.
    You must include the headers that define these methods in wherver you use them
    */
    void to_json(json& j, const FormContainer& fc){
        j = json{{"fullName" , fc._fullName}, {"primaryPhoneNumber", fc._primaryPhoneNumber}, {"projectID", fc._projectID}, {"groupSize", fc._groupSize}, {"msgID", fc._msgID}};
    }

    //In function from_json, use function at() to access the object values rather than operator[]. Example: j["fullName"] = p._fullName; 
    //In case a key does not exist, at throws an exception that you can handle, whereas operator[] exhibits undefined behavior.
    void from_json(const json& j, FormContainer& p) {
        j.at("_fullName").get_to(p._fullName);
        j.at("_primaryPhoneNumber").get_to(p._primaryPhoneNumber);
         j.at("_projectID").get_to(p._projectID);
         j.at("_groupSize").get_to(p._groupSize);
        j.at("_msgID").get_to(p._msgID);
    }





    FormContainer::FormContainer(){
        //default constructor;
    }

    FormContainer::FormContainer(std::string Name, std::string Number, int projID, int groupSize, int msgID):
        _fullName(Name), _primaryPhoneNumber(Number), _projectID(projID), _groupSize(groupSize), _msgID(msgID){

    } 
        
    std::string FormContainer::getFullName() const{
    return _fullName;
    }
    std::string FormContainer::getPrimaryNumber() const{
        return _primaryPhoneNumber;
    }    
    int FormContainer::getProjectID() const{
        return _projectID;
    }

    int FormContainer::getGroupSize() const{
        return _groupSize;
    }

    int FormContainer::getMsgID() const{
        return _msgID;
    }

}
