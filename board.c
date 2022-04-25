#include <board.h>


/**
 * @brief Create size*size checkers board
 * 
 * @param size Number of culumns and rows of the board
 * @return Piece** 
 */
Piece** CreateAndInitialiazeBoard(int size) {
    Piece** board = (Piece**) malloc(sizeof(Piece*)*size);
    for(int i=0;i<size;i++) {
        board[i] = (Piece*) malloc(sizeof(Piece)*size);
    }
    if(board != NULL) {
        InitializeBoard(board, size);
    } else {
        fprintf(stderr,"ERROR : not enough memory\n");
    }
    return board;
}


/**
 * @brief Place the pawns in the board
 * 
 * @param board Board that is modified by the function
 * @param size Size of the board
 */
void InitializeBoard(Piece** board, int size) {

    Piece empty;
    empty.color = 0;
    empty.type = 0;

    Piece wpawn;
    wpawn.color = 0;
    wpawn.type = 1;

    Piece bpawn;
    bpawn.color = 1;
    bpawn.type = 1;

    for(int i=0;i<size/2;i++) {
        board[2*i][0] = empty;
        board[2*i+1][0] = wpawn;
        board[2*i][2] = empty;
        board[2*i+1][2] = wpawn;

        board[2*i+1][1] = empty;
        board[2*i][1] = wpawn;

        board[2*i+1][size-3] = empty;
        board[2*i][size-3] = bpawn;
        board[2*i+1][size-1] = empty;
        board[2*i][size-1] = bpawn;

        board[2*i][size-2] = empty;
        board[2*i+1][size-2] = bpawn;
    }

    for(int i=0;i<size;i++) {
        for(int j=0;j<size-6;j++) {
            board[i][j+3] = empty;
        }
    }
}


/**
 * @brief Print the two letters corresponding to a piece
 * 
 * @param piece Piece that is going to be print by the function
 */
void PrintPiece(Piece piece) {
    if(piece.type == 0) {
        printf("  ");
    } else {
        if(piece.type == 1) {
            printf("P");
        } else {
             printf("D");
        }
        if(piece.color == 0) {
            printf("B");
        } else {
            printf("N");
        }
    }
}


/**
 * @brief Print a checkers board
 * 
 * @param board Board that is going to be print by the function
 * @param size Size of the board
 */
void PrintBoard(Piece** board, int size) {
    //printf("     __ __ __ __ __ __ __ __\n\n");
    for(int i=0;i<size;i++) {
        printf("%d |  ",size-i);
        for(int j=0;j<size;j++) {
            
            PrintPiece(board[j][i]);
            printf(" ");

            //printf("%d  ",board[j][i].type);
        }
        
        printf("\n");
    }
    printf("     __ __ __ __ __ __ __ __\n     a  b  c  d  e  f  g  h\n\n");
}


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
Bool MoveCheck(Piece** board, int size, int startcol, int startrow, int targcol, int targrow) {
    Bool okmove = 0;
    if (board[targcol][targrow].type == 0) {


        if (abs(targcol-startcol) == abs(targrow-startrow) && targrow<size && targrow>=0 && targcol>=0 && targcol<size ) {

            if (board[startcol][startrow].type == 1 && board[startcol][startrow].color == 0) {
                if (startrow-targrow == -1) {
                    okmove = 1;
                } else if (abs(startcol-targcol) == 2 && board[(targcol+startcol)/2][(targrow+startrow)/2].color == 1 && board[(targcol+startcol)/2][(targrow+startrow)/2].type != 0) {
                    okmove = 1;
                } else {
                    printf("Forbidden move !\n");
                }

            } else if (board[startcol][startrow].type == 1 && board[startcol][startrow].color == 1) {
                if (startrow-targrow == 1) {
                    okmove = 1;
                } else if (abs(startcol-targcol) == 2 && board[(targcol+startcol)/2][(targrow+startrow)/2].color == 0 && board[(targcol+startcol)/2][(targrow+startrow)/2].type != 0) {
                    okmove = 1;
                } else {
                    printf("Forbidden move !\n");
                }
                
            } else if (board[startcol][startrow].type == 2 ) {
                okmove = 1;
            } else {
                printf("No piece at this place\n");
            }
        } else {
            printf("Forbidden move !\n");
            
        }


        
    } else {
        printf("There is already a piece in this case !\n");
    }
    return okmove;
}

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
int MoveExecution(Piece** board, int startcol, int startrow, int targcol, int targrow) {
    int rip=0;
    board[targcol][targrow] = board[startcol][startrow];
    board[startcol][startrow].type = 0;
    for(int i=0;i<abs(targcol-startcol);i++) {
        if (board[startcol+abs(targcol-startcol)/(targcol-startcol)*i][startrow+abs(targrow-startrow)/(targrow-startrow)*i].type != 0) {
            rip++;
        }
        board[startcol+abs(targcol-startcol)/(targcol-startcol)*i][startrow+abs(targrow-startrow)/(targrow-startrow)*i].type = 0;
    }
    if((targrow == 7 && board[targcol][targrow].color == 0) || (targrow == 0 && board[targcol][targrow].color == 1)) {
        board[targcol][targrow].type = 2;
    }
    return rip;
}