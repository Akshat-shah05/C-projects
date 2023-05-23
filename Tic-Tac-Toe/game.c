#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char board[3][3]; // creates a 2d array which makes up the board
const char PLAYER = 'X'; // X is assigned to the Player. Scanf with a do... while can also be used to take input for preferred character
const char COMPUTER = 'O'; // O is assigned to the computer. " " 

void resetBoard(); //function for resetting the board
void printBoard(); // function to print the board
int checkFreeSpaces(); // function to look for free spaces
void playerMove(); // function to allow player to move
void computerMove(); // funciton to allow computer to move
char checkWinner(); // function to check the winer
void printWinner(char winner); // function to print out the winener

int main()
{
    char winner = ' '; // meaning there is no winner as of now

    resetBoard(); 
    printBoard();

    // game loop. ensures that there is no winner, and that there are still free spaces on the board
    while (winner == ' ' && checkFreeSpaces() != 0){
        printBoard();

        playerMove();
        winner = checkWinner();
        if(winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }

        computerMove();
        if(winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
    }

    printBoard();
    printWinner(winner);

    return 0;
}

// this function works by replacing each element of the 2d array with a blank space
void resetBoard()
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            board[i][j] = ' ';
        }
    }
}

// this function works manually by physically printing out a board
void printBoard()
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// this function iterates through all elements of the 2d array, and checks for free spaces
int checkFreeSpaces()
{
    int freeSpaces = 9;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (board[i][j] != ' '){
                freeSpaces--;
            }
        }
    }
    return freeSpaces;

}

// this function takes user input to determine which row and column they want. X is decreased by 1 as the index is one less than the row*
void playerMove()
{
    int x;
    int y;

    // check to see if the spot is taken
    do {
        
        printf("Enter row number (1-3): ");
        scanf("%d", &x);
        x--;

        printf("Enter column number (1-3): ");
        scanf("%d", &y);
        y--;

        if(board[x][y] != ' ')
            printf("Invalid move! \n");
        else {
            board[x][y] = PLAYER;
            break;
        }

    }
    while (board[x][y] != ' ' || x > 3 || x < 1 || y > 3 || y < 1);
    
}

// will generate random numbers
void computerMove()
{
    // creates a seed based on current time (srand(time())) --> makes use of the laptops internal clock
    srand(time(0));
    int x;
    int y;

    if(checkFreeSpaces() > 0)
    {
        do 
        {
            x = rand() % 3;
            y = rand() % 3;
        }
        while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else 
    {
        printWinner(' ');
    }
}

char checkWinner()
{
    // check columns

    for (int i = 0; i < 3; i ++){
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];
        }
    }

    // check rows

    for (int i = 0; i < 3; i++){
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }

    // check diagonals (no for loop needed)

    if (board[0][0] == board[1][1] && board[2][2] == board[0][0]){
        return board[0][0];
    }
    else if (board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[0][2];
    }

    // means theres no winner yet
    return ' ';

}

void printWinner(char winner)
{
    if (winner == PLAYER)
    {
        printf("YOU WIN!");
    }
        
    else if (winner == COMPUTER){
        printf("YOU LOSE!");
    }
    else{
        printf("ITS A TIE!");
    }
}
