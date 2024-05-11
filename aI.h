#ifndef H_aI
#define H_aI
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <time.h>

#include "moves.h"
#include "player.h"

class aI : public player
{
public:
    aI(bool color);

    std::string pickMove(int board[8][8], bool turn, std::string previousMove, bool &gameOver);

private:
    int miniMax(int index, int board[8][8], bool p, std::string previousMove, bool leftCastleFinished, bool rightCastleFinished);
    int max(std::vector<int> values);
    int maxIndex(std::vector<int> values);
    int min(std::vector<int> values);
    int minIndex(std::vector<int> values);
    bool color;

    bool hash(int board[8][8]);
    void setTable();
    unsigned rand256();
    unsigned long long rand64bits();
    int table[64][12];
    std::vector<long long> hashedValues;

    void rewindPiece(std::string currentMove, int board[8][8], int value);
    void movePiece(std::string currentMove, int board[8][8], int &value);
    int pieceValue(int board[8][8]);
};

aI::aI(bool color)
{
    setTable();
    this->color = color;
}

std::string aI::pickMove(int board[8][8], bool turn, std::string previousMove, bool &gameOver)
{
    Moves nextMove(board, turn, previousMove, leftCastleFinished, rightCastleFinished);
    if (nextMove.listOfMoves.size() == 0)
    {
        gameOver = true;
        return "";
    }
    printBoard(board);
    int index = 0;
    index = miniMax(0, board, turn, previousMove, leftCastleFinished, rightCastleFinished);
    kingAndRookMove(nextMove.listOfMoves[index]);
    return nextMove.listOfMoves[index];
}
int aI::miniMax(int index, int board[8][8], bool p, std::string previousMove, bool leftCastleFinished, bool rightCastleFinished)
{
    // Searches to a depth of 2 using depth first search
    if (index > 2)
    {
        return pieceValue(board);
    }
    // Havent implemented castling for AI currently
    Moves list(board, p, previousMove, false, false);
    std::vector<int> boardValues;
    // iterator
    for (int i = 0; i < list.listOfMoves.size(); i++)
    {
        int oldValue = 0;
        movePiece(list.listOfMoves[i], board, oldValue);
        if (!hash(board))
        {
            boardValues.push_back(miniMax(index + 1, board, !p, list.listOfMoves[i], leftCastleFinished, rightCastleFinished));
        }
        rewindPiece(list.listOfMoves[i], board, oldValue);
    }
    if (index == 0)
    {
        if (p)
        {
            return maxIndex(boardValues);
        }
        else
        {
            return minIndex(boardValues);
        }
    }
    if (p)
    {
        return max(boardValues);
    }
    else
    {
        return min(boardValues);
    }
}
int aI::max(std::vector<int> values)
{
    int max = -1000;
    for (int i = 0; i < values.size(); i++)
    {
        if (max < values[i])
        {
            max = values[i];
        }
    }

    return max;
}
int aI::maxIndex(std::vector<int> values)
{
    int max = -1000;
    int maxIndex = 0;
    for (int i = 0; i < values.size(); i++)
    {
        if (max < values[i])
        {
            max = values[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}
int aI::min(std::vector<int> values)
{
    int min = 1000;

    for (int i = 0; i < values.size(); i++)
    {
        if (min > values[i])
        {
            min = values[i];
        }
    }

    return min;
}
int aI::minIndex(std::vector<int> values)
{
    int min = 1000;
    int minIndex = 0;

    for (int i = 0; i < values.size(); i++)
    {
        if (min > values[i])
        {
            min = values[i];
            minIndex = i;
        }
    }
    return minIndex;
}
unsigned aI::rand256()
{
    static unsigned const limit = RAND_MAX - RAND_MAX % 256;
    unsigned result = rand();
    while (result >= limit)
    {
        result = rand();
    }
    return result % 256;
}
unsigned long long aI::rand64bits()
{
    unsigned long long results = 0;
    for (int count = 8; count > 0; --count)
    {
        results = 256U * results + rand256();
    }
    return results;
}
bool aI::hash(int board[8][8])
{
    int hashVal = 0;
    int val = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != piece::EMPTY)
            {
                val = board[i][j];
                hashVal = (hashVal ^ table[(i * 8) + j][val]);
            }
        }
    }
    // iterator
    for (int i = 0; i < hashedValues.size(); i++)
    {
        if (hashVal == hashedValues[i])
        {
            return true;
        }
    }
    hashedValues.push_back(hashVal);
    return false;
}
void aI::setTable()
{
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            table[i][j] = rand64bits();
        }
    }
}
int aI::pieceValue(int board[8][8])
{
    int totalValue = 0;

    int pV = 7;
    int nBV = 20;
    int rV = 30;
    int qV = 50;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            switch (board[i][j])
            {
            case 0:
                break;
            case 1:
                totalValue += pV;
                break;
            case 2:
                totalValue += rV;
                break;
            case 3:
                totalValue += nBV;
                break;
            case 4:
                totalValue += nBV;
                break;
            case 5:
                totalValue += qV;
                break;
            case 6:
                break;
            case 7:
                totalValue -= pV;
                break;
            case 8:
                totalValue -= rV;
                break;
            case 9:
                totalValue -= nBV;
                break;
            case 10:
                totalValue -= nBV;
                break;
            case 11:
                totalValue -= qV;
                break;
            case 12:
                break;
            }
        }
    }
    return (totalValue);
}

void aI::rewindPiece(std::string currentMove, int board[8][8], int value)
{
    // std::cout << currentMove << " | " << currentMove.substr(5, 1) << " | ";
    int r1 = stoi(currentMove.substr(2, 1));
    int c1 = stoi(currentMove.substr(3, 1));
    int r2 = stoi(currentMove.substr(4, 1));
    int c2 = stoi(currentMove.substr(5, 1));
    board[r1][c1] = board[r2][c2];
    board[r2][c2] = value;
}

void aI::movePiece(std::string currentMove, int board[8][8], int &value)
{
    // Need something for pawn
    int r1 = stoi(currentMove.substr(2, 1));
    int c1 = stoi(currentMove.substr(3, 1));
    int r2 = stoi(currentMove.substr(4, 1));
    int c2 = stoi(currentMove.substr(5, 1));
    value = board[r2][c2];
    board[r2][c2] = board[r1][c1];
    board[r1][c1] = 0;
}

#endif
