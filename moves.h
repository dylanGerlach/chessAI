#ifndef H_moves
#define H_moves

// All vector for loops go to iterators before I finish(in entirety of program)
class Moves
{
public:
    std::vector<std::string> listOfMoves;
    Moves(int recievedBoard[8][8], bool wOrB, std::string previousMove, bool leftCastleFinished, bool rightCastleFinished);
    void printMoves();
    // Prints every move from listOfMoves
private:
    int enemyCheckedSquares[8][8];
    int emptySquare, allyPawn, allyKnight, allyRook, allyBishop, allyQueen, allyKing, enemyPawn, enemyKnight, enemyRook, enemyBishop, enemyQueen, enemyKing;
    bool color;
    bool allyKingInCheck;
    bool allyKingInDoubleCheck;
    bool leftCastleFinished;
    bool rightCastleFinished;
    std::vector<std::vector<int>> limitedSquares;
    std::vector<std::vector<std::vector<int>>> pinnedPieces;
    int board[8][8];
    int r1Prev = 0;
    int c1Prev = 0;
    int r2Prev = 0;
    int c2Prev = 0;

    void setList();
    // Sets the list of moves, and uses every function listed below to do so
    void pawnMoves(int r, int c);
    // Ally pawn moves
    void knightMoves(int r, int c);
    // Ally knight moves
    void rookMoves(int r, int c);
    // Ally rook moves
    void bishopMoves(int r, int c);
    // Ally bishop moves
    void queenMoves(int r, int c);
    // Ally queen moves
    void kingMoves(int r, int c);
    // Ally king moves
    void addToMoves(int rNew, int cNew, int rOld, int cOld);
    void addToMoves(int rNew, int cNew, int rOld, int cOld, char specialMove);
    // Takes in the value of the piece, the original posi tion of the piece, and the new position of the piece, and creates a move string.
    // Then it adds this move to the vector listOfMoves
    // Overloaded function for special moves

    void changeEnemyCheckedSquares();
    // Sets the occupied enemy squares on the board, used for pinned pieces, and king moves
    void enemyPawnCheckedSquares(int r, int c);
    void enemyRookCheckedSquares(int r, int c);
    void enemyKnightCheckedSquares(int r, int c);
    void enemyBishopCheckedSquares(int r, int c);
    void enemyQueenCheckedSquares(int r, int c);
    void enemyKingCheckedSquares(int r, int c);

    bool inPinnedPieces(int r, int c, std::vector<std::vector<int>> pinnedLine) const;
    // PinnedPieces is a 3d vector, this function checks if the input r (row) and c (col) are found in the input 2d vector (pinned line)
    // (a pinned line is when an ally piece is pinned to its king)
    bool inLimitedSquares(int r, int c) const;
    // Checks if input r (row) and c (col) are found in the 2d vector limitedSquares
    // (limitedSquares are where the ally pieces can go if the king is in check)
    bool pieceIsEnemy(int value) const;
    // Checks if piece is enemy
    bool pieceIsAlly(int value) const;
    // Checks if piece is ally
    bool inBoundsCheck(int r, int c) const;
    // Checks if the input square is in bounds (between 0 and 7)
};
Moves::Moves(int recievedBoard[8][8], bool inputTurn, std::string previousMove, bool leftCastleFinished, bool rightCastleFinished)
{

    this->leftCastleFinished = leftCastleFinished;
    this->rightCastleFinished = rightCastleFinished;
    allyKingInDoubleCheck = false;
    emptySquare = 0;
    allyKingInCheck = false;
    color = inputTurn;

    allyPawn = 1;
    allyRook = 2;
    allyKnight = 3;
    allyBishop = 4;
    allyQueen = 5;
    allyKing = 6;
    enemyPawn = 1;
    enemyRook = 2;
    enemyKnight = 3;
    enemyBishop = 4;
    enemyQueen = 5;
    enemyKing = 6;
    if (inputTurn == true)
    {
        enemyPawn += 6;
        enemyRook += 6;
        enemyKnight += 6;
        enemyBishop += 6;
        enemyQueen += 6;
        enemyKing += 6;
    }
    else
    {
        allyPawn += 6;
        allyRook += 6;
        allyKnight += 6;
        allyBishop += 6;
        allyQueen += 6;
        allyKing += 6;
    }
    if (previousMove.size() == 6)
    {
        r1Prev = stoi(previousMove.substr(2, 1));
        c1Prev = stoi(previousMove.substr(3, 1));
        r2Prev = stoi(previousMove.substr(4, 1));
        c2Prev = stoi(previousMove.substr(5, 1));
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            enemyCheckedSquares[i][j] = 0;
            board[i][j] = recievedBoard[i][j];
        }
    }
    setList();
}

