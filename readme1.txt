Name: Asir Alam
COP4520 Programming Assignment 2
Problem 1: Minotaur’s Birthday Party

Instructions:
- Compile: g++ problem1.cpp -pthread
- Execute: ./a.out

This program simulates the solution to the Minotaur’s Birthday Party problem.

The strategy to verify that all guest have visited the labyrinth is as follows. Assign guest 0
as the counter 0 and the other guests as regular guests. The counter guest is responsible for 
counting the number of unique guests who have visited the labyrinth. Regular guests are responsible
for letting the counter guest know of their visit into the labyrinth. The first time a regular 
guest sees an uneaten cake, he should eat the cake to let the counter know of his visit. The guest
should take no action in following visits. Every time the counter guest sees an uneaten cake, he 
takes note of a guest having visited the cake for the first time and increments the counter. When
the counter guest realizes all guests have visited the cake, they can announce to the Minotaur. This
approach correctly accounts for all the guests because eventually every guest will get to eat the
cake since guests who have already eaten it once will not do so again.

The program spawns a thread for each guest going into the labyrinth. Each of these threads interacts
with the cake as per the corresponding guest's role as either counter or regular guest. The cake
is an atomic variable since it could be accessed by multiple threads at at time. The in_laby
vector keeps track of whether a guest is currently in the maze. This helps prevent spawning multiple
instances of a guest. A mutex is used when modifying a guest's in_laby value since it could be
accessed by a guest thread and the main thread simultaneously. 

The program was tested on numbers of guests upto 1000 and the runtime grows with respect to the
number of guests. Debug statements were used to verify the random order of guests entering the maze
and their effects on the cake depending on the situation. 