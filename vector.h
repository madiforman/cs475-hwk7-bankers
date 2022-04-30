
extern int N_RES;
extern int N_PROC;
/*function prototypes of vector and matrix operations*/
void sub_mtrx(int **MA, int **MB, int **MC);
void find_work(int *W, int **alloc);
int sum_vector(int *vec);
int **read_mtrx(FILE *fp, char mode);
int *copy_vector(int *SRC, int *DST);
void print_mtrx(int **mtrx);