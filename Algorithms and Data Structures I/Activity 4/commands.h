#define QUEUES 4
#define PRIO_AGE 60
#define KEYWORD "SAI"
#define EMPTY_MESSAGE "FILA VAZIA"

typedef enum priorities { ELDERLY_1, NORMAL_1, ELDERLY_0, NORMAL_0 } prio;
typedef enum bool { FALSE, TRUE } bool;
typedef struct Queue queue_t;

typedef struct Commands
{
    int nLines;
    char **linesInput;
    queue_t *main_queue[QUEUES];
} commands_t;

typedef struct Person
{
    char *name;
    int prio, age;
} person_t;

/**
 *  Initializes a person, all variables setted
 */
person_t *personCreate();

/**
 *  Deallocates queue pointer 
 * 
 * @param person: struct Person pointer 
 */
void personDestroy(person_t *person);

/** 
 * Dynamically allocates a line read from stdin
 *
 * @return: vector address allocated
 */
char *read_line(); 

/**
 * Checks the input lines read previously
 * 
 * @param commands: struct Commands pointer
 */
void commandsDecider (commands_t *commands);

/**
 *  Remove the next person in the queues by the following
 * priority order: ELDERLY_1, NORMAL_1, ELDERLY_0, NORMAL_0
 * 
 * @param commands: struct Commands pointer
 * @return: 1 - all good 
 *         -1 - prints a message indicating empty queue
 */
int  queueNext       (commands_t *commands);

/**
 *  Insert a person in your corresponding queue
 * 
 * @param commands: struct Commands pointer
 * @param index: index of the reading line
 * @return: 1 - all good
 *         -1 - no memory for person's register
 */
int  queueAppend     (commands_t *commands, int index);