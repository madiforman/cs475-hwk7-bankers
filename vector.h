
/*** Globals ***/
extern int N_RES;
extern int N_PROC;
/*** Function Prototypes of Vector and Matrix Operations ***/
void sub_mtrx(int **MA, int **MB, int **MC);
void find_available(int *W, int **alloc);
int sum_vector(int *vec);
int **read_mtrx(FILE *fp, char mode);
int *copy_vector(int *SRC, int *DST);
void print_mtrx(int **mtrx);