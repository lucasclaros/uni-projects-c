/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 11/09/2021 06:40
 *   Modified time: 16/09/2021 19:45
 *   Description: Minesweeper Simulator
 */

#include <stdio.h>
#include "minesweeper.h"

int main(){
    board_t *board = NULL;
    board = initialize_board();

    int option;
    scanf("%d", &option);
    getchar();

    board->name = read_line();
    read_board(board);

    switch (option)
    {
        case 1: print_board (board, HINTS_BOARD); break;
        case 2: load_hints  (board); 
                print_board (board, HINTS_BOARD); break;
        case 3: player_move (board);              break;
        default: break;
    }
    destroy_all(board);    
    return 0;
}
