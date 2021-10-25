#include <stdio.h>
#include <stdlib.h>
#include "datasets.h"
#include <sys/time.h>

int icmp(const void *a, const void *b)
{
#define _I(x) *(const int *)x
	return _I(a) < _I(b) ? -1 : _I(a) > _I(b);
#undef _I
}

/* filter items in place and return number of uniques.  if a separate
   list is desired, duplicate it before calling this function */
int uniq(int *a, int len)
{
	int i, j;
	qsort(a, len, sizeof(int), icmp);
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j])
			a[++j] = a[i];
	return j + 1;
}

int main()
{
	// get start time
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	int x[] = INPUT;
	int i, len = uniq(x, sizeof(x) / sizeof(x[0]));
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