#include <algorithm>
#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <vector>
#include <queue>
#include <string>

//Player options
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define LIZARD 3
#define SPOCK 4

// Numbers of play rounds
#define MATCHS 100
#define PLAYERS 2
#define ID_PLAYER_A 0
#define ID_PLAYER_B 1




// variables for setup choices
 int SETUP_1_PLAYER_A_CHOICE = PAPER;
 bool SETUP_1_PLAYER_B_RANDOM = true;
 bool SETUP_2_RANDOM_CHOICES = true;

// Mutex for thread synchronization
std::mutex mtx;

// A two-dimensional vector to store player choices for multiple matches
std::vector< std::vector<int> > players_choices(PLAYERS, std::vector<int>(100, -1));

// A queue to keep track of matches that haven't been evaluated and are prepared for evaluation.
std::queue<int> matchsToEvaluete;

// A vector to store the results (0: Player A wins, 1: Player B wins, 2: Ties)
std::vector<int> results(3, 0);

// Counter for the total number of matches evaluated
int total_matchs_evaluated = 0;

// Function to generate a random choice for a player
int getRandomChoice() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 4);
    return dist(gen);
}

// Function to determine Player A's choice based on the setup
int playerAChoose() {
    if (SETUP_1_PLAYER_A_CHOICE != -1) {
        return SETUP_1_PLAYER_A_CHOICE;
    } else {
        return getRandomChoice();
    }
}


// Function to calculate winner and load the results of a match
//results (0: Player A wins, 1: Player B wins, 2: Ties)
void loadResults(std::vector<int> match) {
    int playerAChoice = match[ID_PLAYER_A];
    int playerBChoice = match[ID_PLAYER_B];
    if (playerAChoice == playerBChoice) {
        results[2]++;
    } else {
        if ((playerAChoice == SCISSORS && (playerBChoice == PAPER || playerBChoice == LIZARD)) ||
            (playerAChoice == ROCK && (playerBChoice == SCISSORS || playerBChoice == LIZARD)) ||
            (playerAChoice == PAPER && (playerBChoice == ROCK || playerBChoice == SPOCK)) ||
            (playerAChoice == LIZARD && (playerBChoice == SPOCK || playerBChoice == PAPER)) ||
            (playerAChoice == SPOCK && (playerBChoice == SCISSORS || playerBChoice == ROCK))) {
            results[0]++;
        } else {
            results[1]++;
        }
    }
}

// Function for Player actions
void playerA() {
    for (int i = 0; i < MATCHS; i++) {
        int player_choice = playerAChoose();
        std::lock_guard<std::mutex> lock(mtx);
        players_choices[0][i] = player_choice;
        if (players_choices[0][i] != -1 && players_choices[1][i] != -1) {
            matchsToEvaluete.push(i);
        }
    }
}

void playerB() {
    for (int i = 0; i < MATCHS; i++) {
        int player_choice = getRandomChoice();
        std::lock_guard<std::mutex> lock(mtx);
        players_choices[1][i] = player_choice;
        if (players_choices[0][i] != -1 && players_choices[1][i] != -1) {
            matchsToEvaluete.push(i);
        }
    }
}

// Thread function for Judge actions
void judge() {
    while (total_matchs_evaluated < MATCHS) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!matchsToEvaluete.empty()) {
            int pos = matchsToEvaluete.front();
            matchsToEvaluete.pop();
            int playerAChoice = players_choices[ID_PLAYER_A][pos];
            int playerBChoice = players_choices[ID_PLAYER_B][pos];
            if (playerAChoice == playerBChoice) {
                results[2]++;
            } else {
                if ((playerAChoice == SCISSORS && (playerBChoice == PAPER || playerBChoice == LIZARD)) ||
                    (playerAChoice == ROCK && (playerBChoice == SCISSORS || playerBChoice == LIZARD)) ||
                    (playerAChoice == PAPER && (playerBChoice == ROCK || playerBChoice == SPOCK)) ||
                    (playerAChoice == LIZARD && (playerBChoice == SPOCK || playerBChoice == PAPER)) ||
                    (playerAChoice == SPOCK && (playerBChoice == SCISSORS || playerBChoice == ROCK))) {
                    results[0]++;
                } else {
                    results[1]++;
                }
            }
            total_matchs_evaluated++;
        }
    }
}

int main() {
    int setupChoice;
    std::cout << "Select the setup (1 or 2): ";
    std::cin >> setupChoice;

    if (setupChoice == 1) {
        // Setup 1: Player A always chooses PAPER, Player B is random
        SETUP_1_PLAYER_A_CHOICE = PAPER;
        SETUP_1_PLAYER_B_RANDOM = true;
        SETUP_2_RANDOM_CHOICES = false;
    } else if (setupChoice == 2) {
        // Setup 2: Both players are random
        SETUP_1_PLAYER_A_CHOICE = -1;
        SETUP_1_PLAYER_B_RANDOM = true;
        SETUP_2_RANDOM_CHOICES = true;
    } else {
        std::cout << "Invalid setup choice. Exiting." << std::endl;
        return 1;
    }

    // Create threads and join for Player A, Player B, and multiple judges
    std::thread threadPlayerA(playerA);
    std::thread threadPlayerB(playerB);
    std::thread threadJudge1(judge);
    std::thread threadJudge2(judge);
    std::thread threadJudge3(judge);

    threadPlayerA.join();
    threadPlayerB.join();
    threadJudge1.join();
    threadJudge2.join();
    threadJudge3.join();

    // Display the results of the game
    std::cout << "Player A wins " << results[0] << " of " << results[2] + results[1] + results[0] << " games" << std::endl;
    std::cout << "Player B wins " << results[1] << " of " << results[2] + results[1] + results[0] << " games" << std::endl;
    std::cout << "Tie: " << results[2] << " of " << results[2] + results[1] + results[0] << " games" << std::endl;
   
    if (results[0] > results[1]) {
        std::cout << "Winner is: Player A" << " (" << results[0] << " to " << results[1] << " wins)" << std::endl;
    } else if (results[1] > results[0]) {
        std::cout << "Winner is: Player B" << " (" << results[1] << " to " << results[0] << " wins)" << std::endl;
    } else {
        std::cout << "It's a tie! No clear winner." << std::endl;
    }

    return 0;
}