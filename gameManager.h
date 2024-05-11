// Need passed pawn
// Go over public / private (entire folder)
// Game Manager
// Moves
// Player (Done)
// Human
// AI
#ifndef H_gameManager
#define H_gameManager

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <time.h>

#include "aI.h"
#include "human.h"
class gameManager
{
public:
    enum piece
    {
        EMPTY = 0,
        WHITE_PAWN = 1,
        WHITE_ROOK = 2,
        WHITE_KNIGHT = 3,
        WHITE_BISHOP = 4,
        WHITE_QUEEN = 5,
        WHITE_KING = 6,
        BLACK_PAWN = 7,
        BLACK_ROOK = 8,
        BLACK_KNIGHT = 9,
        BLACK_BISHOP = 10,
        BLACK_QUEEN = 11,
        BLACK_KING = 12
    };
    enum color
    {
        WHITE = true,
        BLACK = false
    };
    void pVsC();
    // Starts a chess game between a human and an AI
    // The human will always go first
    void pVsP();
    // Starts a chess game between two humans (locally)
    gameManager();
    void movePiece(std::string move);
    // (move string is a 6 character long string that stores information about a move)
    // Takes a move string and changes the board with it
    int board[8][8];
    bool gameOver = false;

private:
};

gameManager::gameManager()
{
    // Setting up the board (with traditional piece positions)
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i == 1)
            {
                board[i][j] = BLACK_PAWN;
            }
            else if (i == 6)
            {
                board[i][j] = WHITE_PAWN;
            }
            else
            {
                board[i][j] = EMPTY;
            }
        }
    }
    board[0][0] = BLACK_ROOK;
    board[0][1] = BLACK_KNIGHT;
    board[0][2] = BLACK_BISHOP;
    board[0][3] = BLACK_QUEEN;
    board[0][4] = BLACK_KING;
    board[0][5] = BLACK_BISHOP;
    board[0][6] = BLACK_KNIGHT;
    board[0][7] = BLACK_ROOK;

    board[7][0] = WHITE_ROOK;
    board[7][1] = WHITE_KNIGHT;
    board[7][2] = WHITE_BISHOP;
    board[7][3] = WHITE_QUEEN;
    board[7][4] = WHITE_KING;
    board[7][5] = WHITE_BISHOP;
    board[7][6] = WHITE_KNIGHT;
    board[7][7] = WHITE_ROOK;
}

void gameManager::pVsC()
{
    human player1(color::WHITE);
    aI player2(color::BLACK);
    std::string move = "";
    while (!gameOver)
    {
        move = player1.pickMove(board, true, move, gameOver);
        if (gameOver)
        {
            std::cout << " Game Over ";
            return;
        }
        movePiece(move);
        move = player2.pickMove(board, false, move, gameOver);
        if (gameOver)
        {
            std::cout << " Game Over ";
            return;
        }
        movePiece(move);
    }
}

void gameManager::pVsP()
{
    human player1(color::WHITE);
    human player2(color::BLACK);
    std::string move = "";
    while (!gameOver)
    {
        move = player1.pickMove(board, true, move, gameOver);
        if (gameOver)
        {
            std::cout << " Game Over ";
            return;
        }
        movePiece(move);
        move = player2.pickMove(board, false, move, gameOver);
        if (gameOver)
        {
            std::cout << " Game Over ";
            return;
        }
        movePiece(move);
    }
}

void gameManager::movePiece(std::string move)
{

    board[stoi(move.substr(4, 1))][stoi(move.substr(5, 1))] = board[stoi(move.substr(2, 1))][stoi(move.substr(3, 1))];
    board[stoi(move.substr(2, 1))][stoi(move.substr(3, 1))] = 0;
    // Special instructions for special moves (en passant and castling)
    if (move.substr(0, 1) == "P")
    {
        board[stoi(move.substr(2, 1))][stoi(move.substr(5, 1))] = 0;
    }
    else if (move.substr(0, 1) == "C")
    {
        int rookValue;
        if (move.substr(1, 1) == "6")
        {
            rookValue = WHITE_ROOK;
        }
        else
        {
            rookValue = BLACK_ROOK;
        }
        if (move.substr(5, 1) == "2")
        {
            board[stoi(move.substr(4, 1))][0] = 0;
            board[stoi(move.substr(4, 1))][3] = rookValue;
        }
        else
        {
            board[stoi(move.substr(4, 1))][7] = 0;
            board[stoi(move.substr(4, 1))][5] = rookValue;
        }
    }
}

#endif