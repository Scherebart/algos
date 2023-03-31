#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

struct linked_list
{
  struct linked_list *next;
  int value;
};

void print_linked_list(struct linked_list *head)
{
  struct linked_list *e = head;
  while (e)
  {
    printf("%d ", e->value);
    e = e->next;
  }
  printf("\n");
}

struct linked_list *shift_linked_list(struct linked_list *head, int k)
{
  if (k == 0)
  {
    return head;
  }

  int length;
  {
    length = 1;
    struct linked_list *el = head;
    while (el = el->next)
    {
      length++;
    }
  }

  k %= length;
  if (k < 0)
  {
    k += length;
  }

  struct linked_list *tail;
  struct linked_list *new_head;
  struct linked_list *new_tail;
  {
    new_head = head;
    for (int i = 0; i < k; i++)
    {
      new_tail = new_head;
      new_head = new_head->next;
    }

    struct linked_list *el = new_head;
    while (el->next)
    {
      el = el->next;
    }
    tail = el;

    if (new_head == head)
    {
      new_tail = tail;
    }
  }

  tail->next = head;
  new_tail->next = 0;

  return new_head;
}

void do_case()
{
  int length, k;
  scanf("%d %d", &length, &k);
  struct linked_list *head = malloc(sizeof(struct linked_list) * length);
  scanf("%d", &head->value);
  struct linked_list *tail = head;
  for (int i = 1; i < length; i++)
  {
    tail->next = tail + 1;
    tail = tail->next;

    tail->next = 0;
    scanf("%d", &tail->value);
  }
  print_linked_list(head);

  struct linked_list *shifted_head = shift_linked_list(head, k);
  print_linked_list(shifted_head);
  printf("\n");
}

int main()
{
  int cases;
  scanf("%d", &cases);
  for (int i = 0; i < cases; i++)
  {
    do_case();
  }
}
