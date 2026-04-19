#include "QueueObject.h"
#include "Group.h"
#include <string>
using namespace std;

Group::Group(string ID):GroupID(ID){

}

void Group::addToGroup(QueueObject person){
    QueueObjs.push_back(person);
}