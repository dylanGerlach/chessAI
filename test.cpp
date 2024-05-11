
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <time.h>
int wP = 1;
int wR = 2;
int wN = 3;
int wB = 4;
int wQ = 5;
int wK = 6;
int bP = 7;
int bR = 8;
int bN = 9;
int bB = 10;
int bQ = 11;
int bK = 12;

unsigned rand256()
{
    static unsigned const limit = RAND_MAX - RAND_MAX % 256;
    unsigned result = rand();
    while (result >= limit)
    {
        result = rand();
    }
    return result % 256;
}
unsigned long long rand64bits()
{
    unsigned long long results = 0;
    for (int count = 8; count > 0; --count)
    {
        results = 256U * results + rand256();
    }
    return results;
}
void table()
{
    int table[64][12];
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            table[i][j] = rand64bits();
        }
    }
    for (int i = 0; i < 64; i++)
    {
        std::cout << std::endl;
        for (int j = 0; j < 12; j++)
        {
            std::cout << table[i][j] << " ";
        }
    }
}
int main()
{
    int x = 5;
    int y  = -3;
    x += y;
    std::cout << " X: " << x ;
    // int board[8][8];

    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         board[i][j] = 0;
    //     }
    // }
    // board[7][7] = bP;
    // board[5][7] = bP;
    // board[3][7] = bP;

    // board[6][5] = wN;
    // bool wOrB = true;
    // Moves nextMove(board, wOrB);
    // printBoard(board);
    // int index = 0;
    // index = miniMax(0, board, wOrB);
    // std::cout << " Next Move: " << nextMove.listOfMoves[index];

    //table();
    // int a = 5;
    // int b = 9;
    // std::cout << (a ^ b);
    // int board[8][8];
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         board[i][j] = 1;
    //     }
    // }
    // hash(board);
    return 0;
}
