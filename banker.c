#include <stdio.h>
#include <stdlib.h>
#include "banker.h"
#include "vector.h"

int is_safe(int *avail, int **alloc, int **need)
{
    /*finished array, safe sequence array, and work vector*/
    int F[N_PROC], safe_seq[N_PROC], W[N_RES], ind = 0;
    for (int i = 0; i < N_PROC; i++)
    {
        F[i] = 0;
    }
    /*copy total resource vector into work vector*/
    copy_vector(avail, W);
    /*calculate work that needs to be done*/
    find_work(W, alloc);

    /*** BANKER'S SAFETY ALGORITHM ***/
    for (int k = 0; k < N_PROC; k++)
    {
        for (int i = 0; i < N_PROC; i++)
        {
            /*if process i has not yet been set*/
            if (!F[i])
            {
                int flag = 0;
                for (int j = 0; j < N_RES; j++)
                {
                    /*check if process i's needs can be met*/
                    if (need[i][j] > W[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (!flag)
                {
                    /*if its safe increase ind and add it to safe seq*/
                    safe_seq[ind++] = i;
                    for (int j = 0; j < N_RES; j++)
                    {
                        /* "give back" resources */
                        W[j] += alloc[i][j];
                    }
                    /*mark as finished*/
                    F[i] = 1;
                }
            }
        }
    }
    /*check to see if all indexes of F are 1*/
    int pflag = 0;
    for (int i = 0; i < N_PROC; i++)
    {
        if (!F[i])
        {
            pflag = 1;
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
        return 1;
    }
    else
    {
        printf("UNSAFE:\t");
        for (int i = 0; i < N_PROC; i++)
        {
            if (F[i] != 1)
            {
                printf("T%d ", F[i]);
            }
        }
        printf("can't finish\n");
        return 0;
    }
}