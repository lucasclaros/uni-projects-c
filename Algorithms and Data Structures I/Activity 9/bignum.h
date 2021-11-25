
typedef struct BigNum bignum_t;
typedef enum bool { FALSE, TRUE } bool;

char *readLine(bool *isEOF);
bignum_t *bignumRead();
void bignumDestroy(bignum_t *num);
void bignumSum(bignum_t *num1, bignum_t *num2);
int bignumBigger(bignum_t *num1, bignum_t *num2);
int bignumSmaller(bignum_t *num1, bignum_t *num2);
int bignumEqual(bignum_t *num1, bignum_t *num2);