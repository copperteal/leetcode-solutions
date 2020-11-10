/* moved ordering to insertion, still too slow */
#include <stdlib.h>
#define INITSIZE 32


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
	int i;
	if (obj->count == obj->size) {
		obj->size <<= 1;
		obj->arr = realloc(obj->arr, obj->size * sizeof(int));
	}
	if (obj->count == 0) {
		(obj->arr)[0] = number;
		obj->count = 1;
	} else {
		for (i = obj->count-1; i>= 0; i--) {
			if ((obj->arr)[i] > number) {
				(obj->arr)[i+1] = (obj->arr)[i];
			} else {
				break;
			}
		}
		(obj->arr)[i+1] = number;
		obj->count++;
	}
}

/** Find if there exists any pair of numbers which sum is equal to the value.
* */
bool
twoSumFind(TwoSum* obj, int value)
{
	int count = obj->count;
	int *arr = obj->arr;

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
