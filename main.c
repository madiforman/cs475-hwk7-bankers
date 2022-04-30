/*
 ============================================================================
 Name        : Bankers Algorithm
 Author      : Madison Sanchez-Forman
 Version     : 4.30.22
 Description : Uses Edsger Dijkstra's deadlock avoidance algorithm by simulating
 allocating resources to processes and seeing if deadlocks
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "banker.h"

/*** Globals and Prototypes***/
int N_RES;  /*num resources*/
int N_PROC; /*num processes*/
int sanity_check(int *available, int **alloc, int **max, int **need);

int main(int argc, char *argv[])
{
  /*check for correct number of arguments*/
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
      int *total_r = (int *)malloc(sizeof(int) * N_PROC); /*malloc availability vector*/
      for (i = 0; i < N_RES; i++)
      {
        fscanf(fp, "%d", &total_r[i]);
      }
      /*initalize main matrix structures*/
      int **max = read_mtrx(fp, 'w');
      int **alloc = read_mtrx(fp, 'w');
      int **need = read_mtrx(fp, 'r');
      /*calculate need*/
      sub_mtrx(max, alloc, need);
      /*if the file doesnt pass sanity check return*/
      if (!sanity_check(total_r, alloc, max, need))
      {
        is_safe(total_r, alloc, need);
      }
      /*cleanup*/
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
/**
 * @brief Preforms state file integrity check before running bankers algorithm
 *
 * @param available total resource vector
 * @param alloc allocate matrix
 * @param max max matrix
 * @param need need matrix
 * @return int 1 if error found 0 else
 */
int sanity_check(int *available, int **alloc, int **max, int **need)
{
  int total_r = sum_vector(available);
  for (int i = 0; i < N_RES; i++)
  { /*check that each processes' currently allocated resources do not exceed the total # of resources */
    if (sum_vector(alloc[i]) > total_r)
    {
      printf("Integrity test failed: allocated resources exceed total resources\n");
      return 1;
    }
  }
  for (int i = 0; i < N_PROC; i++)
  {
    for (int j = 0; j < N_RES; j++)
    {
      /*check that each processes' needs do not exceed its max demands*/
      if (need[i][j] < 0)
      {
        printf("Integrity test failed: allocated resources exceed total resources for Thread %d\n", i);
        printf("Need %d instances of resource %d\n", need[i][j], j);
        return 1;
      }
    }
  }
  return 0;
}
