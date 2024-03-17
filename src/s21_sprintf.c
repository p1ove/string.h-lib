#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *str_start = str;
  char check = 0;
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      spec spec = {0};
      while (*format == '+' || *format == '-' || *format == ' ' ||
             *format == '#' || *format == '0') {
        if (*format == '+') {
          spec.plus = 1;
          format++;
        }
        if (*format == '-') {
          spec.minus = 1;
          format++;
        }
        if (*format == ' ') {
          spec.space = 1;
          format++;
        }
        if (*format == '#') {
          spec.hash = 1;
          format++;
        }
        if (*format == '0') {
          spec.zero = 1;
          format++;
        }
      }

      while (*format >= '0' && *format <= '9') {
        spec.width = spec.width * 10 + (*format - '0');
        format++;
      }

      if (*format == '*') {
        spec.width = va_arg(args, int);
        format++;
      }

      if (*format == '.') {
        format++;
        while (*format >= '0' && *format <= '9') {
          spec.default_accuracy += 2;
          if (*format == '0' && spec.default_accuracy == 2)
            spec.default_accuracy = 1;

          spec.accuracy = spec.accuracy * 10 + (*format - '0');
          format++;
        }
        if (spec.default_accuracy == 0) {
          spec.default_accuracy = 1;
        }

        if (*format == '*') {
          spec.accuracy = va_arg(args, int);
          format++;
          spec.default_accuracy = 0;
        }
        spec.accuracy_defined = 1;
      }

      if (*format == 'h') {
        format++;
        spec.length = 'h';
      }

      if (*format == 'l') {
        format++;
        spec.length = 'l';
      }

      if (*format == 'L') {
        format++;
        spec.length = 'L';
      }

      switch (*format) {
        case 'u': {
          spec.specifier = 'u';
          if (!spec.accuracy_defined) {
            spec.accuracy = 1;
          }
          long int int_arg;
          if (spec.length == 'l') {
            int_arg = (long unsigned)va_arg(args, long int);
          } else if (spec.length == 'h') {
            int_arg = (short unsigned)va_arg(args, int);
          } else {
            int_arg = (unsigned)va_arg(args, int);
          }
          char stringified_number[1000] = {0};
          sspec_d(int_arg, stringified_number, spec);
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 'd': {
          spec.specifier = 'd';
          if (!spec.accuracy_defined) {
            spec.accuracy = 1;
          }
          long int int_arg;
          if (spec.length == 'l') {
            int_arg = va_arg(args, long int);
          } else if (spec.length == 'h') {
            int_arg = (short)va_arg(args, int);
          } else {
            int_arg = (int)va_arg(args, int);
          }

          char stringified_number[100] = {0};
          sspec_d(int_arg, stringified_number, spec);
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 'i': {
          spec.specifier = 'i';
          if (!spec.accuracy_defined) {
            spec.accuracy = 1;
          }
          long int int_arg;
          if (spec.length == 'l') {
            int_arg = va_arg(args, long int);
          } else if (spec.length == 'h') {
            int_arg = (short)va_arg(args, int);
          } else {
            int_arg = (int)va_arg(args, int);
          }

          char stringified_number[1000] = {0};
          sspec_d(int_arg, stringified_number, spec);
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 'f': {
          spec.specifier = 'f';
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }

          char stringified_number[10000] = {0};
          sspec_f(double_arg, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 'c': {
          spec.specifier = 'c';
          char char_arg = va_arg(args, int);
          char stringified_number[2];
          stringified_number[0] = char_arg;
          stringified_number[1] = '\0';
          if (char_arg == '\0') {
            *str = '\0';
            str++;
          } else {
            str += add_width_and_flags(stringified_number, str, spec);
          }
          format++;
          break;
        }
        case '%': {
          char stringified_number[2];
          stringified_number[0] = '%';
          stringified_number[1] = '\0';
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 'X': {
          spec.specifier = 'X';
          long int int_arg = va_arg(args, long int);

          char stringified_number[1000] = {0};

          spec_x(int_arg, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);

          format++;
          break;
        }
        case 'x': {
          spec.specifier = 'x';
          long int int_arg = va_arg(args, long int);

          char stringified_number[1000] = {0};

          spec_x(int_arg, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);

          format++;
          break;
        }
        case 'o': {
          spec.specifier = 'o';
          long int int_arg = va_arg(args, long int);

          char stringified_number[1000] = {0};

          spec_x(int_arg, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);

          format++;
          break;
        }
        case 'E': {  // dobavil
          spec.specifier = 'E';
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }
          char stringified_number[100] = {0};
          spec_e(double_arg, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 'e': {
          spec.specifier = 'e';
          long double double_arg;
          if (spec.length == 'L') {
            double_arg = va_arg(args, long double);
          } else {
            double_arg = (double)va_arg(args, double);
          }
          char stringified_number[100] = {0};
          spec_e(double_arg, stringified_number, &spec);
          str += add_width_and_flags(stringified_number, str, spec);
          format++;
          break;
        }
        case 'p': {
          spec.specifier = 'p';
          void *pointer_value = va_arg(args, void *);
          char mini[1000] = {0};
          spec_p(mini, pointer_value, spec);
          str += add_width_and_flags(mini, str, spec);
          format += 1;
          break;
        }
        case 'n': {
          format++;
          break;
        }
        case 's': {
          spec.specifier = 's';
          char mini[1000] = {0};
          char *string_arg = va_arg(args, char *);
          if (spec.plus || spec.space) {
            spec.plus = 0;
            spec.space = 0;
          }
          if (string_arg != NULL && spec.default_accuracy != 1)
            sspec_s(string_arg, mini, spec.accuracy);  // fix segfault
          else if (spec.default_accuracy != 1) {
            s21_strncpy(mini, "(null)", 8);
          }
          str += add_width_and_flags(mini, str, spec);
          format++;
          break;
        }
      }
      check = spec.specifier;
    } else {
      *str = *format;
      str++;
      format++;
    }
  }
  *str = '\0';
  int result = s21_strlen(str_start);
  if (check == 'c' || check == 's') result = result_count(str_start, str);
  va_end(args);
  return result;
}

int result_count(char *str, char *str_ptr) {
  s21_size_t result = 0;
  for (char *p = str; p != str_ptr; p++) {
    result++;
  }
  return result;
}

void sspec_c(int symbol, char *buff) {
  *buff = symbol;
  buff++;
}

void sspec_s(const char *str, char *mini, int accuracy) {
  int i = 0;
  if (accuracy > 0) {
    while (str[i] != '\0' && 0 < accuracy) {
      *mini = str[i];
      mini++;
      i++;
      accuracy--;
    }
  } else {
    while (str[i] != '\0') {
      *mini = str[i];
      mini++;
      i++;
    }
  }
}

void sspec_d(long int number, char *stringified_number, spec spec) {
  int i = 0;
  int length = 0;
  int flag_minus = 0;

  if (number < 0) {
    number *= -1;
    stringified_number[i] = '-';
    i++;
    length++;
    flag_minus++;
  } else if (number == 0) {
    length++;
    stringified_number[0] =
        (spec.accuracy == 0 && (spec.specifier == 'd' ||
                                spec.specifier == 'u' || spec.specifier == 'i'))
            ? '\0'
            : '0';  // i dobavit
    i = 1;
  }

  long int temp = number;
  while (temp != 0) {
    temp /= 10;
    length++;
  }

  for (; length < spec.accuracy + flag_minus; i++) {
    stringified_number[i] = '0';
    length++;
  }

  stringified_number[length] = '\0';
  if (number != 0) {
    for (int str_end = length - 1; str_end >= i; str_end--) {
      stringified_number[str_end] = number % 10 + '0';
      number /= 10;
    }
  }
}

void sspec_f(long double number, char *stringified_number, spec *spec) {
  if (!spec->accuracy_defined) {
    spec->accuracy = 6;
  }
  long double int_part = 0;
  long double decimal_part = modfl(number, &int_part);
  decimal_part = round(decimal_part * pow(10, spec->accuracy));

  if (labs((long int)decimal_part) / (int)(pow(10, spec->accuracy)) % 10 == 1) {
    if (decimal_part >= 0) {
      int_part += 1;
    } else if (decimal_part < 0) {
      int_part -= 1;
    }
    decimal_part = 0;
  }

  if (decimal_part < 0) {
    decimal_part *= -1;
  }

  char s[1000] = {0};

  sspec_d((long int)decimal_part, s, *spec);

  int decimal_accuracy = spec->accuracy;
  spec->accuracy = 0;

  sspec_d((long int)int_part, stringified_number, *spec);  // insert lower

  if (decimal_accuracy != 0) {
    s21_strcat(stringified_number, ".");
    // here
    s21_strcat(stringified_number, s);
  } else if (decimal_accuracy == 0 && spec->hash) {
    s21_strcat(stringified_number, ".");
  }
}

void spec_x(long int decimalValue, char hexString[], spec *spec) {
  if (!spec->accuracy_defined) {
    spec->accuracy = 1;
  }
  long int number;
  if (spec->length == 'l') {
    number = (long unsigned)decimalValue;
  } else if (spec->length == 'h') {
    number = (short unsigned)decimalValue;
  } else {
    number = (unsigned)decimalValue;
  }
  int remainder;
  int index = 0;

  char letter = 'a';
  int hex_or_oct = 16;
  if (spec->specifier == 'X') {
    letter = 'A';
  }
  if (spec->specifier == 'o') {
    hex_or_oct = 8;
  }

  if (number == 0) {
    hexString[0] = spec->accuracy == 0 ? '\0' : '0';
    index++;
    spec->hash = 0;
  }

  while (number != 0) {
    remainder = number % hex_or_oct;

    if (spec->specifier == 'o') {
      hexString[index] = remainder + '0';
    } else {
      if (remainder < 10) {
        hexString[index] = remainder + '0';
      } else {
        hexString[index] = remainder - 10 + letter;
      }
    }

    number = number / hex_or_oct;
    index++;
  }

  // Accuracy
  for (; index < spec->accuracy; index++) {
    hexString[index] = '0';
  }

  hexString[index] = '\0';

  int i, j;
  char temp;
  for (i = 0, j = index - 1; i < j; i++, j--) {
    temp = hexString[i];
    hexString[i] = hexString[j];
    hexString[j] = temp;
  }
}

void spec_e(long double number, char *stringified_number, spec *spec) {
  char sign = '+';
  if (number < 0) {
    number *= -1;
    stringified_number[0] = '-';
    stringified_number++;
  }

  int pow = 0;
  while (number >= 10 || number < 1) {
    if (number == 0) {
      break;
    }
    if (number >= 10) {
      number /= 10;
    } else {
      number *= 10;
      sign = '-';
    }
    pow++;
  }

  char pow_string[4] = {0};
  pow_calc(pow, pow_string);

  char e = spec->specifier == 'E' ? 'E' : 'e';
  char notation[3] = {e, sign, '\0'};

  sspec_f(number, stringified_number, spec);
  s21_strcat(stringified_number, notation);
  s21_strcat(stringified_number, pow_string);
  stringified_number[s21_strlen(stringified_number)] = '\0';
}

void pow_calc(int pow, char *pow_string) {
  int i = 2;
  // 0
  if (pow == 0) {
    pow_string[0] = '0';
    pow_string[1] = '0';
    pow_string[2] = '\0';
  } else if (pow < 10) {
    pow_string[0] = '0';
    pow_string[2] = '\0';
  } else if (pow >= 100) {
    i = 3;
    pow_string[3] = '\0';
  }
  while (i >= 0) {
    pow_string[i - 1] = pow % 10 + '0';
    pow /= 10;
    i--;
  }
}

s21_size_t add_width_and_flags(char *stringified_number, char *str, spec spec) {
  char s = spec.specifier;
  int xXo = (s == 'x' || s == 'X' || s == 'o' || s == 'c' || s == 'u') ? 1 : 0;
  int is_plus_added = (spec.plus && *stringified_number != '-') ? 1 : 0;
  int is_space_added =
      (spec.space && *stringified_number != '-' && !is_plus_added) ? 1 : 0;
  hash_flag(stringified_number, spec);

  if (xXo) {
    is_plus_added = 0;
    is_space_added = 0;
  }
  s21_size_t shift =
      s21_strlen(stringified_number) + is_plus_added + is_space_added;

  if (spec.zero && (is_plus_added || is_space_added)) {
    *str++ = is_plus_added ? '+' : ' ';
    is_plus_added = 0;
    is_space_added = 0;
  } else if (spec.zero && *stringified_number == '-') {
    *str++ = *stringified_number++;
  }
  while ((int)shift < spec.width && !spec.minus) {
    *str++ = (spec.zero) ? '0' : ' ';
    shift++;
  }
  if (is_plus_added) {
    *str++ = '+';
  }
  if (is_space_added) {
    *str++ = ' ';
  }
  while (*stringified_number != '\0') {
    *str++ = *stringified_number++;
  }
  while ((int)shift < spec.width && spec.minus) {
    *str++ = ' ';
    shift++;
  }
  return shift;
}

int hash_flag(char *stringified_number, spec spec) {
  int is_added = 0;
  char s[2] = {spec.specifier, '\0'};
  char *x = s[0] == 'x' ? "x" : "X";
  if (s[0] == 'o' && stringified_number[0] != '0' && spec.hash) {
    int i = s21_strlen(stringified_number) - 1;
    s21_strcat(stringified_number, "0");
    while (i >= 0) {
      char temp = stringified_number[i];
      stringified_number[i] = stringified_number[i + 1];
      stringified_number[i + 1] = temp;
      i--;
    }
    is_added = 1;
  } else if ((s[0] == 'x' || s[0] == 'X') && spec.hash) {
    int i = s21_strlen(stringified_number) - 1;
    s21_strcat(stringified_number, x);
    while (i >= 0) {
      char temp = stringified_number[i];
      stringified_number[i] = stringified_number[i + 1];
      stringified_number[i + 1] = temp;
      i--;
    }
    i = s21_strlen(stringified_number) - 1;
    s21_strcat(stringified_number, "0");
    while (i >= 0) {
      char temp = stringified_number[i];
      stringified_number[i] = stringified_number[i + 1];
      stringified_number[i + 1] = temp;
      i--;
    }
    is_added = 1;
  }
  return is_added;
}

void spec_p(char *mini, void *pointer, spec spec) {
  unsigned long pointer_value = (unsigned long)pointer;
  char temp[100] = {0};
  int index = 0;
  int width_default = spec.width;
  while (pointer_value != 0) {
    int digit = pointer_value % 16;
    temp[index++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
    pointer_value /= 16;
    spec.accuracy--;
    spec.width--;
  }

  if (spec.accuracy_defined == 0)
    if (index == 0) {
      temp[index++] = '0';
    }
  int current_length = s21_strlen(temp);

  while ((
      (spec.accuracy > 0 || spec.width > 0) &&
      (width_default - 1 < current_length || current_length < spec.accuracy))) {
    temp[index++] = '0';
    spec.accuracy--;
    spec.width--;
  }
  temp[index++] = 'x';
  temp[index++] = '0';

  for (int i = index - 1; i >= 0; i--) {
    *mini = temp[i];
    mini++;
  }
}
