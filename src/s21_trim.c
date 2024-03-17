#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (!src || !trim_chars) return res;

  res = calloc((s21_strlen(src) + 1), sizeof(char));
  int flag = -1;
  s21_size_t index_start = 0, index_end = 0;
  for (s21_size_t i = 0; i < s21_strlen(src); i++) {
    s21_size_t count = 0;
    for (s21_size_t j = 0; j < s21_strlen(trim_chars); j++) {
      if (src[i] == trim_chars[j]) {
        count++;
      }
    }
    if (count == 0) {
      if (flag != 1) index_start = i;
      flag = 1;
      index_end = 0;
    } else
      index_end += count;
  }
  for (s21_size_t i = index_start, current = 0; i < s21_strlen(src) - index_end;
       i++, current++) {
    for (s21_size_t j = 0; j < s21_strlen(trim_chars); j++) {
      res[current] = src[i];
    }
  }
  return res;
}