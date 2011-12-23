#include "Tetris.h"
//#include <curses.h>

//typedef enum {false,true} bool;

/*int main()
{
    return 0;
};*/

void init(char matrix[H][W], struct point **curr, struct piece **bank, int *score)
{
    srand ( time(NULL) );
    *bank = initBank();

    int k,l;

    for (k=0;k<H;k++)
        for (l=0;l<W;l++)
            matrix[k][l] = '.';

    for (k=0;k<H;k++)
        matrix[k][0] = matrix[k][W-1] = '|';
    for (k=0;k<W;k++)
        matrix[H-1][k] = '-';

    matrix[H-1][0] = matrix[H-1][W-1] = '+';

    *curr = malloc(sizeof(struct point));
    (*curr)->x = malloc(sizeof(int));
    (*curr)->y = malloc(sizeof(int));

    score = 0;
};

void dropBlock()
{

};

bool movePiece(char matrix[H][W], struct point *curr, struct piece *orig, int dir)
{
    bool hit = false, end = false;
    int i;
    int x[4];
    int y[4];
    for (i=0;i<4;i++)
    {
        switch (dir)
        {
            case 2:
                x[i] = *(curr->x);
                y[i] = *(curr->y)+1;

                break;
            case 3:
                x[i] = *(curr->x)-1;
                y[i] = *(curr->y);
                break;
            case 4:
                x[i] = *(curr->x)+1;
                y[i] = *(curr->y);
                break;
            default:
                break;
        };
    };

    for (i=0;i<4;i++)
    {
        matrix[ *(curr->y) + *((orig->parts[i]).y) - 1 ][( *(curr->x)) + *((orig->parts[i]).x) - 1 ] = '.';
    };

    for (i=0;i<4;i++)
    {
        if (matrix[ y[i] + *((orig->parts[i]).y) - 1 ][ x[i] + *((orig->parts[i]).x) - 1 ] != '.')
            {
                hit = true;
                if (dir == 2)
                    end = true;
            };
    };

    for (i=0;i<4;i++)
    {
        if (!hit)
        {
            if (x[i] < 0)
                *(curr->x) = x[i];
            else
                *(curr->x) = x[i];
            if (y[i] < 0)
                *(curr->y) = y[i];
            else
                *(curr->y) = y[i];
        };
        matrix[ *(curr->y) + *((orig->parts[i]).y) - 1 ][( *(curr->x)) + *((orig->parts[i]).x) - 1 ] = '#'; //implement different chars for diff pieces
    };

    return end;
}

void rotate(char matrix[H][W], struct point *curr, struct piece *orig, int dir)
{
    bool hit = false;
    int i;
    int x[4];
    int y[4];
    if (orig->dim == 3)
    {
        for (i=0;i<4;i++)
        {
            x[i] = *((orig->parts[i]).x)-2;
            y[i] = *((orig->parts[i]).y)-2;
            int temp;
            temp = y[i];
            y[i] = x[i];
            x[i] = - temp;

            x[i]+=2;
            y[i]+=2;
        };
    }
    else
    {
        for (i=0;i<4;i++)
        {
            if (*((orig->parts[i]).x) < 3)
                x[i] = *((orig->parts[i]).x)-3;
            else
                x[i] = *((orig->parts[i]).x)-2;
            if (*((orig->parts[i]).y) < 3)
                y[i] = *((orig->parts[i]).y)-3;
            else
                y[i] = *((orig->parts[i]).y)-2;
            int temp;
            temp = y[i];
            y[i] = x[i];
            x[i] = - temp;

            if (x[i] < 0)
                x[i] += 3;
            else
                x[i] += 2;
            if (y[i] < 0)
                y[i] += 3;
            else
                y[i] += 2;
        };

    };

    for (i=0;i<4;i++)
    {
        matrix[ *(curr->y) + *((orig->parts[i]).y) - 1 ][( *(curr->x)) + *((orig->parts[i]).x) - 1 ] = '.';
    };

    for (i=0;i<4;i++)
    {
        if (matrix[ *(curr->y) + y[i] - 1 ][( *(curr->x)) + x[i] - 1 ] != '.')
            hit = true;
    };

    for (i=0;i<4;i++)
    {
        if (!hit)
        {
            if (x[i] < 0)
                *((orig->parts[i]).x) = x[i];
            else
                *((orig->parts[i]).x) = x[i];
            if (y[i] < 0)
                *((orig->parts[i]).y) = y[i];
            else
                *((orig->parts[i]).y) = y[i];
        };
        matrix[ *(curr->y) + *((orig->parts[i]).y) - 1 ][( *(curr->x)) + *((orig->parts[i]).x) - 1 ] = '#'; //implement different chars for diff pieces
    };
};

bool keyParse(char command, char matrix[H][W], struct point *curr, struct piece *orig)
{
    bool end = false;
    switch ((int)command)
    {
        case 119: // up
            rotate(matrix, curr, orig, 1);
            break;
        case 115: // down
            end = movePiece(matrix, curr, orig, 2);
            break;
        case 97: // left
            end = movePiece(matrix, curr, orig, 3);
            break;
        case 100: // right
            end = movePiece(matrix, curr, orig, 4);
            break;
        default:
            break;
    };
    return end;
};

int checkRow(char matrix[H][W], int row) // 0 == none, 1 == some, 2 == full
{
    int count, i;
    count = 0;
    for (i=1;i<W-1;i++)
        if (matrix[row][i] != '.')
            count++;
    if (count == 0)
        return 0;
    else if (count == W-2)
        return 2;
    else
        return 1;
};

