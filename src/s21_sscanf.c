#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

#define BUFFER 10000
typedef struct {
  char width;
  int lenght;
  int star;
  int spec;
} format_struct;

int space_skip(const char *str);
int star(const char *format, const char *str, int *star_skip_form,
         int *star_skip_str);
int lenght(format_struct *l, const char *format);
int width(format_struct *l, const char *format);
int spec_f(format_struct *l, const char *str, void *f_arg, int *result);
int spec_s(format_struct *l, const char *str, int *result, char *s_arg);
int spec_c(format_struct *l, const char *str, char *c_arg, int *result);
int spec_d(format_struct *l, const char *str, void *d_arg, int *result,
           int number_system);

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *s_arg = s21_NULL;
  long int *d_arg_long;
  short *d_arg_short;
  int *d_arg_int;
  double *f_arg;
  long double *f_arg_long;
  int *n_arg;
  char *c_arg;

  int n = (int)s21_strlen(str);
  int f = (int)s21_strlen(format);

  int result = 0;
  for (s21_size_t i = 0; i < s21_strlen(format) && *format != '\0'; format++) {
    if (*format == '%') {
      format++;
      format_struct l = {0};

      int star_skip_form = 0;
      int star_skip_str = 0;
      if (*format == '*') {
        if (star(format, str, &star_skip_form, &star_skip_str)) break;
      }
      format += star_skip_form;
      str += star_skip_str;

      format += width(&l, format);
      format += lenght(&l, format);

      l.spec = *format;

      int number_system = 10;
      switch (l.spec) {
        case 's':
          s_arg = va_arg(args, char *);
          if (s_arg == s21_NULL) {
            result = -1;
            break;
          }
          str += spec_s(&l, str, &result, s_arg);
          str += space_skip(str);
          break;
        case 'd':
        case 'i':
        case 'u':
          if (*format == 'i' &&
              (*(str) == '0' ||
               ((*str == '-' || *str == '+') && *(str + 1) == '0'))) {
            if (*(str + 1) == 'x' || *(str + 1) == 'X' || *(str + 2) == 'x' ||
                *(str + 2) == 'X') {
              number_system = 16;
            } else {
              number_system = 8;
            }
          }
          if (l.lenght == 'l') {
            d_arg_long = va_arg(args, long int *);
            if (d_arg_long != s21_NULL) {
              str += spec_d(&l, str, d_arg_long, &result, number_system);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          } else if (l.lenght == 'h') {
            d_arg_short = va_arg(args, short *);
            if (d_arg_short != s21_NULL) {
              str += spec_d(&l, str, d_arg_short, &result, number_system);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          } else {
            d_arg_int = va_arg(args, int *);
            if (d_arg_int != s21_NULL) {
              str += spec_d(&l, str, d_arg_int, &result, number_system);
              str += space_skip(str);
            } else {
              result = -1;
              break;
            }
          }
          break;
        case 'E':
        case 'e':
        case 'f':
        case 'g':
        case 'G':
          if (l.lenght == 'L') {
            f_arg_long = va_arg(args, long double *);
            if (f_arg_long != s21_NULL) {
              str += spec_f(&l, str, f_arg_long, &result);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          } else {
            f_arg = va_arg(args, double *);
            if (f_arg == s21_NULL) {
              result = -1;
              break;
            }
            str += spec_f(&l, str, f_arg, &result);
            str += space_skip(str);
            break;
          }
          break;
        case 'c':
          c_arg = va_arg(args, char *);
          if (c_arg == s21_NULL) {
            result = -1;
            break;
          }
          str += spec_c(&l, str, c_arg, &result);
          str += space_skip(str);
          break;
        case 'n':
          n_arg = va_arg(args, int *);
          if (n_arg == s21_NULL) {
            result = -1;
            break;
          }
          *n_arg = n - (int)s21_strlen(str);
          break;
        case 'o':
          if (l.lenght == 'l') {
            d_arg_long = va_arg(args, long int *);
            if (d_arg_long != s21_NULL) {
              str += spec_d(&l, str, d_arg_long, &result, 8);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          } else if (l.lenght == 'h') {
            d_arg_short = va_arg(args, short *);
            if (d_arg_short != s21_NULL) {
              str += spec_d(&l, str, d_arg_short, &result, 8);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          } else {
            d_arg_int = va_arg(args, int *);
            if (d_arg_int != s21_NULL) {
              str += spec_d(&l, str, d_arg_int, &result, 8);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          }
          break;
        case 'x':
        case 'X':
          if (l.lenght == 'l') {
            d_arg_long = va_arg(args, long int *);
            if (d_arg_long != s21_NULL) {
              str += spec_d(&l, str, d_arg_long, &result, 16);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          } else if (l.lenght == 'h') {
            d_arg_short = va_arg(args, short *);
            if (d_arg_short != s21_NULL) {
              str += spec_d(&l, str, d_arg_short, &result, 16);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          } else {
            d_arg_int = va_arg(args, int *);
            if (d_arg_int != s21_NULL) {
              str += spec_d(&l, str, d_arg_int, &result, 16);
              str += space_skip(str);
            } else {
              {
                result = -1;
                break;
              }
            }
          }
          break;
        case 'p':
          n_arg = va_arg(args, int *);
          if (n_arg == s21_NULL) {
            result = -1;
            break;
          }
          str += spec_d(&l, str, n_arg, &result, 16);
          str += space_skip(str);
          break;
        case '%':
          c_arg = va_arg(args, char *);
          if (c_arg == s21_NULL) {
            result = -1;
            break;
          }
          *c_arg = '%';
          result++;
          str += space_skip(str);
          break;
        default:
          break;
      }
    }
  }
  va_end(args);
  if (f < 3 && result == 0) result = -1;
  return result;
}

int space_skip(const char *str) {
  int skip = 0;
  if (*str == ' ') {
    while (*str == ' ' && *str != '\0') {
      str++;
      skip++;
    }
  } else {
    if (*str != '\0') {
      str++;
      skip++;
    }
    while (*str == ' ' && *str != '\0') {
      str++;
      skip++;
    }
  }
  return skip;
}

int star(const char *format, const char *str, int *star_skip_form,
         int *star_skip_str) {
  int star_result = 0;
  int f = 0;
  int s = 0;
  for (; *format != '\0'; format++, f++) {
    if (*format == '%') {
      format++;
      f++;
      break;
    }
    if (*(format + 1) == '\0') star_result = 1;
  }
  if (*str == ' ') {
    while (*str == ' ' && *str != '\0') {
      str++;
      s++;
    }
    while (*(str + 1) != ' ' && *str != '\0') {
      str++;
      s++;
    }
    while (*(str + 1) == ' ' && *str != '\0') {
      str++;
      s++;
    }
  } else {
    while (*(str + 1) != ' ' && *str != '\0') {
      str++;
      s++;
    }
    while (*(str + 1) == ' ' && *str != '\0') {
      str++;
      s++;
    }
  }
  *star_skip_form = f;
  *star_skip_str = s;
  return star_result;
}

int lenght(format_struct *l, const char *format) {
  int skip = 0;
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    l->lenght = *format;
    format++;
    skip++;
  }
  return skip;
}

int width(format_struct *l, const char *format) {
  int skip = 0;
  if (isdigit(*format)) {
    char *end;
    l->width = (int)strtol(format, &end, 10);
    for (; isdigit(*format); format++, skip++) {
    }
  }
  return skip;
}

int spec_s(format_struct *l, const char *str, int *result, char *s_arg) {
  int skip = 0;
  if (l->width == 0) {
    for (; *str != ' ' && *str != '\0'; str++, skip++, s_arg++) {
      *s_arg = *str;
    }
  } else {
    for (; *str != '\0' && l->width > 0; str++, skip++, s_arg++, l->width--) {
      *s_arg = *str;
    }
  }
  *(s_arg + 1) = '\0';
  (*result)++;
  s_arg -= skip;
  return skip;
}

int spec_c(format_struct *l, const char *str, char *c_arg, int *result) {
  int skip = 0;
  if (l->width == 0) {
    while (*str != '\0') {
      if (*str != '\0' && *str != ' ') {
        *c_arg = *str;
        (*result)++;
        break;
      }
      str++;
      skip++;
    }
  } else {
    for (; *str != '\0' && l->width > 0; str++, skip++, l->width--) {
      if (*str != '\0' && *str != ' ') {
        *c_arg = *str;
        (*result)++;
        break;
      }
    }
  }
  return skip;
}

int spec_d(format_struct *l, const char *str, void *d_arg, int *result,
           int number_system) {
  char *end;
  int skip = 0;
  if (l->width == 0) {
    if (l->lenght == 'l')
      *(long int *)d_arg = (long int)strtol(str, &end, number_system);
    if (l->lenght == 'h')
      *(short *)d_arg = (short)strtol(str, &end, number_system);
    if (l->lenght == 0) *(int *)d_arg = (int)strtol(str, &end, number_system);
    if (end > str) (*result)++;
    for (; (isdigit(*str) || *str == '+' || *str == '-' ||
            s21_strchr("abcdifABCDIFxX", *str) != s21_NULL) &&
           *str != '\0';
         str++, skip++) {
    }
  } else {
    char string_int[BUFFER] = {0};
    int y = 0;
    skip -= 1;
    for (; (isdigit(*str) || *str == '+' || *str == '-' ||
            s21_strchr("abcdifABCDIFxX", *str) != s21_NULL) &&
           l->width > 0 && *str != '\0';
         y++, str++, skip++, l->width--) {
      // if (*str=='+')l->width++;
      string_int[y] = *str;
    }
    string_int[y] = '\0';
    if (l->lenght == 'l')
      *(long int *)d_arg = (long int)strtol(string_int, &end, number_system);
    if (l->lenght == 'h')
      *(short *)d_arg = (short)strtol(string_int, &end, number_system);
    if (l->lenght == 0)
      *(int *)d_arg = (int)strtol(string_int, &end, number_system);
    if (end > string_int) (*result)++;
  }
  return skip;
}

int spec_f(format_struct *l, const char *str, void *f_arg, int *result) {
  char *end;
  int skip = 0;
  if (l->width == 0) {
    if (l->lenght == 'L') {
      *(long double *)f_arg = strtold(str, &end);
    } else {
      *(float *)f_arg = strtod(str, &end);
    }
    if (end > str) (*result)++;
    for (; (isdigit(*str) || *str == '+' || *str == '-' || *str == '.' ||
            *str == 'e' || *str == 'E' || *str == 'x' || *str == 'X') &&
           *str != '\0';
         str++, skip++) {
    }
  } else {
    char string_f[BUFFER] = {0};
    int y = 0;
    skip = skip - l->width;
    for (; (isdigit(*str) || *str == '.' || *str == '+' || *str == '-' ||
            *str == 'e' || *str == 'E' || *str == 'x' || *str == 'X') &&
           l->width > 0;
         y++, str++, skip++, l->width--) {
      // if (*str=='+'||*str=='-') l->width++;
      string_f[y] = *str;
    }
    string_f[y + 1] = '\0';
    if (l->lenght == 'L') {
      *(long double *)f_arg = (long double)strtold(string_f, &end);
    } else {
      *(float *)f_arg = (float)strtod(string_f, &end);
    }
    if (end > string_f) (*result)++;
  }
  return skip;
}