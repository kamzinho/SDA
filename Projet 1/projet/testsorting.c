#include "Sort.h"
#include "Stable.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

const int studentcode = 20180093;

static size_t comparison_count = 0;
static size_t swap_count = 0;

static void swap_int(void *array, size_t i, size_t j);
static int compare_int(const void *array, size_t i, size_t j);

static void swap_int(void *array, size_t i, size_t j)
{
    swap_count++;
    int temp = ((int *)array)[i];
    ((int *)array)[i] = ((int *)array)[j];
    ((int *)array)[j] = temp;
}

static int compare_int(const void *array, size_t i, size_t j)
{
    comparison_count++;
    return (((int *)array)[i] - ((int *)array)[j]);
}

int main(int argc, char *argv[])
{
    srand(42);

    size_t n = atoi(argv[1]);
    size_t num_tests = atoi(argv[2]);

    int *array = malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++)
        /*array[i] = rand() % (n * 10) - (n * 10) / 2;*/
        array[i] = i;
        /*array[i] = n - i;*/

    swap_int(array,0,n-1);

    printf("Sorting a random array of size %zu with %zu tests\n", n, num_tests);

    double total_cpu_time;
    size_t total_comparisons = 0;
    size_t total_swap = 0;

    for (size_t algo = 0; algo < 7; algo++) {
        printf("\nAlgorithm %zu:\n", algo);

        total_cpu_time = 0;
        total_comparisons = 0;
        total_swap = 0;

        for (size_t test = 0; test < num_tests; test++) {
            int *temp_array = malloc(n * sizeof(int));
            memcpy(temp_array, array, n * sizeof(int));

            comparison_count = 0;
            swap_count = 0;
            clock_t start = clock();

            sort(algo, temp_array, n, compare_int, swap_int);

            clock_t end = clock();

            total_comparisons += comparison_count;
            total_swap += swap_count;
            total_cpu_time += (double)(end - start) / (double)CLOCKS_PER_SEC;
            free(temp_array);
        }

        printf("Average CPU time: %f\n", total_cpu_time / num_tests);
        printf("Average number of comparisons: %zu\n", total_comparisons / num_tests);
        printf("Average number of swaps: %zu\n", total_swap / num_tests);
    }

    free(array);
}
