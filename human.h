#ifndef H_human
#define H_human

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <time.h>

#include "moves.h"
#include "player.h"
class human : public player
{
public:
    std::string pickMove(int board[8][8], bool turn, std::string previousMove, bool &gameOver);
    // Allows a human player to pick a move
    // Converts the human form of a board (numbers for the rows and letters for the columns) into numbers between 0-7 for the computer
    human(bool color);

private:
    bool color;

    bool inBoundsCheck(int r, int c);
    // Checks if the input square is in bounds (between 0 and 7)
};

human::human(bool color)
{
    this->color = color;
}

std::string human::pickMove(int board[8][8], bool turn, std::string previousMove, bool &gameOver)
{
    // Assuming that input from player will always be valid
    bool validMove = false;
    std::string move = "";
    std::string startPos = "";
    std::string endPos = "";
    printBoard(board);
    while (!validMove)
    {
        Moves list(board, turn, previousMove, leftCastleFinished, rightCastleFinished);
        if (list.listOfMoves.size() == 0)
        {
            gameOver = true;
            return "";
        }
        std::cout << "What square is the piece you would like to move on?" << std::endl;
        std::cin >> startPos;
        std::cout << "What square would you like to place this piece" << std::endl;
        std::cin >> endPos;
        int r1 = 8 - std::stoi(startPos.substr(1, 1));
        int c1 = int(startPos.substr(0, 1)[0]) - 65; // s1L
        int r2 = 8 - std::stoi(endPos.substr(1, 1));
        int c2 = int(endPos.substr(0, 1)[0]) - 65; // s2L
        if (!inBoundsCheck(r1, c1) || !inBoundsCheck(r2, c2))
        {
            std::cout << "Invalid Input, please input a new move " << std::endl;
            continue;
        }

        move = std::to_string(board[r1][c1]) + std::to_string(r1) + std::to_string(c1) + std::to_string(r2) + std::to_string(c2);

        if (move.size() == 5)
        {
            move.insert(0, "0");
        }
        // iterator
        // Searches if the input move from the player is in the list of valid moves
        for (int i = 0; i < list.listOfMoves.size(); i++)
        {
            if ((list.listOfMoves[i].substr(0, 1) == "P" || list.listOfMoves[i].substr(0, 1) == "C") && list.listOfMoves[i].substr(1, 5) == move.substr(1, 5))
            {
                kingAndRookMove(move);
                return list.listOfMoves[i];
            }
            else if (move == list.listOfMoves[i])
            {
                validMove = true;
                break;
            }
        }
        if (!validMove)
        {
            // Continues through the while loop until a valid move is chosen
            std::cout << "Invalid Move, please input a new move " << std::endl;
            continue;
        }
    }
    kingAndRookMove(move);
    return move;
}

bool human::inBoundsCheck(int r, int c)
{
    if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
    {
        return true;
    }
    return false;
}

#endif