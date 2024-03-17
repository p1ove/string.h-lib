#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *upper_str = s21_NULL;
  if (str) {
    upper_str = calloc(s21_strlen(str) + 1, sizeof(char));
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
      if (str[i] >= 'a' && str[i] <= 'z')
        upper_str[i] = str[i] - 32;
      else
        upper_str[i] = str[i];
    }
  }
  return upper_str;
}