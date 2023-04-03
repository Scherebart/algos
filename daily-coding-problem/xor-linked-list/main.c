#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <callback.h>

int next_int()
{
  int int_local;
  scanf("%d", &int_local);

  return int_local;
}

void doNTimes(int times, void (*f)())
{
  for (int i = 0; i < times; i++)
  {
    f(i);
  }
}

void print_int_arr(int *arr, int length)
{
  void printNthElement(int i)
  {
    printf("| %d |\n", arr[i]);
  }

  printf("+---+\n");
  doNTimes(length, printNthElement);
  printf("+---+\n");
}

struct xor_list_item
{
  int value;
  unsigned long link;
};

struct xor_list
{
  struct xor_list_item head;
  struct xor_list_item tail;
};

struct xor_list_place
{
  struct xor_list_item *prev_item;
  struct xor_list_item *curr_item;
  struct xor_list_item *next_item;
};

struct xor_list *xor_list_make()
{
  struct xor_list *list = malloc(sizeof(struct xor_list));
  list->head.link = (unsigned long)&list->tail;
  list->tail.link = (unsigned long)&list->head;
  list->head.value = -200;
  list->tail.value = -400;

  return list;
}

void xor_list_add(struct xor_list *list, int value)
{
  struct xor_list_item *last_item = (struct xor_list_item *)list->tail.link;

  struct xor_list_item *new_item = malloc(sizeof(struct xor_list_item));
  new_item->value = value;

  last_item->link = (last_item->link ^ (unsigned long)&list->tail) ^ (unsigned long)new_item;
  new_item->link = (long unsigned)last_item ^ (long unsigned)&list->tail;
  list->tail.link = (unsigned long)new_item;
}

const struct xor_list_place xor_list_skip_to(const struct xor_list *list, int index)
{

  struct xor_list_item *prev_item = 0;
  struct xor_list_item *curr_item = &list->head;
  struct xor_list_item *next_item;

  struct xor_list_item *comp_next_item()
  {
    return (struct xor_list_item *)((unsigned long)prev_item ^ curr_item->link);
  };

  for (int i = 0; i <= index; i++)
  {
    next_item = comp_next_item();
    if (next_item == &list->tail)
    {
      return (const struct xor_list_place){
          .curr_item = 0};
    }

    prev_item = curr_item;
    curr_item = next_item;
    next_item = comp_next_item();
  }

  return (const struct xor_list_place){
      .prev_item = prev_item,
      .curr_item = curr_item,
      .next_item = next_item};
}

void xor_list_remove(struct xor_list *list, int index)
{
  const struct xor_list_place place = xor_list_skip_to(list, index);
  if (place.curr_item == 0)
  {
    return;
  }

  place.prev_item->link = (place.prev_item->link ^ (unsigned long)place.curr_item) ^ (unsigned long)place.next_item;
  place.next_item->link = (place.next_item->link ^ (unsigned long)place.curr_item) ^ (unsigned long)place.prev_item;
  free(place.curr_item);
}

int *xor_list_get(const struct xor_list *list, int index)
{
  const struct xor_list_place place = xor_list_skip_to(list, index);
  if (place.curr_item == 0)
  {
    return 0;
  }

  return &place.curr_item->value;
}

void xor_list_print(const struct xor_list *list)
{
  int index = 0;
  int *value = 0;
  printf("+---+\n");
  while ((value = xor_list_get(list, index++)) != 0)
  {
    printf("| %d |\n", *value);
  }
  printf("+---+\n");
}

int main()
{
  struct xor_list *list = xor_list_make();

  void load_next_int()
  {
    xor_list_add(list, next_int());
  }
  doNTimes(next_int(), load_next_int);
  xor_list_print(list);

  xor_list_remove(list, 0);
  xor_list_print(list);

  xor_list_remove(list, 4);
  xor_list_print(list);

  xor_list_remove(list, 2);
  xor_list_print(list);
}