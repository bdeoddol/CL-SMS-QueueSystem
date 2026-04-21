#include <iostream>
#include <vector>
#include <queue>
#include <map>
// #include "QueueObject.h"
#include "Group.h"
#include "utilityFunc.h"

class GroupManager{
    public: 
        void addGroup();
        void addMember(Group* Group);
        
        //search for a group
        Group* searchGroup(std::string groupID);
        
        //return all queued groups
        std::vector<Group*> getActiveGroups();

        //return all queues groups in their order
        std::vector<Group*> getQueue();

        //pop group from queue, delete from active group
        Group popGroup();

        //Returns the next group in queue (used for info, do not use to pop from queue)
        Group* peekQueue();

        //sets the corresponding group to "dead" such that it will be popped immediately from the queue when it rises to the top, 
        //delete its pointer in the activeGroup tracker.
        void deleteGroup(std::string groupID);

    private:
        std::vector<Group*> _activeGroups;
        std::priority_queue<Group> _groupQueue;
        int _idTracker;

};