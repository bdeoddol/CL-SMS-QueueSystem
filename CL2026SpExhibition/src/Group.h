// #include "QueueObject.h"
#include <string>
#include <vector>


class Group{
    public:

        /*
    projID
    1 = 86!
    2 = Frission
    3 = Desk Drawer
    */
    // void addMember(QueueObject person);
    Group(std::string Name, std::string Number, int projID, int size);    
    Group();
    void killGroup();

    //upon construction, sanitize/validate number and determine if the number is valid
    std::string sanitizeNumber(std::string Number);
    bool validateNumber(std::string Number);
    
    //When the queue in a group is popped. All groups will incremenet an elapsed wait time since their arrival in the queue
    void incrementElapsedWait();
    
    //Used by GroupManager to set groupID. Kinda like a name. Format: G-##
    void setGroupID(std::string groupID);

    //returns the string ID of the Group, "G-###"
    std::string getGroupID() const;

    //this is to determine priority
    //effective priority is calculated by totalpriority = groupsize * 10 + priority boost
    int getGroupSize() const;
    int getBoostVal() const;
    
    int getIncrementPosition() const;  //returns the numerical ID of the Group or otherwise known as the incremental position. EX: "G-4" returns 4
    void setIncrementPosition(int groupID); //the numerical order in which the group has arrived. i.e the 4th groups in the queue will have a position of 4. This is how we determine their ID
    

    //book keeping
    std::string getPrimaryName() const;
    std::string getNumber() const;
    std::vector<std::string> getSecondaryNumbers() const;
    std::string getAwaitingProject() const;
    int getProjectID();
    
    bool _validObj;

    private: 
        std::string _fullName;  
        std::string _primaryPhoneNumber;
        int _projectID;
        int _groupSize;
        int _msgID;    
    std::string _groupID; //generated externally 
    std::vector<std::string> _secondaryPhoneNumbers;
    int _incrementPosition;
    int _popsSinceArrival;
    int _priorityBoost;
    
    
    
    std::string _awaitingProject;    
  
    bool dead;
};

