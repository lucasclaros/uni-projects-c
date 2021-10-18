#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

unsigned char* read_wav_data(char* fname);
char *read_line();

int main(){
    char *filename = read_line();
    int nCoef;
    scanf("%d", &nCoef);
    getchar();
    unsigned char *teste = read_wav_data(filename);
    
    //audio_t *audio = createAudio(filename, nCoef);
    //read_audio(audio);
    //printAudio(audio);
    //destroyAudio(audio);
    return 0;
}


unsigned char* read_wav_data(char* fname) {
    FILE* fp = fopen(fname, "rb");
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    int dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    unsigned char* data = malloc(sizeof(*data) * (dataSize));
    
    int i = 0;
    while (i < dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    return data;
}
char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}