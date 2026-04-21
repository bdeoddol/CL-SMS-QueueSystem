#include <iostream>
#include <vector>
#include <algorithm>
#include "Group.h"
#include "utilityFunc.h"
// #include "QueueObject.h"

class GroupManager{
    public: 
        /*
        projID
        1 = 86!
        2 = Frission
        3 = Desk Drawer
        */
        GroupManager(int projID);

        void addGroup(Group groupAddition, std::string groupID);
        // void addMember(std::string groupID, std::string );
        
        //search for a group
        Group* searchGroup(std::string groupID);
        
        //return all queued groups
        std::vector<Group> getActiveGroups();

        //pop group from queue, and retrieve its infor
        Group popGroup();

        //Returns the next group in queue (used for info, do not use to pop from queue)
        Group* peekQueue();

        //delete Group from queue, reorganize the heap.
        void deleteGroup(std::string groupID);

    private:
        std::vector<Group> _activeGroups;
        int _idTracker;
        int _projectID;
        std::string _manageProject;

};