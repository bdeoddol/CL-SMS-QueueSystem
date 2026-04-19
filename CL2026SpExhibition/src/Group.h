#include "QueueObject.h"
#include <string>
#include <vector>


class Group{
    public:
    void addToGroup(QueueObject person);
    Group(std::string ID);    

    private:    
    std::string GroupID; //generated externally 
    std::vector<QueueObject> QueueObjs;
};