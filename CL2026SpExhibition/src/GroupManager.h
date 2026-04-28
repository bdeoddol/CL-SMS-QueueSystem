#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Group.h"

class GroupManager{
    public:
        /*
        projID
        1 = 86!
        2 = Frission
        3 = Desk Drawer
        */
       //give the groupmanager an ID and the name of the project it will be handling.
        GroupManager(int projID, std::string ProjectName);

        int getProjectId();
        void addGroup(Group groupAddition);
        Group* searchGroup(std::string groupID);
        std::vector<Group> getActiveGroups();
        std::string getProjectName();
        Group popGroup();
        Group* peekQueue();
        void deleteGroup(std::string groupID);

        //generates the gruop id using the current value and formats it as "G-[_idTracker]"
        std::string generateGroupID();

    private:
        std::vector<Group> _activeGroups;
        int _idTracker;
        int _projectID;
        std::string _manageProject;
};

#endif
