#include <iostream>
#include <vector>
#include <algorithm>
#include "Group.h"
#include "GroupManager.h"
#include "GroupCompare.h"
#include "utilityFunc.h"

using namespace std;

GroupManager::GroupManager(int projID, string ProjectName){
    this->_projectID = projID;
    this->_manageProject = ProjectName;

    // if(projID == 1){this->_manageProject = "86!";}
    // else if(projID == 2){this->_manageProject = "Frisson";}
    // else if(projID == 3){this->_manageProject = "Desk Drawer";}
    _idTracker = 0;
}

void GroupManager::addGroup(Group groupAddition, string groupID){
    if(groupAddition._validObj == false){
        cout << "! Bad data being inserted. Fields listed as " << endl;
        cout << "! Group ID: " << groupAddition.getGroupID() << endl;
        cout << "! Group Primary Name: " << groupAddition.getPrimaryName() << endl;
        cout << "! Contact field failed at: " <<  groupAddition.getNumber() << endl;

        return;
    }
    groupAddition.setIncrementPosition(_idTracker); //the id tracker labels groups incrementally. As they are passed into the queue, they are labeled by their order of arrival. This is also the ID for their group
    groupAddition.setGroupID(generateGroupID());
    this->_activeGroups.push_back(groupAddition);
    push_heap(this->_activeGroups.begin(), this->_activeGroups.end(), GroupCompare());
}

string GroupManager::generateGroupID(){
    string newID = "G" + to_string(this->_projectID) + "-" + to_string(this->_idTracker);

    this->_idTracker++;
    return newID;
}
// void addMember();

//search for a group
Group* GroupManager::searchGroup(string groupID){
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
vector<Group> GroupManager::getActiveGroups(){
    return this->_activeGroups;
}

//get name of project this gruopmanager is manager
string GroupManager::getProjectName(){
    return _manageProject;
}

//pop group from queue to retrieve its info
Group GroupManager::popGroup() {

    while (!_activeGroups.empty()) {

        pop_heap(_activeGroups.begin(), _activeGroups.end(), GroupCompare());
        Group retGroup = _activeGroups.back();
        _activeGroups.pop_back();

        // increment wait time for remaining groups
        for (int i = 0; i < _activeGroups.size(); i++) {
            _activeGroups[i].incrementElapsedWait();
        }

        make_heap(_activeGroups.begin(), _activeGroups.end(), GroupCompare());

        //return only if valid
        if (retGroup._validObj) {
            return retGroup;
        }

        //otherwise skip and continue loop
    }

    // nothing valid left
    cout << "! No valid groups in queue for project: " << _manageProject << endl;
    return Group();  // invalid group
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

int GroupManager::getProjectId(){
    return this->_projectID;
}
