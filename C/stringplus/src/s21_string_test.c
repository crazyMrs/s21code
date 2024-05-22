#include "s21_string.h"

#include <check.h>
#include <string.h>

//Функция тестирования какой-либо задачи.

START_TEST(test_s21_memchr) {
  char str[4096] = {0};
  char str1[50] = "hello ";
  char str1_1[50] = "hello ";
  char str2[50] = "world!";
  char str3[50] = "gajgwyfdy44343";
  char str3_3[50] = "gajgwyfdy44343";
  char str4[50] = "world!2222";
  char str5[50] = "";
  char str5_5[50] = "";
  char str6[1024] = "LUGANO THE BEST!";
  strcat(str, "Hello world! SOS Be careful!/t/123456");
  ck_assert_pstr_eq(s21_memchr(str, 'H', 10), memchr(str, 'H', 10));
  ck_assert_pstr_eq(s21_memchr(str, 'O', 20), memchr(str, 'O', 20));
  ck_assert_pstr_eq(s21_memchr(str, '/', 50), memchr(str, '/', 50));
  ck_assert_pstr_eq(s21_memchr(str, 't', 6), memchr(str, 't', 6));
  ck_assert_pstr_eq(s21_memchr(str, ' ', 10), memchr(str, ' ', 10));
  ck_assert_pstr_eq(s21_memchr(str, 1, 16), memchr(str, 1, 16));
  ck_assert_pstr_eq(s21_memchr(str, '!', 3), memchr(str, '!', 3));
  ck_assert_pstr_eq(s21_memchr(str, 'k', 3), memchr(str, 'k', 3));
  ck_assert_pstr_eq(strcat(str1, str2), s21_strcat(str1_1, str2));
  ck_assert_pstr_eq(strcat(str3, str4), s21_strcat(str3_3, str4));
  ck_assert_pstr_eq(strcat(str5, str6), s21_strcat(str5_5, str6));
}
END_TEST

START_TEST(test_s21_memcmp) {
  char buf1[] = "hello, im here";
  char buf2[] = "hello, im not here";
  char buf3[] = "you are here";
  char buf4[] = "you are there";
  char buf5[] = "you are there";
  char buf6[] = "";
  char buf7[] = "";
  ck_assert_int_eq(s21_memcmp(buf1, buf2, 4), memcmp(buf1, buf2, 4));
  ck_assert_int_eq(s21_memcmp(buf3, buf4, 2), memcmp(buf3, buf4, 2));
  ck_assert_int_eq(s21_memcmp(buf4, buf5, 15), memcmp(buf4, buf5, 15));
  ck_assert_int_eq(s21_memcmp(buf6, buf7, 1), memcmp(buf6, buf7, 1));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char buf1[] = "hello, im here";
  char buf2[] = "hello, im not here";
  char buf3[] = "you are here";
  char buf4[] = "you are there";
  char buf5[] = "\0";
  char dest[4096] = {0};
  ck_assert_pstr_eq(s21_memcpy(dest, buf1, 10), memcpy(dest, buf1, 10));
  ck_assert_pstr_eq(s21_memcpy(dest, buf2, 0), memcpy(dest, buf2, 0));
  ck_assert_pstr_eq(s21_memcpy(dest, buf3, 5), memcpy(dest, buf3, 5));
  ck_assert_pstr_eq(s21_memcpy(dest, buf4, 13), memcpy(dest, buf4, 13));
  ck_assert_pstr_eq(s21_memcpy(dest, buf5, 1), memcpy(dest, buf5, 1));
  ck_assert_pstr_eq(s21_memcpy(dest, buf5, 0), memcpy(dest, buf5, 0));
}
END_TEST

START_TEST(test_s21_memset) {
  char dest1[] = "hello, im here";
  char dest2[] = "123   567   890   htuj   *** ???";
  ck_assert_pstr_eq(s21_memset(dest1, '*', 10), memset(dest1, '*', 10));
  ck_assert_pstr_eq(s21_memset(dest1, '^', 4), memset(dest1, '^', 4));
  ck_assert_pstr_eq(s21_memset(dest2, '3', 5), memset(dest2, '3', 5));
  ck_assert_pstr_eq(s21_memset(dest2, 'a', 13), memset(dest2, 'a', 13));
  ck_assert_pstr_eq(s21_memset(dest2, 'a', strlen(dest2)),
                    memset(dest2, 'a', strlen(dest2)));
  ck_assert_pstr_eq(s21_memset(dest2, '\0', 0), memset(dest2, '\0', 0));
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest1[100] = "we are teamdddd   $$$###";
  char dest2[100] = "good people   123789___";
  char src1[] = "best!!!   )))/?@@";
  char src2[] = "are good    !!2345";
  char src3[] = "";
  char src4[] = "\0";
  ck_assert_pstr_eq(s21_strncat(dest1, src1, 10), strncat(dest1, src1, 10));
  ck_assert_pstr_eq(s21_strncat(dest1, src2, 1), strncat(dest1, src2, 1));
  ck_assert_pstr_eq(s21_strncat(dest2, src1, 5), strncat(dest2, src1, 5));
  ck_assert_pstr_eq(s21_strncat(dest2, src2, 13), strncat(dest2, src2, 13));
  ck_assert_pstr_eq(s21_strncat(dest2, src3, 1), strncat(dest2, src3, 1));
  ck_assert_pstr_eq(s21_strncat(dest2, src4, 1), strncat(dest2, src4, 1));
}
END_TEST

