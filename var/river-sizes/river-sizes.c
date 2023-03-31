#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

void print_arr(int *arr)
{
  int i = 0;
  while (arr[i] != INT_MIN)
  {
    printf("%d ", arr[i]);
    i++;
  }
  printf("\n");
}

void river_sizes_too_simple_solution(bool *matrix, int height, int width)
{
  int row_counter = 0;
  int *col_counters = malloc(sizeof(int) * width);
  for (int c = 0; c < width; c++)
  {
    col_counters[c] = 0;
  }

  for (int r = 0; r < height; r++)
  {
    for (int c = 0; c < width; c++)
    {
      bool value = matrix[r * width + c];

      if (value == 1)
      {
        row_counter++;
        col_counters[c]++;
      }
      else
      {
        if (row_counter > 0)
        {
          printf("%d ", row_counter);
          row_counter = 0;
        }

        if (col_counters[c] > 0)
        {
          printf("%d ", col_counters[c]);
          col_counters[c] = 0;
        }
      }
    }
    if (row_counter > 0)
    {
      printf("%d ", row_counter);
      row_counter = 0;
    }
  }
  for (int c = 0; c < width; c++)
  {
    if (col_counters[c] > 0)
    {
      printf("%d ", col_counters[c]);
    }
  }

  printf("\n");
}

struct matrix
{
  bool *arr;
  int height;
  int width;
};

bool *matrix_at(struct matrix *matrix, int h, int w)
{
  if (h < 0 || h >= matrix->height || w < 0 || w >= matrix->width)
  {
    return 0;
  }

  return matrix->arr + (h * matrix->width + w);
}

int count(struct matrix *matrix, int h, int w)
{
  int counter = 0;

  bool *river_at = matrix_at(matrix, h, w);
  if (river_at != 0 && *river_at == true)
  {
    *river_at = false;
    counter += 1;
    counter += count(matrix, h - 1, w);
    counter += count(matrix, h + 1, w);
    counter += count(matrix, h, w - 1);
    counter += count(matrix, h, w + 1);
  }

  return counter;
}

void river_sizes(struct matrix *matrix)
{
  for (int h = 0; h < matrix->height; h++)
  {
    for (int w = 0; w < matrix->width; w++)
    {
      int counter = count(matrix, h, w);
      if (counter > 0)
      {
        printf("%d ", counter);
      }
    }
  }
  printf("\n");
}

int main()
{
  struct matrix *matrix = malloc(sizeof(struct matrix));
  scanf("%d %d", &matrix->height, &matrix->width);
  matrix->arr = malloc(matrix->height * matrix->width);
  char tmp;
  int matrix_arr_idx = 0;
  for (int h = 0; h < matrix->height; h++)
  {
    for (int w = 0; w < matrix->width; w++)
    {
      do
      {
        scanf("%c", &tmp);
      } while (tmp == ' ' || tmp == '\n');
      matrix->arr[matrix_arr_idx++] = (tmp == '#' ? true : false);
    }
  }

  river_sizes(matrix);
}