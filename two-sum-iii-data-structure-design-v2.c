/* insertion sort, slow but works */
#include <stdlib.h>
#define INITSIZE 32


void insertionSort(int*, int);

typedef struct {
	int *arr;
	int count;
	int size;
} TwoSum;

/** Initialize your data structure here. */

TwoSum*
twoSumCreate()
{
	TwoSum *new = (TwoSum*)malloc(sizeof(TwoSum));
	new->arr = (int*)malloc(INITSIZE * sizeof(int));
	new->count = 0;
	new->size = INITSIZE;
	return new;
}

/** Add the number to an internal data structure.. */
void
twoSumAdd(TwoSum* obj, int number)
{
	if (obj->count == obj->size) {
		obj->size <<= 1;
		obj->arr = realloc(obj->arr, obj->size * sizeof(int));
	}
	(obj->arr)[obj->count] = number;
	obj->count++;
}

/** Find if there exists any pair of numbers which sum is equal to the value.
* */
bool twoSumFind(TwoSum* obj, int value)
{
	int count = obj->count;
	int *arr = obj->arr;

	insertionSort(arr, count);

	int lidx, ridx;
	int diff;
	for (lidx = 0, ridx = count-1; lidx < ridx; ) {
		diff = value - arr[ridx];
		if (arr[lidx] > diff) {
			ridx--;
		} else if (arr[lidx] < diff) {
			lidx++;
		} else {
			return true;
		}
	}
	return false;
}

void
twoSumFree(TwoSum* obj)
{
	free(obj->arr);
	obj->arr = NULL;
	free(obj);
}

/**
*  * Your TwoSum struct will be instantiated and called as such:
*   * TwoSum* obj = twoSumCreate();
*    * twoSumAdd(obj, number);
*     
*      * bool param_2 = twoSumFind(obj, value);
*       
*        * twoSumFree(obj);
*        */

/* go from right to left */
void
insertionSort(int *arr, int count)
{
	if (count < 2) {
		return;
	}

	int i, j;
	int elem;
	for (i = count-2; i >= 0; i--) {
		elem = arr[i];
		for (j = i+1; j < count; j++) {
			if (elem < arr[j]) {
				break;
			}
			arr[j-1] = arr[j];
		}
		arr[j-1] = elem;
	}
}
