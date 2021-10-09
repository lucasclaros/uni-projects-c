/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 03/10/2021 16:59
 *   Modified time: 09/10/2021 19:08
 */

#define SIZE_OPENERS 3

typedef enum bool { FALSE, TRUE } bool;
typedef struct stack stack_t;
/**
 *  Checks if a char it's a opening bracket ( "({[" )
 * 
 * @param c: char to check
 * @return : TRUE  - c  = opening bracket
 *           FALSE - c != opening bracket 
 */
bool isaOpeningBracket(char c);

/**
 *  Compares if c is equal to the character corresponding
 * to openingBracket at closingBrackets index.
 * 
 * @param c: char to check
 * @return : TRUE  - c  = opening bracket
 *           FALSE - c != opening bracket 
 */
bool checkLastCharAdded(char c, int index);

/**
 *  Checks if a char it's a closing bracket ( ")}]" )
 * 
 * @param c: char to check
 * @return : -1 - c not found
 *           closingBrackets index - c found
 */
int getClosingBracketIndex(char c);

/**
 *  Prints the result of given stack 
 * 
 * @param s: stack containing a sequence
 * @return : "BALANCEADO"     - all brackets opened were closed (stack empty)
 *           "NÃO BALANCEADO" - opened brackets weren't closed (stack not empty) 
 */
void checkSequence(stack_t *s);

/**
 * Dynamically allocates a line read from stdin
 *
 * @return: char * address allocated
 */
char *read_line(bool *isEOF);