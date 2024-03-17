#include "test_me.h"

START_TEST(strlen_1) {
  char s[] = "Hello, world!";
  ck_assert_int_eq(strlen(s), s21_strlen(s));
}
END_TEST

START_TEST(strlen_2) {
  char s[] = "";
  ck_assert_int_eq(strlen(s), s21_strlen(s));
}
END_TEST

START_TEST(strlen_3) {
  char s[] = "\n\t\v        !";
  ck_assert_int_eq(strlen(s), s21_strlen(s));
}
END_TEST

START_TEST(strlen_4) {
  char s[] = "\03123125341";
  ck_assert_int_eq(strlen(s), s21_strlen(s));
}
END_TEST

START_TEST(strlen_6) {
  char s[] = "Hello my little birdszzz\nqz";
  ck_assert_int_eq(strlen(s), s21_strlen(s));
  ;
}
END_TEST

START_TEST(strlen_7) {
  char s[] = "54u8989u 8t9 guhtr;giu438h43 34tpq9atj43!";
  ck_assert_int_eq(strlen(s), s21_strlen(s));
}
END_TEST

START_TEST(strlen_8) {
  char s[] = "Helo,@#$\\^&*() ord!";
  ck_assert_int_eq(strlen(s), s21_strlen(s));
}
END_TEST

Suite *test_strlen(void) {
  Suite *s = suite_create("\033[45m-=S21_strlen=-\033[0m");
  TCase *tc = tcase_create("strlen_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strlen_1);
  tcase_add_test(tc, strlen_2);
  tcase_add_test(tc, strlen_3);
  tcase_add_test(tc, strlen_4);
  tcase_add_test(tc, strlen_6);
  tcase_add_test(tc, strlen_7);
  tcase_add_test(tc, strlen_8);

  suite_add_tcase(s, tc);
  return s;
}
