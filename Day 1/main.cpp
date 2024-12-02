#include <map>
#include <cassert>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

constexpr auto IDS_LEN = 1000;
constexpr auto IDS_FILENAME = "inputs.txt";

static void readIds(int* ids1, int* ids2) {
    FILE* fp = NULL;
    fopen_s(&fp, IDS_FILENAME, "r");
    assert(fp);

    for (int i = IDS_LEN - 1; i >= 0; i--) {
        fscanf_s(fp, "%5d  %5d", &ids1[i], &ids2[i]);
    }

    fclose(fp);
}

static int intSort(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int main(void) {
    // setup
    int* ids1 = (int*)malloc(IDS_LEN * sizeof(int));
    int* ids2 = (int*)malloc(IDS_LEN * sizeof(int));
    assert(ids1);
    assert(ids2);

    readIds(ids1, ids2);

    qsort(ids1, IDS_LEN, sizeof(int), intSort);
    qsort(ids2, IDS_LEN, sizeof(int), intSort);

    std::map<int, int> ids2Occurences;
    for (int i = IDS_LEN - 1; i >= 0; i--) {
        ids2Occurences[ids2[i]] += 1;
    }

    // compute metrics
    int sum = 0;
    int similarity = 0;
    for (int i = IDS_LEN - 1; i >= 0; i--) {
        int idA = ids1[i];
        int idB = ids2[i];

        sum += std::abs(idA - idB);
        similarity += idA * ids2Occurences[idA];
    }

    // print results
    printf("Sum: %d\n", sum);
    printf("Similarity: %d\n", similarity);

    free(ids1);
    free(ids2);
    return 0;
}