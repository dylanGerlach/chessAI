#ifndef H_player
#define H_player

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <time.h>
class player
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
    bool leftCastleFinished = false;
    bool rightCastleFinished = false;
    void printBoard(int board[8][8]) const;
    void kingAndRookMove(std::string move);
    // Updates the king and rooks to see if they have moved, if they have then the no castling variables are set to true

private:
};

void player::printBoard(int board[8][8]) const
{
    int m = 8;
    for (int i = 0; i < 8; i++)
    {
        std::cout << std::endl;
        for (int j = 0; j < 8; j++)
        {
            if (j == 0)
            {
                for (int i = 8; i > 0; i--)
                {
                    if (i == m)
                    {
                        std::cout << i << " ";
                    }
                }
                m--;
                std::cout << "*";
            }
            if (board[i][j] == 0)
            {
                std::cout << " 0 ";
            }
            if (board[i][j] == WHITE_PAWN)
            {
                std::cout << " P ";
            }
            if (board[i][j] == WHITE_ROOK)
            {
                std::cout << " R ";
            }
            if (board[i][j] == WHITE_KNIGHT)
            {
                std::cout << " N ";
            }
            if (board[i][j] == WHITE_BISHOP)
            {
                std::cout << " B ";
            }
            if (board[i][j] == WHITE_QUEEN)
            {
                std::cout << " Q ";
            }
            if (board[i][j] == WHITE_KING)
            {
                std::cout << " K ";
            }

            if (board[i][j] == BLACK_PAWN)
            {
                std::cout << " p ";
            }
            if (board[i][j] == BLACK_ROOK)
            {
                std::cout << " r ";
            }
            if (board[i][j] == BLACK_KNIGHT)
            {
                std::cout << " n ";
            }
            if (board[i][j] == BLACK_BISHOP)
            {
                std::cout << " b ";
            }
            if (board[i][j] == BLACK_QUEEN)
            {
                std::cout << " q ";
            }
            if (board[i][j] == BLACK_KING)
            {
                std::cout << " k ";
            }
        }
    }
    std::cout << std::endl
              << "   ";
    for (int i = 0; i < 16; i++)
    {
        if (i < 8)
        {
            std::cout << " * ";
        }
        if (i == 8)
        {
            std::cout << std::endl;
        }
        if (i == 8)
        {
            std::cout << "    A ";
        }
        if (i == 9)
        {
            std::cout << " B ";
        }
        if (i == 10)
        {
            std::cout << " C ";
        }
        if (i == 11)
        {
            std::cout << " D ";
        }
        if (i == 12)
        {
            std::cout << " E ";
        }
        if (i == 13)
        {
            std::cout << " F ";
        }
        if (i == 14)
        {
            std::cout << " G ";
        }
        if (i == 15)
        {
            std::cout << " H " << std::endl;
        }
    }
}

void player::kingAndRookMove(std::string move)
{
    if (stoi(move.substr(0, 2)) == WHITE_KING || stoi(move.substr(0, 2)) == BLACK_KING)
    {
        leftCastleFinished = true;
        rightCastleFinished = true;
    }
    if (stoi(move.substr(0, 2)) == WHITE_ROOK || stoi(move.substr(0, 2)) == BLACK_ROOK)
    {
        if (!leftCastleFinished && move.substr(3, 1) == "0")
        {
            leftCastleFinished = true;
        }
        if (!rightCastleFinished && move.substr(3, 1) == "7")
        {
            rightCastleFinished = true;
        }
    }
}

#endif