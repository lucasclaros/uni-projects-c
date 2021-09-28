/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 21/09/2021 04:53
 *   Modified time: 27/09/2021 23:27
 */

typedef enum bool { FALSE, TRUE } bool;
typedef struct Queue queue_t;
typedef struct Input input_t;
typedef struct Word word_t;
typedef struct Freq_words freq_words_t;


/**
 * Dynamically allocates a line read from stdin
 *
 * @return: char * address allocated
 */
char *read_line();

input_t *inputCreate();
int inputDestroy(input_t *t);
bool inputRead(input_t *t);
int inputPrint(input_t *t);

freq_words_t *wordCount(input_t *t);
freq_words_t *freqWordCreate();
int freqWordDestroy(freq_words_t *f);
void freqWordPrint(input_t *t, freq_words_t *f);

void insertionSort(freq_words_t *, int n);
void insertionSort2(freq_words_t *, int n);

word_t **wordCheck(freq_words_t *f, char *word);