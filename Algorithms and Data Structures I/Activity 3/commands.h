typedef enum bool { FALSE, TRUE } bool;
typedef struct Queue queue_t;

/**
 * Dynamically allocates a line read from stdin
 *
 * @return: vector address allocated
 */
char *read_line(bool *); 
