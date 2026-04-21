#include <iostream>
#include "Group.h"

class GroupCompare{
    public:
    //operator overload for comp() for a given class comp or in this case, "GroupCompare"=> GroupCompare()
    //should ONLY return TRUE if the first argument is LESS than the second argument when the heap calls the comparison class GroupCompare.
    //https://en.cppreference.com/cpp/algorithm/push_heap 
    bool operator()(const Group& a, const Group& b) const;

    private:

};