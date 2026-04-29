#include <iostream>
#include "Group.h"
#include "GroupCompare.h"

//'a' should evaluate to TRUE if 'a' has LOWER priority
bool GroupCompare::operator()(const Group& a, const Group& b) const{
    ////combine groupsize and priorityboost into a "total priority", evaluate total priority
    //this evaluates to a<=b
    int aTotalPriority = a.getGroupSize()*10 + a.getBoostVal();
    int bTotalPriority = b.getGroupSize()*10 + b.getBoostVal();
    if(aTotalPriority != bTotalPriority){
        //if 'a' has a higher TotalPriority than 'b', evaluate to false, such that it is false that 'a' has a LOWER priority
        if(aTotalPriority > bTotalPriority){
            return false;
        }
        return true;
    }

    else{
        //if the size is the same, consider their arrival order and starvation state, we can check arrival order based on groupID which is incremental
        //note that this should ONY return TRUE if the first argument, we are comparing relative to Group a.
        if(a.getIncrementPosition() > b.getIncrementPosition()){
            return true;
        }
        else{
            return false;
        }

    }
}