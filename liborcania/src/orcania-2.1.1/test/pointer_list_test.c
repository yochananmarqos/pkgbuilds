/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <check.h>
#include "orcania.h"

int counter = 0;

void free_with_test(void * ptr) {
  counter++;
  o_free(ptr);
}

START_TEST(test_pointer_list_init)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list->size, 0);
  ck_assert_ptr_eq(pointer_list->list, NULL);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_append)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list->size, 0);
  ck_assert_ptr_eq(pointer_list->list, NULL);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x42), 1);
  ck_assert_int_eq(pointer_list_append(NULL, (void *)0x42), 0);
  ck_assert_int_eq(pointer_list->size, 1);
  ck_assert_int_eq(pointer_list_append(NULL, (void *)0x43), 0);
  ck_assert_int_eq(pointer_list_append(pointer_list, NULL), 1);
  ck_assert_int_eq(pointer_list->size, 2);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_size)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x42), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x43), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x44), 1);
  ck_assert_int_eq(pointer_list_size(pointer_list), 3);
  ck_assert_int_eq(pointer_list_size(pointer_list), pointer_list->size);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_get_at)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x42), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x43), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x44), 1);
  ck_assert_int_eq(pointer_list->size, 3);
  ck_assert_ptr_ne(pointer_list_get_at(pointer_list, 0), NULL);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 0), (void *)0x42);
  ck_assert_ptr_ne(pointer_list_get_at(pointer_list, 1), NULL);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 1), (void *)0x43);
  ck_assert_ptr_ne(pointer_list_get_at(pointer_list, 2), NULL);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 2), (void *)0x44);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 3), NULL);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_remove_at)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x42), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x43), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x44), 1);
  ck_assert_int_eq(pointer_list->size, 3);
  ck_assert_int_eq(pointer_list_remove_at(pointer_list, 0), 1);
  ck_assert_int_eq(pointer_list_remove_at(pointer_list, 4), 0);
  ck_assert_int_eq(pointer_list->size, 2);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_remove_at_free)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, o_strdup("test1")), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x43), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x44), 1);
  ck_assert_int_eq(pointer_list->size, 3);
  counter = 0;
  ck_assert_int_eq(pointer_list_remove_at_free(pointer_list, 0, &free_with_test), 1);
  ck_assert_int_eq(counter, 1);
  ck_assert_int_eq(pointer_list_remove_at_free(pointer_list, 4, &free_with_test), 0);
  ck_assert_int_eq(counter, 1);
  ck_assert_int_eq(pointer_list->size, 2);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_insert_at)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x42), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x43), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x44), 1);
  ck_assert_int_eq(pointer_list->size, 3);
  ck_assert_int_eq(pointer_list_insert_at(pointer_list, (void *)0x45, 0), 1);
  ck_assert_int_eq(pointer_list->size, 4);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 0), (void *)0x45);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 1), (void *)0x42);
  ck_assert_int_eq(pointer_list_insert_at(pointer_list, (void *)0x46, 3), 1);
  ck_assert_int_eq(pointer_list->size, 5);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 0), (void *)0x45);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 1), (void *)0x42);
  ck_assert_ptr_eq(pointer_list_get_at(pointer_list, 3), (void *)0x46);
  ck_assert_int_eq(pointer_list_insert_at(pointer_list, (void *)0x47, 10), 0);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_remove_pointer)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x42), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x43), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x44), 1);
  ck_assert_int_eq(pointer_list->size, 3);
  ck_assert_int_eq(pointer_list_remove_pointer(pointer_list, (void *)0x42), 1);
  ck_assert_int_eq(pointer_list->size, 2);
  ck_assert_int_eq(pointer_list_remove_pointer(pointer_list, (void *)0x42), 0);
  ck_assert_int_eq(pointer_list->size, 2);
  ck_assert_int_eq(pointer_list_remove_pointer(pointer_list, (void *)0x44), 1);
  ck_assert_int_eq(pointer_list->size, 1);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_remove_pointer_free)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  char * test1 = o_strdup("test1"), * test3 = o_strdup("test3");
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, test1), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x43), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, test3), 1);
  ck_assert_int_eq(pointer_list->size, 3);
  counter = 0;
  ck_assert_int_eq(pointer_list_remove_pointer_free(pointer_list, test1, &free_with_test), 1);
  ck_assert_int_eq(counter, 1);
  ck_assert_int_eq(pointer_list->size, 2);
  ck_assert_int_eq(pointer_list_remove_pointer(pointer_list, (void *)0x42), 0);
  ck_assert_int_eq(pointer_list->size, 2);
  ck_assert_int_eq(pointer_list_remove_pointer_free(pointer_list, test3, &free_with_test), 1);
  ck_assert_int_eq(counter, 2);
  ck_assert_int_eq(pointer_list->size, 1);
  pointer_list_clean(pointer_list);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_clean)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x42), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x43), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, (void *)0x44), 1);
  ck_assert_int_eq(pointer_list->size, 3);
  pointer_list_clean(pointer_list);
  ck_assert_int_eq(pointer_list->size, 0);
  o_free(pointer_list);
}
END_TEST

START_TEST(test_pointer_list_clean_free)
{
  struct _pointer_list * pointer_list = o_malloc(sizeof(struct _pointer_list));
  
  pointer_list_init(pointer_list);
  ck_assert_int_eq(pointer_list_append(pointer_list, o_strdup("test1")), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, o_strdup("test2")), 1);
  ck_assert_int_eq(pointer_list_append(pointer_list, o_strdup("test3")), 1);
  ck_assert_int_eq(pointer_list->size, 3);
  counter = 0;
  pointer_list_clean_free(pointer_list, &free_with_test);
  ck_assert_int_eq(pointer_list->size, 0);
  ck_assert_int_eq(counter, 3);
  o_free(pointer_list);
}
END_TEST

static Suite *orcania_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Orcania tests pointer list structure functions");
	tc_core = tcase_create("test_pointer_list");
	tcase_add_test(tc_core, test_pointer_list_init);
	tcase_add_test(tc_core, test_pointer_list_append);
	tcase_add_test(tc_core, test_pointer_list_size);
	tcase_add_test(tc_core, test_pointer_list_get_at);
	tcase_add_test(tc_core, test_pointer_list_remove_at);
	tcase_add_test(tc_core, test_pointer_list_remove_at_free);
	tcase_add_test(tc_core, test_pointer_list_insert_at);
	tcase_add_test(tc_core, test_pointer_list_remove_pointer);
	tcase_add_test(tc_core, test_pointer_list_remove_pointer_free);
	tcase_add_test(tc_core, test_pointer_list_clean);
	tcase_add_test(tc_core, test_pointer_list_clean_free);
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
