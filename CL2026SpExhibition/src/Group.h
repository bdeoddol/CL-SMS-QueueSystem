// #include "QueueObject.h"
#include <string>
#include <vector>


class Group{
    public:
    // void addMember(QueueObject person);
    Group(std::string Name, std::string ID, std::string Number, int projID, int size, int incrementPosition);    
    void killGroup();
    std::string sanitizeNumber(std::string Number);
    bool validateNumber(std::string Number);
    void incrementElapsedWait();
    int getGroupSize() const;
    int getIncrementPosition() const;
    std::string getGroupID() const;
    int getBoostVal() const;
    std::string getPrimaryName() const;
    std::string getNumber() const;
    
    bool _validObj;

    private: 
    std::string _fullName;  
    std::string _groupID; //generated externally 
    std::string _primaryPhoneNumber;
    std::vector<std::string> _secondaryPhoneNumbers;
    int _projectID;
    int _groupSize;
    int _incrementPosition;
    int _popsSinceArrival;
    int _priorityBoost;
    
    
    std::string _awaitingProject;    
  
    bool dead;
};

