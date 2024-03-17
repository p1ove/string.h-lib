#include "test_me.h"

START_TEST(trim_1) {
  char *str1 = "Hello World";
  char *str2 = "H";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "ello World");
  free(str3);
}
END_TEST

START_TEST(trim_2) {
  char *str1 = "Hello World";
  char *str2 = "Hedl";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "o Wor");
  free(str3);
}
END_TEST

START_TEST(trim_3) {
  char *str1 = "";
  char *str2 = "";
  char *str3 = (char *)s21_trim(str1, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(trim_4) {
  char *str = "empty";
  char *str2 = "empty";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(trim_5) {
  char *str = s21_NULL;
  char *str2 = s21_NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(trim_6) {
  char *str = "";
  char *str2 = s21_NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(trim_7) {
  char *str = s21_NULL;
  char *str2 = "          ";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(trim_8) {
  char *str = "empty";
  char *str2 = "t";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_ne(str3, "em");
  free(str3);
}
END_TEST

Suite *test_trim(void) {
  Suite *s = suite_create("\033[45m-=S21_trim=-\033[0m");
  TCase *tc = tcase_create("trim_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, trim_1);
  tcase_add_test(tc, trim_2);
  tcase_add_test(tc, trim_3);
  tcase_add_test(tc, trim_4);
  tcase_add_test(tc, trim_5);
  tcase_add_test(tc, trim_6);
  tcase_add_test(tc, trim_7);
  tcase_add_test(tc, trim_8);

  suite_add_tcase(s, tc);
  return s;
}