#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Represents 2D vector
struct Vector2D{
    // X position on the board
    int positionX;
    // Y position on the board
    int positionY;
};

typedef struct Vector2D Vector2D;

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
void getUserInput(int);

// Validates the user' input for his adjacent space
// Return 1 -> Represents input is valid
// Return 0 -> Represents input is not valid
int validateSpace(int, int);

// Places ai on the game board based on the game rules
void placeAI(int);

// Finds a valid location based on the given location's adjacents on the game board
// Third parameter is representing whether displays the valid location or not
// 1 -> display 0 -> do not display
Vector2D **findValidLocation(int, int, int);

// Returns random numbers between 0 to given number
int randomNumberInRange(int);

// Validates if given points is a member of the list
// Return 1 -> if matches
// Return 0 -> if not
int validateSpaces(Vector2D**, int, int);

int main(){

    // Represents game board
    int **gameBoard = (int**)malloc(36 * sizeof(int*));

    // Represents the game' on the begin state
    int onGameStarting = 1;
    randomNumberInRange(3);

    // create game board
    createGameBoard(gameBoard);

    // get user input
    getUserInput(onGameStarting);

    // display game board
    displayGameBoard(gameBoard);

    // places ai on the game board
    placeAI(onGameStarting);

    // display game board
    displayGameBoard(gameBoard);

    printf("\n");

    // Represent the game is not begin state
    onGameStarting = -1;

    // game loop
    while(controlGameStatus() == 1){

        // get user input
        getUserInput(onGameStarting);

        // display game board
        displayGameBoard(gameBoard);

        // places ai on the game board
        placeAI(onGameStarting);

        // display game board
        displayGameBoard(gameBoard);

        printf("\n");
    }
    

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

            // Controls Player location on the game board
            if(i == playerXPosition -1 && j == playerYPosition -1){
                printf("P ");
            }

            // Controls AI location on the game board
            else if(i == aiXPosition -1 && j == aiYPosition - 1){
                printf("A ");

            }

            else{
                // Assings the value to all cell
                printf("%d ", gameBoard[i][j]);
            }
            
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

void getUserInput(int onBeginState){

    //Represents user input' row and column
    int row, column;

    // If the game is not newly started
    while(onBeginState != 1){

        printf("You will place your builder in on the board in this fashion: 'row col'\n");
        printf("The row and column must be an integer between 1 and 6 \n");

        // Stores valid adjacents points on the game board
        Vector2D **validSpaces = findValidLocation(playerXPosition, playerYPosition, 1);
        printf("Check the valid spaces and place your builder based on the spaces\n");

        printf("Place your builder: ");
        
        scanf("%d", &row);
        scanf("%d", &column);

        // If not on the begin state
        if(validateSpaces(validSpaces, row, column) == 1){

            printf("Player moves to (%d, %d)\n\n",row,column);

            //Update player' location on the game board
            playerXPosition = row;

            playerYPosition = column;

            // Then break the endless loop
            break;
        }

        else{
            printf("\n!!! The row and column must be an integer between 1 and 6\n");
            printf("!!! You should not place your builder to your current location or current AI builder's location\n\n");
        }
    }

    // If the game is newly started
    while(onBeginState == 1){

        printf("You will place your builder in on the board in this fashin: 'row col'\n");
        printf("The row and column must be an integer between 1 and 6 \n");

        printf("Place your builder: ");
        
        scanf("%d", &row);
        scanf("%d", &column);
        
        // Validates the user input
        if(validateSpace(row,column)) {

            printf("Player moves to (%d, %d)\n\n",row,column);

            //Update player' location on the game board
            playerXPosition = row;

            playerYPosition = column;

            // Then break the endless loop
            break;
        }

        else{
            printf("\n!!! The row and column must be an integer between 1 and 6\n");
            printf("!!! You should not place your builder to your current location or current AI builder's location\n\n");
        }
    }
}

int validateSpace(int row, int column){

    return (row > 0 && row < 7 && column > 0 && column < 7) 
            && !(row == playerXPosition && column == playerYPosition)
            && !(row == aiXPosition && column == aiYPosition);
}

void placeAI(int onBeginState){

    Vector2D **validSpaces;

    if(onBeginState == 1){
        // get the valid spaces on the game board based on the game rules
        validSpaces = findValidLocation(playerXPosition, playerYPosition, 0);
    }
    else{
        // get the valid spaces on the game board based on the game rules
        validSpaces = findValidLocation(aiXPosition, aiYPosition, 0);
    }

    int i, validSpacesCount = 0;

    // Finds the validSpaces elements counts
    for(i = 0; i < 9; i++){
        if(validSpaces[i] != NULL)
            validSpacesCount++;
        else
            break;
    }

    // Pick a valid places randomly
    int randNum = randomNumberInRange(validSpacesCount);

    aiXPosition = validSpaces[randNum]->positionX;

    aiYPosition = validSpaces[randNum]->positionY;

    printf("AI moves to (%d, %d)\n\n",aiXPosition, aiYPosition);
}

Vector2D **findValidLocation(int x, int y, int displayValidLocations){

    // Represents valid spaces on the game board based on the given locations
    Vector2D **spaces = (Vector2D**)malloc(9 * sizeof(Vector2D*));

    // Loop helper variables
    int i,j,spaceIndex = 0;

    if(displayValidLocations)
        printf("Valid Spaces: ");

    // Calculates the adjacents 2d points on the board
    for(i = -1; i < 2; i++){

        for(j = -1; j < 2; j++){

            int row = x + i;

            int column = y + j;

            // Validate the adjacent points
            if(validateSpace(row, column)){

                if(displayValidLocations){
                    printf("(%d, %d) ", row, column);
                }

                else{

                    // Then adds the list
                    Vector2D *newVector = (Vector2D*)malloc(sizeof(Vector2D));

                    newVector->positionX = row;

                    newVector->positionY = column;

                    spaces[spaceIndex] = newVector;

                    spaceIndex++;
                }
            }
        }
    }

    printf("\n");

    return spaces;
}

int randomNumberInRange(int max){

    //Intializes random number generator
    srand(time(NULL)); 

    return rand() % max;
}

int validateSpaces(Vector2D** spaces, int x, int y){

    int i;

    // Check the condition for each element
    for(i = 0; i < 9; i++){

        if(spaces[i] != NULL){
            if(spaces[i]->positionX == x && spaces[i]->positionY == y)
                return 1;
        }
    }

    return 0;
}