#include "QueueObject.h"
#include "Group.h"
#include <string>
#include <vector>
#include <random>
#include <iostream>
using namespace std;

int generate4digNum(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1,9999);

    return distrib(gen);
}

void printGroup(Group group){
    //name, primary and seecondary phone numbers, awaiting project
    cout << "Group Name: " << group.getPrimaryName() << endl;
    cout << "Awaiting Project: " << group.getAwaitingProject() << endl;
    cout << "------------------------------" << endl;
    cout << "Primary Phone Number: " << group.getNumber() << endl;
    cout << "Secondary Phone Numbers: " << endl;
    vector<string> secondaryNumbers = group.getSecondaryNumbers();
    for(int i = 0; i < secondaryNumbers.size(); i++){
        cout << secondaryNumbers[i] << endl;
    }
    cout << "------------------------------" << endl << endl;
}