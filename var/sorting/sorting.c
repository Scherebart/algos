#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> /* clock_t, clock, CLOCKS_PER_SECOND */
#include <math.h>

void print_arr(int *arr, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void insertion_sort(int *arr, int length)
{
  for (int i = 1; i < length; i++)
  {
    int value = arr[i];
    int j = i - 1;
    while (arr[j] > value && j >= 0)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = value;
  }
}

void swap(int *arr, int n, int k)
{
  int value_at_n = arr[n];
  arr[n] = arr[k];
  arr[k] = value_at_n;
}

void bubble_sort(int *arr, int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    for (int j = length - 1; j > i; j--)
    {
      if (arr[j - 1] > arr[j])
      {
        swap(arr, j - 1, j);
      }
    }
  }
}

void _merge_sort(int *arr, int length, int *buff)
{
  if (length <= 1)
  {
    return;
  }

  const int length_left = length / 2;
  const int length_right = length - length / 2;
  int *arr_left = arr;
  int *arr_right = arr + length_left;
  _merge_sort(arr, length_left, buff);
  _merge_sort(arr_right, length_right, buff);

  int i_left = 0;
  int i_right = 0;
  int i_buff = 0;
  while (i_left < length_left && i_right < length_right)
  {
    if (arr_left[i_left] < arr_right[i_right])
    {
      buff[i_buff] = arr_left[i_left];
      i_left++;
    }
    else
    {
      buff[i_buff] = arr_right[i_right];
      i_right++;
    }

    i_buff++;
  }
  while (i_left < length_left)
  {
    buff[i_buff++] = arr_left[i_left++];
  }
  while (i_right < length_right)
  {
    buff[i_buff++] = arr_right[i_right++];
  }

  for (int i = 0; i < length; i++)
  {
    arr[i] = buff[i];
  }
}

void merge_sort(int *arr, int length)
{
  int *tmp = malloc(sizeof(int) * length);
  _merge_sort(arr, length, tmp);
  free(tmp);
}

char *make_space(int n)
{
  if (n < 0)
  {
    n = 0;
  }

  char *space = (char *)malloc(n + 1);
  if (space)
  {
    memset(space, ' ', n);
  }
  return space;
}
void print_heap(int *arr, int length)
{
  int i;

  int width = 1;
  i = 0;
  while (i < length)
  {
    i += width;
    width *= 2;
  }

  const int SPOT_WIDTH = 3;
  int used_width;

  i = 0;
  for (int level = 1; level <= width; level *= 2)
  {
    const int step = width / (level * 2);
    const int step_width = step * SPOT_WIDTH;

    for (int j = 0; j < level / 2 && i + j < length; j++)
    {
      printf("%s", make_space(step_width));
      printf("%s", make_space(step_width / 2));
      printf("/");
      printf("%s", make_space(step_width - 1));
      printf("\\");
      printf("%s", make_space(step_width / 2 - 1));
      printf("%s", make_space(step_width));
    }
    printf("\n\n");

    for (int j = 0; j < level && i + j < length; j++)
    {
      printf("%s", make_space(step_width));
      used_width = printf("%d", arr[i + j]);
      printf("%s", make_space(step_width - used_width));
    }

    i += level;
    printf("\n\n");
  }
}

void heapify_through_parent(int *arr, int length, int i)
{
  int j = i;
  int parent_j;
  while (arr[j] > arr[(parent_j = (j - 1) / 2)])
  {
    swap(arr, j, parent_j);
    j = parent_j;
  }
}

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

struct sort_function
{
  char *code;
  void (*fun)(int *arr, int length);
};

#define SORT_FUNCTIONS_COUNT 5
struct sort_function SORT_FUNCTIONS[SORT_FUNCTIONS_COUNT] = {
    {
      code : "bubble",
      fun : bubble_sort
    },
    {
      code : "insertion",
      fun : bubble_sort
    },
    {
      code : "merge",
      fun : merge_sort
    },
    {
      code : "heap",
      fun : heap_sort
    },
    {
      code : "print_heap",
      fun : print_heap
    }};

int main(int argc, char *argv[])
{
  char *sort_algo = "bubble";
  if (argc > 1)
  {
    sort_algo = argv[1];
  }

  int length;
  scanf("%d", &length);
  int *arr = malloc(sizeof(int) * length);
  for (int i = 0; i < length; i++)
  {
    scanf("%d", arr + i);
  }
  // print_arr(arr, length);

  struct sort_function sort_function = {code : NULL};
  {
    for (int i = 0; i < SORT_FUNCTIONS_COUNT; i++)
    {
      if (strcmp(SORT_FUNCTIONS[i].code, sort_algo) == 0)
      {
        sort_function = SORT_FUNCTIONS[i];
        break;
      }
    }
  }
  if (sort_function.code == NULL)
  {
    printf("Unrecognized algo \"%s\"\n", sort_algo);
    return 1;
  }

  clock_t t = clock();
  printf("Doing the %s sort...\n", sort_function.code);
  sort_function.fun(arr, length);
  t = clock() - t;
  printf("clock ticked %ld times, which is %ld miliseconds \n", t, t / (CLOCKS_PER_SEC / 1000));

  // print_arr(arr, length);
}