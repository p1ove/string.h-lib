#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *lower_str = s21_NULL;
  if (str) {
    lower_str = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
      if (str[i] >= 'A' && str[i] <= 'Z')
        lower_str[i] = str[i] + 32;
      else
        lower_str[i] = str[i];
    }
  }
  return lower_str;
}
