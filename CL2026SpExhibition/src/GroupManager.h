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
       //give the groupmanager an ID and the name of the project it will be handling.
        GroupManager(int projID, string ProjectName);

       //get the numerical ID of the project/group
        int getProjectId();

        //add a group to the queue
        void addGroup(Group groupAddition);
        // void addMember(std::string groupID, std::string );
        
        //search for a group given their groupID
        Group* searchGroup(std::string groupID);
        
        //return all queued groups
        std::vector<Group> getActiveGroups();

        //get name of project htis manager is managing
        std::string getProjectName();

        //pop group from queue, and retrieve its infor
        Group popGroup();

        //Returns the next group in queue (used for info, do not use to pop from queue)
        Group* peekQueue();

        //delete Group from queue, reorganize the heap.
        void deleteGroup(std::string groupID);

        //generates the gruop id using the current value and formats it as "G-[_idTracker]"
        string generateGroupID();

    private:
        std::vector<Group> _activeGroups;
        int _idTracker;
        int _projectID;
        std::string _manageProject; //the name of the project it is managing

};