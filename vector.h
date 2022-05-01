
/*** Globals ***/
extern int N_RES;
extern int N_PROC;
/*** Function Prototypes ***/
int **read_mtrx(FILE *fp, char mode);
void sub_mtrx(int **MA, int **MB, int **MC);
void print_mtrx(int **mtrx);

void find_available(int *W, int **alloc);
int sum_vector(int *vec);

int *copy_vector(int *SRC, int *DST);
