#include "s21_string.h"

void *s21_memchr(const void *s, int c, s21_size_t n) {
  const char *sdvig = s;
  s21_size_t i = 0;
  for (; *sdvig != (char)c && i < n; sdvig++, i++) {
  }
  if (i == n || *sdvig != (char)c || n == 0) sdvig = s21_NULL;
  return (void *)sdvig;
}