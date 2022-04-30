#include <stdio.h>
#include <stdlib.h>
#include "banker.h"
#include "vector.h"
/*boolean T/F value declarations (not necessary)*/
#define TRUE 1
#define FALSE 0
/**
 * @brief Safety algorithm portion of Banker's algorithm
 *
 * @param total_r total resource vector
 * @param alloc allocated resource matrix
 * @param need  needed resource matrix
 * @return int 1 if sequence is safe 0 if not
 */
int is_safe(int *total_r, int **alloc, int **need)
{
    /*finished array, safe sequence array, and work vector*/
    int F[N_PROC], safe_seq[N_PROC], W[N_RES], P = 0;
    for (int i = 0; i < N_PROC; i++)
    {
        F[i] = FALSE;
    }
    /*copy total resource vector into work vector*/
    copy_vector(total_r, W);
    /*calculate availability vector*/
    find_available(W, alloc);

    /*** BANKER'S SAFETY ALGORITHM ***/
    for (int k = 0; k < N_PROC; k++)
    {
        for (int i = 0; i < N_PROC; i++)
        {
            /*if process i has not yet been set*/
            if (!F[i])
            {
                int flag = FALSE;
                for (int j = 0; j < N_RES; j++)
                {
                    /*check if process i's needs can be met*/
                    if (need[i][j] > W[j])
                    {
                        flag = TRUE;
                        break;
                    }
                }
                if (!flag)
                {
                    /*if its safe increase ind and add it to safe seq*/
                    safe_seq[P++] = i;
                    for (int j = 0; j < N_RES; j++)
                    {
                        /* "give back" resources */
                        W[j] += alloc[i][j];
                    }
                    /*mark as finished*/
                    F[i] = TRUE;
                }
            }
        }
    }
    /*check to see if all indexes of F are 1*/
    int pflag = FALSE;
    for (int i = 0; i < N_PROC; i++)
    {
        if (!F[i])
        {
            pflag = TRUE;
            /*if an unfinished process found, set F[i] to index it was found out for printing unsafe seq*/
            F[i] = i;
        }
    }
    /*if pflag was never set, no unfinished processes were found*/
    if (!pflag)
    {
        printf("SAFE:\t");
        for (int i = 0; i < N_PROC - 1; i++)
        {
            printf("T%d => ", safe_seq[i]);
        }
        printf("T%d\n", safe_seq[N_PROC - 1]);
        return TRUE;
    }
    else
    {
        printf("UNSAFE:\t");
        for (int i = 0; i < N_PROC; i++)
        {
            if (F[i] != TRUE)
            {
                printf("T%d ", F[i]);
            }
        }
        printf("can't finish\n");
        return FALSE;
    }
}