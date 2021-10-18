/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Course: SCC0201
 *   Create Time: 12/10/2021 10:16
 *   Modified time: 13/10/2021 02:54
 */

#include <complex.h>

typedef struct sample sample_t;
typedef struct audio audio_t;
typedef unsigned char uchar;


char *read_line();
void read_audio(audio_t *audio);

double complex getMagnitude(double complex number);
uchar *IDFT(audio_t *audio);
void    DFT(audio_t *audio);

audio_t *createAudio      (char *filename, int nCoef);
void sortByMagnitude      (audio_t *audio);
void mergesortMagnitude   (sample_t *samples, int start, int end);
void mergesortIndex       (sample_t *samples, int start, int end);
void createNewAudio       (audio_t *audio);
void clearNewAudio        (audio_t *audio);
void destroyAudio         (audio_t *audio);
void printAudio           (audio_t *audio);