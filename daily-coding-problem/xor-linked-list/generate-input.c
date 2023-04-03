#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void fill_random(int length)
{
  int min = -length * 2;
  int max = length * 2;

  const double factor = (double)RAND_MAX / (max - min);
  srand(time(NULL));
  for (int i = 0; i < length; i++)
  {
    printf("%d ", (int)(rand() / factor - (max - min) / 2));
  }
}

void fill_ascending(int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%d ", i * 2 + i % 2);
  }
}

void fill_descending(int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%d ", (length - 1 - i) * 2 + (length - 1 - i) % 2);
  }
}
int main()
{
  int length = 33;
  // printf("length of array?\n");
  scanf("%d", &length);
  printf("%d\n", length);

  fill_random(length);
  // fill_ascending(length);
  // fill_descending(length);
  printf("\n");
}