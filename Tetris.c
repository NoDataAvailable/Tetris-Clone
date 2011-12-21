// Working on putting blocks in

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H 22
#define W 12

typedef enum {True, False} bool;

struct point
{
    int *x;
    int *y;
};

struct piece
{
    int dim;
    struct point parts[4];
};

void mprintf(char matrix[H][W], int length, int height);
bool move(char matrix[H][W], struct point *orig, int dir);
bool rotate(char matrix[H][W], struct piece *orig, int dir);
void keyParse(char command, char matrix[H][W], struct point *curr);
int checkRow(char matrix[H][W], int row);
struct piece *initBank();

int main()
{
    srand ( time(NULL) );
    struct piece *bank = initBank();


    char grid[H][W];

    int k,l;

    for (k=0;k<H;k++)
        for (l=0;l<W;l++)
            grid[k][l] = '.';

    for (k=0;k<H;k++)
        grid[k][0] = grid[k][W-1] = '|';
    for (k=0;k<W;k++)
        grid[H-1][k] = '-';

    struct point *curr;
    curr = malloc(sizeof(curr));
    curr->x = malloc(sizeof(int));
    curr->y = malloc(sizeof(int));

    *(curr->x) = 3;
    *(curr->y) = 3;

    grid[*(curr->x)][*(curr->y)] = '*';

    mprintf(grid, W, H);

    printf("%d",checkRow(grid,0));

    while (!checkRow(grid,0))
    {
        char ch = 0;
        while (ch!=27) //(i=0;i<10;i++)
        {
            keyParse(ch, grid, curr);
            system("cls");
            mprintf(grid, W, H);
            printf("%d - %c -\n",ch,ch);
            ch = getch(stdin);
        };
    };

    return 0;
};

void mprintf(char matrix[H][W], int length, int height)
{
    int i,j;
    for (i=0;i<height;i++)
    {
        for (j=0;j<length;j++)
            printf("%c",matrix[i][j]);
        printf("\n");
    }
};

bool move(char matrix[H][W], struct point *orig, int dir)
{
    switch (dir)
    {
        case 0: // no movement
            break;

        case 1: // up
            if (*(orig->y) > 0 && matrix[(*(orig->y))-1][*(orig->x)] == '.')
            {
                matrix[  *(orig->y)      ][ *(orig->x) ] = '.';
                matrix[ (*(orig->y)) - 1 ][ *(orig->x) ] = '*';
                (*(orig->y))--;
            }
            else return True;
            break;

        case 2: // down
            if (*(orig->y) < H-1 && matrix[(*(orig->y))+1][*(orig->x)] == '.')
            {
                matrix[  *(orig->y)      ][ *(orig->x) ] = '.';
                matrix[ (*(orig->y)) + 1 ][ *(orig->x) ] = '*';
                (*(orig->y))++;
            }
            else return True;
            break;

        case 3: // left
            if (*(orig->x) > 0 && matrix[ *(orig->y) ][( *(orig->x)) - 1 ] == '.')
            {
                matrix[ *(orig->y) ][  *(orig->x)      ] = '.';
                matrix[ *(orig->y) ][ (*(orig->x)) - 1 ] = '*';
                (*(orig->x))--;
            }
            else return True;
            break;

        case 4: // right
            if (*(orig->x) < W-1 && matrix[*(orig->y)][ (*(orig->x))+1] == '.')
            {
                matrix[ *(orig->y) ][  *(orig->x)      ] = '.';
                matrix[ *(orig->y) ][ (*(orig->x)) + 1 ] = '*';
                (*(orig->x))++;
            }
            else return True;
            break;

        default:
            break;
    };
    return False;
}

bool rotate(char matrix[H][W], struct piece *orig, int dir)
{
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
        };
    }
    else
    {
        for (i=0;i<4;i++)
        {
            if (*((orig->parts[i]).x) < 3)
                printf("%d",x[i] = *((orig->parts[i]).x)-3);
            else
                printf("%d",x[i] = *((orig->parts[i]).x)-2);
            if (*((orig->parts[i]).y) < 3)
                {y[i] = *((orig->parts[i]).y)-3;}
            else
                y[i] = *((orig->parts[i]).y)-2;
            int temp;
            temp = y[i];
            y[i] = x[i];
            x[i] = - temp;
            if (x[i] < 0)
                *((orig->parts[i]).x) = 3 + x[i];
            else
                *((orig->parts[i]).x) = 2 + x[i];
            if (y[i] < 0)
                *((orig->parts[i]).y) = 3 + y[i];
            else
                *((orig->parts[i]).y) = 2 + y[i];
        };

    };

    return False;
};

void keyParse(char command, char matrix[H][W], struct point *curr)
{
    bool hit = False;
    switch ((int)command)
    {
        case 119: // up
            hit = move(matrix, curr, 1);
            break;
        case 115: // down
            hit = move(matrix, curr, 2);
            break;
        case 97: // left
            hit = move(matrix, curr, 3);
            break;
        case 100: // right
            hit = move(matrix, curr, 4);
            break;
        default:
            break;
    };
}

int checkRow(char matrix[H][W], int row) // 0 == none, 1 == some, 2 == full
{
    int count, i;
    count = 0;
    for (i=1;i<W-1;i++)
        if (matrix[row][i] != '.')
            count++;
    if (count == 0)
        return 0;
    else if (count == W)
        return 2;
    else
        return 1;
};

struct piece *initBank()
{
    int i;
    struct piece *pieces;
    pieces = malloc(7*sizeof(struct piece));
    pieces[0].dim = 4; // Line
    for (i=0;i<4;i++)
    {
        *((pieces[0].parts[i]).x = malloc(sizeof(int))) = i+1;
        *((pieces[0].parts[i]).y = malloc(sizeof(int))) = 2;
    }



    return pieces;
}
