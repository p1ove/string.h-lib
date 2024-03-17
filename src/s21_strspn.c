#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t index = 0;
  if (s21_strlen(str2)) {
    s21_size_t count = 0;
    for (s21_size_t i = 0; str1[i] != '\0' && count == 0; i++) {
      count = 0;
      for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
        if (str1[i] == str2[j]) {
          count = 0;
          index = i + 1;
          j = s21_strlen(str2);
        } else {
          count += 1;
          index = i;
        }
      }
    }
  }
  return index;
}