#include <iostream>
#include <string>
#include <vector>
#include "GroupManager.h"

class App{
  public:
    void displayOptions();
    void handle(std::string input);

  private:
    void programStatus();
    void groupManagerStatus(std::string manager_id);
    bool pauseParse();
    bool resumeParse();
    void pop(int project_id);
    void showActiveGroups(int project_id);
    void connectToJavaServer();

    bool _paused;

    vector<GroupManager> _managers;
};