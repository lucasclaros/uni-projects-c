typedef struct Polys poly_t;


/**
 * Dynamically allocates a line read from stdin
 *
 * @return: char * address allocated
 */
char *read_line();

/**
 *  Initializes a polynomial struct, all variables setted
 *  @return: poly_t* - all good
 */
poly_t *polynomialCreate(int numPol);

/**
 *  Reads a polynomial from stdin with
 * a format like: (a, b, c, d).
 * @param
 */
void polynomialRead(poly_t *p, int index);

/**
 *  Deallocates a poly_t structure 
 * 
 * @param p: poly_t to be destroyed 
 */
void polynomialDestroy(poly_t *p);

/**
 * 
 *  Sums all polynomyals of poly_t and put it
 * all in finalPoly 
 * 
 * @param p: poly_t to sum
 */
void polynomialSum(poly_t *p);


/**
 *  Prints the finalPoly 
 * 
 * @param p: poly_t* containing the final polynomial to be printed
 */
void printFinalPoly(poly_t *p);