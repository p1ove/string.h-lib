#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t index = 0;
  if (!s21_strlen(str2))
    index = s21_strlen(str1);
  else {
    s21_size_t count = 1;
    for (s21_size_t i = 0; str1[i] != '\0' && count != 0; i++) {
      count = 0;
      for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
        if (str1[i] != str2[j]) {
          count++;
          index = i + 1;
        } else {
          count = 0;
          index = i;
          j = s21_strlen(str2);
        }
      }
    }
  }
  return index;
}