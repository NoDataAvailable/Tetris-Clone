#include "Tetris.h"
#include "Tetris_curses.h"
//#include <curses.h>

int main()
{
    initscr();
    noecho();
    nodelay(stdscr,TRUE);

    char grid[H][W];
    struct point *curr;
    struct piece *bank;
    int score = 0;

    init(grid, curr, bank, &score);

    mprintf(grid, W, H);

    while (!checkRow(grid,0))
    {
        struct piece orig = bank[rand()%7];
        bool end = false;
        *(curr->x) = W/2-2;
        *(curr->y) = 0;
        int i;
        for (i=0;i<4;i++)
        {
            grid[ *(curr->y) + *((orig.parts[i]).y) - 1 ][( *(curr->x)) + *((orig.parts[i]).x) - 1 ] = '#'; //implement different chars for diff pieces
        };

        mvprintw(2,W+1,"+---------------+", score);
        mvprintw(3,W+1,"| Points: %.5d |", score);
        mvprintw(4,W+1,"+---------------+", score);

        char ch = 0;
        int startTime = clock();
        while (!end) //(i=0;i<10;i++)
        {
            refresh();
            end = keyParse(ch, grid, curr, &orig);
            if (clock()-startTime>500000)
            {
                end = movePiece(grid, curr, &orig, 2);
                startTime = clock();
            };
            mprintf(grid, W, H);
            ch = getch();
        };
        int addition = checkAll(grid);
        score += addition * addition;
    };

    mvaddstr(H/2-1,W/2-7,"+------------+");
    mvaddstr(H/2,W/2-7, "| Game Over! |");
    mvaddstr(H/2+1,W/2-7,"+------------+");
    move(H,W);
    refresh();
    nodelay(stdscr,FALSE);
    getch();
    endwin();
    return 0;
};

void mprintf(char matrix[H][W], int length, int height)
{
    int i,j;
    for (i=0;i<height;i++)
    {
        for (j=0;j<length;j++)
            mvaddch(i+1,j+1,matrix[i][j]);
    }
};

