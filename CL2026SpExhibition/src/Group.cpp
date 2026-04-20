// #include "QueueObject.h"
#include "Group.h"
#include <string>
using namespace std;

Group::Group(string Name, string ID, string Number, int projID):
            _fullName(Name), _GroupID(ID), _projectID(projID)
{
    this->dead = false;
    this->_validObj = true;

    _primaryPhoneNumber = sanitizeNumber(Number);
    _validObj = validateNumber(_primaryPhoneNumber);
    


    if(_projectID == 1){this->_awaitingProject = "86!";}
    else if(_projectID == 2){this->_awaitingProject = "Desk Drawer";}
    else if(_projectID == 3){this->_awaitingProject = "Frisson";}
    else{
        this->_awaitingProject = "Invalid Project";
        this->_validObj = false;    
    }

}

// void Group::addMember(QueueObject person){
//     _QueueObjs.push_back(person);
// }

void Group::killGroup(){
    this->dead = true;
}

    //assuming this is a ten digit number based in the US
    
string Group::sanitizeNumber(string Number){
    string sanitizedDigits;
    for(int i = 0; i < Number.length(); i++){
        if(isdigit(Number[i]) == true){
            sanitizedDigits.push_back(Number[i]);
        }
    }
     
    return sanitizedDigits;
}

bool Group::validateNumber(string Number){
    if(Number.length() < 10){
        return false;
    }
    else if((Number.length() == 11) && (Number[0] == '1')){
        Number = Number.substr(1);
        return true;
    }
    else if(Number[0] < '2' || Number[0] > '9'){
        return false;
    }
    else if(Number[3] < '2' || Number[3] > '9'){
        return false;
    }
    else if((Number.length() > 10) ){
        return false;
    }
    else{
        return true;
    }



}