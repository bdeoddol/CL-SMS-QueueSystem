#include <tabulate/table.hpp>
//#include "App.h"

using namespace std;
using namespace tabulate;

void programStatus();

int main(){
    cout << "hi" << endl;
    programStatus();
}

void App::programStatus(){
    Table groups;
    groups.add_row({"Group Name", "Project", "Group Size","Primary Phone", "Secondary Phones" });
    groups[0].format().font_style({FontStyle::bold});
    for(int i = 0; i < _managers.size(); i++){
        GroupManager* curr = _managers[i];
        const vector<Group>& currProject = curr->getActiveGroups();
        for(int j = 0; j < currProject.size(); j++){
            const Group& g = currProject[j];
            string secondaryNums = secondaryNumHelper(g.getSecondaryNumbers());
            groups.add_row({g.getPrimaryName(), g.getAwaitingProject(), to_string(g.getGroupSize()), g.getPrimaryNumber(), secondaryNums});
        }
    }
    cout << groups;
}

string App::secondaryNumHelper(vector<std::string> numbers){
    string nums = "";
    for(int i = 0; i < numbers.size(); i++){
        nums += numbers[i];
        if(i < numbers.size() - 1){
            nums += "\n";
        }
    }
    return nums;
}