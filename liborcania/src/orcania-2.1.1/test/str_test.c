/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <check.h>
#include "orcania.h"

START_TEST(test_str_replace)
{
  char * str = "abcdeffedcba", * old_1 = "cd", * new_1 = "gh", * old_2 = "f", * target;
  target = str_replace(str, old_1, new_1);
  ck_assert_str_eq(target, "abgheffedcba");
  ck_assert_ptr_eq(str_replace(NULL, old_1, new_1), NULL);
  ck_assert_ptr_eq(str_replace(str, NULL, new_1), NULL);
  ck_assert_ptr_eq(str_replace(str, old_1, NULL), NULL);
  o_free(target);
  target = str_replace(str, old_2, new_1);
  ck_assert_str_eq(target, "abcdeghghedcba");
  o_free(target);
  target = str_replace(str, str, "");
  ck_assert_str_eq(target, "");
  o_free(target);
}
END_TEST

START_TEST(test_o_strdup)
{
  char * str = "abcdeffedcba", * target;
  target = o_strdup(str);
  ck_assert_str_eq(target, str);
  o_free(target);
  ck_assert_ptr_eq(o_strdup(NULL), NULL);
}
END_TEST

START_TEST(test_o_strndup)
{
  char * str = "abcdeffedcba", * target;
  target = o_strndup(str, strlen(str));
  ck_assert_str_eq(target, str);
  o_free(target);
  target = o_strndup(str, strlen(str)-2);
  ck_assert_str_eq(target, "abcdeffedc");
  o_free(target);
  ck_assert_ptr_eq(o_strndup(NULL, 12), NULL);
  target = o_strndup("abcdeffedc", 0);
  ck_assert_ptr_ne(target, NULL);
  o_free(target);
}
END_TEST

START_TEST(test_o_strcmp)
{
  char * str_1 = "abcdeffedcba", * str_2 = "bob", * str_3 = "abcdeffedcba";
  ck_assert_int_eq(o_strcmp(str_1, str_3), 0);
  ck_assert_int_ne(o_strcmp(str_1, str_2), 0);
  ck_assert_int_ne(o_strcmp(str_1, NULL), 0);
  ck_assert_int_ne(o_strcmp(NULL, str_1), 0);
  ck_assert_int_eq(o_strcmp(NULL, NULL), 0);
}
END_TEST

START_TEST(test_o_strncmp)
{
  char * str_1 = "abcdeffedcba", * str_2 = "abc", * str_3 = "abcdeffedcba";
  ck_assert_int_eq(o_strncmp(str_1, str_3, strlen(str_3)), 0);
  ck_assert_int_eq(o_strncmp(str_1, str_2, strlen(str_2)), 0);
  ck_assert_int_ne(o_strncmp(str_1, str_2, strlen(str_1)), 0);
  ck_assert_int_ne(o_strncmp(str_1, NULL, strlen(str_1)), 0);
  ck_assert_int_ne(o_strncmp(NULL, str_1, strlen(str_1)), 0);
  ck_assert_int_eq(o_strncmp(NULL, NULL, 0), 0);
  ck_assert_int_eq(o_strncmp(NULL, NULL, 1), 0);
}
END_TEST

START_TEST(test_o_strcasecmp)
{
  char * str_1 = "abcdeffedcba", * str_2 = "bob", * str_3 = "AbcdeFfedcba";
  ck_assert_int_eq(o_strcasecmp(str_1, str_3), 0);
  ck_assert_int_ne(o_strcasecmp(str_1, str_2), 0);
  ck_assert_int_ne(o_strcasecmp(str_1, NULL), 0);
  ck_assert_int_ne(o_strcasecmp(NULL, str_1), 0);
  ck_assert_int_eq(o_strcasecmp(NULL, NULL), 0);
}
END_TEST

START_TEST(test_o_strncasecmp)
{
  char * str_1 = "abcdeFfedcba", * str_2 = "abC", * str_3 = "abCdeffedCba";
  ck_assert_int_eq(o_strncasecmp(str_1, str_3, strlen(str_3)), 0);
  ck_assert_int_eq(o_strncasecmp(str_1, str_2, strlen(str_2)), 0);
  ck_assert_int_ne(o_strncasecmp(str_1, str_2, strlen(str_1)), 0);
  ck_assert_int_ne(o_strncasecmp(str_1, NULL, strlen(str_1)), 0);
  ck_assert_int_ne(o_strncasecmp(NULL, str_1, strlen(str_1)), 0);
  ck_assert_int_eq(o_strncasecmp(NULL, NULL, 0), 0);
  ck_assert_int_eq(o_strncasecmp(NULL, NULL, 1), 0);
}
END_TEST

