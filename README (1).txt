Jimmy Fallon (Project 04)

	main: This is the function takes the command line argument of how many calls need to be 
    answered (integer). It is also used to create the number of threads or phone calls and join these 
    threads. Two semaphores are initialized and destroyed in the main too.

    phonecall: This function  is run by the threads. Each individual thread runs through semaphore 
    locks. A thread will first enter the critical section i.e it is connected to a line. The first semaphore checks to see if there are less than 5 threads processing at a time. If all 5 lines are busy, the thread will wait until a line is available. The second counting semaphore will let 3 threads as it represents the 3 operators. Once a thread enters here, it 
    sleeps for 3 seconds and ends(ticket purchased successfully). The thread is returned to the main function. This repeats for all the threads specified in the command line. When the semaphores are full, they send a busy signal to a thread. 


link to video : https://youtu.be/I-8U6MITY40
Ritwik Bagga, Umair Afzal, Abhishek Dutt