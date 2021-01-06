/**
 * 
 * @file orcania.h
 * @brief Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * other projects
 * 
 * orcania.h: public header file
 * 
 * Copyright 2015-2020 Nicolas Mora <mail@babelouest.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation;
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU GENERAL PUBLIC LICENSE for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef __ORCANIA_H__
#define __ORCANIA_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "orcania-cfg.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @defgroup str string functions
 * These functions are used for string manipulation
 * Types of functions available:
 * - crash safe version of <string.h> library
 * - build heap allocated strings using printf-like format
 * @{
 */

/**
 * char * str_replace(const char * source, char * old, char * new)
 * replace all occurences of old by new in the string source
 * return a char * with the new value
 * @param source: the source string
 * @param str_old string to be replaced in source
 * @param str_new new string to replace
 * @return a heap-allocated string with the replacements applied
 * return NULL on error
 * returned value must be free'd after use
 */
char * str_replace(const char * source, const char * str_old, const char * str_new);

/**
 * o_strdup
 * a modified strdup function that don't crash when source is NULL, instead return NULL
 * @param source the source string to duplicate
 * @return a heap-allocated string
 * Returned value must be free'd after use
 */
char * o_strdup(const char * source);

/**
 * o_strndup
 * a modified strndup function that don't crash when source is NULL, instead return NULL
 * @param source the source string to duplicate
 * @param len the maximum length of the string source to duplicate
 * @return a heap-allocated string
 * Returned value must be free'd after use
 */
char * o_strndup(const char * source, size_t len);

/**
 * o_strcmp
 * a modified strcmp function that don't crash when p1 is NULL or p2 us NULL
 * @param p1 the first string to compare
 * @param p2 the second string to compare
 * @return 0 if p1 is equal to p2, negative number if p1 is inferior to p2, positive number otherwise
 */
int o_strcmp(const char * p1, const char * p2);

/**
 * o_strncmp
 * a modified strncmp function that don't crash when p1 is NULL or p2 us NULL
 * @param p1 the first string to compare
 * @param p2 the second string to compare
 * @param n the maximum number of char to compare
 * @return 0 if p1 is equal to p2, negative number if p1 is inferior to p2, positive number otherwise
 */
int o_strncmp(const char * p1, const char * p2, size_t n);

/**
 * o_strcpy
 * a modified strcpy function that don't crash when p1 is NULL or p2 us NULL
 * @param p1 the string to copy p2
 * @param p2 the source string to be copied
 * @return p1
 */
char * o_strcpy(char * p1, const char * p2);

/**
 * o_strncpy
 * @param p1 the string to copy p2
 * @param p2 the source string to be copied
 * @param n the maximum characters to copy from p2 to p1
 * @return p1
 * a modified strncpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * o_strncpy(char * p1, const char * p2, size_t n);

/**
 * o_strcasecmp
 * a modified strcasecmp function that don't crash when p1 is NULL or p2 us NULL
 * @param p1 the first string to compare
 * @param p2 the second string to compare
 * @return 0 if p1 is equal to p2, negative number if p1 is inferior to p2, positive number otherwise
 */
int o_strcasecmp(const char * p1, const char * p2);

/**
 * o_strncasecmp
 * a modified strncasecmp function that don't crash when p1 is NULL or p2 us NULL
 * @param p1 the first string to compare
 * @param p2 the second string to compare
 * @param n the maximum number of char to compare
 * @return 0 if p1 is equal to p2, negative number if p1 is inferior to p2, positive number otherwise
 */
int o_strncasecmp(const char * p1, const char * p2, size_t n);

/**
 * o_strstr
 * a modified strstr function that don't crash when haystack is NULL or needle us NULL
 * @param haystack the string to be looked for
 * @param needle the string to search in haystack
 * @return the pointer to the first occurence of needle in haystack or NULL if not found
 */
char * o_strstr(const char * haystack, const char * needle);

/**
 * o_strnstr
 * a modified strnstr function that don't crash when haystack is NULL or needle us NULL
 * @param haystack the string to be looked for
 * @param needle the string to search in haystack
 * @param len the maximum length to look for in haystack
 * @return the pointer to the first occurence of needle in haystack or NULL if not found
 */
char * o_strnstr(const char * haystack, const char * needle, size_t len);

