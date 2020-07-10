Emilia Segura, 40138440

Assignment 3

The program should run as specified in assignment

Some details 
Menu:
-Same functionality as assignment 1, implemented with vector
-contains 1 free function readInt() that is also used in LineManager. Functions checks that user input is an integer

MiniDB:
-template
-indexing is 0-based. 
-I chose to explicitely default all the special member functions.
-Implemented using list as storage

LineManager:
-User interface uses 1-based indexing. Behind the scenes, MiniDB is 0-based
-Uses on instance of MiniDB<std::string> as underlying storage
-uses two menu objects to display and receive user option choice
-deleted copy constructor and assignment operator. From UML diagram in assignment instructions, it is clear that only 1 instance
of LineManager is needed.
-Save to file (option 11) will create a file for output if it doesn't already exist
