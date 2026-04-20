# CL-SMS-QueueSystem
A command line interface program that manages a queue system for Creative Labs @ USC

This project is a queue system designed to take input from a google form and queues people into groups into a game-like party system
Upon the next groups turn, their information should include their phone number that will be used to send a SMS text notification

## Google Form
google forms requires...\
->full name\
->phone number\
->projectID -> 1 = 86, 2 = frissions, 3 = desk drawer...

### is person a groupleader or not?
->if yes, generate groupID\
->if no, join group via groupID

all in a .csv file

## Object Hierarchy
### app
->CLI interface\
-> check status of program\
-> pause/resume parse\
-> recieve and confirm update queue\
-> exit

### parser
->parse and pass data to group manager //communicate cross-language via sockets/servers
-> pass the data in the format of a array of strings to the groupManager

### saveFile
->read/write active groups to a file and save data

### groupManager
-> set gorupIDs\
-> construct group given an array of strings with fields
-> modify group (add members or create group)\
-> priority queue (heap)\
->     full > larger group > smaller groups
(talk about heap tail insertion later)\
->pop from queue when notified by the app\
->upon generating groupID, construct group(groupID)

### group
 -> string groupID
 -> Players vector<>

parse csv file -> into obj QueueObject
### Queue Object   
-> Full name\
-> groupID\
-> Phone number (214) 931-4749 -> +2149314749\
-> projectID\





## How do we know when is it the next turn of a group?
-> give each project lead that is present a switch\
-> upon next gorups turn, they flick switch\
-> convert the electrical signal to a BOOLEAN (true/false)\
-> send the boolean back to us\
-> we send a response boolean to confirm, and pop the next gruop form the queue\
-> once both bool flags are true, program should pop from the queue  

### upon next in line
->notify all groupmembers it's their turn, iterate thru group\
  -> retrive their name, projectID, phone number\
  -> SIM800L\
    +2149314749
    "it's your turn in queue"\
->Once all members processed pop group from heap/priority queue, set boolean flag to true to confirm pop()





  
</p>