/**
 * o_strcasestr
 * a modified strcasestr function that don't crash when haystack is NULL or needle us NULL
 * @param haystack the string to be looked for
 * @param needle the string to search in haystack
 * @return the pointer to the first occurence of needle in haystack or NULL if not found
 */
char * o_strcasestr(const char * haystack, const char * needle);

/**
 * o_strchr
 * a modified strchr function that don't crash when haystack is NULL
 * @param haystack the string to be looked for
 * @param c the character to look for in haystack
 * @return the pointer to the first occurence of c in haystack or NULL if not found
 */
char * o_strchr(const char * haystack, int c);

/**
 * o_strnchr
 * a modified strnchr function that don't crash when haystack is NULL
 * @param haystack the string to be looked for
 * @param len the maxmimum length of characters to look for in haystack
 * @param c the character to look for in haystack
 * @return the pointer to the first occurence of c in haystack or NULL if not found
 */
const char * o_strnchr(const char * haystack, size_t len, char c);

/**
 * o_strrchr
 * a modified strrchr function that don't crash when haystack is NULL
 * @param haystack the string to be looked for
 * @param c the character to look for in haystack
 * @return the pointer to the last occurence of c in haystack or NULL if not found
 */
char * o_strrchr(const char * haystack, int c);

/**
 * o_strrnchr
 * a modified strrnchr function that don't crash when haystack is NULL
 * @param haystack the string to be looked for
 * @param len the maxmimum length of characters to look for in haystack
 * @param c the character to look for in haystack
 * @return the pointer to the last occurence of c in haystack or NULL if not found
 */
const char * o_strrnchr(const char * haystack, size_t len, char c);

/**
 * o_strlen
 * a modified version of strlen that don't crash when s is NULL
 * @param s the string to calculate length
 * @return the length of s, 0 if s is NULL
 */
size_t o_strlen(const char * s);

/**
 * Remove string of beginning and ending whitespaces
 * the string str will be modified
 * @param str the string to trim
 * @return the trimmed str
 */
char * trimwhitespace(char * str);

/**
 * Remove string of beginning and ending given character
 * the string str will be modified
 * @param str the string to trim
 * @return the trimmed str
 */
char * trimcharacter(char * str, char to_remove);

/**
 * char * msprintf(const char * message, ...)
 * Implementation of sprintf that return a malloc'd char * with the string construction
 * because life is too short to use 3 lines instead of 1
 * but don't forget to free the returned value after use!
 * Disclaimer: When I made this function, I didn't know
 * asprintf existed. If I did I surely wouldn't make msprintf
 * although, msprintf has the advantage to work with o_malloc and o_free
 * so it can use specific memory allocation functions
 * @param message the message format to concat to source, printf format
 * @return a heap-allocated char * containing the result string
 */
char * msprintf(const char * message, ...);

/**
 * char * mstrcatf((char * source, const char * message, ...)
 * A combination of strcat and msprintf that will concat source and message formatted
 * and return the combination as a new allocated char *
 * and will o_free source
 * but don't forget to free the returned value after use!
 * @param source the source string to concat message, source will be free'd during the process
 * @param message the message format to concat to source, printf format
 * @return a heap-allocated char * containing the result string
 */
char * mstrcatf(char * source, const char * message, ...);

/**
 * @}
 */

/**
 * @defgroup split split string and string array functions
 * @{
 */

/**
 * Split a string into an array of strings using separator string
 * return the number of elements to be returned, 0 on error
 * @param string the string to split
 * @param separator the string separator, will not be included in the result
 * @param return_array an reference to a char ** that will be heap-allocated by the function
 * The last element in return_array will be NULL
 * @return the number of string elements in result_array
 * if return_array is not NULL, set the returned array in it
 * return_array is an array of char * ending with a NULL value
 * return_array must be free'd after use
 * you can use free_string_array to free return_array
 */
size_t split_string(const char * string, const char * separator, char *** return_array);

/**
 * Clean an array of strings
 * @param array an array of char * to free using o_free for each element
 * the last element of array must be a NULL
 */
void free_string_array(char ** array);

/**
 * Count the number of elements in an array of strings
 * @param array an array of char * with NULL in the last element
 * @return the number of string elements in array
 */
size_t string_array_size(char ** array);

