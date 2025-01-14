/*
 ============================================================================
 Name        : Banker's Algorithm
 Author      : Madison Sanchez-Forman
 Version     : 4.30.22
 Description : Uses Edsger Dijkstra's deadlock avoidance algorithm by simulating
 resource allocation and checking to see if deadlocks occur
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "banker.h"
/*** Globals ***/
int N_RES;  /*num resources*/
int N_PROC; /*num processes*/

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: ./bankers <state file> \n");
    return 0;
  }
  else
  {
    FILE *fp = fopen(argv[1], "r");
    int i;
    if (fp != NULL)
    {
      fscanf(fp, "%d", &N_RES);
      fscanf(fp, "%d", &N_PROC);
      /*allocate total resource vector*/
      int *total_r = (int *)malloc(sizeof(int) * N_PROC);
      for (i = 0; i < N_RES; i++)
      {
        /*read in values*/
        fscanf(fp, "%d", &total_r[i]);
      }
      /*initalize main matrix structures*/
      int **max = read_mtrx(fp, 'w');
      int **alloc = read_mtrx(fp, 'w');
      int **need = read_mtrx(fp, 'r');
      /* calculate need */
      sub_mtrx(max, alloc, need);
      /* if the file passes sanity check run safety algorithm */
      if (!sanity_check(total_r, alloc, need))
      {
        is_safe(total_r, alloc, need);
      }
      /* either way, free up memory and exit cleanly */
      free(total_r);
      free(max);
      free(alloc);
      free(need);
      return 0;
    }
    else
    {
      printf("File not found: %s\n", argv[1]);
      return 0;
    }
  }
}