START_TEST(test_o_strcpy)
{
  char * src = "abcd", target[5];
  ck_assert_ptr_ne(o_strcpy(target, src), NULL);
  ck_assert_str_eq(target, src);
  ck_assert_ptr_eq(o_strcpy(target, NULL), NULL);
  ck_assert_ptr_eq(o_strcpy(NULL, src), NULL);
  ck_assert_ptr_eq(o_strcpy(NULL, NULL), NULL);
}
END_TEST

START_TEST(test_o_strncpy)
{
  char * src = "abcd", target[5] = {0};
  ck_assert_ptr_ne(o_strncpy(target, src, 3), NULL);
  ck_assert_str_eq(target, "abc");
  ck_assert_ptr_eq(o_strncpy(target, NULL, 4), NULL);
  ck_assert_ptr_eq(o_strncpy(NULL, src, 4), NULL);
  ck_assert_ptr_eq(o_strncpy(NULL, NULL, 4), NULL);
}
END_TEST

START_TEST(test_o_strstr)
{
  char * str_1 = "abcdeffedcba", * str_2 = "def", * str_3 = "bob";
  ck_assert_ptr_ne(o_strstr(str_1, str_2), NULL);
  ck_assert_ptr_eq(o_strstr(str_1, str_3), NULL);
  ck_assert_ptr_eq(o_strstr(NULL, str_3), NULL);
  ck_assert_ptr_eq(o_strstr(str_1, NULL), NULL);
  ck_assert_ptr_eq(o_strstr(NULL, NULL), NULL);
}
END_TEST

START_TEST(test_o_strnstr)
{
  char * str_1 = "abcdeffedcba", * str_2 = "def", * str_3 = "bob";
  ck_assert_ptr_ne(o_strnstr(str_1, str_2, strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, str_3, strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, str_3, 0), NULL);
  ck_assert_ptr_eq(o_strnstr(NULL, str_3, strlen(str_3)), NULL);
  ck_assert_ptr_eq(o_strnstr(str_1, NULL, strlen(str_1)), NULL);
  ck_assert_ptr_eq(o_strnstr(NULL, NULL, strlen(str_3)), NULL);
}
END_TEST

START_TEST(test_o_strchr)
{
  char * str_1 = "abcdef", str_2 = 'd', str_3 = 'g';
  ck_assert_ptr_ne(o_strchr(str_1, str_2), NULL);
  ck_assert_ptr_eq(o_strchr(str_1, str_3), NULL);
  ck_assert_ptr_eq(o_strchr(NULL, str_3), NULL);
}
END_TEST

START_TEST(test_o_strnchr)
{
  char * str_1 = "abcdef", str_2 = 'd';
  ck_assert_ptr_ne(o_strnchr(str_1, 5, str_2), NULL);
  ck_assert_ptr_eq(o_strnchr(str_1, 2, str_2), NULL);
  ck_assert_ptr_eq(o_strnchr(str_1, 0, str_2), NULL);
  ck_assert_ptr_ne(o_strnchr(str_1, 8, str_2), NULL);
  ck_assert_ptr_eq(o_strnchr(NULL, 4, str_2), NULL);
}
END_TEST

START_TEST(test_o_strrchr)
{
  char * str_1 = "abcdef", str_2 = 'd', str_3 = 'g';
  ck_assert_ptr_ne(o_strrchr(str_1, str_2), NULL);
  ck_assert_ptr_eq(o_strrchr(str_1, str_3), NULL);
  ck_assert_ptr_ne(o_strrchr(str_1, str_2), NULL);
  ck_assert_ptr_eq(o_strrchr(NULL, str_3), NULL);
}
END_TEST

START_TEST(test_o_strrnchr)
{
  char * str_1 = "abcdef", str_2 = 'd';
  ck_assert_ptr_ne(o_strrnchr(str_1, 5, str_2), NULL);
  ck_assert_ptr_eq(o_strrnchr(str_1, 2, str_2), NULL);
  ck_assert_ptr_eq(o_strrnchr(str_1, 0, str_2), NULL);
  ck_assert_ptr_ne(o_strrnchr(str_1, 8, str_2), NULL);
  ck_assert_ptr_eq(o_strrnchr(NULL, 4, str_2), NULL);
}
END_TEST

