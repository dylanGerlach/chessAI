
#include "gameManager.h"
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
int main()
{
    gameManager game1;
    // game1.pVsC(true);
    game1.pVsP();

    // test minimax in aI

    // int board[8][8];

    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         board[i][j] = 0;
    //     }
    // }

    // board[3][3] = bN;
    // board[5][5] = wN;
    // board[0][0] = bR;
    // board[7][7] = wR;

    // aI newPlayer;

    // newPlayer.bestMove(board, true);
    // newPlayer.printBoard(board);

    // Moves ex(board, true);
    // ex.printBoard(board);
    // ex.printListOfMoves();
    // chessBoard newBoard;
    // newBoard.pVsC(true);

    return 0;
}