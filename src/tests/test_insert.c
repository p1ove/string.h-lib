#include "test_me.h"

START_TEST(insert_1) {
  char str1[7] = "puff +";
  char str2[6] = " puff";
  char *str3 = (char *)s21_insert(str1, str2, 6);
  ck_assert_str_eq(str3, "puff + puff");
  free(str3);
}
END_TEST

START_TEST(insert_2) {
  char str1[1] = "";
  char str2[14] = "checking null";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_3) {
  char str1[] = "splitme satisfaction";
  char str2[] = " ";
  char *str3 = (char *)s21_insert(str1, str2, 5);
  ck_assert_str_eq(str3, "split me satisfaction");
  free(str3);
}
END_TEST

START_TEST(insert_4) {
  char str1[14] = "checking null";
  char *str2 = s21_NULL;
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_5) {
  char str1[4] = "end";
  char str2[6] = "start";
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_str_eq(str3, "startend");
  free(str3);
}
END_TEST

START_TEST(insert_6) {
  char str1[7] = "caseof";
  char str2[8] = "mistake";
  char *str3 = (char *)s21_insert(str1, str2, -1);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST

START_TEST(insert_7) {
  char *str1 = s21_NULL;
  char str2[14] = "checking null";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_8) {
  char str1[2] = " ";
  char str2[32] = "if strlen src lesser than index";
  char *str3 = (char *)s21_insert(str1, str2, 3);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_9) {
  char *str1 = s21_NULL;
  char str2[1] = "";
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_10) {
  char *str1 = s21_NULL;
  char *str2 = s21_NULL;
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

START_TEST(insert_11) {
  char str1[4] = "";
  char str2[6] = "";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, s21_NULL);
  free(str3);
}
END_TEST

Suite *test_insert(void) {
  Suite *s = suite_create("\033[45m-=S21_insert=-\033[0m");
  TCase *tc = tcase_create("insert_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, insert_1);
  tcase_add_test(tc, insert_2);
  tcase_add_test(tc, insert_3);
  tcase_add_test(tc, insert_4);
  tcase_add_test(tc, insert_5);
  tcase_add_test(tc, insert_6);
  tcase_add_test(tc, insert_7);
  tcase_add_test(tc, insert_8);
  tcase_add_test(tc, insert_9);
  tcase_add_test(tc, insert_10);
  tcase_add_test(tc, insert_11);

  suite_add_tcase(s, tc);
  return s;
}