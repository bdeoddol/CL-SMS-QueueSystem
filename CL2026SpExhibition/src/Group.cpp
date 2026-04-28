// #include "QueueObject.h"
#include "Group.h"
#include <string>
using namespace std;

Group::Group(){
    this->_validObj = false;
}

Group::Group(string Name, string Number, int projID, int size):
            _fullName(Name), _projectID(projID),_groupSize(size)
{
    this->dead = false;
    this->_validObj = true;
    this->_priorityBoost = 0;
    this->_popsSinceArrival = 0;
    this->_groupID = "-1";


    _primaryPhoneNumber = sanitizeNumber(Number);
    if(validateNumber(_primaryPhoneNumber) == false){
        this->_validObj = false;
        return;
    }
    

    if(projID == 1){this->_awaitingProject = "86!";}
    else if(projID == 2){this->_awaitingProject = "Frisson";}
    else if(projID == 3){this->_awaitingProject = "Desk Drawer";}
    else{
        this->_awaitingProject = "Invalid projectID!";
        this->_validObj = false;
        return;
        
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

string Group::getNumber() const{
    return _primaryPhoneNumber;
}

string Group::getPrimaryName() const{
    return _fullName;
}

int Group::getGroupSize() const{
    return this->_groupSize;
}

int Group::getIncrementPosition() const{
    return this->_incrementPosition;
}
void Group::setIncrementPosition(int groupID){
    this->_incrementPosition = groupID;
}

string Group::getGroupID() const{
    return this->_groupID;
}

void Group::incrementElapsedWait(){
    this->_popsSinceArrival++;
    if(_popsSinceArrival%6==0){
        _priorityBoost += max(0,(5 - _groupSize));
        //this ensures that those with smaller group sizes get a larger boost relative to those that have larger group sizes
        //boosts only occur if the group has been in queue for every 6th pop so about 30 minutes, each pop occuring every 5 miuntes for a typical project.
    }
}

int Group::getBoostVal() const{
    return _priorityBoost;
}

vector<string> Group::getSecondaryNumbers() const{
    return _secondaryPhoneNumbers;
}

string Group::getAwaitingProject() const{
    return _awaitingProject;
}

void Group::setGroupID(string groupID){
    this->_groupID = groupID;
}

int Group::getProjectID(){
    return _projectID;
}
