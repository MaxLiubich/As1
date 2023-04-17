/*********************************************************************
** Program Filename:
** Author: Max Liubich
** Date: 4/16/2023
** Description: Allow the users 
** Input: player amount, mb rack postition, repeat game decision
** Output:moneyball rack score, winner, repeat game option
*********************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

class Player {
private:
    static const int NUM_POSITIONS = 5;
    static const int NUM_BALLS_PER_RACK = 5;
    static const int REG_BALL_POINTS = 1;
    static const int MONEY_BALL_POINTS = 2;
    static const int MONEY_BALL_VALUE = 2;
    static const int REGULAR_BALL_VALUE = 1;
    static const string values[3];
    int moneyRackPosition;
    char shots[5][5];

public:
    int total_score = 0;

    void runGame() {
    int moneyBallPosition = MBRackPosition();
    cout << "Player shooting at position " << moneyBallPosition + 1 << endl;


    int score = 0;
    for (int i = 0; i < NUM_BALLS_PER_RACK; ++i){
        if (i == moneyBallPosition){
            score = scorePerRack(true);
        }
        else{
            score = scorePerRack(false);
        }
        total_score += score;
    }

    cout << total_score << endl;
}

    void displayShots() {
        for (int i = 0; i < NUM_POSITIONS; i++) {
            cout << "Position " << (i+1) << ": ";
            for (int j = 0; j < NUM_BALLS_PER_RACK; ++j) {
                cout << shots[i][j] << " ";
            }
            cout << endl;
        }
    }

    int MBRackPosition() {
        cout << "Where do you want to put your money-ball rack? (1-" << NUM_POSITIONS << "): ";
        int position;
        cin >> position;
        while (position < 1 || position > NUM_POSITIONS) {
            cout << "Invalid position. Choose again (1-" << NUM_POSITIONS << "): ";
            cin >> position;
        }
        return position - 1;                                           // Subtract 1 to convert to 0-based index
    }

    int shoot() {
    return rand() % 2;                                                 // 0 for a miss, 1 for a made shot
    }

    int scorePerRack(bool isMoneyRack) { 
    string rack_array[NUM_BALLS_PER_RACK] = {"O","O","O","O","O",};
    int score = 0;

    bool didHit = false;
    
    if (isMoneyRack){
        for (int i = 0; i < 5; ++i){
            int shootBall = shoot();                                       // returns 0 or 1 //
            
            if (shootBall == 1){
                didHit = true;
                rack_array[i] = "M";
            }
            else {
                rack_array[i] = "O";
            }
            
        }
    }
    else {
        for (int i = 0; i < 5; ++i){
            int shootBall = shoot();                                       // returns 0 or 1 //
            
            if (shootBall == 1){
                didHit = true;
                rack_array[i] = "X";
            }
            else {
                rack_array[i] = "O";
            }
            if (i == 4 && didHit){
                    rack_array[4] = "M";
            }
        }
    }
    

    // score calculation
    for (int i = 0; i < NUM_BALLS_PER_RACK; ++i){
        if (rack_array[i] == "X"){
            score += 1;
        }
        else if ( rack_array[i] == "M"){
            score +=2;
        }
    }
    
    for (int i = 0; i < 5; ++i) {
        std::cout << rack_array[i] << " ";
    }
    std::cout << std::endl;

    return score;
}

};

int getAmountOfPlayers(){
    int n;
    std::cout << "Enter number of players: ";
    std::cin >> n;
    return n;
}

void initializePlayerObjectsAndRunGame(int n){
     Player *players = new Player[n];                         // allocate array of Player objects using dynamic memory allocation
    int highestScore = 0;
    int highScoreIndex = -1;

    for (int i = 0; i < n; ++i) {
        players[i].runGame();
        int playerScore = players[i].total_score;
        std::cout << "Player " << (i+1) << " score: " << playerScore << std::endl;
        if (playerScore > highestScore) {
            highestScore = playerScore;
            highScoreIndex = i;
        }
    }
    // Print the highest score and the player who got it
    if (highScoreIndex >= 0) {
        std::cout << "Player " << (highScoreIndex + 1) << " is the winner! " << highestScore << std::endl;
    }
    
    // free the allocated memory
    delete [] players; 
}


void playGame() {
    int players = getAmountOfPlayers();
    initializePlayerObjectsAndRunGame(players);
    int playAgain;
    std::cout << "Would you like to play again? (1: Yes, 0: No): ";
    std::cin >> playAgain;

    if (playAgain == 1) {
        playGame();
    } else if (playAgain == 0) {
        std::cout << "GAME OVER!" << std::endl;
    } else {
        std::cout << "Invalid option. Please try again." << std::endl;
    }
}
int main() {
    srand(time(NULL));                                    // Set the seed for the random number generator
    playGame();
    return 0;
}