int checkAll(char matrix[H][W])
{
    int lines = 0;
    int full;
    int currRow = H-2;
    while (currRow>0)
    {
        full = checkRow(matrix,currRow);
        if (full == 2)
        {
            lines++;
            int i,j;
            for (i=currRow;i>0;i--)
                for (j=0;j<W-1;j++)
                    matrix[i][j] = matrix[i-1][j];
        }
        else
            currRow--;
    };
    return lines;
};

struct piece *initBank()
{
    int i;
    struct piece *pieces;
    pieces = malloc(7*sizeof(struct piece));
    pieces[0].dim = 4; // Line
    for (i=0;i<4;i++)
    {
        *((pieces[0].parts[i]).y = malloc(sizeof(int))) = i+1;
        *((pieces[0].parts[i]).x = malloc(sizeof(int))) = 2;
    };

    pieces[1].dim = 4; // Cube
    {
        *((pieces[1].parts[0]).y = malloc(sizeof(int))) = 2;
        *((pieces[1].parts[0]).x = malloc(sizeof(int))) = 2;
        *((pieces[1].parts[1]).y = malloc(sizeof(int))) = 2;
        *((pieces[1].parts[1]).x = malloc(sizeof(int))) = 3;
        *((pieces[1].parts[2]).y = malloc(sizeof(int))) = 3;
        *((pieces[1].parts[2]).x = malloc(sizeof(int))) = 2;
        *((pieces[1].parts[3]).y = malloc(sizeof(int))) = 3;
        *((pieces[1].parts[3]).x = malloc(sizeof(int))) = 3;
    };

    pieces[2].dim = 3; // Z-piece
    {
        *((pieces[2].parts[0]).y = malloc(sizeof(int))) = 1;
        *((pieces[2].parts[0]).x = malloc(sizeof(int))) = 1;
        *((pieces[2].parts[1]).y = malloc(sizeof(int))) = 1;
        *((pieces[2].parts[1]).x = malloc(sizeof(int))) = 2;
        *((pieces[2].parts[2]).y = malloc(sizeof(int))) = 2;
        *((pieces[2].parts[2]).x = malloc(sizeof(int))) = 2;
        *((pieces[2].parts[3]).y = malloc(sizeof(int))) = 2;
        *((pieces[2].parts[3]).x = malloc(sizeof(int))) = 3;
    };

    pieces[3].dim = 3; // S-piece
    {
        *((pieces[3].parts[0]).y = malloc(sizeof(int))) = 3;
        *((pieces[3].parts[0]).x = malloc(sizeof(int))) = 1;
        *((pieces[3].parts[1]).y = malloc(sizeof(int))) = 3;
        *((pieces[3].parts[1]).x = malloc(sizeof(int))) = 2;
        *((pieces[3].parts[2]).y = malloc(sizeof(int))) = 2;
        *((pieces[3].parts[2]).x = malloc(sizeof(int))) = 2;
        *((pieces[3].parts[3]).y = malloc(sizeof(int))) = 2;
        *((pieces[3].parts[3]).x = malloc(sizeof(int))) = 3;
    };

    pieces[4].dim = 3; // T-piece
    {
        *((pieces[4].parts[0]).y = malloc(sizeof(int))) = 2;
        *((pieces[4].parts[0]).x = malloc(sizeof(int))) = 1;
        *((pieces[4].parts[1]).y = malloc(sizeof(int))) = 1;
        *((pieces[4].parts[1]).x = malloc(sizeof(int))) = 2;
        *((pieces[4].parts[2]).y = malloc(sizeof(int))) = 2;
        *((pieces[4].parts[2]).x = malloc(sizeof(int))) = 2;
        *((pieces[4].parts[3]).y = malloc(sizeof(int))) = 2;
        *((pieces[4].parts[3]).x = malloc(sizeof(int))) = 3;
    };

    pieces[5].dim = 3; // L-piece
    {
        *((pieces[5].parts[0]).y = malloc(sizeof(int))) = 1;
        *((pieces[5].parts[0]).x = malloc(sizeof(int))) = 2;
        *((pieces[5].parts[1]).y = malloc(sizeof(int))) = 2;
        *((pieces[5].parts[1]).x = malloc(sizeof(int))) = 2;
        *((pieces[5].parts[2]).y = malloc(sizeof(int))) = 3;
        *((pieces[5].parts[2]).x = malloc(sizeof(int))) = 2;
        *((pieces[5].parts[3]).y = malloc(sizeof(int))) = 3;
        *((pieces[5].parts[3]).x = malloc(sizeof(int))) = 3;
    };

    pieces[6].dim = 3; // Rev-L-piece
    {
        *((pieces[6].parts[0]).y = malloc(sizeof(int))) = 1;
        *((pieces[6].parts[0]).x = malloc(sizeof(int))) = 2;
        *((pieces[6].parts[1]).y = malloc(sizeof(int))) = 2;
        *((pieces[6].parts[1]).x = malloc(sizeof(int))) = 2;
        *((pieces[6].parts[2]).y = malloc(sizeof(int))) = 3;
        *((pieces[6].parts[2]).x = malloc(sizeof(int))) = 2;
        *((pieces[6].parts[3]).y = malloc(sizeof(int))) = 1;
        *((pieces[6].parts[3]).x = malloc(sizeof(int))) = 3;
    };

    return pieces;
}
