#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H 21
#define W 12

#define BLOCK 219
#define BKG 32

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

typedef enum {false,true} bool;

void init(char matrix[H][W], struct point **curr, struct piece **bank);
void dropBlock();
bool movePiece(char matrix[H][W], struct point *curr, struct piece *orig, int dir);
void rotate(char matrix[H][W], struct point *curr, struct piece *orig, int dir);
bool keyParse(char command, char matrix[H][W], struct point *curr, struct piece *orig);
int checkRow(char matrix[H][W], int row);
int checkAll(char matrix[H][W]);
struct piece *initBank();

#endif // TETRIS_H_INCLUDED
