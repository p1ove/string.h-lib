#include "s21_string.h"

int s21_strcmp(const void *str1, const void *str2) {
  const unsigned char *p1 = str1;
  const unsigned char *p2 = str2;
  int result = 0;
  s21_size_t i = 0;
  for (; *p1 != '\0' && *p2 != '\0' && *p1 == *p2; p1++, p2++, i++) {
  }
  if (*p1 == *p2)
    result = 0;
  else {
    if (*p1 > *p2)
      result = 1;
    else
      result = -1;
  }
  return result;
}