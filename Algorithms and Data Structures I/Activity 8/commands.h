typedef struct Polys poly_t;


char *read_line();
poly_t *polynomialCreate(int);
void polynomialRead(poly_t *, int);
void polynomialDestroy(poly_t *);
void polynomialSum(poly_t *);
void printFinalPoly(poly_t *);