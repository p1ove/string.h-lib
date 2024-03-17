#include "s21_string.h"
void *s21_memset(void *destination, int c, s21_size_t n) {
  char *dest = destination;
  s21_size_t i;
  for (i = 0; i < n; i++) {
    dest[i] = c;
  }
  return (void *)dest;
}