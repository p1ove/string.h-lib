#include "s21_string.h"

int s21_memcmp(const void *ptr1, const void *ptr2, s21_size_t num) {
  const unsigned char *p1 = ptr1;
  const unsigned char *p2 = ptr2;
  int result = 0;
  s21_size_t i = 0;
  for (; i < num && *p1 == *p2; p1++, p2++, i++) {
  }
  if (*p1 == *p2 || i == num)
    result = 0;
  else {
    if (*p1 > *p2)
      result = 1;
    else
      result = -1;
  }
  return result;
}