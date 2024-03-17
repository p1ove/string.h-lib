#include "test_me.h"

START_TEST(strcspn_1) {
  char s[] = "Hello, world!";
  char *cmp = "loehl";
  ck_assert_int_eq(strcspn(s, cmp), s21_strcspn(s, cmp));
}
END_TEST

START_TEST(strcspn_2) {
  char s[] = "";
  char *cmp = "";
  ck_assert_int_eq(strcspn(s, cmp), s21_strcspn(s, cmp));
}
END_TEST

START_TEST(strcspn_3) {
  char s[] = "\n\t\v        !";
  char *cmp = "!";
  ck_assert_int_eq(strcspn(s, cmp), s21_strcspn(s, cmp));
}
END_TEST

START_TEST(strcspn_4) {
  char s[] = "\031231253419";
  char *cmp = "49998";
  ck_assert_int_eq(strcspn(s, cmp), s21_strcspn(s, cmp));
}
END_TEST

START_TEST(strcspn_6) {
  char s[] = "Hello my little birdszzz\nqz";
  char *cmp = "loeh ym ";
  ck_assert_int_eq(strcspn(s, cmp), s21_strcspn(s, cmp));
  ;
}
END_TEST

START_TEST(strcspn_7) {
  char s[] = "54u8989u 8t9 guhtr;giu438h43 34tpq9atj43!";
  char *cmp = "!";
  ck_assert_int_eq(strcspn(s, cmp), s21_strcspn(s, cmp));
}
END_TEST

START_TEST(strcspn_8) {
  char s[] = "Helo,@#$\\^&*() ord!";
  char *cmp = "ord";
  ck_assert_int_eq(strcspn(s, cmp), s21_strcspn(s, cmp));
}
END_TEST

Suite *test_strcspn(void) {
  Suite *s = suite_create("\033[45m-=S21_strcspn=-\033[0m");
  TCase *tc = tcase_create("strcspn_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strcspn_1);
  tcase_add_test(tc, strcspn_2);
  tcase_add_test(tc, strcspn_3);
  tcase_add_test(tc, strcspn_4);
  tcase_add_test(tc, strcspn_6);
  tcase_add_test(tc, strcspn_7);
  tcase_add_test(tc, strcspn_8);

  suite_add_tcase(s, tc);
  return s;
}
