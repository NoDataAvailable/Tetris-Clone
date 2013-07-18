#include "Tetris.h"
#include "Tetris_curses.h"
#include <curses.h>

#define XRES 4
#define YRES 2

int main()
{
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    attron(COLOR_PAIR(1));
    initscr();
    noecho();
    nodelay(stdscr,TRUE);
    char grid[H][W];
    struct point *curr;
    struct piece *bank;
    int score = 0;
    int lines = 0;
    int initLevel = 3;
    init(grid, &curr, &bank);
    mprintf(grid, W, H);
    refresh();

    while (!checkRow(grid,0))
    {
        mvprintw(1,1,"1");
        refresh();
        struct piece orig = bank[rand()%7];
        mvprintw(2,1,"2");
        refresh();
        bool end = false;
        *(curr->x) = W/2-2;
        *(curr->y) = 0;
        int i;
        refresh();
        for (i=0;i<4;i++)
        {
            grid[ *(curr->y) + *((orig.parts[i]).y) - 1 ][( *(curr->x)) + *((orig.parts[i]).x) - 1 ] = BLOCK; //implement different chars for diff pieces
        };
        mvprintw(2,XRES*W+1,"+---------------+");
        mvprintw(3,XRES*W+1,"| Points: %.5d |", score);
        mvprintw(4,XRES*W+1,"| Lines:    %.3d |", lines);
        mvprintw(5,XRES*W+1,"| Level:     %.2d |", lines/10+initLevel);
        mvprintw(6,XRES*W+1,"+---------------+");
        refresh();
        char ch = 0;
        int startTime = clock();
        while (!end) //(i=0;i<10;i++)
        {
            refresh();
            end = keyParse(ch, grid, curr, &orig);
            if (clock()-startTime > (1000000/(lines/10+initLevel)))
            {
                end = movePiece(grid, curr, &orig, 2);
                startTime = clock();
            };
            mprintf(grid, W, H);
            ch = getch();
        };
        int addition = checkAll(grid);
        score += (addition * addition * (lines/10+initLevel));
        lines += addition;
    };

    mvaddstr(YRES*H/2-1,XRES*W/2-7,"+------------+");
    mvaddstr(YRES*H/2  ,XRES*W/2-7,"| Game Over! |");
    mvaddstr(YRES*H/2+1,XRES*W/2-7,"+------------+");
    move(H,W);
    refresh();
    nodelay(stdscr,FALSE);
    attroff(COLOR_PAIR(1));
    getch();
    endwin();
    return 0;
};

void mprintf(char matrix[H][W], int length, int height)
{
    int i,j,k,l;
    for (i=0;i<height;i++)
        for (l=0;l<YRES;l++)
            for (j=0;j<length;j++)
                for (k=0;k<XRES;k++)
                    mvaddch(YRES*i+l+1,XRES*j+k+1,matrix[i][j]);
};

