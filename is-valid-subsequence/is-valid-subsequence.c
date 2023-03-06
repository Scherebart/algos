#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_valid_subsequence(int *arr, int *seq)
{
  int arr_idx = 0;
  int seq_idx = 0;

  while (arr[arr_idx] != INT_MIN && seq[seq_idx] != INT_MIN)
  {
    if (seq[seq_idx] == arr[arr_idx])
    {
      seq_idx++;
    }
    arr_idx++;
  }

  return seq[seq_idx] == INT_MIN ? 1 : 0;
}

int main()
{
  int arr[] = {5, 1, 22, 25, 6, -1, 8, 10, INT_MIN};
  int seq[] = {1, 6, -1, 10, INT_MIN};

  int res = is_valid_subsequence(arr, seq);
  printf("result: %d\n", res);
}