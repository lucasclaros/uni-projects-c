/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 11/09/2021 06:40
 *   Modified time: 13/09/2021 03:28
 *   Description: Minesweeper Simulator
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BORDERS 8
#define BLANK_SPACE 46
#define BOMB 42
#define UNREVEALED 88

typedef struct board
{
    char *name, **matrix;
    int isEOF, lines, posY, posX;
} board_t;

char *read_line();
char *read_line_file(FILE *, board_t *);
void read_board (board_t *);
void print_board(board_t *);
void load_tips  (board_t *);
void prepare_board (board_t *, int, int, int);
void check_neighbors  (board_t *, int, int);
void player_move(board_t *);
void fill_board (board_t *, int, int);

int main(){
    board_t *board;
    board = malloc(sizeof(board_t));
    board->isEOF = 0;

    board->matrix = NULL;
    int option;
    scanf("%d", &option);
    getchar();

    board->name = NULL;
    board->name = read_line();

    read_board(board);

    switch (option)
    {
        case 1: print_board (board); break;
        case 2: load_tips   (board); print_board(board); break;
        case 3: player_move (board); print_board(board); break;
        default: break;
    }

    for (int i = 0; i < board->lines; i++)
        free(board->matrix[i]);
    free(board->matrix);
    free(board->name);
    free(board);
    return 0;
}

char *read_line(){
    char *line = NULL;
    int c, k = 0;
    while(( c = getchar()) != EOF && c != '\n')
    {
        line = realloc(line, (k+1) * sizeof(char));
        line[k++] = c;
    }
    line = realloc(line, (k+1) * sizeof(char));
    line[k] = '\0';
    return line;
}

char *read_line_file(FILE *arquivo, board_t *board){
    char *line = NULL;
    int c, k = 0; // letters
    while ((c = fgetc(arquivo)) != EOF && c != '\n')
    {
        line = realloc(line, (k+1) * sizeof(char));
        line[k++] = c;
    }
    if (c == EOF) board->isEOF = 1;
    line = realloc(line, (k+1) * sizeof(char));
    line[k] = '\0';
    return line;
}

void print_board(board_t *board){
    for (int i = 0; i < board->lines; i++)
    {
        printf("%s", board->matrix[i]);
        if (i+1 < board->lines)
            printf("\n"); 
    }
}

void read_board(board_t *board){
    FILE *file = fopen(board->name, "r");
    for (board->lines = 0; board->isEOF != 1; board->lines++)
    {
        board->matrix = realloc(board->matrix, (board->lines+1) * sizeof(char *));
        board->matrix[board->lines] = NULL;
        board->matrix[board->lines] = read_line_file(file, board);
    }
    fclose(file);
}

void load_tips(board_t *board){
    int maxIndex = board->lines*strlen(board->matrix[0]) ;
    for (int index=0; index < maxIndex; index++)
    {
        int row = index / strlen(board->matrix[0]);
        int col = index % strlen(board->matrix[0]);
        if (board->matrix[row][col] == '*')
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
            neighborX < 0 || neighborX > (strlen(board->matrix[0])-1)
        )
        {
            continue;
        }
        if (board->matrix[neighborY][neighborX] == BLANK_SPACE)
            board->matrix[neighborY][neighborX] = '1';
        else if (board->matrix[neighborY][neighborX] == BOMB)
            continue;
        else
        {
            int neighbor = board->matrix[neighborY][neighborX] - '0';
            neighbor++;
            board->matrix[neighborY][neighborX] = neighbor + '0';
        } 
    }

}

void player_move(board_t *board){
    scanf("%d %d", &board->posY, &board->posX);
    getchar();

    load_tips(board);

    char position = board->matrix[board->posY][board->posX];
    if (position == BOMB)
        return;
    else if (position == BLANK_SPACE)
    {
        prepare_board(board, board->posY, board->posX, 1);
        fill_board(board, board->posY, board->posX);
    }
    else
        prepare_board(board, board->posY, board->posX, 0);
}

void prepare_board(board_t *board, int posY, int posX, int tipsRevealed){
    for (int row = 0; row < board->lines; row++)
    {
        for (int col = 0; col < strlen(board->matrix[0]); col++)
        {
            if(tipsRevealed == 1)
            {
                if (board->matrix[row][col] == BLANK_SPACE || board->matrix[row][col] == BOMB)
                    board->matrix[row][col] = UNREVEALED;
            }
            else
            {
                if (row == posY && col == posX)
                    continue;
                else
                    board->matrix[row][col] = UNREVEALED;
            }
        }
    }
}

void fill_board(board_t *board, int posY, int posX){
    if (board->matrix[posY][posX] == UNREVEALED)
        board->matrix[posY][posX] = BLANK_SPACE;   
    if (posY+1 < board->lines && board->matrix[posY+1][posX] == UNREVEALED)
        fill_board(board, posY+1, posX);
    if (posY-1 >= 0 && board->matrix[posY-1][posX] == UNREVEALED)
        fill_board(board, posY-1, posX);
    if (posX+1 < strlen(board->matrix[0]) && board->matrix[posY][posX+1] == UNREVEALED)
        fill_board(board, posY, posX+1);
    if (posX-1 >= 0 && board->matrix[posY][posX-1] == UNREVEALED)
        fill_board(board, posY, posX-1);
}