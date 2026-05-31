#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int ROWS = 6;
const int COLS = 7;

int board[ROWS][COLS] = {0};

bool gameOver = false;

int currentPlayer = 1;


void drawBoard(sf::RenderWindow &window)
{
    window.clear(sf::Color::Blue);

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            sf::CircleShape circle(40);

            circle.setPosition(col * 100 + 10,
                               row * 100 + 10);

            if (board[row][col] == 0)
                circle.setFillColor(sf::Color::White);

            else if (board[row][col] == 1)
                circle.setFillColor(sf::Color::Red);

            else
                circle.setFillColor(sf::Color::Yellow);

            window.draw(circle);
        }
    }

    window.display();
}

bool placeDisc(int col, int player)
{
    for (int row = ROWS - 1; row >= 0; row--)
    {
        if (board[row][col] == 0)
        {
            board[row][col] = player;
            return true;
        }
    }

    return false;
}
bool checkHorizontal(int player)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS - 3; col++)
        {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player)
            {
                return true;
            }
        }
    }

    return false;
}

bool checkVertical(int player)
{
    for (int row = 0; row < ROWS - 3; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player)
            {
                return true;
            }
        }
    }

    return false;
}


bool checkDiagonal(int player)
{
    // Left to right
    for (int row = 0; row < ROWS - 3; row++)
    {
        for (int col = 0; col < COLS - 3; col++)
        {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player)
            {
                return true;
            }
        }
    }

    // Right to left
    for (int row = 0; row < ROWS - 3; row++)
    {
        for (int col = 3; col < COLS; col++)
        {
            if (board[row][col] == player &&
                board[row + 1][col - 1] == player &&
                board[row + 2][col - 2] == player &&
                board[row + 3][col - 3] == player)
            {
                return true;
            }
        }
    }

    return false;
}


bool checkWinner(int player)
{
    if (checkHorizontal(player))
        return true;

    if (checkVertical(player))
        return true;

    if (checkDiagonal(player))
        return true;

    return false;
}


bool checkDraw()
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (board[row][col] == 0)
                return false;
        }
    }

    return true;
}
void computerMove()
{
    int randomColumn;

    while (true)
    {
        randomColumn = rand() % COLS;

        if (placeDisc(randomColumn, 2))
        {
            cout << "Computer inserted in column: "
                 << randomColumn + 1 << endl;

            break;
        }
    }
}


int main()
{
    cout << "PROGRAM STARTED" << endl;
    system("pause");

    srand(time(0));

    sf::RenderWindow window(
        sf::VideoMode(700, 600),
        "Connect 4 - Player vs Computer");
        cout << "Window created" << endl;
        cout << "Entering loop" << endl;

    while (window.isOpen())
    {
        cout << "Loop running" << endl;
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

    
            if (!gameOver &&
                currentPlayer == 1 &&
                event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button ==
                    sf::Mouse::Left)
                {
                    int mouseX = event.mouseButton.x;

                    int selectedColumn = mouseX / 100;

                    if (selectedColumn >= 0 &&
                        selectedColumn < COLS)
                    {
                        bool success =
                            placeDisc(selectedColumn, 1);

                        if (success)
                        {
                            if (checkWinner(1))
                            {
                                gameOver = true;

                                cout << "Player Wins!"
                                     << endl;
                            }
                            else if (checkDraw())
                            {
                                gameOver = true;

                                cout << "Match Draw!"
                                     << endl;
                            }
                            else
                            {
                                currentPlayer = 2;
                            }
                        }
                    }
                }
            }
        }

        
        if (!gameOver && currentPlayer == 2)
        {
            sf::sleep(sf::milliseconds(500));

            computerMove();

            if (checkWinner(2))
            {
                gameOver = true;

                cout << "Computer Wins!"
                     << endl;
            }
            else if (checkDraw())
            {
                gameOver = true;

                cout << "Match Draw!"
                     << endl;
            }
            else
            {
                currentPlayer = 1;
            }
        }

        drawBoard(window);
        window.display();
    }

    return 0;
}