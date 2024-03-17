#include "test_me.h"

START_TEST(strspn_1) {
  char s[] = "Hello, world!";
  char *cmp = "loehl";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

START_TEST(strspn_2) {
  char s[] = "";
  char *cmp = "";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

START_TEST(strspn_3) {
  char s[] = "\n\t\v        !";
  char *cmp = "!";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

START_TEST(strspn_4) {
  char s[] = "\03123125341";
  char *cmp = "123";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

START_TEST(strspn_6) {
  char s[] = "Hello my little birdszzz\nqz";
  char *cmp = "loeh ym ";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
  ;
}
END_TEST

START_TEST(strspn_7) {
  char s[] = "54u8989u 8t9 guhtr;giu438h43 34tpq9atj43!";
  char *cmp = "54";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

START_TEST(strspn_8) {
  char s[] = "Helo,@#$\\^&*() ord!";
  char *cmp = "ord";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

START_TEST(strspn_9) {
  char s[] = "Helo";
  char *cmp = "";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

START_TEST(strspn_10) {
  char s[] = "Heldfe2g3  23gf34 o  r323 r23 !@#$^&*";
  char *cmp = "";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

START_TEST(strspn_11) {
  char s[] = "";
  char *cmp = "  fewfewfewf f32 f3";
  ck_assert_int_eq(strspn(s, cmp), s21_strspn(s, cmp));
}
END_TEST

Suite *test_strspn(void) {
  Suite *s = suite_create("\033[45m-=S21_strspn=-\033[0m");
  TCase *tc = tcase_create("strspn_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strspn_1);
  tcase_add_test(tc, strspn_2);
  tcase_add_test(tc, strspn_3);
  tcase_add_test(tc, strspn_4);
  tcase_add_test(tc, strspn_6);
  tcase_add_test(tc, strspn_7);
  tcase_add_test(tc, strspn_8);
  tcase_add_test(tc, strspn_9);
  tcase_add_test(tc, strspn_10);
  tcase_add_test(tc, strspn_11);

  suite_add_tcase(s, tc);
  return s;
}
