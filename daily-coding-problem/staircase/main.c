#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> /* clock_t, clock, CLOCKS_PER_SECOND */
#include <math.h>

void heapify_through_children(int *arr, int length, int i)
{
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < length && arr[left] > arr[largest])
  {
    largest = left;
  }
  if (right < length && arr[right] > arr[largest])
  {
    largest = right;
  }

  if (largest != i)
  {
    swap(arr, i, largest);
    heapify_through_children(arr, length, largest);
  }
}

void heap_sort(int *arr, int length)
{
  for (int i = length / 2; i >= 0; i--)
  {
    heapify_through_children(arr, length, i);
  }

  for (int i = length - 1; i > 0; i--)
  {
    swap(arr, i, 0);
    heapify_through_children(arr, i, 0);
  }
}

int solve(unsigned N, unsigned *step_lengths, unsigned k);

int main()
{
}

int solve(unsigned N, unsigned *step_lengths, unsigned K)
{
  heap_sort(step_lengths, K);
  const unsigned longest_step = step_lengths[0];
  unsigned *const buff = calloc(longest_step , sizeof(unsigned));
  for (unsigned i = 0; i < N; i++)
  {
    for(unsigned k=0;k<K;k++){
      buff[longest_step[k]+]
    }
  }
}
