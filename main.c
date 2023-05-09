#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define F_ARGS _Size* size, _Bool (*board)[size->width], char (*neighbours)[size->width], int y, int x

typedef struct {
    int height;
    int width;
} _Size;


void iter(void (*f)(F_ARGS), _Size *size, _Bool (*board)[size->width], char (*neighbours)[size->width])
{
    for(int y = 0; y < size->height; ++y)
    {
        for(int x = 0; x < size->width; ++x)
        {
            (*f)(size, board, neighbours, y, x);
        }
    }
}

void get_neighbours(F_ARGS)
{
    if(y > 0)
    {
        if(board[y - 1][x]) neighbours[y][x] += 1; // n

    	if((x + 1) < size->width && board[y - 1][x + 1]) neighbours[y][x] += 1; // ne
        if( x > 0                && board[y - 1][x - 1]) neighbours[y][x] += 1; // nw
    }

    if((x + 1) < size->width && board[y][x + 1]) neighbours[y][x] += 1; // e
    if( x > 0                && board[y][x - 1]) neighbours[y][x] += 1; // w

    if((y + 1) < size->height)
    {
        if(board[y + 1][x]) neighbours[y][x] += 1; // s

        if((x + 1) < size->height && board[y + 1][x + 1]) neighbours[y][x] += 1; // se
        if( x > 0                 && board[y + 1][x - 1]) neighbours[y][x] += 1; // sw
    }
}

void print_board_pos(F_ARGS)
{
    if(board[y][x])
        mvaddch(y, x, '*');
}

void apply_rules(F_ARGS)
{
    if(neighbours[y][x] < 2 || neighbours[y][x] > 3)
    {
        board[y][x] = 0;
    }
    else if(neighbours[y][x] == 3)
    {
        board[y][x] = 1;
    }
}

int handle_input(int input)
{
    switch(input)
    {
        case 'q':
            return 0;
        case KEY_RESIZE:
            return 0;
        default:
            return 1;
    }
}

int main(void)
{
    initscr();
    cbreak();
    noecho();

    _Size size;
    getmaxyx(stdscr, size.height, size.width);

    _Bool (*board     )[size.width] = malloc(size.height * size.width * sizeof(_Bool));
    char  (*neighbours)[size.width] = malloc(size.height * size.width * sizeof(char ));

    memset(board     , 0, size.height * size.width * sizeof(_Bool));
    memset(neighbours, 0, size.height * size.width * sizeof(char ));

    board[0][1] = 1;
    board[1][2] = 1;
    board[2][0] = 1;
    board[2][1] = 1;
    board[2][2] = 1;

    iter(&print_board_pos, &size, board, neighbours);

    int input = getch();
    _Bool run = handle_input(input);

    while(run)
    {
        iter(&get_neighbours, &size, board, neighbours);

        iter(&apply_rules, &size, board, neighbours);

        clear();
        iter(&print_board_pos, &size, board, neighbours);
        refresh();

        input = getch();
        run = handle_input(input);

        memset(neighbours, 0, size.height * size.width * sizeof(char ));
    }

    free(board);
    free(neighbours);

    endwin();

    return run;
}
