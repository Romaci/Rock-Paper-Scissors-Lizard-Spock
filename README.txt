

** Paper–scissor–rock–lizard–spock (PSRLS) Game **

This contains a C++ program that simulates the Paper–scissor–rock–lizard–spock game
played between two players, Player A and Player B. 
The program provides two setup options for the players' choices 
and uses multiple threads to simulate and evaluate the game.

-Prerequisites
Before running the program, ensure you have the following prerequisites installed:

C++ compiler (e.g., g++)
C++11 standard library support


-Run the program:

The program will prompt you to select a setup (1 or 2). Choose either setup to run the game simulation.

The program will simulate the game, and once completed, it will display the results,
showing the number of wins for Player A, Player B, and ties, along with the overall winner.

-Program Setup Options
Setup 1:
Player A always chooses "PAPER."
Player B's choices are randomized.
Both Player A and Player B make choices for 100 matches.

Setup 2:
Player A and Player B make randomized choices.
Both Player A and Player B make choices for 100 matches.
Output

-The program will display the following output:

The number of wins for Player A.
The number of wins for Player B.
The number of tie games.
The overall winner of the simulation.

-Technologies and Libraries Used:

C++ Standard Libraries: The code extensively utilizes C++'s standard libraries, including:
<algorithm>, <iostream>, <thread>, <random>, <mutex>, <vector>, and `<queue>, among others. 
These libraries provide essential functionalities for tasks like string manipulation, concurrency management, random number generation, and data structures.

std::random_device and std::mt19937: These are used for generating random numbers. 
std::random_device provides a source of adequate entropy, and 
std::mt19937 is a Mersenne Twister pseudo-random number generator.

std::mutex: The std::mutex class is used to provide safe synchronization between threads,
ensuring that shared data is manipulated safely and preventing race conditions.

std::vector and std::queue: These data structures are used to store player choices and matches to be evaluated. 
Vectors are used to maintain player choices, 
and the queue is used to schedule matches for synch evaluation.

-Object-Oriented Implementation:
Work is underway on an object-oriented implementation of the game. 
This implementation will make unit testing more straightforward and modular, 
thereby enhancing code maintenance and extensibility.

-GitHub Repository:
The implementation will be available in a GitHub repository in the coming days. 
https://github.com/Romaci

-Author
This program was created by Rocío.