START_TEST(test_o_strlen)
{
  ck_assert_int_eq(o_strlen("abcdef"), 6);
  ck_assert_int_eq(o_strlen(NULL), 0);
  ck_assert_int_eq(o_strlen(""), 0);
}
END_TEST

START_TEST(test_msprintf)
{
  char * target;
  char tmp[100];
  target = msprintf("target1 %s %d %p", "str1", 42, NULL);
  sprintf(tmp, "target1 str1 42 %p", NULL);
  ck_assert_str_eq(target, tmp);
  o_free(target);
  ck_assert_ptr_eq(msprintf(NULL, "str1", 42, NULL), NULL);
}
END_TEST

START_TEST(test_mstrcatf)
{
  char * target;
  char tmp[200];
  target = msprintf("target1 %s %d %p", "str1", 42, NULL);
  target = mstrcatf(target, "target2 %s %d %p", "str2", 42, NULL);
  sprintf(tmp, "target1 str1 42 %ptarget2 %s 42 %p", NULL, "str2", NULL);
  ck_assert_str_eq(target, tmp);
  o_free(target);
  ck_assert_ptr_eq(msprintf(NULL, NULL, "str1", 42, NULL), NULL);
  target = NULL;
  target = mstrcatf(target, "target2 %s %d %p", "str2", 42, NULL);
  sprintf(tmp, "target2 %s 42 %p", "str2", NULL);
  ck_assert_str_eq(target, tmp);
  o_free(target);
}
END_TEST

START_TEST(test_trimwhitespace)
{
  char * test1 = o_strdup(" bob trimmed  "), * test2 = o_strdup(" \t \t"), * test3 = o_strdup("");
  ck_assert_str_eq(trimwhitespace(test1), "bob trimmed");
  ck_assert_str_eq(trimwhitespace(test2), "");
  ck_assert_str_eq(trimwhitespace(test3), "");
  ck_assert_ptr_eq(trimwhitespace(NULL), NULL);
  o_free(test1);
  o_free(test2);
  o_free(test3);
}
END_TEST

START_TEST(test_trimcharacter)
{
  char test1[] = "3bob trimmed33", test2[] = "333", test3[] = "";
  ck_assert_str_eq(trimcharacter(test1, '3'), "bob trimmed");
  ck_assert_str_eq(trimcharacter(test2, '3'), "");
  ck_assert_str_eq(trimcharacter(test3, '3'), "");
  ck_assert_ptr_eq(trimcharacter(NULL, '3'), NULL);
}
END_TEST

START_TEST(test_string_array)
{
	char ** array, * str_orig = "Alice,Bob,Carol,Dave,Eve,Isaac";
	int size = split_string(str_orig, ",", &array);
	
	ck_assert_int_eq(size, 6);
	ck_assert_int_eq(string_array_has_value((const char **)array, "Alice"), 1);
	ck_assert_int_eq(string_array_has_value((const char **)array, "Mallory"), 0);
	ck_assert_int_eq(string_array_has_value_case((const char **)array, "alice"), 1);
	ck_assert_int_eq(string_array_has_value_case((const char **)array, "mallory"), 0);
	ck_assert_int_eq(string_array_has_value_n((const char **)array, "Aliceeee", 5), 1);
	ck_assert_int_eq(string_array_has_value_n((const char **)array, "Malloryyyy", 7), 0);
	ck_assert_int_eq(string_array_has_value_ncase((const char **)array, "aliceeee", 5), 1);
	ck_assert_int_eq(string_array_has_value_ncase((const char **)array, "malloryyyy", 7), 0);
	
	free_string_array(array);
}
END_TEST

START_TEST(test_string_array_has_trimmed_value)
{
	char ** array, * str_orig = "Alice,Bob,Carol,Dave,Eve,Isaac", * str_match_ok = "Carol", * str_match_not_found = "Sam";
	int size = split_string(str_orig, ",", &array);
	
	ck_assert_int_eq(size, 6);
	ck_assert_int_eq(string_array_has_trimmed_value((const char **)array, str_match_ok), 1);
	ck_assert_int_eq(string_array_has_trimmed_value((const char **)array, str_match_not_found), 0);
	ck_assert_int_eq(string_array_has_trimmed_value((const char **)array, NULL), 0);
	ck_assert_int_eq(string_array_has_trimmed_value(NULL, str_match_ok), 0);
	ck_assert_int_eq(string_array_has_trimmed_value(NULL, NULL), 0);
	
	free_string_array(array);
}
END_TEST

