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
-> support a function that creates a socket client connection to the Java server\
-> recieves JSON strings streamed from server and passes to the C++ parser object\
-> exit

### JAVA parser
->support a method to continuously parse line by line and convert fields into a java object //communicate cross-language via sockets/servers\
-> support a method to start/pause the parser\
-> support a method to convert the created java object into a JSON object using GSON\
-> support a method to convert the JSON Object into a JSON string\
the following string will be used to stream thru a server/socket connection to the C++ program\
->support a method that hosts a server via local or internet connection in which json strings will be streamed thru the server socket\
!!!-> In java, ensure that json strings are appended with "\n" before being streamed

### C++ Parser
-> recieve JSON strings from APP obj\
-> parse recieved JSON strings into Group objects\
-> pass created Group Objects to the group Manager 

### saveFile
->read/write active groups at increments to a file and save data

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
-> Full name\
-> string groupID\
-> group leader Phone number (214) 931-4749 -> +2149314749\
-> projectID\
-> name of awaiting project\
-> validObj flag\
-> dead object flag\
-> vector of extra phonenumber for extra members\
-> should support sanitizing and validating phone nummbers








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
