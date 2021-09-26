/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 21/09/2021 04:53
 *   Modified time: 26/09/2021 18:35
 */

typedef enum bool { FALSE, TRUE } bool;
typedef struct Queue queue_t;

typedef struct Message
{
    char *phrase, *target, *sub;
} message_t;


/**
 * Dynamically allocates a line read from stdin
 *
 * @return: char * address allocated
 */
char *read_line(bool *);

/**
 *  Creates a struct Message, all setted
 * 
 * @return: NULL - no memory available
 *          message_t * address allocated - all good
 */
message_t *messageCreate();
 
/**
 *  Deallocates all the content of struct Message allocated
 * 
 * @param message: struct Message pointer
 * @return: 1 - all good and deallocated 
 *         -1 - message pointer is NULL
 */
int messageDestroy(message_t *message);

/**
 *  Reads stdin input wich must contain the initial phrase,
 * substring to replace and a string that will be placed.
 * 
 * @param message: struct Message pointer
 * @return: TRUE  - reached the EOF
 *          FALSE - not EOF found
 **/
bool readMessages(message_t *message);


/**
 *  Replace a substring with another string from a given phrase.
 * 
 * @param dest: string to be checked
 * @param src : substring to replace
 * @param sub : string to be replaced
 * @return: char * with all src replaced with sub
 */
char *strsub(char *dest, char *src, char *sub);