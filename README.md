### CL-SMS-QueueSystem

A command line interface program that manages a queue system for Creative Labs @ USC

This project is a queue system designed to take input from a Google Form and queues people into groups into a game-like party system

Upon the next group’s turn, their information should include their phone number that will be used to send an SMS text notification

note for next semester buy this to support sms texting: 

https://www.amazon.com/waveshare-SIM7600G-H-DONGLE-Adapter-Communication/dp/B08CSB596W 


### Google Form

## Google Forms requires:
* full name
* phone number
* projectID -> 1 = 86, 2 = frissions, 3 = desk drawer

## Is person a group leader or not?

* if yes, generate groupID
* if no, join group via groupID

All stored in a .csv file

### Object Hierarchy

## app

* CLI interface
 check status of program
* check status of specified group managers 
    * (each project will have its own group manager)
* pause/resume parse
* receive and confirmation to pop from specified project queue
* request show all active groups from all groupManagers 
    * (should be organized)
    * _extra_:
        * should be it's own page, therefore clear the terminal
        * allow feature to return to the menu once finished viewing. clear the terminal, and display the menu again
* request show queues from all groupManagers 
    * (should be organized)
    * _extra_:
        * should be it's own page, therefore clear the terminal
        * allow feature to return to the menu once finished viewing. clear the terminal, and display the menu
* support a function that creates a socket client connection to the Java server
    * this function will create 1 thread within itself that should be constructed upon connecting.
    * this function will handle both IPv4 and IPv6 protocols of the destination address. It should swap inbetween protocols depending on the specified connection set by the user. 
        * in this way, connection will have a mode of either ipv4 or ipv6 
* support reconnecting to the parser
    * there should be an error if there has been no previous connection or there is already an established connection
* support disconnecting from the parser
    * upon disconnecting, wake threads and tidy up their work, and die
* receives JSON strings streamed from server and passes to the C++ parser object
    * therad should, UPON CONNECTION, begin listening for data.
    * this function should be a callable function upon thread creation
    * when disconnecting within the thread's execution, set _connection flag = false and _paused = true and check on the main thread, call disconnect() if any of the previous conditions are true

* for any new connection via connection() or reconnect(), join the receiveThread before creating a new one
    * app should indicate _alive == true if the thread is created and executing
    
* send byte commands streams back to the Java parser.
    * p = pause
        * when paused, set _paused to true, block the thread from executing after finishing up parsing the last jasonString it sees. 
        * this can be done by placing a _pause checker within the while execution loop. If true, sleep
    * s = start
    * c-## = confirm object recieved for msgID = ##
* exit

## JAVA parser

* support a method to continuously parse line by line and convert fields into a Java object
* communicate cross-language via sockets/servers
* support a method to start/pause the parser
* support a method to convert the created Java object into a JSON object using GSON
* support a method to convert the JSON object into a JSON string
    * the string will be streamed through a server/socket connection to the C++ program
* support a method that hosts a server via local or internet connection in which JSON strings will be streamed
    * ensure JSON strings are appended with "\n" before being streamed

## C++ Parser

* receive JSON strings from APP object
* parse received JSON strings into an array of strings of corresponding fields
* pass created string arrays to the correct group manager to construct groups

## saveFile

* this feature will connect the C++ program to mySQL
* read/write active groups at increments to a file and save data

## groupManager

* generate and set groupIDs (setting group IDs has not been supported, as of 4/21, groupID are a constructor args for groups)
* construct group given a string array received from the C++ parser
* modify group 
    * (add secondary phone numbers or create group)
* priority queue (heap)
    * to track queue and allow for random access/modification, we will not be using a priority queue, instead we will used a vector-based heap
    * full + high boosted groups > larger group + boosted groups > smaller groups + little to no boosted groups 
    * 
    * (talk about heap tail insertion later)
* pop from queue when notified
    * if queue is empty, the returned group will be marked invalid
* display active groups
    * should be in order of the queue


## group

* std::string _fullName  
* std::string _groupID
    * (given by groupManager generated externally)  
* std::string _primaryPhoneNumber  
    * (214) 931-4749 -> +2149314749
* std::vector<std::string> _secondaryPhoneNumbers  
* int _projectID 
    * this determines string awaitingProject upon construction
* int _groupSize  
* int _incrementPosition 
    * (this is also given by groupManager. It is used to generate a string as the groupID as well) 
    * this helps determine what order the object arrived at. I.e. position = 4 means the 4th group to be queued
* int _popsSinceArrival  
    * number of pops that have passed while waiting in queue
* int _priorityBoost  
    * a value that will help boost the priority once the group has waited a given number of pops
    * totalpriority = groupsize * 10 + priority boost
        * an euqation to determine which group gets higher priority considering their size and how long they've waited
* std::string _awaitingProject  
* bool _validObj  
    * flag to signal bad data/groups. These should be not included into queue and resubmitted.

* should support functions for sanitizing and validating phone numbers 

### How do we know when it is the next turn of a group?

* give each project lead that is present a switch
* upon next group’s turn, they flick switch
* convert the electrical signal to a BOOLEAN (true/false)
* send the boolean back to us
* we send a response boolean to confirm, and pop the next group from the queue
* once both bool flags are true, program should pop from the queue

## upon next in line

* notify all group members it’s their turn, iterate through group
* retrieve their name, projectID, phone number
* SIM800L
* +2149314749
* "it's your turn in queue"
* once all members processed, pop group from heap/priority queue
* set boolean flag to true to confirm pop()