/**
 * Check if an array of string has a specified value, case sensitive
 * @param array an array of char * with NULL in the last element
 * @param needle the value to look for in array
 * @return 1 if needle exists in array, 0 otherwise
 */
int string_array_has_value(const char ** array, const char * needle);

/**
 * Check if an array of string has a specified value, case insensitive
 * @param array an array of char * with NULL in the last element
 * @param needle the value to look for in array
 * @return 1 if needle exists in array, 0 otherwise
 */
int string_array_has_value_case(const char ** array, const char * needle);

/**
 * Check if an array of string has a specified value, case sensitive, limit to len characters
 * @param array an array of char * with NULL in the last element
 * @param needle the value to look for in array
 * @return 1 if needle exists in array, 0 otherwise
 */
int string_array_has_value_n(const char ** array, const char * needle, size_t len);

/**
 * Check if an array of string has a specified value, case insensitive, limit to len characters
 * @param array an array of char * with NULL in the last element
 * @param needle the value to look for in array
 * @return 1 if needle exists in array, 0 otherwise
 */
int string_array_has_value_ncase(const char ** array, const char * needle, size_t len);

/**
 * Check if an array of string has a specified trimmed value
 * @param array an array of char * with NULL in the last element
 * @param needle the value to look for in array
 * @return 1 if needle exists in array, 0 otherwise
 */
int string_array_has_trimmed_value(const char ** array, const char * needle);

/**
 * Join a string array into a single string
 * @param array an array of char * with NULL in the last element
 * @param separator a string to put between the elements
 * @return a heap allocated string
 */
char * string_array_join(const char ** array, const char * separator);

/**
 * @}
 */

/**
 * @defgroup plist _pointer_list structure
 * @{
 */
struct _pointer_list {
  size_t size; /* size of the list */
  void ** list; /* list of pointers */
};

/**
 * pointer_list_init
 * Initialize a pointer list structure
 * @param pointer_list a pointer list to initialize
 */
void pointer_list_init(struct _pointer_list * pointer_list);

/**
 * pointer_list_clean
 * Clean a pointer list structure
 * @param pointer_list a pointer list to clean
 */
void pointer_list_clean(struct _pointer_list * pointer_list);

/**
 * pointer_list_clean_free
 * Clean a pointer list structure
 * Free all elements using the free_function given in parameters
 * @param pointer_list a pointer list to clean
 * @param free_function a function to use for freeing values
 */
void pointer_list_clean_free(struct _pointer_list * pointer_list, void (* free_function)(void * elt));

/**
 * pointer_list_size
 * @param pointer_list a pointer list
 * @return the size of a pointer list
 */
size_t pointer_list_size(struct _pointer_list * pointer_list);

/**
 * pointer_list_append
 * Appends an element at the end of a pointer list
 * @param pointer_list a pointer list
 * @param element an element to append
 * @return 1 on success, 0 on error
 */
int pointer_list_append(struct _pointer_list * pointer_list, void * element);

/**
 * pointer_list_get_at
 * @param pointer_list a pointer list
 * @param index the index of the element in pointer_list
 * @return an element of a pointer list at the specified index or NULL if non valid index
 */
void * pointer_list_get_at(struct _pointer_list * pointer_list, size_t index);

/**
 * pointer_list_remove_at
 * Removes an element of a pointer list at the specified index
 * @param pointer_list a pointer list
 * @param index the index of the element in pointer_list
 * @return 1 on success, 0 on error or non valid index
 */
int pointer_list_remove_at(struct _pointer_list * pointer_list, size_t index);

/**
 * pointer_list_remove_at_free
 * Removes an element of a pointer list at the specified index
 * Free the element using the free_function given in parameters
 * @param pointer_list a pointer list
 * @param index the index of the element in pointer_list
 * @param free_function the function to use to free the element
 * @return 1 on success, 0 on error or non valid index
 */
int pointer_list_remove_at_free(struct _pointer_list * pointer_list, size_t index, void (* free_function)(void * elt));

/**
 * pointer_list_insert_at
 * Inserts an element at the specified index of a pointer list
 * @param pointer_list a pointer list
 * @param element the element to set at index
 * @param index the index of the element in pointer_list
 * @return 1 on success, 0 on error or non valid inde
 */
