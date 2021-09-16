/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 15/09/2021 22:35
 *   Modified time: 16/09/2021 19:42
 *   Description: Minesweeper Header
 * 
 *   Gostaria muito de um feedback sincero se possível sobre o programa
 *  e os comentários/explicações(tanto no header quanto nos .c), não tenho 
 *  muito contato com pessoas da minha sala então não sei se o que programo 
 *  está muito fora do padrão. Estou tentando melhorar meu inglês então peço 
 *  desculpas se tiver algum erro gramatical. :)
 * 
 */

#define BLANK_SPACE '.'
#define BOMB        '*'
#define UNREVEALED  'X'
#define BORDERS      8
#define HINTS_BOARD  0
#define USER_BOARD   1

typedef struct board
{
    char *name, ***matrix;
    int isEOF, lines, width, posY, posX, boards;
    int *offsetsX, *offsetsY;
} board_t;

/*
 * Prepares and sets all the board variables
 */
board_t *initialize_board();

/* 
 * Dynamically allocates a line read from stdin
 *
 * @return: vector address allocated
 */
char *read_line();

/*
 * Dynamically allocates a line read from a file
 *
 * @param file: pointer to the pre opened file
 * @param isEOF: int to check the end of file
 * @return: vector address allocated
 */
char *read_line_file (FILE *file, int *isEOF);

/*
 * Deallocates all memory allocated for the board
 *
 * @param board: pointer to the board address
 */
void destroy_all     (board_t *board);

/*
 * Reads a board from stdin using read_line_file
 *
 * @param board: pointer to the board address
 */
void read_board      (board_t *board);

/*
 * Prints the board selected by board_option
 *
 * @param board: pointer to the board address
 * @param board_option: selects what board to print
 *                      (HINTS_BOARD,  USER_BOARD)
 */
void print_board     (board_t *board, int board_option);

/*
 * Checks all neighbors of the given position
 * 
 * @param board: pointer to the board address
 * @param posY: row of the position
 * @param posX: column of the position
 */
void check_neighbors (board_t *board, int posY, int posX);

/*
 * Loads all the possible hints of the read board
 *
 * @param board: pointer to the board address
 */
void load_hints      (board_t *board);

/*
 * Sets a second board wich it will be displayed later
 *
 *@param board: pointer to the board address
 */
void prepare_board   (board_t *board);

/*
 * Reads the position that is given by a player input
 * and proceeds depending os the result. If the position is:
 * 
 * BOMB - prints the entire board with hints and bombs
 * HINT - prints just the hint with the entire board covered
 * NONE - unconver all the none spaces/hints around the position
 * 
 * @param board: pointer to the board address
 */
void player_move     (board_t *board);

/*
 * Recursive function used to uncover all none spaces and hints
 *
 * @param board: pointer to the board address
 * @param posY: row of the position
 * @param posX: column of the position
 */
void fill_board      (board_t *board, int posY, int posX);