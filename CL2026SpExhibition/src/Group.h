// #include "QueueObject.h"
#include <string>
#include <vector>


class Group{
    public:
    // void addMember(QueueObject person);
    void killGroup();
    std::string sanitizeNumber(std::string Number);
    bool validateNumber(std::string Number);
    Group(std::string Name, std::string ID, std::string Number, int projID);    

    private: 
    std::string _fullName;  
    std::string _GroupID; //generated externally 
    std::string _primaryPhoneNumber;
    int _projectID;
    
    std::string _awaitingProject;    


    bool _validObj;  
    bool dead;
};