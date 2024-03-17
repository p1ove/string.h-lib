#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *buffer = s21_NULL;
  char *token_start = s21_NULL;
  // printf("blya: in str %s in buffer: %s\n", str, buffer);
  if (str != s21_NULL) {
    buffer = str;
    while (*buffer != '\0' && s21_strchr(delim, *buffer)) {
      *buffer = '\0';
      buffer++;
    }
  } else if ((buffer == s21_NULL && str == s21_NULL) || *buffer == '\0') {
    return token_start;
  }

  token_start = buffer;

  while (*buffer != '\0' && s21_strchr(delim, *buffer) == s21_NULL) {
    buffer++;
  }
  while (*buffer != '\0' && s21_strchr(delim, *buffer) != s21_NULL) {
    if (*buffer != '\0') {
      *buffer = '\0';
      buffer++;
    }
  }
  return token_start;
}
