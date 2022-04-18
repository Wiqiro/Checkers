#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <board.h>

/*

8 |     PB    PB    PB    PB
7 |  PB    PB    PB    PB
6 |     PB    PB    PB    PB
5 |
4 |
3 |  PN    PN    PN    PN
2 |     PN    PN    PN    PN
1 |  PN    PN    PN    PN
     __ __ __ __ __ __ __ __
     a  b  c  d  e  f  g  h

*/

int main(int argc, char *argv[])
{
    int size = 8, moves = 0;
    Piece **CheckersBoard = CreateAndInitialiazeBoard(size);
    Bool turn;
    int startcol, startrow, targcol, targrow, whitepieces, blackpieces;

    PrintBoard(CheckersBoard, size);
    printf("Whites begin !\n");

    do
    {

        do
        {
            do
            {
                printf("Enter the piece you want to move\n");
                char input[2];
                scanf("%s", input);
                startcol = toupper(input[0]) - 'A';
                startrow = size - (input[1] - '0');

            } while (startcol < 0 || startcol >= size || startrow < 0 || startrow >= size);
            do
            {
                printf("Where do you want to move this piece ?\n");
                char input[2];
                scanf("%s", input);
                targcol = toupper(input[0]) - 'A';
                targrow = size - (input[1] - '0');
            } while (targcol < 0 || targcol >= size || targrow < 0 || targrow >= size);
            if (CheckersBoard[startcol][startrow].color != turn)
            {
                printf("You can't move this piece !\n");
            }
        } while (!MoveCheck(CheckersBoard, size, startcol, startrow, targcol, targrow) || turn != CheckersBoard[startcol][startrow].color);

        moves++;
        turn = moves % 2;

        if (turn == 0)
        {
            whitepieces = MoveExecution(CheckersBoard, startcol, startrow, targcol, targrow);
            PrintBoard(CheckersBoard, size);
            printf("It's whites turn !\n");
        }
        else
        {
            blackpieces = MoveExecution(CheckersBoard, startcol, startrow, targcol, targrow);
            PrintBoard(CheckersBoard, size);
            printf("It's blacks turn !\n");
        }

    } while (blackpieces < size * 3 / 2 && whitepieces < size * 3 / 2);

    if (blackpieces == 0)
    {
        printf("Whites win !");
    }
    else
    {
        printf("Blacks win !");
    }
}
