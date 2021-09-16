/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 15/09/2021 22:35
 *   Modified time: 16/09/2021 19:35
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "minesweeper.h"

/** 
 *  Get char by char from stdin reallocating properly
 * until a \n is read. At the end, a \0 is setted to
 * close the string.
 */
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

/** 
 *  It works same way of read_line but the characters is read
 * from a file pre opened before the function call (param file).
 * A variable isEOF is used to check the EOF char of the file
 * so the file reading might be stopped.
 */
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

/**
 *  The function runs through the all board lines, printing 
 * them. The parameter board_option selects wich board will be 
 * printed, USER_BOARD and HINTS_BOARD must be used for this.
 */ 
void print_board(board_t *board, int board_option){
    for (int i = 0; i < board->lines; i++)
    {
        printf("%s", board->matrix[board_option][i]);
        if (i+1 < board->lines)
            printf("\n"); 
    }
}

/**
 *  It opens the board's file and reads line by line using
 * read_line_file.
 */
void read_board(board_t *board){
    FILE *file = fopen(board->name, "r");
    for (board->lines = 0; board->isEOF != 1; board->lines++)
    {
        board->matrix[HINTS_BOARD] = (char **) realloc(board->matrix[HINTS_BOARD], (board->lines+1) * sizeof(char *));
        board->matrix[HINTS_BOARD][board->lines] = NULL;
        board->matrix[HINTS_BOARD][board->lines] = read_line_file(file, &board->isEOF);
    }
    board->width = strlen(board->matrix[HINTS_BOARD][0]);
    fclose(file);
}

/**
 *  Calculates how many elements the board(matrix) has and
 * check one by one in the HINTS_BOARD calling the check_neighbors
 * if th element is a bomb.
 * 
 *  The logic was made to run with just one for loop. The index
 * variable starts at 0 increasing till maxIndex-1, every time the
 * index reaches the width value and its multiples, the row increments 
 * (because it's given by the floor division of index / width) and
 * the column resets since the result value comes from a modular expression.
 */
void load_hints(board_t *board){
    int maxIndex = board->lines * board->width;
    for (int index=0; index < maxIndex; index++)
    {
        int row = index / board->width;
        int col = index % board->width;
            if (board->matrix[HINTS_BOARD][row][col] == BOMB)
                check_neighbors(board, row, col);  
    }
}

/**
 *  This function checks all the adjacents neighbors of
 * a given position in the funciton call. The for loop
 * iterates through the offsets vectors:
 * 
 * offsetY[] = {-1,-1,-1,0,0, 1,1,1}
 * offsetX[] = {-1, 0, 1,0,0,-1,0,1}
 * 
 *  Running through all neighbors by adding each corresponding index
 * to the parameters position. If sum value is out of matrix bounds
 * the algorithm skips that neighbor, otherwise it checks the element:
 * 
 * BLANK_SPACE: a 1 is set
 * Any number: convert char to int (- '0'), increments, convert int to char (+ '0')
 */
void check_neighbors(board_t *board, int posY, int posX){

    for (int i = 0; i < BORDERS; i++)
    {
        int neighborY = posY + board->offsetsY[i];
        int neighborX = posX + board->offsetsX[i];
        if
        (    
            neighborY < 0 || neighborY > (board->lines-1) ||
            neighborX < 0 || neighborX > (board->width-1)
        )
        {
            continue;
        }
        char position = board->matrix[HINTS_BOARD][neighborY][neighborX];
        if (position == BLANK_SPACE)
            board->matrix[HINTS_BOARD][neighborY][neighborX] = '1';
        else if (position == BOMB)
            continue;
        else
        {
            int neighbor = board->matrix[HINTS_BOARD][neighborY][neighborX] - '0';
            neighbor++;
            board->matrix[HINTS_BOARD][neighborY][neighborX] = neighbor + '0';
        } 
    }
}

