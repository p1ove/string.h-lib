#include "s21_string.h"
void *s21_memcpy(void *destination, const void *source, s21_size_t n) {
  char *dest = destination;
  const char *src = source;
  s21_size_t i;
  for (i = 0; i < n; i++) {
    dest[i] = src[i];
  }
  return (void *)dest;
}