void Moves::setList()
{
    changeEnemyCheckedSquares();

    if (listOfMoves.size() > 0)
    {
        std::cout << "resetting list";
        listOfMoves.resize(0);
    }
    // If the king is in check two ways, then it can generate the only possible moves
    if (allyKingInDoubleCheck)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                if (board[i][j] == allyKing)
                {
                    kingMoves(i, j);
                    return;
                }
            }
        }
    }
    // Going through each square on the board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == allyPawn)
            {
                pawnMoves(i, j);
            }
            if (board[i][j] == allyRook)
            {
                rookMoves(i, j);
            }
            if (board[i][j] == allyKnight)
            {
                knightMoves(i, j);
            }
            if (board[i][j] == allyBishop)
            {
                bishopMoves(i, j);
            }
            if (board[i][j] == allyQueen)
            {
                queenMoves(i, j);
            }
            if (board[i][j] == allyKing)
            {
                kingMoves(i, j);
            }
        }
    }
}

void Moves::pawnMoves(int r, int c)
{
    bool isPinned = false;
    int pinnedIndex = 0;
    // iterator
    // Checks if this piece is pinned, if it is it sets isPinned to true to use for later
    for (int i = 0; i < pinnedPieces.size(); i++)
    {
        if (r == pinnedPieces[i][pinnedPieces[i].size() - 1][0] && c == pinnedPieces[i][pinnedPieces[i].size() - 1][1])
        {
            if (allyKingInCheck)
            {
                return;
            }
            isPinned = true;
            pinnedIndex = i;
        }
    }
    // Setting variables for differences between white and black pawns, pawns are the only piece in the game that dont have the "same" movement as its enemy
    int multiplier = 1;
    int startRow = 0;
    int enPassantRow = 0;
    if (color)
    {
        multiplier = -1;
        startRow = 6;
        enPassantRow = 3;
    }
    else
    {
        startRow = 1;
        enPassantRow = 4;
    }
    // Pawn moving forward one square
    if (board[r + multiplier][c] == emptySquare && inBoundsCheck(r + multiplier, c))
    {
        if ((allyKingInCheck && inLimitedSquares(r + multiplier, c)) ||
            (isPinned && (inPinnedPieces(r + multiplier, c, pinnedPieces[pinnedIndex]))) ||
            (!allyKingInCheck && !isPinned))
        {
            addToMoves(r + multiplier, c, r, c);
        }
    }
    // Pawn moving forward two squares
    if (board[r + (2 * multiplier)][c] == emptySquare && board[r + multiplier][c] == emptySquare && r == startRow && inBoundsCheck(r + (2 * multiplier), c))
    {
        if ((allyKingInCheck && inLimitedSquares(r + (2 * multiplier), c)) ||
            (isPinned && (inPinnedPieces(r + (2 * multiplier), c, pinnedPieces[pinnedIndex]))) ||
            (!allyKingInCheck && !isPinned))
        {
            addToMoves(r + (2 * multiplier), c, r, c);
        }
    }
    // Pawn taking an enemy piece on the right
    if (pieceIsEnemy(board[r + multiplier][c + 1]) && inBoundsCheck(r + multiplier, c + 1))
    {
        if ((allyKingInCheck && inLimitedSquares(r + multiplier, c + 1)) ||
            (isPinned && (inPinnedPieces(r + multiplier, c + 1, pinnedPieces[pinnedIndex]))) ||
            (!allyKingInCheck && !isPinned))
        {
            addToMoves(r + multiplier, c + 1, r, c);
        }
    }
    // Pawn taking an enemy piece on the left
    if (pieceIsEnemy(board[r + multiplier][c - 1]) && inBoundsCheck(r + multiplier, c - 1))
    {
        if ((allyKingInCheck && inLimitedSquares(r + multiplier, c - 1)) ||
            (isPinned && (inPinnedPieces(r + multiplier, c - 1, pinnedPieces[pinnedIndex]))) ||
            (!allyKingInCheck && !isPinned))
        {

            addToMoves(r + multiplier, c - 1, r, c);
        }
    }
    // En passant moves
    if (r == enPassantRow && board[r + multiplier][c + 1] == emptySquare && c1Prev == c + 1 && r == r1Prev - (2 * multiplier) && r == r2Prev)
    {
        if ((allyKingInCheck && inLimitedSquares(r + multiplier, c + 1)) ||
            (isPinned && (inPinnedPieces(r + multiplier, c + 1, pinnedPieces[pinnedIndex]))) ||
            (!allyKingInCheck && !isPinned))
        {
            addToMoves(r + multiplier, c + 1, r, c, 'p');
        }
    }
    if (r == enPassantRow && board[r + multiplier][c - 1] == emptySquare && c1Prev == c - 1 && r == r1Prev - (2 * multiplier) && r == r2Prev)
    {
        if ((allyKingInCheck && inLimitedSquares(r + multiplier, c - 1)) ||
            (isPinned && (inPinnedPieces(r + multiplier, c - 1, pinnedPieces[pinnedIndex]))) ||
            (!allyKingInCheck && !isPinned))
        {
            addToMoves(r + multiplier, c - 1, r, c, 'p');
        }
    }
}

