// #ifndef QueueObject
// #define QueueObject
#include <string>
#include <iostream>

    class QueueObject{
        public:
            
            QueueObject(std::string phone, std::string name, int projectID);
            void sanitizeNumber();
            bool validateNumber();

            




        private:

            
            std::string phoneNumber;
            std::string fullName;
            int projectID;
            std::string awaitingProject;    
            bool validObj;  
    };





// #endif