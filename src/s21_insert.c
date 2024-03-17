#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int count = 0;
  char *res = s21_NULL;
  if ((str && src) && start_index <= s21_strlen(src)) {
    s21_size_t size = s21_strlen(src) + s21_strlen(str);
    res = calloc((size + 1), sizeof(char));
    for (s21_size_t i = 0; i < start_index; i++, count++) {
      res[count] = src[i];
    }
    for (s21_size_t j = 0; j < s21_strlen(str); j++, count++) {
      res[count] = str[j];
    }
    for (s21_size_t i = start_index; i < s21_strlen(src); i++, count++) {
      res[count] = src[i];
    }
  }
  return res;
}