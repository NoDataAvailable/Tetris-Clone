#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H 15
#define W 12

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

typedef enum {false,true} boolean;

void init(char matrix[H][W], struct point **curr, struct piece **bank, int *score);
void dropBlock();
boolean movePiece(char matrix[H][W], struct point *curr, struct piece *orig, int dir);
void rotate(char matrix[H][W], struct point *curr, struct piece *orig, int dir);
boolean keyParse(char command, char matrix[H][W], struct point *curr, struct piece *orig);
int checkRow(char matrix[H][W], int row);
int checkAll(char matrix[H][W]);
struct piece *initBank();

#endif // TETRIS_H_INCLUDED
