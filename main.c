#include <stdio.h>

#define WIDTH 213
#define HEIGHT 56

#define F_ARGS _Bool board[HEIGHT][WIDTH], int neighbours[HEIGHT][WIDTH], int y, int x

int get_neighbours(_Bool board[HEIGHT][WIDTH], int y, int x)
{
    int neighbours = 0;

    if(y > 0)
    {
        if(board[y - 1][x]) ++neighbours; // n

    	if((x + 1) < WIDTH && board[y - 1][x + 1]) ++neighbours; // ne
        if( x > 0          && board[y - 1][x - 1]) ++neighbours; // nw
    }

    if((x + 1) < WIDTH && board[y][x + 1]) ++neighbours; // e
    if( x > 0         && board[y][x - 1]) ++neighbours; // w

    if((y + 1) < HEIGHT)
    {
        if(board[y + 1][x]) ++neighbours; // s

        if((x + 1) < WIDTH && board[y + 1][x + 1]) ++neighbours; // se
        if( x > 0          && board[y + 1][x - 1]) ++neighbours; // sw
    }

    return neighbours;
}

void iter(void (*f)(F_ARGS), _Bool board[HEIGHT][WIDTH], int neighbours[HEIGHT][WIDTH])
{
    for(int y = 0; y < HEIGHT; ++y)
    {
        for(int x = 0; x < WIDTH; ++x)
        {
            (*f)(board, neighbours, y, x);
        }
    }
}

void print_board_pos(F_ARGS)
{
    board[y][x] ? putc('*', stdout) : putc('.', stdout);
    if(x + 1 == WIDTH)
        putc('\n', stdout);
}

void calculate_neighbours(F_ARGS)
{
    neighbours[y][x] = get_neighbours(board, y, x);
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
        default:
            return 1;
    }
}

int main(void)
{
    _Bool board[HEIGHT][WIDTH] = { 0 };
    int neighbours[HEIGHT][WIDTH] = { 0 };

    board[0][1] = 1;
    board[1][2] = 1;
    board[2][0] = 1;
    board[2][1] = 1;
    board[2][2] = 1;

    iter(&print_board_pos, board, neighbours);
    
    int input = getchar();
    _Bool run = handle_input(input);

    while(run)
    {
        iter(&calculate_neighbours, board, neighbours);

        iter(&apply_rules, board, neighbours);

        iter(&print_board_pos, board, neighbours);

        input = getchar();
        run = handle_input(input);
    }

    return 0;
}
