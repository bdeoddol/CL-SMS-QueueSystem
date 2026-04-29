#ifndef GROUPCOMPARE_H
#define GROUPCOMPARE_H

#include "Group.h"

class GroupCompare{
    public:
    bool operator()(const Group& a, const Group& b) const;
};

#endif
