#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
/**
 * @brief MA - MB = MC
 *
 * @param MA matrix A
 * @param MB matrix B
 * @param MC result of A - B
 */
void sub_mtrx(int **MA, int **MB, int **MC)
{
    int i, j;
    for (i = 0; i < N_PROC; i++)
    {
        for (j = 0; j < N_RES; j++)
        {
            MC[i][j] = MA[i][j] - MB[i][j];
        }
    }
}
/**
 * @brief Used to caclulate work to be done given total resource vector
 * in bankers.c
 *
 * @param W total work vector
 * @param alloc matrix
 */
void find_work(int *W, int **alloc)
{
    for (int i = 0; i < N_PROC; i++)
    {
        for (int j = 0; j < N_RES; j++)
        {
            W[j] -= alloc[i][j];
        }
    }
}
/**
 * @brief Sum the items at each index of a vector
 *
 * @param vec vector
 * @return int sum of vector
 */
int sum_vector(int *vec)
{
    int sum = 0;
    for (int i = 0; i < N_RES; i++)
    {
        sum += vec[i];
    }
    return sum;
}
/**
 * @brief copies vector SRC into DST
 *
 * @param SRC vector to copy
 * @param DST location to copy vector
 * @return int* copied vector
 */
int *copy_vector(int *SRC, int *DST)
{
    for (int i = 0; i < N_RES; i++)
    {
        DST[i] = SRC[i];
    }

    return DST;
}
/**
 * @brief Used to allocate/read in a matrix. If char mode is 'W', it will also scan in ints from file fp,
 *  Otherwise, it will just return allocated blank matrix
 *
 * @param fp fille to be read
 * @param mode to indicate if matrix should be written to
 * @return int** allocated matrix
 */
int **read_mtrx(FILE *fp, char mode)
{
    int i, j;
    int **matrix = (int **)malloc(N_PROC * sizeof(int *));
    for (i = 0; i < N_PROC; i++)
    {
        matrix[i] = (int *)malloc(N_RES * sizeof(int));
    }
    if (mode == 'w')
    {
        for (i = 0; i < N_PROC; i++)
        {
            for (j = 0; j < N_RES; j++)
            {

                fscanf(fp, "%d", &matrix[i][j]);
            }
        }
    }

    return matrix;
}

/**
 * @brief Used during testing to format and print matrices
 *
 * @param mtrx matrix to print
 */
void print_mtrx(int **mtrx)
{
    int i, j;
    for (i = 0; i < N_PROC; i++)
    {
        for (j = 0; j < N_RES; j++)
        {
            printf("%d\t", mtrx[i][j]);
        }
        printf("\n");
    }
}