/**
 *  Reads the player input and call load_hints. If the player selects:
 * 
 *  BOMB: game is over and prints the entire board revealed
 *  BLANK_SPACE: reveals the area around the blank space including hints
 *  HINT: prints just the hint selected
 */
void player_move(board_t *board){
    scanf("%d %d", &board->posY, &board->posX);
    getchar();

    load_hints(board);

    char position = board->matrix[HINTS_BOARD][board->posY][board->posX];
    if (position == BOMB)
        print_board (board, HINTS_BOARD);
    else if (position == BLANK_SPACE)
    {
        prepare_board(board);
        fill_board(board, board->posY, board->posX);
        print_board (board, USER_BOARD);
    }
    else
    {
        prepare_board(board);
        board->matrix[USER_BOARD][board->posY][board->posX] = board->matrix[HINTS_BOARD][board->posY][board->posX];
        print_board (board, USER_BOARD);
    }
}

/**
 *  Reallocates one more board, the board that will be displayed
 * after player_move. This board is initalized with all elements
 * UNREVEALED, and might be modified by fill_board
 */
void prepare_board(board_t *board){
    board->matrix = realloc(board->matrix, (board->boards+1)*sizeof(char**));
    board->boards++;
    board->matrix[USER_BOARD] = malloc(board->lines * sizeof(char *));

    for (int j,i = 0; i < board->lines; i++)
    {
        board->matrix[USER_BOARD][i] = malloc((board->width+1) * sizeof(char));
        for (j = 0; j < board->width; j++)
            board->matrix[USER_BOARD][i][j] = UNREVEALED;
        board->matrix[USER_BOARD][i][j] = '\0';
    }
}

/**
 *  Recursive function to reveal the hints/blank_spaces around a blank_space selected
 * 
 *  Copies the position from HINTS_BOARD to USER_BOARD, if the value copied is not a
 * BLANK_SPACE(it's a number!) the function returns. If it is, applies the same logic
 * from check_neighbors.
 */
void fill_board(board_t *board, int posY, int posX){
    board->matrix[USER_BOARD][posY][posX] = board->matrix[HINTS_BOARD][posY][posX];   

    if(board->matrix[HINTS_BOARD][posY][posX] != BLANK_SPACE)
        return;

    for (int i = 0; i < BORDERS; i++)
    {
        int neighborY = posY + board->offsetsY[i];
        int neighborX = posX + board->offsetsX[i];
        if
        (    
            neighborY < 0 || neighborY > (board->lines-1) ||
            neighborX < 0 || neighborX > (board->width-1) ||
            board->matrix[USER_BOARD][neighborY][neighborX] != UNREVEALED // doesnt check visited neighbors
        ) continue;
        fill_board(board, neighborY, neighborX);
    }
}

/**
 * Sets up all variables needed in funtions
 */
board_t *initialize_board(){
    board_t *board = (board_t *) malloc(1 * sizeof(board_t));
    assert(board != NULL);
    board->offsetsX = (int *) malloc(BORDERS * sizeof(int));
    assert(board->offsetsX != NULL);
    board->offsetsY = (int *) malloc(BORDERS * sizeof(int));
    assert(board->offsetsY != NULL);
    board->matrix   = (char ***) malloc(sizeof(char **));
    assert(board->matrix != NULL);
    board->boards = 1;
    board->isEOF = 0;
    board->matrix[0] = NULL;
    board->name = NULL;

    int offsety[] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int offsetx[] = {-1, 0, 1,-1, 1,-1, 0, 1};
    for (int i = 0; i < BORDERS; i++)
    {
        board->offsetsY[i] = offsety[i];
        board->offsetsX[i] = offsetx[i];
    }
    return board;
}

/**
 * Deallocates all heap allocations in board struct
 */
void destroy_all(board_t *board){
    for (int i = 0; i < board->boards; i++)
    {
        for (int j = 0; j < board->lines; j++)
            free(board->matrix[i][j]);
        free(board->matrix[i]);
    }
    free(board->offsetsX);
    free(board->offsetsY);
    free(board->matrix);
    free(board->name);
    free(board);
}