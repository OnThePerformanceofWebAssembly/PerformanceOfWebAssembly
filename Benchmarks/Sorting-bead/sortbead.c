#include <stdio.h>
#include <stdlib.h>
#include "datasets.h"
#include <sys/time.h>


void bead_sort(int *a, int len)
{
	int i, j, max, sum;
	unsigned char *beads;
#define BEAD(i, j) beads[i * max + j]

	for (i = 1, max = a[0]; i < len; i++)
		if (a[i] > max)
			max = a[i];

	beads = calloc(1, max * len);

	/* mark the beads */
	for (i = 0; i < len; i++)
		for (j = 0; j < a[i]; j++)
			BEAD(i, j) = 1;

	for (j = 0; j < max; j++)
	{
		/* count how many beads are on each post */
		for (sum = i = 0; i < len; i++)
		{
			sum += BEAD(i, j);
			BEAD(i, j) = 0;
		}
		/* mark bottom sum beads */
		for (i = len - sum; i < len; i++)
			BEAD(i, j) = 1;
	}

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < max && BEAD(i, j); j++)
			;
		a[i] = j;
	}
	free(beads);
}

int main()
{
	// get start time
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	int i, x[] = INPUT;
	int len = sizeof(x) / sizeof(x[0]);

	bead_sort(x, len);
	for (i = 0; i < len; i++)
		printf("%d\n", x[i]);

	// get end time
	gettimeofday(&tv2, NULL);
	double exectime =
		(double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
		(double)(tv2.tv_sec - tv1.tv_sec);
	printf("Time: %f\n", exectime);

	return 0;
}