int pointer_list_insert_at(struct _pointer_list * pointer_list, void * element, size_t index);

/**
 * pointer_list_remove_pointer
 * Removes an element of a pointer list corresponding to the specified element
 * @param pointer_list a pointer list
 * @param element the element to set at index
 * @return 1 on success, 0 on error or non valid inde
 */
int pointer_list_remove_pointer(struct _pointer_list * pointer_list, void * element);

/**
 * pointer_list_remove_pointer_free
 * Removes an element of a pointer list corresponding to the specified element
 * Free the element using the free_function given in parameters
 * @param pointer_list a pointer list
 * @param element the element to set at index
 * @param free_function the function to use to free the element
 * @return 1 on success, 0 on error or non valid inde
 */
int pointer_list_remove_pointer_free(struct _pointer_list * pointer_list, void * element, void (* free_function)(void * elt));

/**
 * @}
 */

/**
 * @defgroup mem Memory functions
 * @{
 */

/* C89 allows these to be macros */
#undef malloc
#undef realloc
#undef free

/**
 * typedefs use to replace glib's memory functions
 */
typedef void *(*o_malloc_t)(size_t);
typedef void *(*o_realloc_t)(void *, size_t);
typedef void (*o_free_t)(void *);

/**
 * Allocate a memory block
 * @param size the size of the block to allocate in memory
 * @return a pointer to the new allocated block
 */
void * o_malloc(size_t size);

/**
 * Reallocate a memory block
 * @param ptr the previous memory block that will be free'd
 * @param size the size of the block to allocate in memory
 * @return a pointer to the new allocated block with a copy of the data previously in ptr
 */
void * o_realloc(void * ptr, size_t size);

/**
 * Free a block allocated by o_malloc
 */
void o_free(void * ptr);

/**
 * Updates the memory functions by user-specific ones
 * @param malloc_fn a pointer to a malloc function, if NULL, will use current function
 * @param realloc_fn a pointer to a realloc function, if NULL, will use current function
 * @param free_fn a pointer to a free function, if NULL, will use current function
 */
void o_set_alloc_funcs(o_malloc_t malloc_fn, o_realloc_t realloc_fn, o_free_t free_fn);

/**
 * Gets the pointer to current memory functions
 * @param malloc_fn reference to a pointer to a malloc function
 * @param realloc_fn reference to a pointer to a realloc function
 * @param free_fn reference to a pointer to a free function
 */
void o_get_alloc_funcs(o_malloc_t * malloc_fn, o_realloc_t * realloc_fn, o_free_t * free_fn);

/**
 * @}
 */

/**
 * @defgroup base64 Base64 encode and decode functions
 * @{
 */

/**
 * o_base64_encode - Base64 encode
 * @param src: Data to be encoded
 * @param len: Length of the data to be encoded
 * @param out: Pointer to output variable
 * @param out_len: Pointer to output length variable
 * @return : 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64_encode(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64_decode - Base64 decode
 * @param src: Data to be decoded
 * @param len: Length of the data to be decoded
 * @param out: Pointer to output variable
 * @param out_len: Pointer to output length variable
 * @return : 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64_decode(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64url_encode - Base64url encode (url format)
 * @param src: Data to be encoded
 * @param len: Length of the data to be encoded
 * @param out: Pointer to output variable
 * @param out_len: Pointer to output length variable
 * @return : 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64url_encode(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64url_decode - Base64 decode (url format)
 * @param src: Data to be decoded
 * @param len: Length of the data to be decoded
 * @param out: Pointer to output variable
 * @param out_len: Pointer to output length variable
 * @return : 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64url_decode(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64url_2_base64 - Convert a base64 url format to base64 format
 * @param src: Data to be decoded
 * @param len: Length of the data to be decoded
 * @param out: Pointer to output variable
 * @param out_len: Pointer to output length variable
 * @return : 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 * out must be at least len+2
 */
int o_base64url_2_base64(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len);

/**
 * o_base64url_2_base64 - Convert a base64 format to base64 url format
 * @param src: Data to be decoded
 * @param len: Length of the data to be decoded
 * @param out: Pointer to output variable
 * @param out_len: Pointer to output length variable
 * @return : 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 * out must be at least len+2
 */
int o_base64_2_base64url(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // __ORCANIA_H__
