#include "Cparser.h"
#include "Group.h"
#include "GroupManager.h"
#include "FormContainer.h"

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


ns::FormContainer CParser::parseJsonString(std::string jsonString){
    json jsonObj = json::parse(jsonString);
     ns::FormContainer data = jsonObj.get<ns::FormContainer>();


    //Group(string Name, string Number, int projID, int size)


    return data;
}

Group CParser::convertFormContainerToGroup(ns::FormContainer fc){
    //Group(std::string Name, std::string Number, int projID, int size);   
    Group retGroup = Group(fc.getFullName(), fc.getPrimaryNumber(), fc.getProjectID(), fc.getGroupSize());

    return retGroup;
}