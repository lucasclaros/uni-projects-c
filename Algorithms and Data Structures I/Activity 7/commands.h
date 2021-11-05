typedef struct List list_t;

typedef struct User
{
    char *name;
    int id;
} users_t;

char *read_line();
void checkAction(char *action, list_t *l);