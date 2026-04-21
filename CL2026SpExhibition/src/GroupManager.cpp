#include <iostream>
#include <vector>
#include <algorithm>
#include "Group.h"
#include "GroupManager.h"
#include "GroupCompare.h"
#include "utilityFunc.h"

using namespace std;

GroupManager::GroupManager(int projID){
    if(projID == 1){this->_manageProject = "86!";}
    else if(projID == 2){this->_manageProject = "Frisson";}
    else if(projID == 3){this->_manageProject = "Desk Drawer";}
}

void GroupManager::addGroup(Group groupAddition){
    if(groupAddition._validObj == false){
        cout << "Bad data being inserted. Fields listed as " << endl;
        cout << "Group ID: " << groupAddition.getGroupID() << endl;
        cout << "Group Primary Name: " << groupAddition.getPrimaryName() << endl;
        cout << "Contact field failed at: " <<  groupAddition.getNumber() << endl;

        return;
    }

    this->_activeGroups.push_back(groupAddition);
    push_heap(this->_activeGroups.begin(), this->_activeGroups.end(), GroupCompare());
}
// void addMember();

//search for a group
Group* GroupManager::searchGroup(std::string groupID){
    vector<Group>::iterator it;
    for(it = this->_activeGroups.begin(); it != this->_activeGroups.end(); ++it){
        if(it->getGroupID() == groupID){
            return &(*it); //return the address of the object in the vector that "it" is pointing at
        }
    }

    cout << "Group Not Found, returning null..." << endl;
    return nullptr;
}

//return all queued groups
std::vector<Group> GroupManager::getActiveGroups(){
    return this->_activeGroups;
}

//pop group from queue to retrieve its info
Group GroupManager::popGroup(){
    if(_activeGroups.empty() == true){
        cout << "GroupManager for Project: " << _manageProject << " has no queue Groups at this time. Returning a group marked invalid.." << endl;
        Group badGroup = Group("bad", "bad", "bad", 0, 0,0);
        badGroup._validObj = false;
        return badGroup;
    }
    pop_heap(this->_activeGroups.begin(), this->_activeGroups.end(), GroupCompare()); //send top element to back of queue
    Group retGroup = _activeGroups.back();
    _activeGroups.pop_back(); //remove the back element

    //increment elapsed wait time for all groups
    for(int i = 0; i < _activeGroups.size(); i++){
        _activeGroups[i].incrementElapsedWait();
    }
    //reheapify the queue such that the new priorities are evaluated
    make_heap(_activeGroups.begin(), _activeGroups.end(), GroupCompare());
    

    return retGroup;
}

//Returns the next group in queue (used for info, do not use to pop from queue)
Group* GroupManager::peekQueue(){
    return &_activeGroups.front();
}

//delete Group from queue, reorganize the heap.
void GroupManager::deleteGroup(std::string groupID){
    for(int i = 0; i < this->_activeGroups.size(); i++){
        if(_activeGroups[i].getGroupID() == groupID){
            _activeGroups.erase(_activeGroups.begin() + i);
            make_heap(this->_activeGroups.begin(), this->_activeGroups.end(), GroupCompare());
            break;
        }
    }
    return;
}