START_TEST(test_s21_strchr) {
  char str1[] = "we are teamdddd   $$$###";
  char str2[] = "good people   123789___";
  char str3[] = "";
  char str4[] = "\0";
  ck_assert_pstr_eq(s21_strrchr(str1, '$'), strrchr(str1, '$'));
  ck_assert_pstr_eq(s21_strrchr(str2, '_'), strrchr(str2, '_'));
  ck_assert_pstr_eq(s21_strrchr(str1, 'a'), strrchr(str1, 'a'));
  ck_assert_pstr_eq(s21_strrchr(str2, '5'), strrchr(str2, '5'));
  ck_assert_pstr_eq(s21_strrchr(str3, '5'), strrchr(str3, '5'));
  ck_assert_pstr_eq(s21_strrchr(str4, '5'), strrchr(str4, '5'));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char buf1[] = "hello, im here";
  char buf2[] = "hello, im not here";
  char buf3[] = "you are here";
  char buf4[] = "you are there";
  char buf5[] = "";
  char buf6[] = "\0";
  ck_assert_int_eq(s21_strncmp(buf1, buf2, 9), strncmp(buf1, buf2, 9));
  ck_assert_int_eq(s21_strncmp(buf1, buf3, 2), strncmp(buf1, buf3, 2));
  ck_assert_int_eq(s21_strncmp(buf1, buf4, 2), strncmp(buf1, buf4, 2));
  ck_assert_int_eq(s21_strncmp(buf5, buf6, 1), strncmp(buf5, buf6, 1));
  ck_assert_int_eq(s21_strncmp(buf6, buf4, 9), strncmp(buf6, buf4, 9));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char str1[] = "hello 121212\n";
  char str2[] = "world!";
  char str3[] = "gajgwyfdy44343";
  char str4[] = "world!2222";
  ck_assert_pstr_eq(strncpy(str1, str2, 10), s21_strncpy(str1, str2, 10));
  ck_assert_pstr_eq(strncpy(str3, str4, 10), s21_strncpy(str3, str4, 10));
}
END_TEST

// START_TEST(test_s21_strspn) {
//   char buf1[] = "hello, im here";
//   char buf2[] = "hello";
//   char buf3[] = "you are";
//   char buf4[] = "you are there";
//   char buf5[] = "";
//   char buf6[] = "\0";
//   ck_assert_int_eq(s21_strspn(buf1, buf2), strspn(buf1, buf2));
//   ck_assert_int_eq(s21_strspn(buf1, buf3), strspn(buf1, buf3));
//   ck_assert_int_eq(s21_strspn(buf1, buf4), strspn(buf1, buf4));
//   ck_assert_int_eq(s21_strspn(buf5, buf6), strspn(buf5, buf6));
//   ck_assert_int_eq(s21_strspn(buf6, buf4), strspn(buf6, buf4));
// }
// END_TEST

START_TEST(test_s21_strpbrk) {
  ck_assert_int_eq(strcmp(s21_strpbrk("hello every one", "ern"),
                          strpbrk("hello every one", "ern")),
                   0);
  ck_assert_int_eq(strcmp(s21_strpbrk("hello every one", "eon"),
                          strpbrk("hello every one", "eon")),
                   0);
  ck_assert_int_eq(strcmp(s21_strpbrk("hello every one", "eln"),
                          strpbrk("hello every one", "eln")),
                   0);
  ck_assert_msg(
      s21_strpbrk("hello every one", "") == strpbrk("hello every one", ""),
      "Fail1");
  ck_assert_msg(s21_strpbrk("hello every one", "rnho") ==
                    strpbrk("hello every one", "rnho"),
                "Fail2");
}
END_TEST

START_TEST(test_s21_strrchr) {
  ck_assert_str_eq((s21_strrchr("034907676934", '7')),
                   (strrchr("034907676934", '7')));
  ck_assert_msg(
      s21_strrchr("034907676934", '1') == strrchr("034907676934", '1'), "FAIL");
  ck_assert_msg(
      s21_strrchr("034907676934", 'g') == strrchr("034907676934", 'g'),
      "FAIL1");
  ck_assert_ptr_eq(s21_strrchr("hello, im here", 'e'),
                   strrchr("hello, im here", 'e'));
  ck_assert_ptr_eq(s21_strrchr("hello, im here", 'p'),
                   strrchr("hello, im here", 'p'));
  ck_assert_ptr_eq(s21_strrchr("hello, im here", ' '),
                   strrchr("hello, im here", ' '));
  ck_assert_ptr_eq(s21_strrchr("", 'f'), strrchr("", 'f'));
  ck_assert_ptr_eq(s21_strrchr("", '\0'), strrchr("", '\0'));
}
END_TEST

START_TEST(test_s21_strtok) {
  char buf2[] = "test1/test2/test3/test4";
  ck_assert_msg(s21_strtok(buf2, ",") == strtok(buf2, ","), "Fail1");
  ck_assert_msg(s21_strtok(buf2, ".,") == strtok(buf2, ".,"), "Fail2");
  ck_assert_msg(s21_strtok(buf2, "/.,") == strtok(buf2, "/.,"), "Fail3");
  char str[100] = "Hello hello Hello";
  char str1[100] = "Hello";
  char str2[100] = "12341234124";
  ck_assert_pstr_eq(strtok(str, str1), s21_strtok(str, str1));
  ck_assert_pstr_eq(strtok(str, "\0"), s21_strtok(str, "\0"));
  ck_assert_pstr_eq(strtok(str, "l"), s21_strtok(str, "l"));
  ck_assert_pstr_eq(strtok(str, "A"), s21_strtok(str, "A"));
  ck_assert_pstr_eq(strtok(str2, "12"), s21_strtok(str2, "12"));
  ck_assert_pstr_eq(strtok("69917020", "6998"), s21_strtok("69917020", "6998"));
  ck_assert_pstr_eq(strtok(str, " "), s21_strtok(str, " "));
}
END_TEST

