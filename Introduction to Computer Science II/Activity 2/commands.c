/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Course: SCC0201
 *   Create Time: 12/10/2021 10:16
 *   Modified time: 18/10/2021 17:27
 */

#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include <errno.h>

struct sample{
    uchar c;
    double complex tc;
    double complex magnitude;
    int prevIndex;
};

struct audio
{
    char *filename;
    int dataSize, nCoef, zeroCoef;
    sample_t *samples;
};

char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n')
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}

void read_audio(audio_t *audio) {
    FILE* fp = fopen(audio->filename, "rb");
    uchar buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    audio->dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    audio->samples = (sample_t *) malloc(sizeof(sample_t) * (audio->dataSize));
    
    int j = 0;
    while (j < audio->dataSize) {
        audio->samples[j].prevIndex = j;
        audio->samples[j].tc = 0;
        fread(&audio->samples[j++].c, sizeof(uchar), 1, fp);
    }
    fclose(fp);
}

void DFT(audio_t *audio) {
    for (int k = 0; k < audio->dataSize; k++) {
        for (int n = 0; n < audio->dataSize; n++) {
            audio->samples[k].tc += audio->samples[n].c * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (audio->dataSize * 1.0))) * _Complex_I);
        }
		if (creal(audio->samples[k].tc) <= 0.0 && cimag(audio->samples[k].tc) <= 0.0) audio->zeroCoef++;
        audio->samples[k].magnitude = getMagnitude(audio->samples[k].tc);
    }
}

uchar *IDFT(audio_t *audio) {
    uchar *coef = (uchar *) calloc(audio->dataSize, sizeof(uchar));

    for (int k = 0; k < audio->dataSize; k++) {
        double complex aux;
        for (int n = 0; n < audio->dataSize; n++) {
            aux += creal(audio->samples[n].tc) * cexp((2.0 * M_PI * (((k+1) * n * 1.0) / (audio->dataSize * 1.0))) * _Complex_I);
        }
        coef[k] = (int)creal(aux) / (int)(audio->dataSize * 1.0);
    }
    return coef;
}

double complex getMagnitude(double complex number){
    double a = pow(creal(number), 2.0);
    double b = pow(cimag(number), 2.0);
    return sqrt(a + b);
}

audio_t *createAudio(char *filename, int nCoef){
    audio_t *a = malloc(sizeof(audio_t));
	a->zeroCoef = 0;
    a->filename = filename;
    a->nCoef = nCoef;
    a->samples = NULL;
    return a;
}

void destroyAudio(audio_t *a){
    free(a->filename);
    free(a->samples);
	free(a);
}

void printAudio(audio_t *audio){
    printf("%d\n", audio->dataSize);
    printf("%d\n", audio->zeroCoef);
    for (int i = 0; i < audio->nCoef; i++)
        printf("%d\n", (int)creal(audio->samples[i].magnitude));
}

void sortByMagnitude(audio_t *audio){
    mergesortMagnitude(audio->samples, 0, (audio->dataSize-1)); 
    clearNewAudio(audio); 
}

void mergesortMagnitude(sample_t *samples, int start, int end){
	if (end <= start) return;

	int c = (int) (end+start)/2.0;

	mergesortMagnitude(samples, start, c);
	mergesortMagnitude(samples, c+1, end);

	sample_t* aux = (sample_t*) malloc(sizeof(sample_t) * (end-start+1));

	int i = start;
	int j = c+1;
	int k = 0; 

	while (i <= c && j <= end) 
	{
		if ((double)samples[i].magnitude >= (double)samples[j].magnitude) 
			aux[k] = samples[i++]; 
		else
			aux[k] = samples[j++];
		k++;
	}

	while (i <= c)
		aux[k++] = samples[i++];

	while (j <= end) 
		aux[k++] = samples[j++];

	for (i = start, k = 0; i <= end; i++, k++)
		samples[i] = aux[k];

	free(aux);
}

void mergesortIndex(sample_t *samples, int start, int end){
	if (end <= start) return;

	int c = (int) (end+start)/2.0;

	mergesortIndex(samples, start, c);
	mergesortIndex(samples, c+1, end);

	sample_t* aux = (sample_t*) malloc(sizeof(sample_t) * (end-start+1));

	int i = start;
	int j = c+1;
	int k = 0; 

	while (i <= c && j <= end) 
	{
		if ((double)samples[i].prevIndex <= (double)samples[j].prevIndex) 
			aux[k] = samples[i++]; 
		else
			aux[k] = samples[j++];
		k++;
	}

	while (i <= c)
		aux[k++] = samples[i++];

	while (j <= end) 
		aux[k++] = samples[j++];

	for (i = start, k = 0; i <= end; i++, k++)
		samples[i] = aux[k];

	free(aux);
}

void createNewAudio(audio_t *audio){
    mergesortIndex(audio->samples, 0, (audio->dataSize-1));
    uchar *newTransAudio = IDFT(audio);
    FILE *originalAudio = fopen(audio->filename, "rb");
    FILE *newAudio = fopen("new_audio.wav", "wb");
    uchar buf44[44];

    fread(buf44, sizeof(uchar), 44, originalAudio);
    fwrite(buf44, 1, sizeof(buf44), newAudio);
    for (int i = 0; i < audio->dataSize; i++)
        fwrite(&audio->samples[i].c, sizeof(uchar), 1, newAudio);
    
    fclose(originalAudio);
    fclose(newAudio);
    free(newTransAudio);
}

void clearNewAudio(audio_t *audio){
    for (int i = audio->nCoef; i < audio->dataSize; i++)
        audio->samples[i].tc = 0.0;
}