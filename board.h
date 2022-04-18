#include <stdlib.h>
#include <stdio.h>

typedef enum
{
    TRUE = 1,
    FALSE = 0,
} Bool;

typedef struct Piece
{
    Bool color;
    int type;
} Piece;

/**
 * @brief Create size*size checkers board
 *
 * @param size Number of culumns and rows of the board
 * @return Piece**
 */
Piece **CreateAndInitialiazeBoard(int size);

/**
 * @brief Place the pawns in the board
 *
 * @param board Board that is modified by the function
 * @param size Size of the board
 */
void InitializeBoard(Piece **board, int size);

/**
 * @brief Print the two letters corresponding to a piece
 *
 * @param piece Piece that is going to be print by the function
 */
void PrintPiece(Piece piece);

/**
 * @brief Print a checkers board
 *
 * @param board Board that is going to be print by the function
 * @param size Size of the board
 */
void PrintBoard(Piece **board, int size);

/**
 * @brief Check if a move is legal
 *
 * @param board Board where the move has to be check
 * @param size Size of the board
 * @param startcol Column of the actual position of the piece
 * @param startrow Row of the actual position of the piece
 * @param targcol Column of the targetted position of the piece
 * @param targrow Row of the targetted position of the piece
 * @return Bool : 0 if the move is illegal, 1 if the move is legal
 */
Bool MoveCheck(Piece **board, int size, int startcol, int startrow, int targcol, int targrow);

/**
 * @brief Execute the specified move (doesn't check if the move is possible)
 *
 * @param board Board where the move has to be executed
 * @param startcol Column of the actual position of the piece
 * @param startrow Row of the actual position of the piece
 * @param targcol Column of the targetted position of the piece
 * @param targrow Row of the targetted position of the piece
 * @return int : number of captured pieces
 */
int MoveExecution(Piece **board, int startcol, int startrow, int targcol, int targrow);