#include <iostream>
#include <string>


class FormContainer{
    public:
    FormContainer(std::string Name, std::string Number, int projID, int groupSize, std::string msgID);
    std::string getFullName();
    std::string getPrimaryNumber();
    int getProjectID();
    int getGroupSize();



    private:
    std::string _fullName;
    std::string _primaryPhoneNumber;
    int _projectID;
    int _groupSize;
    std::string _msgID;

};