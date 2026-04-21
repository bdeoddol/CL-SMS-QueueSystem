// #include "QueueObject.h"
#include <string>
#include <vector>


class Group{
    public:
    // void addMember(QueueObject person);
    Group(std::string Name, std::string ID, std::string Number, int projID);    
    void killGroup();
    std::string sanitizeNumber(std::string Number);
    bool validateNumber(std::string Number);
    

    private: 
    std::string _fullName;  
    std::string _GroupID; //generated externally 
    std::string _primaryPhoneNumber;
    int _projectID;
    
    std::string _awaitingProject;    


    bool _validObj;  
    bool dead;
};