#pragma once
#include "Group.h"
#include "GroupManager.h"
#include "FormContainer.h"
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CParser{
    public:
        ns::FormContainer parseJsonString(std::string jsonString);
        Group convertFormContainerToGroup(ns::FormContainer group);
};

#endif
