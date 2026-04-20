// #include <iostream>
// #include <cstring>
// #include "QueueObject.h"
// using namespace std;


// QueueObject::QueueObject(string phone, string name, int projID):_phoneNumber(phone),_fullName(name), _projectID(projID){
//     if(_projectID == 1){this->_awaitingProject = "86!";}
//     else if(_projectID == 2){this->_awaitingProject = "Desk Drawer";}
//     else if(_projectID == 3){this->_awaitingProject = "Frisson";}
//     else{this->_awaitingProject = "Invalid Project";}
//     sanitizeNumber();
//     if(validateNumber() == true){
//         _phoneNumber.insert(0,"+"); //prepend with "+" once ensured the number is valid
//         this->_validObj = true;
//     }
//     else{
//         this->_validObj = false;
//     }

// }   

//     //assuming this is a ten digit number based in the US
    
// void QueueObject::sanitizeNumber(){
//     string sanitizedDigits;
//     for(int i = 0; i < _phoneNumber.length(); i++){
//         if(isdigit(_phoneNumber[i]) == true){
//             sanitizedDigits.push_back(_phoneNumber[i]);
//         }
//     }
//     this->_phoneNumber = sanitizedDigits;

// }

// bool QueueObject::validateNumber(){
//     if(_phoneNumber.length() < 10){
//         return false;
//     }
//     else if((_phoneNumber.length() == 11) && (_phoneNumber[0] == '1')){
//         _phoneNumber = _phoneNumber.substr(1);
//         return true;
//     }
//     else if(_phoneNumber[0] < '2' || _phoneNumber[0] > '9'){
//         return false;
//     }
//     else if(_phoneNumber[3] < '2' || _phoneNumber[3] > '9'){
//         return false;
//     }
//     else if((_phoneNumber.length() > 10) ){
//         return false;
//     }
//     else{
//         return true;
//     }



// }