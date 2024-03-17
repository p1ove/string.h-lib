#include "test_me.h"

START_TEST(to_lower_1) {
  char s[] = "Hello, world!";
  char *lower = s21_to_lower(s);
  ck_assert_str_eq("hello, world!", lower);
  free(lower);
}
END_TEST

START_TEST(to_lower_2) {
  char s[] =
      "@Aa, Bb, Cc, Dd, Ee, Ff, Gg, Hh, Ii, Jj, Kk, Ll, Mm, Nn, Oo, Pp, Qq, "
      "Rr, Ss, Tt, Uu, Vv, "
      "Ww, Xx, Yy, Zz[]\n";
  char *lower = s21_to_lower(s);
  ck_assert_str_eq(
      "@aa, bb, cc, dd, ee, ff, gg, hh, ii, jj, kk, ll, mm, nn, oo, pp, qq, "
      "rr, ss, tt, uu, vv, ww, xx, yy, zz[]\n",
      lower);
  free(lower);
}
END_TEST

START_TEST(to_lower_3) {
  char s[] = "";
  char *lower = s21_to_lower(s);
  ck_assert_str_eq("", lower);
  free(lower);
}
END_TEST

START_TEST(to_lower_4) {
  char s[] = " 3123125341";
  char *lower = s21_to_lower(s);
  ck_assert_str_eq(" 3123125341", lower);
  free(lower);
}
END_TEST

START_TEST(to_lower_6) {
  char *s = s21_NULL;
  ck_assert_ptr_eq(s21_NULL, s21_to_lower(s));
}
END_TEST

START_TEST(to_lower_7) {
  char s[] = "Hello my little birdszzz\nQz";
  char *lower = s21_to_lower(s);
  ck_assert_str_eq("hello my little birdszzz\nqz", lower);
  free(lower);
}
END_TEST

START_TEST(to_lower_8) {
  char s[] = "Helo,@#$^&*() ord!";
  char *lower = s21_to_lower(s);
  ck_assert_str_eq("helo,@#$^&*() ord!", lower);
  free(lower);
}
END_TEST

Suite *test_to_lower(void) {
  Suite *s = suite_create("\033[45m-=S21_to_lower=-\033[0m");
  TCase *tc = tcase_create("to_lower_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, to_lower_1);
  tcase_add_test(tc, to_lower_2);
  tcase_add_test(tc, to_lower_3);
  tcase_add_test(tc, to_lower_4);
  tcase_add_test(tc, to_lower_6);
  tcase_add_test(tc, to_lower_7);
  tcase_add_test(tc, to_lower_8);

  suite_add_tcase(s, tc);
  return s;
}
