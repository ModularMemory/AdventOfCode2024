#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define IDS_LEN 1000
#define IDS_FILENAME "lists.txt"

static int intSort(const int* a, const int* b) {
    return *a - *b;
}

static int part1(void) {
    int* ids1 = malloc(IDS_LEN * sizeof(int));
    int* ids2 = malloc(IDS_LEN * sizeof(int));
    assert(ids1);
    assert(ids2);

    FILE* fp = fopen(IDS_FILENAME, "r");
    assert(fp);

    for (int i = IDS_LEN - 1; i >= 0; i--) {
        fscanf_s(fp, "%5d  %5d", &ids1[i], &ids2[i]);
    }

    qsort(ids1, IDS_LEN, sizeof(int), intSort);
    qsort(ids2, IDS_LEN, sizeof(int), intSort);

    int sum = 0;
    for (int i = IDS_LEN - 1; i >= 0; i--) {
        sum += abs(ids1[i] - ids2[i]);
    }

    return sum;
}

int main(void) {
    int sum = part1();
    printf("%d", sum);

    return 0;
}