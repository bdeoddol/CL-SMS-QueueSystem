86! 4 per group
frissions x people per group
Desk Drawer 4 per group

each group elapsed 5-10 minutes

each requires groups of x
run for 5-15 minutes 


google forms 
    full name
    phone number
    projectID -> 86,frissions, desk drawer
-> is person a groupleader or not?
    if yes -> generate groupID
    if no -> what is the groupID

    all in a .csv file


object hierarchy-------------------------------------------------------------
app
->CLI interface
-> check status of program
-> pause/resume parse
-> recieve and confirm update queue
-> exit

parser
->parse and pass data to group manager

saveFile
->read/write active groups to a file and save data

group Manager
-> set gorupIDs
-> modify group (add members or create group)
-> priority queue (heap)
    full > larger group > smaller groups
(tlka about heap tail insertion later)
->pop from queue when notified by the app

upon generating groupID, construct group(groupID)
class group
 -> string groupID
 -> Players vector<>

parse csv file ->
class person   
    - Full name
    - groupID
    - Phone number (214) 931-4749 -> +2149314749
    - projectID


upon next in line
->notify all groupmembers it's their turn
    -> retrive their name, projectID, phone number
    -> SIM800L
    +2149314749
    "it's your turn in queue"
->repeat send SMS for all members in group
->pop group from heap/priority queue
object hierarchy-------------------------------------------------------------


how do we know when is it the next turn of a group?
-> give each project lead that is present a switch
-> upon next gorups turn, they flick switch
-> convert the electrical signal to a BOOLEAN (true/false)
-> send the boolean back to us 
-> we send a response boolean to confirm, and pop the next gruop form the queue
-> once both bool flags are true, program should pop from the queue