START_TEST(test_s21_strstr) {
  ck_assert_str_eq(s21_strstr("Hello", ""), strstr("Hello", ""));
  ck_assert_pstr_eq(strstr("Hello hello Hello", "Hello"),
                    strstr("Hello hello Hello", "Hello"));
  ck_assert_pstr_eq(strstr("Hello hello Hello", "\0"),
                    strstr("Hello hello Hello", "\0"));
  ck_assert_pstr_eq(strstr("Hello hello Hello", "l"),
                    strstr("Hello hello Hello", "l"));
  ck_assert_pstr_eq(strstr("Hello hello Hello", "A"),
                    strstr("Hello hello Hello", "A"));
  ck_assert_msg(s21_strstr("Hello", "") == strstr("Hello", ""), "Fail1");
  ck_assert_msg(s21_strstr("Hello", "He") == strstr("Hello", "He"), "Fail2");
  ck_assert_msg(s21_strstr("Hello", "yu") == strstr("Hello", "yu"), "Fail3");
}
END_TEST

START_TEST(test_s21_strlen) {
  ck_assert_int_eq(s21_strlen("Hello"), strlen("Hello"));
  ck_assert_int_eq(s21_strlen("1234567"), strlen("1234567"));
  ck_assert_int_eq(s21_strlen("123/74"), strlen("123/74"));
  ck_assert_int_eq(s21_strlen("hello/you"), strlen("hello/you"));
  ck_assert_int_eq(s21_strlen(" "), strlen(" "));
  ck_assert_int_eq(s21_strlen("hihi.hi"), strlen("hihi.hi"));
  ck_assert_int_eq(s21_strlen("\n"), strlen("\n"));
}
END_TEST

START_TEST(test_s21_strcspn) {
  ck_assert_int_eq(strcspn("4236589710", "4081"),
                   s21_strcspn("4236589710", "4081"));
  ck_assert_int_eq(strcspn("42/365/89/71/0", "123"),
                   s21_strcspn("42/365/89/71/0", "123"));
  ck_assert_int_eq(strcspn("1234567890", "0/"),
                   s21_strcspn("1234567890", "0/"));
  ck_assert_int_eq(strcspn("12-34-56-78-90", "\\%%*#"),
                   s21_strcspn("12-34-56-78-90", "\\%%*#"));
  ck_assert_int_eq(strcspn("12-34-56-78-90", " "),
                   s21_strcspn("12-34-56-78-90", " "));
  ck_assert_int_eq(strcspn("", ""), s21_strcspn("", ""));
}
END_TEST

