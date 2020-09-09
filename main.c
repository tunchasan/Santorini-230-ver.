#include <stdio.h>
#include <stdlib.h>

// Represents player' 2D position
int playerXPosition;

int playerYPosition;

// Represents ai' 2D position
int aiXPosition;

int aiYPosition;

// Creates the game board to initialize game
void createGameBoard(int**);

// Displays current game board status
void displayGameBoard(int**);

// Controls the current game status
// Return 1 -> Represents game is continues
// Return 2 -> Represents Player win
// Return 3 -> Represent AI win
int controlGameStatus();

// Gets user input for player move
void getUserInput();

// Validates the user' input for his adjacent space
// Return 1 -> Represents input is valid
// Return 0 -> Represents input is not valid
int validateUserInput(int, int);

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

    //Represent user input' row and column
    int row, column;

    while(1){

        printf("You will place your builder in on the board in this fashin: 'row col'\n");
        printf("The row and column must be an integer between 1 and 6 \n");
        printf("Place your builder: ");
        
        scanf("%d", &row);
        printf(" ");
        scanf("%d", &column);
        
        // Validates the user input
        if(validateUserInput(row,column)) {

            printf("Player moves to (%d, %d)\n",row,column);

            //Update player' location on the game board
            playerXPosition = row;

            playerYPosition = column;

            // Then break the endless loop
            break;
        }

        else{
            printf("\n!!! The row and column must be an integer between 1 and 6\n\n");
        }
    }
}

int validateUserInput(int row, int column){

    return row > 0 && row < 7 && column > 0 && column < 7;
}

void placeAI(){

}