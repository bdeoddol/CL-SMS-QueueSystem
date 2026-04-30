# CL-SMS-Queue-System
##  A real-time, multi-threaded system integrating network and hardware inputs
This project has been closed temporarily. It has been deployed on 4/30/2026 <br>
Below are points of feedback and notes taken during it's deployment for future improvement <br>
*   While this project was intended to function similar to a waitlist at a restaurant by organizing groups under a single name and contact, many submissions turned out to be singles from the same group
    * enforce group based submission
    * allow manual group creation/deletion/modification

*   Project wait times were significantly longer than expected
    * require projects to reduce their exhibition time

*   Program occasionally crashed for no known reason
    * support save/load feature
    * It's possible to not process directly and save groups into a database instead before processing

* Priority based queueing lead to samller groups "starving"
    * modify the priority boost to occur more frequently or increased boost value
    * modify  TotalPriority = .getGroupSize()*10 + .getBoostVal(); priority evaluation

 *  Support automated sms messaging
 *  Some group were considered no show
    * Devise feedback system to handle no show signal
    * Possibly include a timer

*   Some groups no longer intended to stay in queue
    * Allow manual deletion of group

*   Some groups were taken in without queue submission
    * Enforce queue systems

*   Projects sought to maximize group sizes by taking members from smaller groups to fill in space
    * This fix could require  restructuring the system to handle individual based submission
        * individuals submit and are processed in groups every "pop"
    * This could also be fixed by including a "merge" groups feature

* Some groups only have single individuals
    * Include a merge group feature

* CLI was difficult to read when presenting groups
    * fix front end
    * overhaul the UI
    * design intuitive "page" oriented design

*   For the purposes of exhibition, it is advised to do standard queueing instead of priority queueing

* Does not support disconnect/reconnect feature on the java end, rendering the cpp reconnect/disconnect

* App::programstatus is throwing error when attempting to call via CLI Menu command 1

* Project leads were not reliable to notify popping from their queues

* Group class construction is designed to handle 86!, Frisson, and Desk Drawer. If the projID during construction does map to any of these, it is an invalid group. 
    * Ensure future builds are adaptable to a number of groups determined ahead of time via main()

* Ensure google form spreadsheet matches 1-to-1 fields found in the Java Parser and CPP Parser
    * Name -> Phone Number -> Project ID -> Group Size
 
* Groups next in queue were not handled properly. Leading to multiple arriving
   * Enforce via button based signal to request pop
   * Request should provide relevant gorup information
   * Allow to accept or reject the pop from queue
    * During deployment, the columsn found in the spreadsheet did not align with the comma seperated fields in the parser. Risha had to swap the fields in the object construction to fix this. Ensure that this is reverted.


* Program status should offer more information
