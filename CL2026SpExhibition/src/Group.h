#ifndef GROUP_H
#define GROUP_H

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
        Group(std::string Name, std::string Number, int projID, int size);
        Group();
        void killGroup();

        std::string sanitizeNumber(std::string Number);
        bool validateNumber(std::string Number);

        void incrementElapsedWait();

        void setGroupID(std::string groupID);
        std::string getGroupID() const;

        int getGroupSize() const;
        int getBoostVal() const;

        int getIncrementPosition() const;
        void setIncrementPosition(int groupID);

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
        std::string _groupID;
        std::vector<std::string> _secondaryPhoneNumbers;
        int _incrementPosition;
        int _popsSinceArrival;
        int _priorityBoost;
        std::string _awaitingProject;
        bool dead;
};

#endif
