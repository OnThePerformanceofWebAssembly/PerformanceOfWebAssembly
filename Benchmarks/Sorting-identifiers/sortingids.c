#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datasets.h"
#include <sys/time.h>

typedef struct oid_tag
{
    char *str_;
    int *numbers_;
    int length_;
} oid;

// free memory, no-op if p is null
void oid_destroy(oid *p)
{
    if (p != 0)
    {
        free(p->str_);
        free(p->numbers_);
        free(p);
    }
}

int char_count(const char *str, char ch)
{
    int count = 0;
    for (const char *p = str; *p; ++p)
    {
        if (*p == ch)
            ++count;
    }
    return count;
}

// construct an OID from a string
// returns 0 on memory allocation failure or parse error
oid *oid_create(const char *str)
{
    oid *ptr = calloc(1, sizeof(oid));
    if (ptr == 0)
        return 0;
    ptr->str_ = strdup(str);
    if (ptr->str_ == 0)
    {
        oid_destroy(ptr);
        return 0;
    }
    int dots = char_count(str, '.');
    ptr->numbers_ = malloc(sizeof(int) * (dots + 1));
    if (ptr->numbers_ == 0)
    {
        oid_destroy(ptr);
        return 0;
    }
    ptr->length_ = dots + 1;
    const char *p = str;
    for (int i = 0; i <= dots && *p;)
    {
        char *eptr = 0;
        int num = strtol(p, &eptr, 10);
        if (*eptr != 0 && *eptr != '.')
        {
            // TODO: check for overflow/underflow
            oid_destroy(ptr);
            return 0;
        }
        ptr->numbers_[i++] = num;
        p = eptr;
        if (*p)
            ++p;
    }
    return ptr;
}

// compare two OIDs
int oid_compare(const void *p1, const void *p2)
{
    const oid *o1 = *(oid *const *)p1;
    const oid *o2 = *(oid *const *)p2;
    int i1 = 0, i2 = 0;
    for (; i1 < o1->length_ && i2 < o2->length_; ++i1, ++i2)
    {
        if (o1->numbers_[i1] < o2->numbers_[i2])
            return -1;
        if (o1->numbers_[i1] > o2->numbers_[i2])
            return 1;
    }
    if (o1->length_ < o2->length_)
        return -1;
    if (o1->length_ > o2->length_)
        return 1;
    return 0;
}

int main()
{
    // get start time
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    const char *input[] = INPUT;
    const int len = sizeof(input) / sizeof(input[0]);
    oid *oids[len];
    memset(oids, 0, sizeof(oids));
    int i;
    for (i = 0; i < len; ++i)
    {
        oids[i] = oid_create(input[i]);
        if (oids[i] == 0)
        {
            fprintf(stderr, "Out of memory\n");
            goto cleanup;
        }
    }
    qsort(oids, len, sizeof(oid *), oid_compare);
    for (i = 0; i < len; ++i)
        puts(oids[i]->str_);
cleanup:
    for (i = 0; i < len; ++i)
        oid_destroy(oids[i]);

    // get end time
    gettimeofday(&tv2, NULL);
    double exectime =
        (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
        (double)(tv2.tv_sec - tv1.tv_sec);
    printf("Time: %f\n", exectime);
    return 0;
}