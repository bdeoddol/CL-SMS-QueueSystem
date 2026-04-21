### CL-SMS-QueueSystem

A command line interface program that manages a queue system for Creative Labs @ USC

This project is a queue system designed to take input from a Google Form and queues people into groups into a game-like party system

Upon the next group’s turn, their information should include their phone number that will be used to send an SMS text notification

### Google Form

## Google Forms requires:
-> full name
-> phone number
-> projectID -> 1 = 86, 2 = frissions, 3 = desk drawer

## Is person a group leader or not?

-> if yes, generate groupID
-> if no, join group via groupID

All stored in a .csv file

### Object Hierarchy
## app

-> CLI interface
-> check status of program
-> check status of specified group managers (each project will have its own group manager)
-> pause/resume parse
-> receive and confirmation to pop from specified project queue
-> request show all active groups from all groupManagers (should be organized)
-> request show queues from all groupManagers (should be organized)
-> request display active groups from specified groupManager
-> request display queue from specified groupManager
-> support a function that creates a socket client connection to the Java server
-> receives JSON strings streamed from server and passes to the C++ parser object
-> exit

## JAVA parser

-> support a method to continuously parse line by line and convert fields into a Java object
-> communicate cross-language via sockets/servers
-> support a method to start/pause the parser
-> support a method to convert the created Java object into a JSON object using GSON
-> support a method to convert the JSON object into a JSON string
-> the string will be streamed through a server/socket connection to the C++ program
-> support a method that hosts a server via local or internet connection in which JSON strings will be streamed
-> ensure JSON strings are appended with "\n" before being streamed

## C++ Parser

-> receive JSON strings from APP object
-> parse received JSON strings into an array of strings of corresponding fields
-> pass created string arrays to the correct group manager to construct groups

## saveFile
-> this feature will connect the C++ program to mySQL
-> read/write active groups at increments to a file and save data

## groupManager

-> generate and set groupIDs
-> construct group given a string array received from the C++ parser
-> modify group (add secondary phone numbers or create group)
-> priority queue (heap)
-> full > larger group > smaller groups
-> (talk about heap tail insertion later)
-> pop from queue when notified by the app
-> display active groups
-> display queue

## group

-> full name
-> string groupID
-> group leader phone number (214) 931-4749 -> +2149314749
-> projectID
-> name of awaiting project
-> validObj flag
-> dead object flag
-> vector of extra phone numbers for extra members
-> should support sanitizing and validating phone numbers

### How do we know when it is the next turn of a group?

-> give each project lead that is present a switch
-> upon next group’s turn, they flick switch
-> convert the electrical signal to a BOOLEAN (true/false)
-> send the boolean back to us
-> we send a response boolean to confirm, and pop the next group from the queue
-> once both bool flags are true, program should pop from the queue

## upon next in line

-> notify all group members it’s their turn, iterate through group
-> retrieve their name, projectID, phone number
-> SIM800L
-> +2149314749
-> "it's your turn in queue"
-> once all members processed, pop group from heap/priority queue
-> set boolean flag to true to confirm pop()