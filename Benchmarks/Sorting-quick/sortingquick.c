#include <stdio.h>
#include <stdlib.h>
#include "datasets.h"
#include <sys/time.h>
#define listTest  \
  {               \
    1, 2, 9, 4, 6 \
  }

void quicksort(int *A, int len);

int main(void)
{
  // get start time
  struct timeval tv1, tv2;
  gettimeofday(&tv1, NULL);
  int a[] = INPUT;
  int n = sizeof a / sizeof a[0]; //   saraiva: known ... 5
  int i;

  quicksort(a, n);

  printf("[");
  for (i = 0; i < n - 1; i++)
  {
    printf("%d,", a[i]);
  }
  printf("%d", a[i]);
  printf("]\n");
  // get end time
  gettimeofday(&tv2, NULL);
  double exectime =
      (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
      (double)(tv2.tv_sec - tv1.tv_sec);
  printf("Time: %f\n", exectime);
  return 0;
}

void quicksort(int *A, int len)
{
  if (len < 2)
    return;

  int pivot = A[len / 2];

  int i, j;
  for (i = 0, j = len - 1;; i++, j--)
  {
    while (A[i] < pivot)
      i++;
    while (A[j] > pivot)
      j--;

    if (i >= j)
      break;

    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
  }

  quicksort(A, i);
  quicksort(A + i, len - i);
}
