#include "s21_string.h"

char *s21_strchr(const char *s, int c) {
  const char *sdvig = s;
  s21_size_t i = 0;
  for (; *sdvig != (char)c && *sdvig != '\0'; sdvig++, i++) {
  }
  if ((*sdvig == '\0' && c != '\0') || *sdvig != (char)c) sdvig = s21_NULL;
  return (char *)sdvig;
}