START_TEST(test_base64)
{
  char * src = "source string", encoded[128], decoded[128], b64_error[] = ";error;";
  size_t encoded_size, decoded_size;
  ck_assert_int_eq(o_base64_encode((unsigned char *)src, o_strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_str_eq(encoded, "c291cmNlIHN0cmluZw==");
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_str_eq(decoded, src);
  ck_assert_int_eq(decoded_size, o_strlen(src));
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error, o_strlen(b64_error), NULL, &decoded_size), 0);
  ck_assert_int_eq(o_base64_decode((unsigned char *)b64_error, o_strlen(b64_error), (unsigned char *)decoded, &decoded_size), 0);
}
END_TEST

START_TEST(test_base64url)
{
  char * src = "source string", encoded[128], decoded[128], b64_error[] = ";error;";
  size_t encoded_size, decoded_size;
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src, o_strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_str_eq(encoded, "c291cmNlIHN0cmluZw");
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size, (unsigned char *)decoded, &decoded_size), 1);
  ck_assert_str_eq(decoded, src);
  ck_assert_int_eq(decoded_size, o_strlen(src));
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error, o_strlen(b64_error), NULL, &decoded_size), 0);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)b64_error, o_strlen(b64_error), (unsigned char *)decoded, &decoded_size), 0);
}
END_TEST

START_TEST(test_base64url_2_base64)
{
  unsigned char src[10] = {0x6f, 0x5b, 0x70, 0x29, 0x27, 0x2d, 0x3d, 0x40, 0x7e, 0x0}, encoded[21] = {0}, encoded_url[21] = {0}, encoded_new[19] = {0};
  size_t encoded_size = 0, encoded_new_size = 0;
  ck_assert_int_eq(o_base64_encode(src, 10, encoded, &encoded_size), 1);
  ck_assert_int_gt(encoded_size, 0);
  encoded[encoded_size] = '\0'; // should be "b1twKSctPUB+AA=="
  ck_assert_int_eq(o_base64url_encode(src, 10, encoded_url, &encoded_size), 1);
  ck_assert_int_gt(encoded_size, 0);
  encoded_url[encoded_size] = '\0'; // should be "b1twKSctPUB-AA"
  ck_assert_str_ne((const char *)encoded_url, (const char *)encoded);
  ck_assert_int_eq(o_base64url_2_base64(encoded_url, encoded_size, encoded_new, &encoded_new_size), 1);
  encoded_new[encoded_new_size] = '\0';
  ck_assert_str_eq((const char *)encoded_new, (const char *)encoded);
}
END_TEST

START_TEST(test_base64_2_base64url)
{
  unsigned char src[10] = {0x6f, 0x5b, 0x70, 0x29, 0x27, 0x2d, 0x3d, 0x40, 0x7e, 0x0}, encoded[21] = {0}, encoded_url[21] = {0}, encoded_new[19] = {0};
  size_t encoded_size = 0, encoded_new_size = 0;
  ck_assert_int_eq(o_base64url_encode(src, 10, encoded, &encoded_size), 1);
  ck_assert_int_gt(encoded_size, 0);
  encoded[encoded_size] = '\0'; // should be "b1twKSctPUB-AA"
  ck_assert_int_eq(o_base64_encode(src, 10, encoded_url, &encoded_size), 1);
  ck_assert_int_gt(encoded_size, 0);
  encoded_url[encoded_size] = '\0'; // should be "b1twKSctPUB+AA=="
  ck_assert_str_ne((const char *)encoded_url, (const char *)encoded);
  ck_assert_int_eq(o_base64_2_base64url(encoded_url, encoded_size, encoded_new, &encoded_new_size), 1);
  encoded_new[encoded_new_size] = '\0';
  ck_assert_str_eq((const char *)encoded_new, (const char *)encoded);
}
END_TEST

