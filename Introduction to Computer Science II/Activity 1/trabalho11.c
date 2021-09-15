/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 11/09/2021 06:40
 *   Modified time: 14/09/2021 17:29
 *   Description: Minesweeper Simulator
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BORDERS 8
#define BLANK_SPACE 46
#define BOMB 42
#define UNREVEALED 88
#define TIPS_BOARD 0
#define USER_BOARD 1

typedef struct board
{
    char *name;
    char ***matrix;
    int isEOF, lines, width, posY, posX, boards;
} board_t;

char *read_line();
char *read_line_file(FILE *, int *);
void read_board (board_t *);
void print_board(board_t *, int);
void load_tips  (board_t *);
void check_neighbors  (board_t *, int, int);
void prepare_board (board_t *);
void player_move(board_t *);
void fill_board (board_t *, int, int);

int main(){
    board_t *board = NULL;
    board = (board_t *) realloc(board, 1 * sizeof(board_t));

    board->isEOF = 0;
    board->name = NULL;
    board->matrix = (char ***) malloc(sizeof(char **));
    board->boards = 1;
    board->matrix[0] = NULL;

    int option;
    scanf("%d", &option);
    getchar();

    board->name = read_line();

    read_board(board);
    board->width = strlen(board->matrix[TIPS_BOARD][0]);

    switch (option)
    {
        case 1: print_board (board, TIPS_BOARD); break;
        case 2: load_tips   (board); print_board (board, TIPS_BOARD); break;
        case 3: player_move (board); break;
        default: break;
    }

    for (int i = 0; i < board->boards; i++)
    {
        for (int j = 0; j < board->lines; j++)
            free(board->matrix[i][j]);
        free(board->matrix[i]);
    }
    free(board->matrix);
    free(board->name);
    free(board);
    return 0;
}

char *read_line(){
    char *line = NULL;
    int c, k = 0;
    while(( c = getchar()) != '\n')
    {
        line = realloc(line, (k+1) * sizeof(char));
        line[k++] = c;
    }
    line = realloc(line, (k+1) * sizeof(char));
    line[k] = '\0';
    return line;
}

char *read_line_file(FILE *file, int *isEOF){
    char *line = NULL, c;
    int k = 0; // letters
    while ((c = fgetc(file)) != '\n')
    {
        line = (char *)realloc(line, ((k+1) * sizeof(char)));
        line[k++] = c;
    }
    if ((c = fgetc(file)) == EOF) *isEOF = 1;
    else ungetc(c, file);
    line = (char *)realloc(line, ((k+1) * sizeof(char)));
    line[k] = '\0';
    return line;
}

void print_board(board_t *board, int board_option){
    for (int i = 0; i < board->lines; i++)
    {
        printf("%s", board->matrix[board_option][i]);
        if (i+1 < board->lines)
            printf("\n"); 
    }
}

void read_board(board_t *board){
    FILE *file = fopen(board->name, "r");
    for (board->lines = 0; board->isEOF != 1; board->lines++)
    {
        board->matrix[TIPS_BOARD] = (char **) realloc(board->matrix[TIPS_BOARD], (board->lines+1) * sizeof(char *));
        board->matrix[TIPS_BOARD][board->lines] = NULL;
        board->matrix[TIPS_BOARD][board->lines] = read_line_file(file, &board->isEOF);
    }
    fclose(file);
}

void load_tips(board_t *board){
    int maxIndex = board->lines * board->width;
    for (int index=0; index < maxIndex; index++)
    {
        int row = index / board->width;
        int col = index % board->width;
            if (board->matrix[TIPS_BOARD][row][col] == BOMB)
                check_neighbors(board, row, col);  
    }
}

void check_neighbors(board_t *board, int row, int col){

    int offsety[] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int offsetx[] = {-1, 0, 1,-1, 1,-1, 0, 1};

    for (int i = 0; i < BORDERS; i++)
    {
        int neighborY = row + offsety[i];
        int neighborX = col + offsetx[i];
        if
        (    
            neighborY < 0 || neighborY > (board->lines-1) ||
            neighborX < 0 || neighborX > (board->width-1)
        )
        {
            continue;
        }
        char position = board->matrix[TIPS_BOARD][neighborY][neighborX];
        if (position == BLANK_SPACE)
            board->matrix[TIPS_BOARD][neighborY][neighborX] = '1';
        else if (position == BOMB)
            continue;
        else
        {
            int neighbor = board->matrix[TIPS_BOARD][neighborY][neighborX] - '0';
            neighbor++;
            board->matrix[TIPS_BOARD][neighborY][neighborX] = neighbor + '0';
        } 
    }
}

void player_move(board_t *board){
    scanf("%d %d", &board->posY, &board->posX);
    getchar();

    load_tips(board);

    char position = board->matrix[TIPS_BOARD][board->posY][board->posX];
    if (position == BOMB)
        print_board (board, TIPS_BOARD);
    else if (position == BLANK_SPACE)
    {
        prepare_board(board);
        fill_board(board, board->posY, board->posX);
        print_board (board, USER_BOARD);
    }
    else
    {
        prepare_board(board);
        board->matrix[USER_BOARD][board->posY][board->posX] = board->matrix[TIPS_BOARD][board->posY][board->posX];
        print_board (board, USER_BOARD);
    }
}

void prepare_board(board_t *board){
    board->matrix = realloc(board->matrix, (board->boards+1)*sizeof(char**));
    board->boards++;
    board->matrix[USER_BOARD] = malloc(board->lines * sizeof(char *));

    int i,j;
    for (i = 0; i < board->lines; i++)
    {
        board->matrix[USER_BOARD][i] = malloc((board->width+1) * sizeof(char));
        for (j = 0; j < board->width; j++)
            board->matrix[USER_BOARD][i][j] = 'X';
        board->matrix[USER_BOARD][i][j] = '\0';
    }
}

void fill_board(board_t *board, int posY, int posX){
    board->matrix[USER_BOARD][posY][posX] = board->matrix[TIPS_BOARD][posY][posX];   
    if(board->matrix[TIPS_BOARD][posY][posX] != BLANK_SPACE)
        return;
    if (posY-1 >= 0 && board->matrix[USER_BOARD][posY-1][posX] == UNREVEALED)
        fill_board(board, posY-1, posX);
    if (posX+1 < board->width && board->matrix[USER_BOARD][posY][posX+1] == UNREVEALED)
        fill_board(board, posY, posX+1);
    if (posY+1 < board->lines && board->matrix[USER_BOARD][posY+1][posX] == UNREVEALED)
        fill_board(board, posY+1, posX);
    if (posX-1 >= 0 && board->matrix[USER_BOARD][posY][posX-1] == UNREVEALED)
        fill_board(board, posY, posX-1);
}