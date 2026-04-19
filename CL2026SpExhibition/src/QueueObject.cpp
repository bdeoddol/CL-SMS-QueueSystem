#include <iostream>
#include <cstring>
#include "QueueObject.h"
using namespace std;


QueueObject::QueueObject(string phone, string name, int projID):phoneNumber(phone),fullName(name), projectID(projID){
    if(projectID == 1){this->awaitingProject = "86!";}
    else if(projectID == 2){this->awaitingProject = "Desk Drawer";}
    else if(projectID == 3){this->awaitingProject = "Frisson";}
    else{this->awaitingProject = "Invalid Project";}
    sanitizeNumber();
    if(validateNumber() == true){
        phoneNumber.insert(0,"+"); //prepend with "+" once ensured the number is valid
        this->validObj = true;
    }
    else{
        this->validObj = false;
    }

}   

    //assuming this is a ten digit number based in the US
    
void QueueObject::sanitizeNumber(){
    string sanitizedDigits;
    for(int i = 0; i < phoneNumber.length(); i++){
        if(isdigit(phoneNumber[i]) == true){
            sanitizedDigits.push_back(phoneNumber[i]);
        }
    }
    this->phoneNumber = sanitizedDigits;

}

bool QueueObject::validateNumber(){
    if(phoneNumber.length() < 10){
        return false;
    }
    else if((phoneNumber.length() == 11) && (phoneNumber[0] == '1')){
        phoneNumber = phoneNumber.substr(1);
        return true;
    }
    else if(phoneNumber[0] < '2' || phoneNumber[0] > '9'){
        return false;
    }
    else if(phoneNumber[3] < '2' || phoneNumber[3] > '9'){
        return false;
    }
    else if((phoneNumber.length() > 10) ){
        return false;
    }
    else{
        return true;
    }



}