START_TEST(test_base64_len)
{
  char * src1 = "a", * src2 = "aa", * src3 = "aaa", * src4 = "aaaa", * src5 = "aaaaa", * src = "source string", encoded[128];
  char * src1_enc = "YQ==", * src2_enc = "YWE=", * src3_enc = "YWFh", *src4_enc = "YWFhYQ==", *src5_enc = "YWFhYWE=";
  size_t encoded_size, decoded_size;
  
  ck_assert_int_eq(o_base64_encode((unsigned char *)src, o_strlen(src), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 20);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src, o_strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)encoded, encoded_size, NULL, &decoded_size), 1);
  ck_assert_int_eq(decoded_size, 13);
  
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src, o_strlen(src), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 18);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src, o_strlen(src), (unsigned char *)encoded, &encoded_size), 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)encoded, encoded_size, NULL, &decoded_size), 1);
  ck_assert_int_eq(decoded_size, 13);
  
  ck_assert_int_eq(o_base64_encode((unsigned char *)src1, o_strlen(src1), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src2, o_strlen(src2), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src3, o_strlen(src3), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src4, o_strlen(src4), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 8);
  ck_assert_int_eq(o_base64_encode((unsigned char *)src5, o_strlen(src5), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 8);
  
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src1, o_strlen(src1), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 2);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src2, o_strlen(src2), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 3);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src3, o_strlen(src3), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src4, o_strlen(src4), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 6);
  ck_assert_int_eq(o_base64url_encode((unsigned char *)src5, o_strlen(src5), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 7);
  
  ck_assert_int_eq(o_base64_decode((unsigned char *)src1_enc, o_strlen(src1_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 1);
  ck_assert_int_eq(o_base64_decode((unsigned char *)src2_enc, o_strlen(src2_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 2);
  ck_assert_int_eq(o_base64_decode((unsigned char *)src3_enc, o_strlen(src3_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 3);
  ck_assert_int_eq(o_base64_decode((unsigned char *)src4_enc, o_strlen(src4_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64_decode((unsigned char *)src5_enc, o_strlen(src5_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 5);
  
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src1_enc, o_strlen(src1_enc)-2, NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 1);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src2_enc, o_strlen(src2_enc)-1, NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 2);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src3_enc, o_strlen(src3_enc), NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 3);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src4_enc, o_strlen(src4_enc)-2, NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 4);
  ck_assert_int_eq(o_base64url_decode((unsigned char *)src5_enc, o_strlen(src5_enc)-1, NULL, &encoded_size), 1);
  ck_assert_int_eq(encoded_size, 5);
}
END_TEST

static Suite *orcania_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Orcania tests string functions");
	tc_core = tcase_create("test_orcania_str");
	tcase_add_test(tc_core, test_str_replace);
	tcase_add_test(tc_core, test_o_strdup);
	tcase_add_test(tc_core, test_o_strndup);
	tcase_add_test(tc_core, test_o_strcmp);
	tcase_add_test(tc_core, test_o_strncmp);
	tcase_add_test(tc_core, test_o_strcasecmp);
	tcase_add_test(tc_core, test_o_strncasecmp);
	tcase_add_test(tc_core, test_o_strcpy);
	tcase_add_test(tc_core, test_o_strncpy);
	tcase_add_test(tc_core, test_o_strstr);
	tcase_add_test(tc_core, test_o_strnstr);
	tcase_add_test(tc_core, test_o_strchr);
	tcase_add_test(tc_core, test_o_strnchr);
	tcase_add_test(tc_core, test_o_strrchr);
	tcase_add_test(tc_core, test_o_strrnchr);
	tcase_add_test(tc_core, test_o_strlen);
	tcase_add_test(tc_core, test_msprintf);
	tcase_add_test(tc_core, test_mstrcatf);
	tcase_add_test(tc_core, test_trimwhitespace);
	tcase_add_test(tc_core, test_trimcharacter);
	tcase_add_test(tc_core, test_base64);
	tcase_add_test(tc_core, test_base64url);
	tcase_add_test(tc_core, test_base64url_2_base64);
	tcase_add_test(tc_core, test_base64_2_base64url);
	tcase_add_test(tc_core, test_base64_len);
	tcase_add_test(tc_core, test_string_array);
	tcase_add_test(tc_core, test_string_array_has_trimmed_value);
	tcase_set_timeout(tc_core, 30);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(int argc, char *argv[])
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = orcania_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
