#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 6;
const int COLS = 7;

int board[ROWS][COLS] = {0};

void printBoard()
{
    cout << "\n";

    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            if(board[r][c] == 0)
                cout << ". ";

            else if(board[r][c] == 1)
                cout << "X "; 

            else
                cout << "O "; 
        }

        cout << endl;
    }

    cout << "1 2 3 4 5 6 7\n";
}

bool placeDisc(int col, int player)
{
    int row;

    for(row = 5; row >= 0; row--)
    {
        if(board[row][col] == 0)
        {
            board[row][col] = player;
            return true;
        }
    }

    return false;
}

bool checkWinner(int player)
{

    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS - 3; c++)
        {
            if(board[r][c] == player &&
               board[r][c+1] == player &&
               board[r][c+2] == player &&
               board[r][c+3] == player)
                return true;
        }
    }

    
    for(int r = 0; r < ROWS - 3; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            if(board[r][c] == player &&
               board[r+1][c] == player &&
               board[r+2][c] == player &&
               board[r+3][c] == player)
                return true;
        }
    }

    
    for(int r = 0; r < ROWS - 3; r++)
    {
        for(int c = 0; c < COLS - 3; c++)
        {
            if(board[r][c] == player &&
               board[r+1][c+1] == player &&
               board[r+2][c+2] == player &&
               board[r+3][c+3] == player)
                return true;
        }
    }

    
    for(int r = 0; r < ROWS - 3; r++)
    {
        for(int c = 3; c < COLS; c++)
        {
            if(board[r][c] == player &&
               board[r+1][c-1] == player &&
               board[r+2][c-2] == player &&
               board[r+3][c-3] == player)
                return true;
        }
    }

    return false;
}

bool boardFull()
{
    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            if(board[r][c] == 0)
                return false;
        }
    }

    return true;
}

void computerMove()
{
    int col;

    do
    {
    
        col = rand() % COLS;
    }
    while(!placeDisc(col, 2));

    cout << "Computer chose column " << col + 1 << endl;
}

int main()
{
    srand(time(0));

    int choice;

    cout << "====== CONNECT 4 / kattamkutta======\n";
    cout <<"Rules:\n";
    cout <<"-lowest empty slot will be filled first\n";
    cout <<"-if you press any column and base row is filled base+1 will be filled\n";
    cout <<"-first to connect 4 wins\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Computer\n";
    cout << "Enter choice: ";
    cin >> choice;

    int currentPlayer = 1;

    while(true)
    {
        printBoard();

        if(choice == 2 && currentPlayer == 2)
        {
            computerMove();
        }
        else
        {
            int col;

            cout << "\nPlayer " << currentPlayer
                 << " Enter column (1-7): ";

            cin >> col;

            col--;

            if(col < 0 || col >= COLS ||
               !placeDisc(col, currentPlayer))
            {
                cout << "Invalid move!\n";
                continue;
            }
        }

        if(checkWinner(currentPlayer))
        {
            printBoard();

            if(choice == 2 && currentPlayer == 2)
                cout << "\nComputer Wins!\n";
            else
                cout << "\nPlayer "
                     << currentPlayer
                     << " Wins!\n";

            break;
        }

        if(boardFull())
        {
            printBoard();
            cout << "\nMatch Draw!\n";
            break;
        }

        if(currentPlayer == 1)
{
    currentPlayer = 2;
}
else
{
    currentPlayer = 1;
}
    }

    return 0;
}