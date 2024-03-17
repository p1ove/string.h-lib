#include "test_me.h"

START_TEST(to_upper_1) {
  char s[] = "Hello, world!";
  char *upper = s21_to_upper(s);
  ck_assert_str_eq("HELLO, WORLD!", upper);
  free(upper);
}
END_TEST

START_TEST(to_upper_2) {
  char s[] =
      "@Aa, Bb, Cc, Dd, Ee, Ff, Gg, Hh, Ii, Jj, Kk, Ll, Mm, Nn, Oo, Pp, Qq, "
      "Rr, Ss, Tt, Uu, Vv, "
      "Ww, Xx, Yy, Zz[]\n";
  char *upper = s21_to_upper(s);
  ck_assert_str_eq(
      "@AA, BB, CC, DD, EE, FF, GG, HH, II, JJ, KK, LL, MM, NN, OO, PP, QQ, "
      "RR, SS, TT, UU, VV, WW, XX, YY, ZZ[]\n",
      upper);
  free(upper);
}
END_TEST

START_TEST(to_upper_3) {
  char s[] = "";
  char *upper = s21_to_upper(s);
  ck_assert_str_eq("", upper);
  free(upper);
}
END_TEST

START_TEST(to_upper_4) {
  char s[] = " 3123125341";
  char *upper = s21_to_upper(s);
  ck_assert_str_eq(" 3123125341", upper);
  free(upper);
}
END_TEST

START_TEST(to_upper_6) {
  char *s = s21_NULL;
  ck_assert_ptr_eq(s21_NULL, s21_to_upper(s));
}
END_TEST

START_TEST(to_upper_7) {
  char s[] = "Hello my little birdszzz\nQz";
  char *upper = s21_to_upper(s);
  ck_assert_str_eq("HELLO MY LITTLE BIRDSZZZ\nQZ", upper);
  free(upper);
}
END_TEST

START_TEST(to_upper_8) {
  char s[] = "Helo,@#$^&*() ord!";
  char *upper = s21_to_upper(s);
  ck_assert_str_eq("HELO,@#$^&*() ORD!", upper);
  free(upper);
}
END_TEST

Suite *test_to_upper(void) {
  Suite *s = suite_create("\033[45m-=S21_to_upper=-\033[0m");
  TCase *tc = tcase_create("to_upper_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, to_upper_1);
  tcase_add_test(tc, to_upper_2);
  tcase_add_test(tc, to_upper_3);
  tcase_add_test(tc, to_upper_4);
  tcase_add_test(tc, to_upper_6);
  tcase_add_test(tc, to_upper_7);
  tcase_add_test(tc, to_upper_8);

  suite_add_tcase(s, tc);
  return s;
}
