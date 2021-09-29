/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 27/09/2021 04:53
 *   Modified time: 29/09/2021 06:52
 */

typedef enum bool { FALSE, TRUE } bool;
typedef struct Input input_t;
typedef struct Word word_t;
typedef struct Frequent_words freq_words_t;


/**
 * Dynamically allocates a line read from stdin
 *
 * @return: char * address allocated
 */
char *read_line();

/**
 *  Initializes a struct Input, all setted to read stdin
 * 
 * @return: NULL - allocation failed
 *          input_t * - all good
 */
input_t *inputCreate();

/**
 *  Deallocates all content in input_t
 * 
 * @return: 1 - all good
 *         -1 - NULL pointer
 */
int inputDestroy(input_t *t);

/**
 *  Reads a text and the maxWords to print out. It checks 
 *  if the EOF was reached as well.
 * 
 * @return: TRUE  - EOF found
 *          FALSE - no EOF found
 */
bool inputRead(input_t *t);

/**
 *  Creates a word_t vector with the text's words
 * and it counts frequency of each word in the text.
 * 
 * @param t: input_t* containing the text read from stdin
 * @return: NULL - allocation failed
 *          freq_words_t * - all good and sorted
 */
freq_words_t *wordCounter(input_t *t);

/**
 *  Creates a new struct word_t and add to 
 * vec_words vector in freq_words_t * parameter.
 * 
 * @param f: freq_words_t* containing the vec_words vector
 * @param src: word to be added
 * @return: -1 - allocation failed / NULL pointer
 *           1 - all good and added up
 */
int addWordtoVector(freq_words_t *f, char *src);

/**
 *  Checks if a word was already added to vec_words.
 * 
 * @param f: freq_words_t* containing the vec_words vector
 * @param word: word to be checked
 * @return:  NULL - word not found
 *           word_t ** - word found
 */
word_t **wasAddedtoVector(freq_words_t *f, char *word);

/**
 *  Initializes a struct Frequent_words, all setted.
 * 
 * @return: NULL - allocation failed
 *          freq_words_t * - all good
 */
freq_words_t *freqWordsCreate();

/**
 *  Deallocates all content in freq_words_t *.
 * 
 * @return: 1 - all good
 *         -1 - NULL pointer
 */
int freqWordsDestroy(freq_words_t *f);

/**
 *  Prints the n words most repetead in text read from stdin,
 * where n is the maxWords provided at inputRead() function. If
 * word's quantity is smaller than maxWords, it prints all.
 * 
 * @param t: input_t* containing the maxWords
 * @param f: freq_words_t* containing vec_words
 */
void freqWordsPrint(input_t *t, freq_words_t *f);

/**
 *  Algorithm to sort a integer vector.
 * 
 * @param vec_words:  vector containing word's frequency number
 * @param nElements:  word's quantity allocated in vec_words
 */
void insertionSort(word_t **vec_words, int nElements);

/**
 *  Algorithm to sort a vector alphabetically.
 * 
 * @param vec_words:  vector containing the words
 * @param nElements:  word's quantity allocated in vec_words
 */
void insertionSortAlphabetical(word_t **vec_words, int nElements);
