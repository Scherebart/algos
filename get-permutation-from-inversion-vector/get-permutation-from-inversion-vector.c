#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void solve(int *arr, int length)
{
  int j, num;

  j = 0;
  do
  {
    num = j + 1;

    for (int i = j - 1; i >= 0; i--)
    {
      if (arr[i] >= num - arr[j])
      {
        arr[i] += 1;
      }
    }
    arr[j] = num - arr[j];

    j++;
  } while (j < length);
}

struct el
{
  struct el *prev;
  int value;
};

void print_linked_arr(struct el *head)
{
  struct el *e = head;
  while (e = e->prev)
  {
    printf("%d ", e->value);
  }
  printf("\n");
}

void solve2(int *arr, int length)
{
  struct el *head;

  head = malloc(sizeof(struct el));
  head->prev = 0;
  head->value = -1;
  for (int i = 0; i < length; i++)
  {
    int rev = arr[i];
    struct el *e = head;
    for (int rep = 1; rep <= rev; rep++)
    {
      e = e->prev;
    }
    struct el *e_prev = e->prev;
    e->prev = malloc(sizeof(struct el));

    e = e->prev;
    e->prev = e_prev;
    e->value = i;
  }

  int order_num = length;
  struct el *e = head;
  while (e = e->prev)
  {
    arr[e->value] = order_num;
    order_num -= 1;
  }
}

void solve3(int *arr, int length)
{
  struct el *valuelist_head;

  // prepare valuelist
  {
    valuelist_head = malloc(sizeof(struct el));

    struct el *valuelist_el = valuelist_head;
    for (int val = length; val >= 1; val--)
    {
      valuelist_el->prev = malloc(sizeof(struct el));
      valuelist_el = valuelist_el->prev;
      valuelist_el->value = val;
    }
  }

  for (int i = length - 1; i >= 0; i--)
  {
    // take arr[i]-ish value and put it into arr[i]
    struct el *valuelist_el = valuelist_head;
    for (int rep = 1; rep <= arr[i]; rep++)
    {
      valuelist_el = valuelist_el->prev;
    }
    arr[i] = valuelist_el->prev->value;
    valuelist_el->prev = valuelist_el->prev->prev;
  }
}

int main()
{
  int arr[] = {0, 0, 1, 1, 2, 1, 4, 5};
  int length = 8;
  solve(arr, length);
  print_arr(arr, length);

  int arr2[] = {0, 0, 1, 1, 2, 1, 4, 5};
  int length2 = 8;
  solve2(arr2, length2);
  print_arr(arr2, length2);

  int arr3[] = {0, 0, 1, 1, 2, 1, 4, 5};
  int length3 = 8;
  solve3(arr3, length3);
  print_arr(arr3, length3);
}
