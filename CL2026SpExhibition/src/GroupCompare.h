#pragma once
#include <iostream>
#include "Group.h"

class GroupCompare{
    public:
    bool operator()(const Group& a, const Group& b) const;
};

#endif
