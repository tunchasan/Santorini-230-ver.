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
int controlGameStatus(int**);

// Gets user input for player move
void getUserInput(int);

// Validates the user' input for his adjacent space
// Return 1 -> Represents input is valid
// Return 0 -> Represents input is not valid
int validateSpace(int, int);

// Validates the user' input for his adjacent space on the game board
// Return 1 -> Represents input is valid
// Return 0 -> Represents input is not valid
int validateSpaceForGameBoard(int, int);

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

// Effect the game board after move
// Paramater 1 -> Player
// Raramater -1 -> AI
void effectGameBoard(int, int**);

// Returns 1 if the given 2D space blocked by player otherwise 0
int blockedByPlayer(int, int);

// Returns 1 if the given 2D space blocked by ai otherwise 0
int blockedByAI(int, int);

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
    while(controlGameStatus(gameBoard) == 1){

        // get user input
        getUserInput(onGameStarting);

        // effect game board as player
        effectGameBoard(1, gameBoard);

        // display game board
        displayGameBoard(gameBoard);

        // places ai on the game board
        placeAI(onGameStarting);

        // effect game board as ai
        effectGameBoard(-1, gameBoard);

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

int controlGameStatus(int** gameBoard){

    int i,j;

    // Represents "4" level builder counts
    int playerPoints = 0;

    // Represents "0" level builder counts
    int aiPoints = 0;

    // loop in the game board spaces
    for(i = 0; i < 6; i++){

        for(j = 0; j < 6; j++){

            // Increase playerPoints
            if(gameBoard[i][j] == 4)
                playerPoints++;

            // Increase aiPoints
            else if(gameBoard[i][j] == 0){
                aiPoints++;
            }
        }
    }

    // Player wins
    if(playerPoints >= 10){

        printf("\nPlayer wins.\n\n");

        return 2;
    }

    // AI wins
    if(aiPoints >= 10){

        printf("\nAI wins.\n\n");

        return 3;
    }

    // Game is continues
    return 1;
}

void getUserInput(int onBeginState){

    //Represents user input' row and column
    int row, column;

    // If the game is not newly started
    while(onBeginState != 1){

        // Stores valid adjacents points on the game board
        Vector2D **validSpaces = findValidLocation(playerXPosition, playerYPosition, 1);
        printf("Check the valid spaces and place your builder based on the spaces\n");

        printf("Place your builder: ");
        
        scanf("%d", &row);
        scanf("%d", &column);

        // If not on the begin state
        if(validateSpaces(validSpaces, row, column) == 1){

            printf("\nPlayer moves to (%d, %d)\n\n",row,column);

            //Update player' location on the game board
            playerXPosition = row;

            playerYPosition = column;

            // Then break the endless loop
            break;
        }

        else
            printf("\n!!!Out of valid spaces. Check the valid spaces and place your builder based on the spaces\n\n");
            
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

int validateSpaceForGameBoard(int row, int column){

    return (row >= 0 && row < 6 && column >= 0 && column < 6);
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

                // Then adds the list
                Vector2D *newVector = (Vector2D*)malloc(sizeof(Vector2D));

                newVector->positionX = row;

                newVector->positionY = column;

                spaces[spaceIndex] = newVector;

                spaceIndex++;
                
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

void effectGameBoard(int point, int** gameBoard){

    int row, column;

    // Represents octogonal count on the game board
    int effectionCounter = 0;

    int xAxis,yAxis;

    do{
        // Loop for each axis except (0, 0)
        for(xAxis = -1; xAxis < 2; xAxis++){
            for(yAxis = -1; yAxis < 2; yAxis++){

                if(xAxis == 0 && yAxis == 0)
                    continue;

                // Update the position informations
                row = point == 1 ? playerXPosition - 1 : aiXPosition - 1;

                column = point == 1 ? playerYPosition - 1 : aiYPosition - 1;

                while(1){
                    row = row + xAxis;

                    column = column + yAxis;

                    // Player
                    if(point == 1){
                        if(blockedByPlayer(row, column))
                            continue;
                        else if(blockedByAI(row, column))
                            break;
                    }

                    // AI
                    if(point == -1){
                        if(blockedByAI(row, column))
                            continue;
                        else if(blockedByPlayer(row, column))
                            break;
                    }

                    if(validateSpaceForGameBoard(row, column)){
                        gameBoard[row][column] += point;

                        // Normalize the overflow values
                        if(gameBoard[row][column] > 4)
                            gameBoard[row][column] = 4;
                        else if(gameBoard[row][column] < 0)
                            gameBoard[row][column] = 0;
                    }
                    else
                        break;
                }

                // Increase the counter
                effectionCounter++;
            }
        }

    } while(effectionCounter < 8);
}

int blockedByPlayer(int row, int column){
    return row == playerXPosition -1 && column == playerYPosition -1;
}

int blockedByAI(int row, int column){
    return row == aiXPosition -1 && column == aiYPosition -1;
}