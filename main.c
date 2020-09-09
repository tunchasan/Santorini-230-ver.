#include <stdio.h>
#include <stdlib.h>

// Represents player position
int playerPosition [1][1];

// Represents ai position
int aiPosition [1][1];

// Creates the game board to initialize game
void createGameBoard(int**);

// Displays current game board status
void displayGameBoard(int**);

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

    // Represents game board
    int **gameBoard = (int**)malloc(36 * sizeof(int*));

    // create game board
    createGameBoard(gameBoard);

    // get user input
    getUserInput();

    // places ai on the game board
    placeAI();

    // display game board
    displayGameBoard(gameBoard);

    // game loop
    /*while(controlGameStatus() == 1){



        // display game board
        displayGameBoard();
    }*/
    

    return 0;
}

void createGameBoard(int** gameBoard) {
    // Loop helper variables
    int i,j;

    // Allocate spaces for gameboard' cells on the memory
    for(i =0; i<6; i++)
        gameBoard[i] = (int*)malloc(sizeof(int));

    // Initialize the game board with "2"s
    for(i = 0; i < 6; i++){

        for(j = 0; j < 6; j++){
            // Assings the value to all cell
            gameBoard[i][j] = 2;
        }
    }
}

void displayGameBoard(int** gameBoard){
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

void getUserInput(){
    
}

void placeAI(){

}