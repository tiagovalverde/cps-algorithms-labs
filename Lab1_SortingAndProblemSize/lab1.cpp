#include <iostream>
#include <array>
#include <cmath>
#include <random>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <chrono>

using namespace std::chrono;
using namespace std;

const int NUM_ARRAYS = 6;

// helpers
int getRandomNumber(int);
void printArray(int arr[], int size);
void pushRandomNumbersToArray(int arr[], int size, int randMax);
void deallocMemOfArrays(int *arraysList[NUM_ARRAYS]);
int *copyArray(int const *src, size_t len);
// sort functions
void selectionSort(int arr[], int n);
void swap(int *xp, int *yp);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void mergeSortModified(int arr[], int l, int r, int arrLen);

int main()
{
    srand((int)time(0)); // seed rand with time

    array<int, NUM_ARRAYS> arraySizes;
    int arraySizeGrowthFactor;
    // obtain base size n
    cout << "Enter size of first array(n): ";
    cin >> arraySizes[0];
    // obtain different
    cout << "Enter growth factor of following arrays (n*2, n*3 ...): ";
    cin >> arraySizeGrowthFactor;

    // generate sizes of other 5 arrays
    for (int i = 1; i < arraySizes.size(); i++)
    {
        int nSize = arraySizes[i - 1] * arraySizeGrowthFactor;
        arraySizes[i] = nSize;
    }
    cout << "\n========\n";

    // alloc mem for arrays
    int **arraysList = new int *[NUM_ARRAYS];
    for (size_t i = 0; i < NUM_ARRAYS; ++i)
    {
        int randMax = arraySizes[i] * 4;
        arraysList[i] = new int[arraySizes[i]]; // alloc mem
        pushRandomNumbersToArray(arraysList[i], arraySizes[i], randMax);
    }

    // loop over all arrays, sort and measure
    for (size_t i = 0; i < NUM_ARRAYS; ++i)
    {
        int *arrayToSelectionSort = copyArray(arraysList[i], arraySizes[i]);
        int *arrayToMergeSort = copyArray(arraysList[i], arraySizes[i]);
        int *arrayToMergeAndSelectionSort = copyArray(arraysList[i], arraySizes[i]);

        cout << "Sorting Array " << i << " (n= " << arraySizes[i] << ")" << endl;

        auto start = system_clock::now();
        selectionSort(arrayToSelectionSort, arraySizes[i]);
        auto stop = system_clock::now();
        auto duration_ms = duration_cast<nanoseconds>(stop - start);
        auto duration_sec = duration_cast<seconds>(stop - start);
        cout << "Time taken by selection sort: " << duration_ms.count() << " nanoseconds (" << duration_sec.count() << " seconds)" << endl;

        auto start2 = system_clock::now();
        mergeSort(arrayToMergeSort, 0, arraySizes[i] - 1);
        auto stop2 = system_clock::now();
        auto duration2_ms = duration_cast<nanoseconds>(stop2 - start2);
        auto duration2_sec = duration_cast<seconds>(stop2 - start2);
        cout << "Time taken by merge sort:     " << duration2_ms.count() << " nanoseconds (" << duration2_sec.count() << " seconds)" << endl;

        auto start3 = system_clock::now();
        mergeSortModified(arrayToMergeAndSelectionSort, 0, arraySizes[i] - 1, arraySizes[i]);
        auto stop3 = system_clock::now();
        auto duration3_ms = duration_cast<nanoseconds>(stop3 - start3);
        auto duration3_sec = duration_cast<seconds>(stop3 - start3);
        cout << "Time taken by combined sort:  " << duration3_ms.count() << " nanoseconds (" << duration3_sec.count() << " seconds)" << endl;

        //printArray(arraysList[i], arraySizes[i]);
        //printArray(arrayToSelectionSort, arraySizes[i]);
        //printArray(arrayToMergeSort, arraySizes[i]);
        //printArray(arrayToMergeAndSelectionSort, arraySizes[i]);

        cout << "========\n";
    }

    deallocMemOfArrays(arraysList);
    return 0;
}

/**********************
 * Selection Sort
 * Worst Case: O(n^2)
 * Average Case: Θ(n^2)
 * Best Case: Ω(n^2)
**********************/
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/*****************
 * Combined Merge Sort
**/
void mergeSortModified(int arr[], int l, int r, int arrLen)
{
    int n = 35; // selection faster when n<35

    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        if (r - l <= n)
        {
            // cout << "\nCombinedSort: SELECTION\n";
            selectionSort(arr, arrLen);
        }
        else
        {
            //   cout << "\nCombinedSort: MERGE\n";
            // Sort first and second halves
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }
}

/**********************
 * Merge Sort
 * Worst Case: Ω(n log(n))	
 * Average Case: Θ(n log(n))
 * Best Case: O(n log(n))
**********************/

/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int getRandomNumber(int randMax)
{
    return (rand() % randMax) + 1;
}

void pushRandomNumbersToArray(int arr[], int size, int randMax)
{
    for (int j = 0; j < size; j++)
    {
        arr[j] = getRandomNumber(randMax);
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << to_string(arr[i]) + ", ";
    }
    cout << "\n";
}

void deallocMemOfArrays(int *arraysList[NUM_ARRAYS])
{
    for (size_t i = 0; i < NUM_ARRAYS; ++i)
    {
        delete[] arraysList[i];
    }
    delete[] arraysList;
}

int *copyArray(int const *src, size_t len)
{
    int *p = (int *)malloc(len * sizeof(int));
    memcpy(p, src, len * sizeof(int));
    return p;
}
