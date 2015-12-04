CIS3210 Computer Networks    
Michael Tran  0524704
Assignment 1

****************
HOW TO RUN & COMPILE
****************
From the root directory
	- Type 'make' to compile everything
	- Type 'make run' to compile everything and start up all the nodes except N1 in the background
	- To open programs seperately: Type ./n1 to open n1.c ./n2 to open n2.c etc

When the program starts up it'll ask for a <file_name> and <destination> to start the simulation
Erorr checking is involved to make sure for correct input

file_name
	- the location of the file to run the simulation

destination
	- choose one of [n2,n3,n4,n5,n6,n7]


*******************
NOTES
*******************

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PLEASE READ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

When you 'make run' for the first time, it will be buggy for some reason. This is what is going to happen for the first run:

CASE 1: If you send a message to n2 or n4 at the beginning of the simulation it will send the first packet than sit there forever

CASE 2: If you send a message to NODES 3, 5 ,6 and 7 it will work normally but when you try to exit it will send a KILL packet than sit there forever. EXAMPLE test.txt n3 will run fine than doing test.txt n7 will run fine etc. Than trying to exit it will sit there forever

CASE 3: If you send a message to NODES 3, 5, 6 and 7 it will work normally but than try to send it to NODE 2 or 4 CASE 1 will happen

To make the simulation to run smoothly without any bugs, for some odd reason you need to kill the process and rerun the 'make run' and the simulation will be fine. I couldn't figure out why this was happening. 

Otherwise running the simulation in seperate terminals works prefectly when you open the programs in order (n1,n2...n7)

If you need a in person explaination I will gladly demo it in person

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PLEASE READ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

- For usleep instead of using 1-2000 I used 1000-2000000. I read the manpage for usleep and it sleeps in microseconds not milliseconds so I changed the number to equal 1-2000 milliseconds
- I used usleep in every node so it may look like it stopped working but it may take up to 2-6 secs to send one packet
- Type 'make clean' to clean up the folder of executable files
- A test file was included called test.txt which has the message "hello world"




