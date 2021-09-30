typedef struct List list_t;

/**
 *  Reads the amount of numbers to print and 
 * its indexes on the list.
 * 
 * @param nIndexes: number of indexes to read
 * @return: NULL  - allocation failed
 *          int * - all good
 */
int *readIndexes(int nIndexes);

/**
 *  Prepares a prime number's list till maxNumber.
 * 
 * @param l: list pointer to insert the numbers
 * @param maxNumber: range of the list
 */
void primesCalculate(list_t *l, int maxNumber);

/**
 *  Sets all numbers from 2 - maxNumber on the list.
 * 
 * @param l: list pointer to insert the numbers
 * @param maxNumber: range of the list
 */
void initiateValues(list_t *l, int maxNumber);

/**
 *  Checks if first paramenter is multiple of the second one.
 * 
 * @param n1: suppose multiple to compare
 * @param n2: number to compare
 * @return: 1 - n1 is multiple of n2
 *          0 - n1 is not multiple of n2
 */
int isMultiple(int n1, int n2);