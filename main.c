#include <stdio.h>

// Represents game board
int gameBoard [6][6];

// Represents player position
int playerPosition [1][1];

// Represents ai position
int aiPosition [1][1];

// Creates the game board to initialize game
void createGameBoard();

// Displays current game board status
void displayGameBoard();

// Controls the current game status
// 1 -> Represents game is continues
// 2 -> Represents Player win
// 3 -> Represent AI win
int controlGameStatus();

// Gets user input for player move
void getUserInput();

// Validates the user' input for his adjacent space
int validateUserInput();

// Places ai on the game board based on the game rules
void placeAI();

int main(){
    // create game board
    createGameBoard();

    // get user input
    getUserInput();

    // places ai on the game board
    placeAI();

    // display game board
    displayGameBoard();

    // game loop
    /*while(controlGameStatus() == 1){



        // display game board
        displayGameBoard();
    }*/
    

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

    // Table' row headline
    printf("%s", "   1 2 3 4 5 6\n");

    // Initialize the game board with "2"s
    for(i = 0; i < 6; i++){

        // Table' column headline
        printf("%d  ", i+1);

        for(j = 0; j < 6; j++){
            // Assings the value to all cell
            printf("%d ", gameBoard[i][j]);
        }
        printf("\n");
    }
}

int controlGameStatus(){
    // TODO
    // Implement other game states

    // Game is continues
    return 1;
}

void placeAI(){

}

void getUserInput(){
    
}