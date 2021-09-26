#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

/** 
 *  Get char by char from stdin reallocating properly
 * until a \n is read(it ignores \r). At the end, a \0 is setted to
 * close the string. If EOF is reached, it changes the variable isEOF
 */
char *read_line(bool *isEOF){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    if (c == EOF) *isEOF = TRUE;
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}

message_t *messageCreate(){
    message_t *m = malloc(sizeof(message_t));
    if (m == NULL)
        return NULL;

    m->phrase = NULL;
    m->target = NULL;
    m->sub = NULL;
    return m;
}

int messageDestroy(message_t *m){
    if(m == NULL)
        return -1;

    free(m->phrase);
    free(m->target);
    free(m->sub);
    free(m);
    return 1;
}

bool readMessages(message_t *m){
    bool isEOF = FALSE;
    m->phrase = read_line(&isEOF);
    m->target = read_line(&isEOF);
    m->sub    = read_line(&isEOF);
    return isEOF;
}

/**
 *  This function creates a copy of dest string, called finalMessage wich 
 * will be analized with strstr() function. The result is stored in the substr_p
 * variable. If it's NULL, the src string was not found and returns the original
 * phrase. Otherwise, it checks the difference between sub and src. If subs is larger
 * than src, allocates enough space to move string.
 * 
 *  Memmove/memcpy functions are the mainly logic behind the scenes, the memmove() shifts
 * all content read by substr_p (right shift (sub > src) or left shift (sub < src)). The
 * substr_p content that will be shifted must be your lenght (strlen(substr_p)) excepts
 * the src string wich will be replaced in memcpy() function. 
 * 
 *          memmove(
 *              (substr_p + strlen(sub)), -> address where the content will be placed             
 *              (substr_p + strlen(src)), -> content to be placed
 *              (strlen(substr_p) - strlen(src) + 1 ) -> bytes to move (+1 for \0)
 *          );
 * 
 *  After the shifting process, memcpy() copies the sub string to substr_p. If the sub
 * string is smaller than src, the functions reallocs deleting the leftover bytes.
 * 
 * Finally, the strstr() is called again to check if there's src remaining.
 */ 
char *strsub(char *dest, char *src, char *sub){
    int strSize = strlen(dest);
    char *finalMessage = malloc(strSize+1 * sizeof(char));
    strcpy(finalMessage, dest);
    char *substr_p = NULL;
    int deltaSize = strlen(sub)-strlen(src);
    if ((substr_p = strstr(finalMessage, src)) != NULL)
    {
        while (substr_p != NULL)
        {
            if (deltaSize > 0)
                finalMessage = realloc(finalMessage, (strSize + deltaSize + 1) * sizeof(char));
            memmove(
                (substr_p + strlen(sub)),            
                (substr_p + strlen(src)),
                (strlen(substr_p) - strlen(src) + 1)
            );
            memcpy(substr_p, sub, strlen(sub));

            if (deltaSize < 0)
            {
                finalMessage = realloc(finalMessage, (strSize + deltaSize + 1) * sizeof(char));
                finalMessage[strSize+deltaSize] = '\0';
            }
                substr_p = strstr(substr_p, src);
        }
    }
    return finalMessage;
}