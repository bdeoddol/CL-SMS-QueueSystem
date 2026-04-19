#include "QueueObject.h"
#include "Group.h"
#include <string>
#include <vector>
#include <random>
using namespace std;

int generate4digNum(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1,9999);

    return distrib(gen);
}