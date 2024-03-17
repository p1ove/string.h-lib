#include "test_me.h"

START_TEST(strtok_2) {
  char s[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char *cmp = "loehl";
  ck_assert_str_eq(strtok(s, cmp), s21_strtok(s2, cmp));
}
END_TEST

START_TEST(strtok_3) {
  char s[] = "\n\t\v        !";
  char s2[] = "\n\t\v        !";
  char *cmp = "!";
  ck_assert_str_eq(strtok(s, cmp), s21_strtok(s2, cmp));
}
END_TEST

START_TEST(strtok_4) {
  char s[] = "\03123125341";
  char s2[] = "\03123125341";
  char *cmp = "123";
  ck_assert_str_eq(strtok(s, cmp), s21_strtok(s2, cmp));
}
END_TEST

START_TEST(strtok_5) {
  char s[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char *cmp = "Hello";
  ck_assert_str_eq(strtok(s, cmp), s21_strtok(s2, cmp));
}
END_TEST

START_TEST(strtok_6) {
  char s[] = "Hello my little birdszzz\nqz";
  char s2[] = "Hello my little birdszzz\nqz";
  char *cmp = "loeh ym ";
  ck_assert_str_eq(strtok(s, cmp), s21_strtok(s2, cmp));
  ;
}
END_TEST

START_TEST(strtok_7) {
  char s[] = "54u8989u 8t9 guhtr;giu438h43 34tpq9atj43!";
  char s2[] = "54u8989u 8t9 guhtr;giu438h43 34tpq9atj43!";
  char *cmp = "54";
  ck_assert_str_eq(strtok(s, cmp), s21_strtok(s2, cmp));
}
END_TEST

START_TEST(strtok_8) {
  char s[] = "Helo,@#$\\^&*() ord!";
  char s2[] = "Helo,@#$\\^&*() ord!";
  char *cmp = "ord";
  ck_assert_str_eq(strtok(s, cmp), s21_strtok(s2, cmp));
}
END_TEST

START_TEST(strtok_9) {
  char s[] = "54u8989u 8t9 guhtr;giu438h43 34tpq9atj43!";
  char s2[] = "54u8989u 8t9 guhtr;giu438h43 34tpq9atj43!";
  char *cmp = "   ;!";
  char *ptr_orig = strtok(s, cmp);
  char *ptr_s21 = s21_strtok(s2, cmp);
  while (ptr_orig != s21_NULL) {
    ck_assert_pstr_eq(ptr_orig, ptr_s21);
    ptr_orig = strtok(s21_NULL, cmp);
    ptr_s21 = s21_strtok(s21_NULL, cmp);
  }
}
END_TEST

START_TEST(strtok_10) {
  char s[] =
      "I didn't want anything... just leave me alone... pls... d u wanna "
      "pizza?";
  char s2[] =
      "I didn't want anything... just leave me alone... pls... d u wanna "
      "pizza?";
  char *cmp = ".;!";
  char *ptr_orig = strtok(s, cmp);
  char *ptr_s21 = s21_strtok(s2, cmp);
  while (ptr_orig != s21_NULL) {
    ck_assert_pstr_eq(ptr_orig, ptr_s21);
    ptr_orig = strtok(s21_NULL, cmp);
    ptr_s21 = s21_strtok(s21_NULL, cmp);
  }
}
END_TEST

START_TEST(strtok_11) {
  char s[] = "WHERE IS MY 300 k/sec ?????";
  char s2[] = "WHERE IS MY 300 k/sec ?????";
  char *cmp = " ? ;!";
  char *ptr_orig = strtok(s, cmp);
  char *ptr_s21 = s21_strtok(s2, cmp);
  while (ptr_orig != s21_NULL) {
    ck_assert_pstr_eq(ptr_orig, ptr_s21);
    ptr_orig = strtok(s21_NULL, cmp);
    ptr_s21 = s21_strtok(s21_NULL, cmp);
  }
}
END_TEST

Suite *test_strtok(void) {
  Suite *s = suite_create("\033[45m-=S21_strtok=-\033[0m");
  TCase *tc = tcase_create("strtok_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strtok_2);
  tcase_add_test(tc, strtok_3);
  tcase_add_test(tc, strtok_4);
  tcase_add_test(tc, strtok_5);
  tcase_add_test(tc, strtok_6);
  tcase_add_test(tc, strtok_7);
  tcase_add_test(tc, strtok_8);
  tcase_add_test(tc, strtok_9);
  tcase_add_test(tc, strtok_10);
  tcase_add_test(tc, strtok_11);

  suite_add_tcase(s, tc);
  return s;
}
