#include <stdio.h>

// Represents game board
int gameBoard [6][6];

// Represents player position
int playerPosition [1][1];

// Represents ai position
int aiPosition [1][1];

// Creates the game board to initialize game
void createGameBoard();

// Display current game board status
void displayGameBoard();

int main(){
    createGameBoard();
    displayGameBoard();
    return 0;
}

void createGameBoard() {
    // Loop helper variables
    int i,j;

    // Initialize the game board with "2"s
    for(i = 0; i < 6; i++){

        for(j = 0; j < 6; j++){
            // Assings the value to all cell
            gameBoard[i][j] = 2;
        }
    }
}

void displayGameBoard(){
    // Loop helper variables
    int i,j;

    // Initialize the game board with "2"s
    for(i = 0; i < 6; i++){

        for(j = 0; j < 6; j++){
            // Assings the value to all cell
            printf("%d ",gameBoard[i][j]);
        }
        printf("\n");
    }
}