void Moves::knightMoves(int r, int c)
{
    int pos[8][2] = {{r + 2, c + 1}, {r + 2, c - 1}, {r - 2, c + 1}, {r - 2, c - 1}, {r + 1, c + 2}, {r + 1, c - 2}, {r - 1, c + 2}, {r - 1, c - 2}};
    // Checks if this piece is pinned, if it is it sets isPinned to true to use for later

    // iterator
    for (int i = 0; i < pinnedPieces.size(); i++)
    {
        if (r == pinnedPieces[i][pinnedPieces[i].size() - 1][0] && c == pinnedPieces[i][pinnedPieces[i].size() - 1][1])
        {
            return;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if (!pieceIsAlly(board[pos[i][0]][pos[i][1]]) && inBoundsCheck(pos[i][0], pos[i][1]))
        {
            if (allyKingInCheck && inLimitedSquares(pos[i][0], pos[i][1]))
            {
                addToMoves(pos[i][0], pos[i][1], r, c);
            }
            else if (!allyKingInCheck)
            {
                addToMoves(pos[i][0], pos[i][1], r, c);
            }
        }
    }
}

void Moves::rookMoves(int r, int c)
{
    int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool isPinned = false;
    int pinnedIndex = 0;
    // Checks if this piece is pinned, if it is it sets isPinned to true to use for later

    // iterator
    for (int i = 0; i < pinnedPieces.size(); i++)
    {
        if (r == pinnedPieces[i][pinnedPieces[i].size() - 1][0] && c == pinnedPieces[i][pinnedPieces[i].size() - 1][1])
        {
            if (allyKingInCheck)
            {
                return;
            }
            isPinned = true;
            pinnedIndex = i;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int x = r + direction[i][0];
        int y = c + direction[i][1];
        while (inBoundsCheck(x, y))
        {
            if (board[x][y] == emptySquare)
            {
                if (allyKingInCheck && inLimitedSquares(x, y) || (isPinned && (inPinnedPieces(x, y, pinnedPieces[pinnedIndex]))) || (!allyKingInCheck && !isPinned))
                {
                    addToMoves(x, y, r, c);
                }
            }
            else if (pieceIsEnemy(board[x][y]))
            {
                if (allyKingInCheck && inLimitedSquares(x, y) || (isPinned && (inPinnedPieces(x, y, pinnedPieces[pinnedIndex]))) || (!allyKingInCheck && !isPinned))
                {
                    addToMoves(x, y, r, c);
                }
                break;
            }
            else
            {
                break;
            }
            x += direction[i][0];
            y += direction[i][1];
        }
    }
}

void Moves::bishopMoves(int r, int c)
{
    int direction[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    bool isPinned = false;
    int pinnedIndex = 0;
    // iterator
    // Checks if this piece is pinned, if it is it sets isPinned to true to use for later

    for (int i = 0; i < pinnedPieces.size(); i++)
    {
        if (r == pinnedPieces[i][pinnedPieces[i].size() - 1][0] && c == pinnedPieces[i][pinnedPieces[i].size() - 1][1])
        {
            if (allyKingInCheck)
            {
                return;
            }
            isPinned = true;
            pinnedIndex = i;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int x = r + direction[i][0];
        int y = c + direction[i][1];
        while (inBoundsCheck(x, y))
        {
            if (board[x][y] == emptySquare)
            {
                if (allyKingInCheck && inLimitedSquares(x, y) || (isPinned && (inPinnedPieces(x, y, pinnedPieces[pinnedIndex]))) || (!allyKingInCheck && !isPinned))
                {
                    addToMoves(x, y, r, c);
                }
            }
            else if (pieceIsEnemy(board[x][y]))
            {
                if (allyKingInCheck && inLimitedSquares(x, y) || (isPinned && (inPinnedPieces(x, y, pinnedPieces[pinnedIndex]))) || (!allyKingInCheck && !isPinned))
                {
                    addToMoves(x, y, r, c);
                }
                break;
            }
            else
            {
                break;
            }
            x += direction[i][0];
            y += direction[i][1];
        }
    }
}

void Moves::queenMoves(int r, int c)
{
    // The queen uses both the rook and bishop mechanics
    rookMoves(r, c);
    bishopMoves(r, c);
}
void Moves::kingMoves(int r, int c)
{
    int pos[8][2] = {{r + 1, c + 1}, {r + 1, c}, {r + 1, c - 1}, {r, c + 1}, {r, c - 1}, {r - 1, c + 1}, {r - 1, c}, {r - 1, c - 1}};
    for (int i = 0; i < 8; i++)
    {
        if (!pieceIsAlly(board[pos[i][0]][pos[i][1]]) && inBoundsCheck(pos[i][0], pos[i][1]) && enemyCheckedSquares[pos[i][0]][pos[i][1]] == 0)
        {
            addToMoves(pos[i][0], pos[i][1], r, c);
        }
    }
    // Castling moves
    if (!allyKingInCheck &&
        !leftCastleFinished &&
        enemyCheckedSquares[r][c - 1] == 0 &&
        enemyCheckedSquares[r][c - 2] == 0 &&
        board[r][c - 1] == 0 &&
        board[r][c - 2] == 0)
    {
        addToMoves(r, c - 2, r, c, 'c');
    }
    if (!allyKingInCheck &&
        !rightCastleFinished &&
        enemyCheckedSquares[r][c + 1] == 0 &&
        enemyCheckedSquares[r][c + 2] == 0 &&
        board[r][c + 1] == 0 &&
        board[r][c + 2] == 0)
    {
        addToMoves(r, c + 2, r, c, 'c');
    }
}
void Moves::addToMoves(int rNew, int cNew, int rOld, int cOld)
{
    std::stringstream ss;
    std::string v;
    ss << board[rOld][cOld] << rOld << cOld << rNew << cNew;
    v = ss.str();
    if (v.size() == 5)
    {

        v.insert(0, "0");
    }
    listOfMoves.push_back(v);
    ss.str("");
}

void Moves::addToMoves(int rNew, int cNew, int rOld, int cOld, char specialMove)
{

    std::stringstream ss;
    std::string v;
    ss << board[rOld][cOld] << rOld << cOld << rNew << cNew;
    v = ss.str();

    if (v.size() == 5)
    {
        if (specialMove == 'x')
        {
            v.insert(0, "0");
        }
        else if (specialMove == 'p')
        {
            v.insert(0, "P");
        }
        else if (specialMove == 'c')
        {
            v.insert(0, "C");
        }
    }
    else if (specialMove == 'c')
    {
        v.replace(0, 1, "C");
    }

    listOfMoves.push_back(v);
    ss.str("");
}

void Moves::changeEnemyCheckedSquares()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == enemyPawn)
            {
                enemyPawnCheckedSquares(i, j);
            }
            if (board[i][j] == enemyRook)
            {
                enemyRookCheckedSquares(i, j);
            }
            if (board[i][j] == enemyKnight)
            {
                enemyKnightCheckedSquares(i, j);
            }
            if (board[i][j] == enemyBishop)
            {
                enemyBishopCheckedSquares(i, j);
            }
            if (board[i][j] == enemyQueen)
            {
                enemyQueenCheckedSquares(i, j);
            }
            if (board[i][j] == enemyKing)
            {
                enemyKingCheckedSquares(i, j);
            }
        }
    }
}
void Moves::enemyPawnCheckedSquares(int r, int c)
{
    int multiplier = 1;
    if (!color)
    {
        multiplier = -1;
    }
    if (inBoundsCheck(r + multiplier, c + 1))
    {

        if (board[r + multiplier][c + 1] == allyKing)
        {
            if (allyKingInCheck)
            {
                allyKingInDoubleCheck = true;
            }
            allyKingInCheck = true;
            limitedSquares.push_back({r, c});
        }
        enemyCheckedSquares[r + multiplier][c + 1]++;
    }
    if (inBoundsCheck(r + multiplier, c - 1))
    {

        if (board[r + multiplier][c - 1] == allyKing)
        {
            if (allyKingInCheck)
            {
                allyKingInDoubleCheck = true;
            }
            allyKingInCheck = true;
            limitedSquares.push_back({r, c});
        }
        enemyCheckedSquares[r + multiplier][c - 1]++;
    }
}
void Moves::enemyRookCheckedSquares(int r, int c)
{

    int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::vector<int>> tempSquares;

    int xPin = 0;
    int yPin = 0;
    for (int i = 0; i < 4; i++)
    {
        bool allyInLine = false;
        tempSquares.resize(0);
        tempSquares.push_back({r, c});
        int x = r + direction[i][0];
        int y = c + direction[i][1];
        while (inBoundsCheck(x, y))
        {
            if (!allyInLine)
            {
                enemyCheckedSquares[x][y]++;
            }
            if (board[x][y] == allyKing)
            {
                if (!allyInLine)
                {
                    if (allyKingInCheck)
                    {
                        allyKingInDoubleCheck = true;
                    }
                    else
                    {
                        allyKingInCheck = true;
                    }
                    limitedSquares = tempSquares;
                }
                else
                {
                    tempSquares.push_back({xPin, yPin});
                    pinnedPieces.push_back(tempSquares);
                }
                break;

                // std::cout << " king: " << x << " " << y << std::endl;

                // std::cout << " ensuring that copy is correct: " << limitedSquares.size() << std::endl;
                // for (int i = 0; i < limitedSquares.size(); i++)
                // {
                //     std::cout << limitedSquares[i][0] << " " << limitedSquares[i][1] << " | ";
                // }
            }
            else if (pieceIsAlly(board[x][y]))
            {
                if (allyInLine)
                {
                    break;
                }
                else
                {
                    allyInLine = true;
                    xPin = x;
                    yPin = y;
                }
            }
            else if (pieceIsEnemy(board[x][y]))
            {
                break;
            }

            tempSquares.push_back({x, y});
            x += direction[i][0];
            y += direction[i][1];
        }
    }
}
void Moves::enemyKnightCheckedSquares(int r, int c)
{
    int pos[8][2] = {{r + 2, c + 1}, {r + 2, c - 1}, {r - 2, c + 1}, {r - 2, c - 1}, {r + 1, c + 2}, {r + 1, c - 2}, {r - 1, c + 2}, {r - 1, c - 2}};
    for (int i = 0; i < 8; i++)
    {
        if (inBoundsCheck(pos[i][0], pos[i][1]))
        {

            if (board[pos[i][0]][pos[i][1]] == allyKing)
            {
                if (allyKingInCheck)
                {
                    allyKingInDoubleCheck = true;
                }
                allyKingInCheck = true;
                limitedSquares.push_back({r, c});
            }
            enemyCheckedSquares[pos[i][0]][pos[i][1]]++;
        }
    }
}
void Moves::enemyBishopCheckedSquares(int r, int c)
{
    int direction[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    std::vector<std::vector<int>> tempSquares;

    int xPin = 0;
    int yPin = 0;
    for (int i = 0; i < 4; i++)
    {
        bool allyInLine = false;
        tempSquares.resize(0);
        tempSquares.push_back({r, c});
        int x = r + direction[i][0];
        int y = c + direction[i][1];
        while (inBoundsCheck(x, y))
        {
            if (!allyInLine)
            {
                enemyCheckedSquares[x][y]++;
            }
            if (board[x][y] == allyKing)
            {
                if (!allyInLine)
                {
                    if (allyKingInCheck)
                    {
                        allyKingInDoubleCheck = true;
                    }
                    else
                    {
                        allyKingInCheck = true;
                    }
                    limitedSquares = tempSquares;
                }
                else
                {
                    tempSquares.push_back({xPin, yPin});
                    pinnedPieces.push_back(tempSquares);
                }
                break;

                // std::cout << " king: " << x << " " << y << std::endl;

                // std::cout << " ensuring that copy is correct: " << limitedSquares.size() << std::endl;
                // for (int i = 0; i < limitedSquares.size(); i++)
                // {
                //     std::cout << limitedSquares[i][0] << " " << limitedSquares[i][1] << " | ";
                // }
            }
            else if (pieceIsAlly(board[x][y]))
            {
                if (allyInLine)
                {
                    break;
                }
                else
                {
                    allyInLine = true;
                    xPin = x;
                    yPin = y;
                }
            }
            else if (pieceIsEnemy(board[x][y]))
            {
                break;
            }

            tempSquares.push_back({x, y});
            x += direction[i][0];
            y += direction[i][1];
        }
    }
}
void Moves::enemyQueenCheckedSquares(int r, int c)
{
    enemyRookCheckedSquares(r, c);
    enemyBishopCheckedSquares(r, c);
}
void Moves::enemyKingCheckedSquares(int r, int c)
{
    int pos[8][2] = {{r + 1, c + 1}, {r + 1, c}, {r + 1, c - 1}, {r, c + 1}, {r, c - 1}, {r - 1, c + 1}, {r - 1, c}, {r - 1, c - 1}};
    for (int i = 0; i < 8; i++)
    {
        if (inBoundsCheck(pos[i][0], pos[i][1]))
        {
            enemyCheckedSquares[r][c]++;
        }
    }
}

bool Moves::inBoundsCheck(int r, int c) const
{
    if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
    {
        return true;
    }
    return false;
}

bool Moves::inLimitedSquares(int r, int c) const
{
    // iterator
    for (int i = 0; i < limitedSquares.size(); i++)
    {
        if (r == limitedSquares[i][0] && c == limitedSquares[i][1])
        {
            return true;
        }
    }
    return false;
}
bool Moves::inPinnedPieces(int r, int c, std::vector<std::vector<int>> pinnedLine) const
{
    for (int i = 0; i < pinnedLine.size(); i++)
    {
        if (r == pinnedLine[i][0] && c == pinnedLine[i][1])
        {
            return true;
        }
    }
    return false;
}
void Moves::printMoves()
{

    std::cout << "List size: " << listOfMoves.size() << " | ";
    std::vector<std::string>::iterator move;
    for (move = listOfMoves.begin(); move < listOfMoves.end(); move++)
    {
        std::cout << *move << " ";
    }
    std::cout << std::endl;
}
bool Moves::pieceIsEnemy(int value) const
{
    if (value >= enemyPawn && value <= enemyKing)
    {
        return true;
    }
    return false;
}

bool Moves::pieceIsAlly(int value) const
{
    if (value >= allyPawn && value <= allyKing)
    {
        return true;
    }
    return false;
}
#endif