#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datasets.h"
#include <sys/time.h>

int compareStrings(const void *a, const void *b)
{
    const char **aa = (const char **)a;
    const char **bb = (const char **)b;
    return strcmp(*aa, *bb);
}

void lexOrder(int n, int *ints)
{
    char **strs;
    int i, first = 1, last = n, k = n, len;
    if (n < 1)
    {
        first = n;
        last = 1;
        k = 2 - n;
    }
    strs = malloc(k * sizeof(char *));
    for (i = first; i <= last; ++i)
    {
        if (i >= 1)
            len = (int)log10(i) + 2;
        else if (i == 0)
            len = 2;
        else
            len = (int)log10(-i) + 3;
        strs[i - first] = malloc(len);
        sprintf(strs[i - first], "%d", i);
    }
    qsort(strs, k, sizeof(char *), compareStrings);
    for (i = 0; i < k; ++i)
    {
        ints[i] = atoi(strs[i]);
        free(strs[i]);
    }
    free(strs);
}

int main()
{
    // get start time
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    int i, j, k, n, *ints;
    int numbers[] = INPUT;
    printf("In lexicographical order:\n\n");
    for (i = 0; i < 5; ++i)
    {
        k = n = numbers[i];
        if (k < 1)
            k = 2 - k;
        ints = malloc(k * sizeof(int));
        lexOrder(n, ints);
        printf("%3d: [", n);
        for (j = 0; j < k; ++j)
        {
            printf("%d ", ints[j]);
        }
        printf("\b]\n");
        free(ints);
    }
    // get end time
    gettimeofday(&tv2, NULL);
    double exectime =
        (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
        (double)(tv2.tv_sec - tv1.tv_sec);
    printf("Time: %f\n", exectime);
    return 0;
}