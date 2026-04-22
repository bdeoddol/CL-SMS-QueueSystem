#include <iostream>
#include <string>
#include "FormContainer.h"
using namespace std;


FormContainer::FormContainer(std::string Name, std::string Number, int projID, int groupSize):
    _fullName(Name), _primaryPhoneNumber(Number), _projectID(projID), _groupSize(groupSize){

} 
    
std::string FormContainer::getFullName(){
 return _fullName;
}
std::string FormContainer::getPrimaryNumber(){
    return _primaryPhoneNumber;
}    
int FormContainer::getProjectID(){
    return _projectID;
}

int FormContainer::getGroupSize(){
    return _groupSize;
}