START_TEST(strerror_1) {
  for (int i = 0; i < 150; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(strerror_2) {
  int n = -1;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST

// SPRINF

START_TEST(test_s21_sprintf_s) {
  // 1
  char str9[BUFSIZ];
  char str10[BUFSIZ];
  char *format = "%s";
  char *vall = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str9, format, vall),
                   sprintf(str10, format, vall));
  ck_assert_str_eq(str9, str10);
  // 2
  char str1[100] = "";
  char str2[100] = "";
  char *str7 = "test %s best";
  char *lav = "Why are you here?!";
  ck_assert_int_eq(sprintf(str1, str7, lav), s21_sprintf(str2, str7, lav));
  ck_assert_pstr_eq(str1, str2);
  // 3
  char str3[100];
  char str4[100];
  char *str5 = "%s test %s best %s";
  char *val1 = "I'm so tired";
  char *val2 = "Who tested this?";
  char *val3 = "This project name is hemmoroids";
  ck_assert_int_eq(sprintf(str3, str5, val1, val2, val3),
                   s21_sprintf(str4, str5, val1, val2, val3));
  ck_assert_pstr_eq(str3, str4);
  // 4
  char *val11 = "Don't need this test";
  char *val22 = "Just for the kicks";
  char *val33 = "Lol";
  ck_assert_int_eq(sprintf(str3, str5, val11, val22, val33),
                   s21_sprintf(str4, str5, val11, val22, val33));
  ck_assert_pstr_eq(str3, str4);
}
END_TEST

// INSERT

START_TEST(test_insert1) {
  char str[] = "Hellopals";
  char insert[] = " ";
  int index = 5;
  char *got = s21_insert(str, insert, index);
  ck_assert_str_eq(("Hello pals"), got);
  if (got) free(got);
}
END_TEST

START_TEST(test_insert2) {
  char str[] = "123";
  char insert[] = "t";
  int index = 3;
  char *got = s21_insert(str, insert, index);
  ck_assert_str_eq(("123t"), got);
  if (got) free(got);
}
END_TEST

START_TEST(test_insert3) {
  char str[] = "123";
  char insert[] = "t";
  int index = 0;
  char *got = s21_insert(str, insert, index);
  ck_assert_str_eq(("t123"), got);
  if (got) free(got);
}
END_TEST

START_TEST(test_insert4) {
  char str[] = "\0";
  char insert[] = " ";
  int index = 5;
  char *got = s21_insert(str, insert, index);
  ck_assert_ptr_null(got);
  if (got) free(got);
}
END_TEST

START_TEST(test_insert5) {
  char str[] = "123";
  char insert[] = " ";
  int index = 4;
  char *got = s21_insert(str, insert, index);
  ck_assert_ptr_null(got);
  if (got) free(got);
}
END_TEST

START_TEST(test_insert6) {
  char str[] = "123";
  int index = 5;
  char *got = s21_insert(str, NULL, index);
  ck_assert_ptr_null(got);
  if (got) free(got);
}
END_TEST

START_TEST(test_insert7) {
  char insert[] = " ";
  int index = 5;
  char *got = s21_insert(NULL, insert, index);
  ck_assert_ptr_null(got);
  if (got) free(got);
}
END_TEST

START_TEST(test_insert8) {
  int index = 5;
  char *got = s21_insert(NULL, NULL, index);
  ck_assert_ptr_null(got);
  if (got) free(got);
}
END_TEST

// UPPER

START_TEST(test_upper1) {
  char str1[] = "hello, world!";
  char *str2 = (char *)s21_to_upper(str1);
  ck_assert_pstr_eq(str2, "HELLO, WORLD!");
  if (str2) free(str2);
}
END_TEST

START_TEST(test_upper2) {
  char str1[] = "you are number 1!";
  char *str2 = (char *)s21_to_upper(str1);
  ck_assert_pstr_eq(str2, "YOU ARE NUMBER 1!");
  if (str2) free(str2);
}
END_TEST

START_TEST(test_upper3) {
  char str_1[] = "best team!";
  char *str_s21 = (char *)s21_to_upper(str_1);
  char *exp = "BEST TEAM!";
  ck_assert_str_eq(str_s21, exp);
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(test_upper4) {
  char str_1[] = "bEsT tEAm!9821";
  char *str_s21 = (char *)s21_to_upper(str_1);
  char *exp = "BEST TEAM!9821";
  ck_assert_str_eq(str_s21, exp);
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(test_upper5) {
  char str_1[] = "";
  char *str_s21 = (char *)s21_to_upper(str_1);
  char *exp = "";
  ck_assert_str_eq(str_s21, exp);
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(test_upper6) {
  char str[] = " ";
  char expected[] = " ";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(test_upper7) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(test_upper8) {
  char str_1[] = ",.?!-_7891355";
  char *str_s21 = (char *)s21_to_upper(str_1);
  char *exp = ",.?!-_7891355";
  ck_assert_str_eq(str_s21, exp);
  if (str_s21) free(str_s21);
}
END_TEST

// TRIM

START_TEST(test_trim1) {
  char str[] = "123qwe123";
  char chars_to_trim[] = "123";
  char *got = s21_trim(str, chars_to_trim);
  ck_assert_str_eq(("qwe"), got);
  if (got) free(got);
}
END_TEST

START_TEST(test_trim2) {
  char str[] = "123qwe";
  char chars_to_trim[] = "123";
  char *got = s21_trim(str, chars_to_trim);
  ck_assert_str_eq(("qwe"), got);
  if (got) free(got);
}
END_TEST

START_TEST(test_trim3) {
  char str[] = "qwe123";
  char chars_to_trim[] = "123";
  char *got = s21_trim(str, chars_to_trim);
  ck_assert_str_eq(("qwe"), got);
  if (got) free(got);
}
END_TEST

START_TEST(test_trim4) {
  char str[] = "123qwe123";
  char chars_to_trim[] = "\0";
  char *got = s21_trim(str, chars_to_trim);
  ck_assert_str_eq(("123qwe123"), got);
  if (got) free(got);
}
END_TEST

// LOWER

START_TEST(test_lower1) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(test_lower2) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(test_lower3) {
  char str1[] = "hEllO, WoRLD!";
  char *str2 = (char *)s21_to_lower(str1);
  ck_assert_pstr_eq(str2, "hello, world!");
  if (str2) free(str2);
}
END_TEST

START_TEST(test_lower4) {
  char str1[] = "YOU ARE NUMBER 1!";
  char *str2 = (char *)s21_to_lower(str1);
  ck_assert_pstr_eq(str2, "you are number 1!");
  if (str2) free(str2);
}
END_TEST

START_TEST(test_lower5) {
  char str_1[] = "RAISE OF EVOLUTION!";
  char *str_s21 = (char *)s21_to_lower(str_1);
  char *exp = "raise of evolution!";
  ck_assert_str_eq(str_s21, exp);
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(test_lower6) {
  char str_1[] = "rAiSe OF evoLuTion! 98127634";
  char *str_s21 = (char *)s21_to_lower(str_1);
  char *exp = "raise of evolution! 98127634";
  ck_assert_str_eq(str_s21, exp);
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(test_lower7) {
  char str_1[] = ",.?!-_7891355";
  char *str_s21 = (char *)s21_to_lower(str_1);
  char *exp = ",.?!-_7891355";
  ck_assert_str_eq(str_s21, exp);
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(test_lower8) {
  char str_1[] = "";
  char *str_s21 = (char *)s21_to_lower(str_1);
  char *exp = "";
  ck_assert_str_eq(str_s21, exp);
  if (str_s21) free(str_s21);
}
END_TEST

START_TEST(test_sprintf_c) {
  // 1
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 9;
  int b = 10;
  int cc = 17;
  int d = 66;
  int e = 124;
  ck_assert_int_eq(sprintf(str1, str3, a, b, cc, d, e),
                   s21_sprintf(str2, str3, a, b, cc, d, e));
  ck_assert_pstr_eq(str1, str2);

  // 2
  char str4[100];
  char str5[100];
  char *str6 = "%6.4c Test %-6.4c Test %4.10lc Test %-4.10lc Test %-0lc";
  int a1 = -10;
  unsigned long int b1 = 10;
  unsigned long int c1 = 10;
  ck_assert_int_eq(sprintf(str4, str6, a1, a1, b1, c1, c1),
                   s21_sprintf(str5, str6, a1, a1, b1, c1, c1));
  ck_assert_pstr_eq(str4, str5);

  // 3
  char c[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  char dest[100];
  char s21_dest[100];

  for (int i = 0; i < 10; i++) {
    int s = sprintf(dest, "%c", c[i]);
    int s21 = s21_sprintf(s21_dest, "%c", c[i]);
    ck_assert_msg(s == s21, "s = %d, s21 = %d, c = %c", s, s21, c[i]);
    ck_assert_msg(strcmp(dest, s21_dest) == 0,
                  "dest = %s, s21_dest = %s, c = %c", dest, s21_dest, c[i]);
  }

  // 4
  ck_assert_int_eq(s21_sprintf(str1, "Watsp school %c %lc", '2', '&'),
                   sprintf(str2, "Watsp school %c %lc", '2', '&'));
  ck_assert_int_eq(s21_sprintf(str1, "Watsp school %-c %c %%%%", '2', '1'),
                   sprintf(str2, "Watsp school %-c %c %%%%", '2', '1'));
  ck_assert_int_eq(s21_sprintf(str1, "Watsp school %20c %-10lc", '2', 0x61),
                   sprintf(str2, "Watsp school %20c %-10lc", '2', 0x61));
  ck_assert_int_eq(s21_sprintf(str1, "Watsp school %-c %c", '2', '1'),
                   sprintf(str2, "Watsp school %-c %c", '2', '1'));

  // 5
  char str13[400];
  char str14[400];
  char *str15 = "%70c Test %-90c Test %080c Test %-065c Test %- 60c";
  int a3 = 255;
  ck_assert_int_eq(sprintf(str13, str15, a3, a3, a3, a3, a3),
                   s21_sprintf(str14, str15, a3, a3, a3, a3, a3));
}
END_TEST

START_TEST(test_sprintf_d) {
  // 1
  char str1[100];
  char str2[100];
  char *str3 = "%ld Test %ld Test %hd GOD %hd";
  long int val = 3088675747373646;
  long val2 = 33030030303;
  short int val3 = 22600;
  short val4 = -120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
  // 2
  char str4[100];
  char str5[100];
  char *str6 = "%3d Test %5d Test %10d";
  int v = -3015;
  int v2 = -11234;
  int v3 = -99;
  ck_assert_int_eq(sprintf(str4, str6, v, v2, v3),
                   s21_sprintf(str5, str6, v, v2, v3));
  ck_assert_pstr_eq(str4, str5);
  // 3
  char str7[200];
  char str8[200];
  char *str9 = "%0d Test %0.d Test %0.0d TEST %0d GOD %.d";
  int va = -3015;
  int va2 = -712;
  int va3 = -99;
  int va4 = -2939;
  int va5 = -0123;
  ck_assert_int_eq(sprintf(str7, str9, va, va2, va3, va4, va5),
                   s21_sprintf(str8, str9, va, va2, va3, va4, va5));
  ck_assert_pstr_eq(str7, str8);
  // 4
  char str10[200];
  char str11[200];
  char *str12 = "%*d Test %-*d Test %*.*d TEST %.*d";
  int val8 = 32;
  int val5 = 8899;
  int val6 = -919;
  int val7 = 32311;
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(sprintf(str10, str12, ast, val8, ast2, val5, ast3, ast4,
                           val6, ast5, val7),
                   s21_sprintf(str11, str12, ast, val8, ast2, val5, ast3, ast4,
                               val6, ast5, val7));
  ck_assert_pstr_eq(str10, str11);
  // 5
  char str13[200];
  char str14[200];
  char *str15 = "%#d Test %#3d Test %#5.7d TEST %#.7d Oof %#.d";
  int l = -32;
  int l2 = 8899;
  int l3 = -91918;
  int l4 = 32311;
  int l5 = -8894;
  ck_assert_int_eq(sprintf(str13, str15, l, l2, l3, l4, l5),
                   s21_sprintf(str14, str15, l, l2, l3, l4, l5));
  ck_assert_pstr_eq(str13, str14);
}
END_TEST

START_TEST(test_sprintf_e) {
  // 1
  char str1[300];
  char str2[300];
  char *str3 = "New test: %020e\nSecond test: %020.e!";
  double num = -5921563224775967.;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
  // 2

  char str7[300];
  char str8[300];
  char *str9 = "Fifth test: %020.2e\nSixth test: %020.1e!";
  double num3 = -592156322477596.;
  ck_assert_int_eq(sprintf(str7, str9, num3, num3),
                   s21_sprintf(str8, str9, num3, num3));
  // 4
  char str10[300];
  char str11[300];
  char *str12 = "New test: % 20e\nSecond test: % 20.5e!";
  double num4 = -592156322477596.;
  ck_assert_int_eq(sprintf(str10, str12, num4, num4),
                   s21_sprintf(str11, str12, num4, num4));
  ck_assert_pstr_eq(str10, str11);
  // 5
  char str13[300];
  char str14[300];
  char *str15 = "New test: % 31e\nSecond test: % 30.5e!";
  double num5 = -592156322477596.;
  ck_assert_int_eq(sprintf(str13, str15, num5, num5),
                   s21_sprintf(str14, str15, num5, num5));
  ck_assert_pstr_eq(str13, str14);
}
END_TEST

START_TEST(test_sprintf_f) {
  // 1
  char str1[400];
  char str2[400];
  char *str3 = "%Lf\n%.Lf!";
  long double num_long = -76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num_long, num_long),
                   s21_sprintf(str2, str3, num_long, num_long));
  ck_assert_pstr_eq(str1, str2);
  // 2
  char str4[400];
  char str5[400];
  char *str6 = "test: %5f\ntest: %6.1f\ntest: %8.2f!";
  double num1 = 76.756589;
  ck_assert_int_eq(sprintf(str4, str6, num1, num1, num1),
                   s21_sprintf(str5, str6, num1, num1, num1));
  ck_assert_pstr_eq(str4, str5);
  // 3
  char str7[400];
  char str8[400];
  char *str9 = "test: %10.4f\ntest: %25.5f!";
  double num2 = -7648938790.756589;
  ck_assert_int_eq(sprintf(str7, str9, num2, num2),
                   s21_sprintf(str8, str9, num2, num2));
  ck_assert_pstr_eq(str7, str8);
  // 4
  char str10[400];
  char str11[400];
  char *str12 = "test: %-26.1f\ntest: %-18.0f\ntest: %#-10.f!";
  double num3 = 7648938790.756589;
  ck_assert_int_eq(sprintf(str10, str12, num3, num3, num3),
                   s21_sprintf(str11, str12, num3, num3, num3));
  ck_assert_pstr_eq(str10, str11);
  // 5
  char str13[400];
  char str14[400];
  char *str15 = "test: %#-10.9f!\ntest: %-+25.15f!";
  double num4 = -365289.3462865487;
  ck_assert_int_eq(sprintf(str13, str15, num4, num4),
                   s21_sprintf(str14, str15, num4, num4));
  ck_assert_pstr_eq(str13, str14);
}
END_TEST

START_TEST(test_g_printf) {
  char buf_for_sprintf[70];
  char buf_for_s21_sprintf[70];
  double x1 = 123.2341;
  double x2 = -0.341;
  char *format_string1 = "love % g %10g love";
  ck_assert_int_eq(s21_sprintf(buf_for_s21_sprintf, format_string1, x1, x2),
                   sprintf(buf_for_sprintf, format_string1, x1, x2));
  ck_assert_str_eq(buf_for_sprintf, buf_for_s21_sprintf);

  long double x3 = 12345.2341;
  long double x4 = -0.00000341;
  char *format_string2 = "love %+.2Lg %10.LG love";
  ck_assert_int_eq(s21_sprintf(buf_for_s21_sprintf, format_string2, x3, x4),
                   sprintf(buf_for_sprintf, format_string2, x3, x4));
  ck_assert_str_eq(buf_for_sprintf, buf_for_s21_sprintf);

  double x5 = -12345;
  double x6 = 0.23453;
  char *format_string3 = "love %#g %-10g love";
  ck_assert_int_eq(s21_sprintf(buf_for_s21_sprintf, format_string3, x5, x6),
                   sprintf(buf_for_sprintf, format_string3, x5, x6));
  ck_assert_str_eq(buf_for_sprintf, buf_for_s21_sprintf);

  memset(buf_for_sprintf, ' ', 40);
  memset(buf_for_s21_sprintf, ' ', 40);
}

END_TEST

START_TEST(test_sprintf_g) {
  // 1
  char str1[200];
  char str2[200];
  char *str3 = "%25.18g TEST\n%.6g TEST\n";
  double num = 838.65400000;
  double num1 = 640.783289182;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));

  // 2
  char str10[400];
  char str11[400];
  char *str12 = "test: %#-10.g\ntest: %-+25.g!";
  double n1 = -7648938790.756589;
  ck_assert_int_eq(sprintf(str10, str12, n1, n1),
                   s21_sprintf(str11, str12, n1, n1));

  // 3
  char str7[200];
  char str8[200];
  char *str9 = "%g TEST %.0g TEST %4.2g TEST %4.g TEST %5.10g!";
  double m = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(str7, str9, m, m, m, m, m),
                   s21_sprintf(str8, str9, m, m, m, m, m));
  // 4
  char dest[100];
  char s21_dest[100];
  char *str5 = "%G TEST\n";
  double num3 = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(dest, str5, num3),
                   s21_sprintf(s21_dest, str5, num3));
}
END_TEST

START_TEST(test_sprintf_i) {
  // 1
  char str1[100];
  char str2[100];
  char *str3 = "%i Test %i Test %i";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
  // 2
  char str4[100];
  char str5[100];
  char *str6 = "%3i Test %5i Test %10i";
  int val4 = -3015;
  int val5 = -11234;
  int val6 = -99;
  ck_assert_int_eq(sprintf(str4, str6, val4, val5, val6),
                   s21_sprintf(str5, str6, val4, val5, val6));
  ck_assert_pstr_eq(str4, str5);
  // 3
  char str7[200];
  char str8[200];
  char *str9 = "%0i Test %0.i Test %0.0i TEST %0i GOD %.i";
  int val7 = -3015;
  int val8 = -712;
  int val9 = -99;
  int val10 = -2939;
  int val11 = -0123;
  ck_assert_int_eq(sprintf(str7, str9, val7, val8, val9, val10, val11),
                   s21_sprintf(str8, str9, val7, val8, val9, val10, val11));
  ck_assert_pstr_eq(str7, str8);
  // 4
  char str13[200];
  char str14[200];
  char *str15 = "%0d Test %06i Test %05.7i TEST %0.7i Oof %0.i";
  int val12 = -32;
  int val13 = 8899;
  int val14 = -91918;
  int val15 = -32311;
  int val16 = -8894;
  ck_assert_int_eq(
      sprintf(str13, str15, val12, val13, val14, val15, val16),
      s21_sprintf(str14, str15, val12, val13, val14, val15, val16));
  ck_assert_pstr_eq(str13, str14);
}
END_TEST

START_TEST(test_sprintf_n) {
  // 1
  char str1[100];
  char str2[100];
  char *str3 = "Test %o T%nest %o%n";
  int val = 012;
  int val2 = 017;
  int valn1 = 0, valn2 = 0, valn3 = 0, valn4 = 0;
  ck_assert_int_eq(sprintf(str1, str3, val, &valn1, val2, &valn3),
                   s21_sprintf(str2, str3, val, &valn2, val2, &valn4));
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(valn1, valn2);
  ck_assert_int_eq(valn3, valn4);
  // 2
  char str4[100] = "";
  char str5[100] = "";
  char *str6 = "Test %n Test";
  int vall1 = 0, vall2 = 0;
  ck_assert_int_eq(sprintf(str4, str6, &vall1),
                   s21_sprintf(str5, str6, &vall2));
  ck_assert_pstr_eq(str4, str5);
}
END_TEST

START_TEST(test_sprintf_o) {
  // 1
  char str1[100];
  char str2[100];
  char *str3 = "%o Test %o Test %o";
  int valn = 3015;
  int valn2 = 712;
  int valn3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, valn, valn2, valn3),
                   s21_sprintf(str2, str3, valn, valn2, valn3));
  ck_assert_pstr_eq(str1, str2);
  // 2
  char *format = "%o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, 0));
  ck_assert_str_eq(str1, str2);
  // 3
  char *format1 = "%#o";
  int val = 57175;
  ck_assert_int_eq(s21_sprintf(str1, format1, val),
                   sprintf(str2, format1, val));

  ck_assert_str_eq(str1, str2);
  // 4
  char *format2 = "%lo, %o, %ho, %.5o, %5.o";
  long int val1 = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format2, val1, 14, 1441, 14414, 9681),
      sprintf(str2, format2, val1, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sprintf_percent) {
  // 1
  char str1[100];
  char str2[100];
  char *str3 = "%o Te%%st %o Test %o";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
  // 2
  char str4[100];
  char str5[100];
  char *str6 = "Test %o Tes%%%%t %o";
  int v = 012;
  int v2 = 017;
  ck_assert_int_eq(sprintf(str4, str6, v, v2), s21_sprintf(str5, str6, v, v2));
  ck_assert_pstr_eq(str4, str5);
}
END_TEST

START_TEST(test_sprintf_pointer) {
  // 1
  char str4[200];
  char str5[200];
  char *str6 = "%p Test %3p Test %5.7p TEST %.7p Oof %#.p";
  char *l = "32";
  char *l2 = "8899";
  char *l3 = "91918";
  char *l4 = "32311";
  char *l5 = "8894";
  ck_assert_int_eq(sprintf(str4, str6, l, l2, l3, l4, l5),
                   s21_sprintf(str5, str6, l, l2, l3, l4, l5));
  ck_assert_pstr_eq(str4, str5);
  // 2
  char str10[200];
  char str11[200];
  char *str12 = "%0p Test %0.p Test %0.0p TEST %0p GOD %.p";
  char *s = "3015";
  char *s2 = "712";
  char *s3 = "99";
  char *s4 = "2939";
  char *s5 = "0123";
  ck_assert_int_eq(sprintf(str10, str12, s, s2, s3, s4, s5),
                   s21_sprintf(str11, str12, s, s2, s3, s4, s5));
  ck_assert_pstr_eq(str10, str11);
}
END_TEST

START_TEST(test_sprintf_x1) {
  // 1
  char str1[200];
  char str2[200];
  char *format = "%5x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));
  ck_assert_str_eq(str1, str2);
  // 2
  int arr1[] = {0, -1, 1, 123, 1234, -1383, 9387};
  char str[80];
  char str111[80];
  int res = s21_sprintf(str, "%x", arr1[0]);
  int res1 = sprintf(str111, "%x", arr1[0]);
  ck_assert_uint_eq((unsigned long)*str, (unsigned long)*str111);
  ck_assert_int_eq(res, res1);
  // 3
  int arr2[] = {0, -1, 1, 123, 1234, -1383, 9387};
  char str7[100];
  char str8[100];
  s21_sprintf(str7, "%-#10.3x", arr2[0]);
  sprintf(str8, "%-#10.3x", arr2[0]);
  ck_assert_uint_eq((unsigned long)*str7, (unsigned long)*str8);

  // 4
  int val1[] = {-100, -10, 0, 1, 10, 21474836, 21474836, 429496729};
  char dest[100];
  char s21_dest[100];
  for (int i = 0; i < 8; i++) {
    int s = sprintf(dest, "%x", val1[i]);
    int s21 = s21_sprintf(s21_dest, "%x", val1[i]);
    ck_assert_msg(s == s21, "s = %d, s21 = %d, val = %x", s, s21, val1[i]);
    ck_assert_msg(strcmp(dest, s21_dest) == 0,
                  "dest = %s, s21_dest = %s, val = %x", dest, s21_dest,
                  val1[i]);
  }
  // 5
  char dest1[100];
  char s21_dest1[100];
  for (int i = 0; i < 8; i++) {
    int s1 = sprintf(dest1, "%-x", val1[i]);
    int s211 = s21_sprintf(s21_dest1, "%-x", val1[i]);
    ck_assert_msg(s1 == s211, "s = %d, s21 = %d, val = %x", s1, s211, val1[i]);
    ck_assert_msg(strcmp(dest1, s21_dest1) == 0,
                  "dest = %s, s21_dest = %s, val = %x", dest1, s21_dest1,
                  val1[i]);
  }
}
END_TEST

START_TEST(test_sprintf_x2) {
  // 1
  char str1[100];
  char str2[100];
  char *str3 = "%X Test %X Test %X";
  int val = 0X7a4;
  int val2 = 0X9112312f;
  int val3 = 0X3123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
  // 2
  char str4[100];
  char str5[100];
  char *str6 = "%lX Test %lX Test %hX GOD %hX";
  unsigned long int v = 3088675747373646;
  unsigned long int v2 = 33030030303;
  unsigned short int v3 = 22600;
  unsigned short v4 = 120;
  ck_assert_int_eq(sprintf(str4, str6, v, v2, v3, v4),
                   s21_sprintf(str5, str6, v, v2, v3, v4));
  ck_assert_pstr_eq(str4, str5);
  // 3
  int val1[] = {-100, -10, 0, 1, 10, 21474836, 21474836, 429496729};
  char dest[100];
  char s21_dest[100];
  for (int i = 0; i < 8; i++) {
    int s = sprintf(dest, "%X", val1[i]);
    int s21 = s21_sprintf(s21_dest, "%X", val1[i]);
    ck_assert_msg(s == s21, "s = %d, s21 = %d, val = %x", s, s21, val1[i]);
    ck_assert_msg(strcmp(dest, s21_dest) == 0,
                  "dest = %s, s21_dest = %s, val = %x", dest, s21_dest,
                  val1[i]);
  }
  // 4
  int valb[] = {-100, -10, 0, 1, 10, 21474836, 21474836, 429496729};
  char best[100];
  char s21_best[100];
  for (int i = 0; i < 8; i++) {
    int sb = sprintf(best, "%-X", valb[i]);
    int s21b = s21_sprintf(s21_best, "%-X", valb[i]);
    ck_assert_msg(sb == s21b, "s = %d, s21 = %d, val = %x", sb, s21b, valb[i]);
    ck_assert_msg(strcmp(best, s21_best) == 0,
                  "dest = %s, s21_dest = %s, val = %x", best, s21_best,
                  valb[i]);
  }
}

START_TEST(test_sprintf_u) {
  // 1
  char str1[100];
  char str2[100];
  char *str3 = "%u Test %u Test %u";
  unsigned int val = 012;
  unsigned int val2 = 017;
  unsigned int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
  // 2
  char str4[100];
  char str5[100];
  char *str6 = "%u Test %u Test %u";
  unsigned int l = 3015;
  unsigned int l2 = 712;
  unsigned int l3 = 99;
  ck_assert_int_eq(sprintf(str4, str6, l, l2, l3),
                   s21_sprintf(str5, str6, l, l2, l3));
  ck_assert_pstr_eq(str4, str5);
  // 3
  char str7[200];
  char str8[200];
  char *str9 = "%6.5u Test %.23u Test %3.u TEST %.u";
  unsigned int valn = 3015;
  unsigned int valn2 = 712;
  unsigned int valn3 = 99;
  unsigned int valn4 = 38;
  ck_assert_int_eq(sprintf(str7, str9, valn, valn2, valn3, valn4),
                   s21_sprintf(str8, str9, valn, valn2, valn3, valn4));
  ck_assert_pstr_eq(str7, str8);
  // 4
  char str10[200];
  char str11[200];
  char *str12 = "%0u Test %0.u Test %0.0u TEST %0u GOD %.u";
  unsigned int vall = 3015;
  unsigned int vall2 = 712;
  unsigned int vall3 = 99;
  unsigned int vall4 = 2939;
  unsigned int vall5 = 0123;
  ck_assert_int_eq(sprintf(str10, str12, vall, vall2, vall3, vall4, vall5),
                   s21_sprintf(str11, str12, vall, vall2, vall3, vall4, vall5));
  ck_assert_pstr_eq(str10, str11);
  // 5
  char str13[200];
  char str14[200];
  char *str15 = "%+u Test %+3.u Test %+5.7u TEST %+10u GOD %+.u";
  unsigned int k = 32;
  unsigned int k2 = 8899;
  unsigned int k3 = 91918;
  unsigned int k4 = 32311;
  unsigned int k5 = 3261;
  ck_assert_int_eq(sprintf(str13, str15, k, k2, k3, k4, k5),
                   s21_sprintf(str14, str15, k, k2, k3, k4, k5));
  ck_assert_pstr_eq(str13, str14);
}
END_TEST

// Функция создания набора тестов.
Suite *example_suite_create(void) {
  Suite *suite = suite_create("Example");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("Core of example");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, test_s21_memchr);
  tcase_add_test(tcase_core, test_s21_memcmp);
  tcase_add_test(tcase_core, test_s21_memcpy);
  tcase_add_test(tcase_core, test_s21_memset);
  tcase_add_test(tcase_core, test_s21_strncat);
  tcase_add_test(tcase_core, test_s21_strchr);
  tcase_add_test(tcase_core, test_s21_strncmp);
  tcase_add_test(tcase_core, test_s21_strncpy);
  // tcase_add_test(tcase_core, test_s21_strspn);
  tcase_add_test(tcase_core, test_s21_strpbrk);
  tcase_add_test(tcase_core, test_s21_strrchr);
  tcase_add_test(tcase_core, test_s21_strtok);
  tcase_add_test(tcase_core, test_s21_strstr);
  tcase_add_test(tcase_core, test_s21_strlen);
  tcase_add_test(tcase_core, test_s21_strcspn);
  tcase_add_test(tcase_core, test_s21_sprintf_s);
  tcase_add_test(tcase_core, test_insert1);
  tcase_add_test(tcase_core, test_insert2);
  tcase_add_test(tcase_core, test_insert3);
  tcase_add_test(tcase_core, test_insert4);
  tcase_add_test(tcase_core, test_insert5);
  tcase_add_test(tcase_core, test_insert6);
  tcase_add_test(tcase_core, test_insert7);
  tcase_add_test(tcase_core, test_insert8);
  tcase_add_test(tcase_core, test_upper1);
  tcase_add_test(tcase_core, test_upper2);
  tcase_add_test(tcase_core, test_upper3);
  tcase_add_test(tcase_core, test_upper4);
  tcase_add_test(tcase_core, test_upper5);
  tcase_add_test(tcase_core, test_upper6);
  tcase_add_test(tcase_core, test_upper7);
  tcase_add_test(tcase_core, test_upper8);
  tcase_add_test(tcase_core, test_trim1);
  tcase_add_test(tcase_core, test_trim2);
  tcase_add_test(tcase_core, test_trim3);
  tcase_add_test(tcase_core, test_trim4);
  tcase_add_test(tcase_core, test_lower1);
  tcase_add_test(tcase_core, test_lower2);
  tcase_add_test(tcase_core, test_lower3);
  tcase_add_test(tcase_core, test_lower4);
  tcase_add_test(tcase_core, test_lower5);
  tcase_add_test(tcase_core, test_lower6);
  tcase_add_test(tcase_core, test_lower7);
  tcase_add_test(tcase_core, test_lower8);
  tcase_add_test(tcase_core, strerror_1);
  tcase_add_test(tcase_core, strerror_2);
  tcase_add_test(tcase_core, test_sprintf_c);
  tcase_add_test(tcase_core, test_sprintf_d);
  tcase_add_test(tcase_core, test_sprintf_e);
  tcase_add_test(tcase_core, test_sprintf_f);
  tcase_add_test(tcase_core, test_sprintf_g);
  tcase_add_test(tcase_core, test_sprintf_i);
  tcase_add_test(tcase_core, test_sprintf_n);
  tcase_add_test(tcase_core, test_sprintf_o);
  tcase_add_test(tcase_core, test_sprintf_percent);
  tcase_add_test(tcase_core, test_sprintf_pointer);
  tcase_add_test(tcase_core, test_sprintf_x1);
  tcase_add_test(tcase_core, test_sprintf_x2);
  tcase_add_test(tcase_core, test_sprintf_u);
  tcase_add_test(tcase_core, test_g_printf);
  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  int fail = 0;
  Suite *suite = example_suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  // Получаем количество проваленных тестов.
  fail = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  // Сигнализируем о том, что тестирование прошло неудачно.
  return (fail != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
