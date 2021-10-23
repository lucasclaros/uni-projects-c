/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Course: SCC0201
 *   Create Time: 12/10/2021 10:16
 *   Modified time: 18/10/2021 18:06
 */

#include <complex.h>

typedef struct sample sample_t;
typedef struct audio audio_t;
typedef unsigned char uchar;


char *read_line();
void read_audio(audio_t *audio);

uchar *IDFT(audio_t *audio);
void    DFT(audio_t *audio);

void sortByMagnitude      (audio_t *audio);

/**
 *  Two modified versons of mergesort for sorting
 * the samples in audio_t. 
 * 
 * @param samples: a sample_t vector contaning audio's chars
 * @param start  : initial position to sort 
 * @param end    : final position to sort
 */
void mergesortMagnitude   (sample_t *samples, int start, int end);
void mergesortIndex       (sample_t *samples, int start, int end);


/**
 *  Creates a struct to store informatons about .wav file.
 * 
 * @param filename: char * containg the .wav filename
 * @param nCoef   : coefficients to consider in operations
 * @return        : audio_t pointer
 */
audio_t *createAudio      (char *filename, int nCoef);

/**
 *  These functions were made to manage the data
 * that was read/modified by others funtions.
 * 
 * @param audio: audio_t pointer containing all
 *               information such as filename,
 *               file datasize, etc.
 */
void createNewAudio       (audio_t *audio);
void clearNewAudio        (audio_t *audio);
void destroyAudio         (audio_t *audio);
void printAudio           (audio_t *audio);