Name: Asir Alam
COP4520 Programming Assignment 2
Problem 2: Minotaur’s Crystal Vase

Instructions:
- Compile: g++ problem2.cpp -pthread
- Execute: ./a.out

This program simulates the Minotaur's Crystal Vase problem using the third approach provided in the 
assignment problem statement. My reasoning for choosing this approach is as follows.

The first approach would be the most naive approach. There is no certain limitation that prevents 
all the guests from seeing the vase eventually. However, there is no guarantee when a guest will 
finally get to see vase. For example, a guest could be the only person waiting outside the room and 
while waiting for the person inside the room to come out there could be more people arriving outside 
the room. There is no protocol that determines the next person to go inside the room, resulting in 
possible contention. Furthermore, the door being open only allows a guest to attempt to see the 
vase. There is no way of knowing if the room is vacant. 

The second approach lets the waiting guests know if the room is vacant using the sign on the door.
However, there is still no protocol that determines the next person to go inside the room.

The third approach allows the guests to line up in a queue. The guest in the front of the queue can 
enter the room as soon as the guest currently in the room finishes admiring the vase. This strategy
incorporates a protocol for determining the order in which the waiting guests can view the vase. 
It allows the guest who has been waiting the longest to be the next to enter the room. Even if a
guest arrives at the queue very late, that guest is still guaranteed to enter the room after all the
guests in front of that guest have had their turns. Therefore, assuming the number of guests is 
finite and guests are not allowed to cut in line, this is the most fair approach.

My implementation of the program is described as follows. During the duration of the program, each
guest is represented by its own thread. Each of these thread has a running while loop with a short
delay between iterations. On each iteration, if the guest is not in the queue or the room, they
will make a roll that gives them a 10% probability of entering the queue. This means an expected 
10 rolls until the guest is queued. The delay in the while loop helps prevent the guest from 
seemingly queueing immediately, which would make the rolls pointless and it would be practically
equivalent to having a 100% chance of queueing. The execution time of the program depends directly
on such arbitrarily chosen parameters. On each iteration, if the guest is in the front of the queue,
the guest is marked as having seen the vase. A counter is increment for each guest's first time 
seeing the vase. The outer most while loop of each thread terminates when this counter reaches n,
which ensures the program keeps running until all guest have had their turn. 

Experimental evaluation of the program was done as follows. I used debug statements to print the
order in which the guests queued and checked to make sure that this varied between each execution.
I wrote a separate checker program and fed the debug output into it to check that the program 
does not terminate until all guests visited the room at least once. I checked that the total number 
of queue events including duplicate guests varied. I observed the scaling behavior of the program by
running it with several powers of two as the number of guests.