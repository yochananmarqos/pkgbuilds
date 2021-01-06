/**
 * 
 * Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * other projects
 * 
 * orcania.c: main functions definitions
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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "orcania.h"

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

/**
 * 
 * Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * other projects
 * 
 */

/**
 * char * str_replace(const char * source, char * str_old, char * str_new)
 * replace all occurences of str_old by str_new in the string source
 * return a char * with the str_new value
 * return NULL on error
 * returned value must be free'd after use
 */
char * str_replace(const char * source, const char * str_old, const char * str_new) {
  char * to_return, * ptr, * pre, * next;
  size_t len, pre_len;
  
  if (source == NULL || str_old == NULL || str_new == NULL) {
    return NULL;
  }
  
  ptr = strstr(source, str_old);
  if (ptr == NULL) {
    return o_strdup(source);
  } else {
    pre_len = ptr-source;
    pre = o_malloc((pre_len+1)*sizeof(char));
    if (pre == NULL) {
      return NULL;
    }
    memcpy(pre, source, pre_len);
    pre[pre_len] = '\0';
    
    next = str_replace(source+strlen(pre)+strlen(str_old), str_old, str_new);
    if (next == NULL) {
      o_free(pre);
      return NULL;
    }
    len = ((ptr-source)+strlen(str_new)+strlen(next));
    to_return = o_malloc((len+1)*sizeof(char));
    if (to_return == NULL) {
      o_free(pre);
      o_free(next);
      return NULL;
    }
    if (snprintf(to_return, (len+1), "%s%s%s", pre, str_new, next) < 0) {
      o_free(pre);
      o_free(next);
      o_free(to_return);
      return NULL;
    }
    o_free(pre);
    o_free(next);
    return to_return;
  }
}

/**
 * char * msprintf(const char * message, ...)
 * Implementation of sprintf that return a malloc'd char * with the string construction
 * because life is too short to use 3 lines instead of 1
 * but don't forget to free the returned value after use!
 */
char * msprintf(const char * message, ...) {
  va_list argp, argp_cpy;
  size_t out_len = 0;
  char * out = NULL;
  if (message != NULL) {
    va_start(argp, message);
    va_copy(argp_cpy, argp); // We make a copy because in some architectures, vsnprintf can modify argp
    out_len = vsnprintf(NULL, 0, message, argp);
    out = o_malloc(out_len+sizeof(char));
    if (out == NULL) {
      va_end(argp);
      va_end(argp_cpy);
      return NULL;
    }
    vsnprintf(out, (out_len+sizeof(char)), message, argp_cpy);
    va_end(argp);
    va_end(argp_cpy);
  }
  return out;
}

/**
 * char * mstrcatf((char * source, const char * message, ...)
 * A combination of strcat and msprintf that will concat source and message formatted
 * and return the combination as a new allocated char *
 * and will o_free source
 * but don't forget to free the returned value after use!
 */
char * mstrcatf(char * source, const char * message, ...) {
  va_list argp, argp_cpy;
  char * out = NULL, * message_formatted = NULL;
  size_t message_formatted_len = 0, out_len = 0, source_len = 0;
  
  if (message != NULL) {
    va_start(argp, message);
    va_copy(argp_cpy, argp); // We make a copy because in some architectures, vsnprintf can modify argp
    if (source != NULL) {
      source_len = o_strlen(source);
      message_formatted_len = vsnprintf(NULL, 0, message, argp);
      message_formatted = o_malloc(message_formatted_len+sizeof(char));
      if (message_formatted != NULL) {
        out = o_malloc(source_len+message_formatted_len+sizeof(char));
        vsnprintf(message_formatted, (message_formatted_len+sizeof(char)), message, argp_cpy);
        if (out != NULL) {
          o_strncpy(out, source, source_len);
          o_strncpy(out+source_len, message_formatted, message_formatted_len);
          out[source_len+message_formatted_len] = '\0';
        }
        o_free(message_formatted);
        o_free(source);
      }
    } else {
      out_len = vsnprintf(NULL, 0, message, argp);
      out = o_malloc(out_len+sizeof(char));
      if (out != NULL) {
        vsnprintf(out, (out_len+sizeof(char)), message, argp_cpy);
      }
    }
    va_end(argp);
    va_end(argp_cpy);
  }
  return out;
}

/**
 * o_strdup
 * a modified strdup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * o_strdup(const char * source) {
  return (source==NULL?NULL:o_strndup(source, strlen(source)));
}

/**
 * o_strndup
 * a modified strndup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * o_strndup(const char * source, size_t len) {
  char *new_str;

  if (source == NULL) {
    return NULL;
  } else {
    new_str = o_malloc(len + 1);
    if(!new_str) {
      return NULL;
    }

    memcpy(new_str, source, len);
    new_str[len] = '\0';
    return new_str;
  }
}

/**
 * o_strcmp
 * a modified strcmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strcmp(const char * p1, const char * p2) {
  if (p1 == NULL && p2 == NULL) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL) {
    return 1;
  } else {
    return strcmp(p1, p2);
  }
}

/**
 * o_strncmp
 * a modified strncmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strncmp(const char * p1, const char * p2, size_t n) {
  if ((p1 == NULL && p2 == NULL) || n <= 0) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL) {
    return 1;
  } else {
    return strncmp(p1, p2, n);
  }
}

/**
 * o_strcpy
 * a modified strcpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * o_strcpy(char * p1, const char * p2) {
  if (p1 == NULL || p2 == NULL) {
    return NULL;
  } else {
    return strcpy(p1, p2);
  }
}

/**
 * o_strncpy
 * a modified strncpy function that don't crash when p1 is NULL or p2 us NULL
 */
char * o_strncpy(char * p1, const char * p2, size_t n) {
  if (p1 == NULL || p2 == NULL) {
    return NULL;
  } else {
    return strncpy(p1, p2, n);
  }
}

/**
 * o_strcasecmp
 * a modified strcasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strcasecmp(const char * p1, const char * p2) {
  if (p1 == NULL && p2 == NULL) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL && p2 != NULL) {
    return 1;
  } else {
    return strcasecmp(p1, p2);
  }
}

/**
 * o_strncasecmp
 * a modified strncasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strncasecmp(const char * p1, const char * p2, size_t n) {
  if ((p1 == NULL && p2 == NULL) || n <= 0) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL && p2 != NULL) {
    return 1;
  } else {
    return strncasecmp(p1, p2, n);
  }
}

/**
 * o_strstr
 * a modified strstr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strstr(const char * haystack, const char * needle) {
  if (haystack == NULL || needle == NULL) {
    return NULL;
  } else {
    return strstr(haystack, needle);
  }
}

/**
 * o_strchr
 * a modified strchr function that don't crash when haystack is NULL
 */
char * o_strchr(const char * haystack, int c) {
  if (haystack == NULL) {
    return NULL;
  } else {
    return strchr(haystack, c);
  }
}

/**
 * o_strnchr
 * a modified strnchr function that don't crash when haystack is NULL
 */
const char * o_strnchr(const char * haystack, size_t len, char c) {
  size_t offset;
  if (haystack != NULL && len > 0) {
    for (offset = 0; offset < len && offset < o_strlen(haystack); offset++) {
      if (haystack[offset] == c) {
        return (haystack+offset);
      }
    }
  }
  return NULL;
}

/**
 * o_strrchr
 * a modified strrchr function that don't crash when haystack is NULL
 */
char * o_strrchr(const char * haystack, int c) {
  if (haystack == NULL) {
    return NULL;
  } else {
    return strrchr(haystack, c);
  }
}

/**
 * o_strrnchr
 * a modified strrnchr function that don't crash when haystack is NULL
 */
const char * o_strrnchr(const char * haystack, size_t len, char c) {
  ssize_t offset;
  if (haystack != NULL && len > 0) {
    for (offset = o_strlen(haystack)-1; offset>=0 && (o_strlen(haystack) - 1 - offset < len); offset--) {
      if (haystack[offset] == c) {
        return (haystack+offset);
      }
    }
  }
  return NULL;
}

#if defined(__linux__) || defined(__GLIBC__) || defined(_WIN32) || defined(O_STRSTR)
static char *strnstr(const char *haystack, const char *needle, size_t len) {
  int i;
  size_t needle_len;

  /* segfault here if needle is not NULL terminated */
  if (0 == (needle_len = strlen(needle)))
    return (char *)haystack;

  for (i=0; i<=(int)(len - needle_len); i++) {
    if ((haystack[0] == needle[0]) && (0 == strncmp(haystack, needle, needle_len)))
      return (char *)haystack;

    haystack++;
  }
  return NULL;
}
#endif

#ifdef _WIN32
static char *strcasestr(const char *haystack, const char *needle) {
  size_t n;
  if (haystack == NULL || needle == NULL) {
    return NULL;
  }
  n = o_strlen(needle);
  while (*haystack) {
    if (!strnicmp(haystack++, needle, n)) {
      return (char *)(haystack-sizeof(char));
    }
  }
  return NULL;
}
#endif

/**
 * o_strnstr
 * a modified strnstr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strnstr(const char * haystack, const char * needle, size_t len) {
  if (haystack == NULL || needle == NULL) {
    return NULL;
  } else {
    return strnstr(haystack, needle, len);
  }
}

/**
 * o_strcasestr
 * a modified strcasestr function that don't crash when haystack is NULL or needle us NULL
 */
char * o_strcasestr(const char * haystack, const char * needle) {
  if (haystack == NULL || needle == NULL) {
    return NULL;
  } else {
    return strcasestr(haystack, needle);
  }
}

/**
 * o_strlen
 * a modified version of strlen that don't crash when s is NULL
 */
size_t o_strlen(const char * s) {
  if (s == NULL) {
    return 0;
  } else {
    return strlen(s);
  }
}

/**
 * Split a string into an array of strings using separator string
 * return the number of elements to be returned, 0 on error
 * if return_array is not NULL, set the returned array in it
 * return_array is an array of char * ending with a NULL value
 * return_array must be free'd after use
 * you can use free_string_array to free return_array
 */
size_t split_string(const char * string, const char * separator, char *** return_array) {
  size_t result = 0;
  char * token;
  const char * begin = string;
  
  if (string != NULL && separator != NULL) {
    if (return_array != NULL) {
      *return_array = NULL;
    }
    result = 1;
    token = strstr(begin, separator);
    while (token != NULL) {
      if (return_array != NULL) {
        (*return_array) = o_realloc((*return_array), (result + 1)*sizeof(char*));
        if ((*return_array) != NULL) {
          (*return_array)[result-1] = o_strndup(begin, (token-begin));
          (*return_array)[result] = NULL;
        }
      }
      result++;
      begin = token+strlen(separator);
      token = strstr(begin, separator);
    }
    if (return_array != NULL) {
      (*return_array) = o_realloc((*return_array), (result + 1)*sizeof(char*));
      if ((*return_array) != NULL) {
        (*return_array)[result-1] = o_strdup(begin);
        (*return_array)[result] = NULL;
      }
    }
  }
  return result;
}

/**
 * Clean an array of strings
 */
void free_string_array(char ** array) {
  int i;
  if (array != NULL) {
    for (i=0; array[i] != NULL; i++) {
      o_free(array[i]);
      array[i] = NULL;
    }
    o_free(array);
  }
}

/**
 * Count the number of elements in an array of strings
 */
size_t string_array_size(char ** array) {
  size_t ret = 0;
  if (array != NULL) {
    for (;array[ret] != NULL; ret++);
  }
  return ret;
}

/**
 * Join a string array into a single string
 */
char * string_array_join(const char ** array, const char * separator) {
  char * to_return = NULL, * tmp;
  int i;
  
  if (array != NULL && separator != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (to_return == NULL) {
        to_return = o_strdup(array[i]);
      } else {
        tmp = msprintf("%s%s%s", to_return, separator, array[i]);
        o_free(to_return);
        to_return = tmp;
      }
    }
  }
  return to_return;
}

/**
 * Remove string of beginning and ending whitespaces
 */
char * trimwhitespace(char * str) {
  char * end;

  if (str == NULL) {
    return NULL;
  } else if(*str == 0) {
    return str;
  }

  while(isspace((unsigned char)*str)) str++;

  end = str + o_strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) {
    end--;
  }

  *(end+1) = 0;

  return str;
}

/**
 * Remove string of beginning and ending given character
 */
char * trimcharacter(char * str, char to_remove) {
  char * end;

  if (str == NULL) {
    return NULL;
  } else if(*str == 0) {
    return str;
  }

  while(*str == to_remove) str++;

  end = str + o_strlen(str) - 1;
  while(end > str && (*end == to_remove)) {
    end--;
  }

  *(end+1) = 0;

  return str;
}

/**
 * Check if an array of string has a specified value, case sensitive
 */
int string_array_has_value(const char ** array, const char * needle) {
  int i;
  if (array != NULL && needle != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (o_strcmp(array[i], needle) == 0) {
        return 1;
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * Check if an array of string has a specified value, case insensitive
 */
int string_array_has_value_case(const char ** array, const char * needle) {
  int i;
  if (array != NULL && needle != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (o_strcasecmp(array[i], needle) == 0) {
        return 1;
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * Check if an array of string has a specified value, case sensitive, limit to len characters
 */
int string_array_has_value_n(const char ** array, const char * needle, size_t len) {
  int i;
  if (array != NULL && needle != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (o_strncmp(array[i], needle, len) == 0) {
        return 1;
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * Check if an array of string has a specified value, case insensitive, limit to len characters
 */
int string_array_has_value_ncase(const char ** array, const char * needle, size_t len) {
  int i;
  if (array != NULL && needle != NULL) {
    for (i=0; array[i] != NULL; i++) {
      if (o_strncasecmp(array[i], needle, len) == 0) {
        return 1;
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * Check if an array of string has a specified trimmed value
 */
int string_array_has_trimmed_value(const char ** array, const char * needle) {
  int i, to_return = 0;
  char * duplicate_needle, * trimmed_needle, * duplicate_value, * trimmed_value;
  if (array != NULL && needle != NULL) {
    duplicate_needle = o_strdup(needle);
    if (duplicate_needle != NULL) {
      trimmed_needle = trimwhitespace(duplicate_needle);
      for (i=0; array[i] != NULL && !to_return; i++) {
        duplicate_value = o_strdup(array[i]);
        if (duplicate_value == NULL) {
          break;
        } else {
          trimmed_value = trimwhitespace(duplicate_value);
          if (o_strcmp(trimmed_value, trimmed_needle) == 0) {
            to_return = 1;
          }
        }
        o_free(duplicate_value);
      }
    }
    o_free(duplicate_needle);
  }
  return to_return;
}

/**
 * pointer_list_init
 * Initialize a pointer list structure
 */
void pointer_list_init(struct _pointer_list * pointer_list) {
  if (pointer_list != NULL) {
    pointer_list->size = 0;
    pointer_list->list = NULL;
  }
}

/**
 * pointer_list_clean
 * Clean a pointer list structure
 */
void pointer_list_clean(struct _pointer_list * pointer_list) {
  size_t i;
  if (pointer_list != NULL) {
    for (i=pointer_list_size(pointer_list); i; i--) {
      pointer_list_remove_at(pointer_list, (i-1));
    }
  }
}

/**
 * pointer_list_clean_free
 * Clean a pointer list structure
 * Free all elements using the free_function given in parameters
 */
void pointer_list_clean_free(struct _pointer_list * pointer_list, void (* free_function)(void * elt)) {
  size_t i;
  if (pointer_list != NULL) {
    for (i=pointer_list_size(pointer_list); i; i--) {
      free_function(pointer_list_get_at(pointer_list, i-1));
      pointer_list_remove_at(pointer_list, (i-1));
    }
  }
}

/**
 * pointer_list_size
 * Return the size of a pointer list
 */
size_t pointer_list_size(struct _pointer_list * pointer_list) {
  if (pointer_list != NULL) {
    return pointer_list->size;
  } else {
    return 0;
  }
}

/**
 * pointer_list_append
 * Appends an element at the end of a pointer list
 * Return 1 on success, 0 on error
 */
int pointer_list_append(struct _pointer_list * pointer_list, void * element) {
  if (pointer_list) {
    pointer_list->list = o_realloc(pointer_list->list, (pointer_list->size+1)*sizeof(void *));
    if (pointer_list->list != NULL) {
      pointer_list->list[pointer_list->size] = element;
      pointer_list->size++;
      return 1;
    } else {
      o_free(pointer_list->list);
      pointer_list->list = NULL;
      return 0;
    }
  } else {
    return 0;
  }
}

/**
 * pointer_list_get_at
 * Returns an element of a pointer list at the specified index or NULL if non valid index
 */
void * pointer_list_get_at(struct _pointer_list * pointer_list, size_t index) {
  if (pointer_list != NULL && index < pointer_list->size) {
    return pointer_list->list[index];
  } else {
    return NULL;
  }
}

/**
 * pointer_list_remove_at
 * Removes an element of a pointer list at the specified index
 * Return 1 on success, 0 on error or non valid index
 */
int pointer_list_remove_at(struct _pointer_list * pointer_list, size_t index) {
  size_t i;
  if (pointer_list != NULL && index < pointer_list->size) {
    for (i=index; i<pointer_list->size-1; i++) {
      pointer_list->list[i] = pointer_list->list[i+1];
    }
    if (pointer_list->size > 1) {
      pointer_list->list = o_realloc(pointer_list->list, (pointer_list->size-1)*sizeof(void *));
    } else {
      o_free(pointer_list->list);
      pointer_list->list = NULL;
    }
    pointer_list->size--;
    return 1;
  } else {
    return 0;
  }
}

/**
 * pointer_list_remove_at_free
 * Removes an element of a pointer list at the specified index
 * Return 1 on success, 0 on error or non valid index
 * Free the element using the free_function given in parameters
 */
int pointer_list_remove_at_free(struct _pointer_list * pointer_list, size_t index, void (* free_function)(void * elt)) {
  if (pointer_list != NULL && index < pointer_list->size) {
    free_function(pointer_list_get_at(pointer_list, index));
    return pointer_list_remove_at(pointer_list, index);
  } else {
    return 0;
  }
}

/**
 * pointer_list_insert_at
 * Inserts an element at the specified index of a pointer list
 * Return 1 on success, 0 on error or non valid index
 */
int pointer_list_insert_at(struct _pointer_list * pointer_list, void * element, size_t index) {
  size_t i;
  if (pointer_list != NULL && index <= pointer_list->size) {
    pointer_list->list = o_realloc(pointer_list->list, (pointer_list->size + 1)*sizeof(void *));
    if (pointer_list->list != NULL) {
      for (i=pointer_list->size; i>index; i--) {
        pointer_list->list[i] = pointer_list->list[i-1];
      }
      pointer_list->list[index] = element;
      pointer_list->size++;
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

/**
 * pointer_list_remove_at
 * Removes an element of a pointer list corresponding to the specified element
 * Return 1 on success, 0 on error or non valid element
 */
int pointer_list_remove_pointer(struct _pointer_list * pointer_list, void * element) {
  size_t index;
  if (pointer_list != NULL) {
    for (index=0; index<pointer_list->size; index++) {
      if (pointer_list->list[index] == element) {
        return pointer_list_remove_at(pointer_list, index);
      }
    }
    return 0;
  } else {
    return 0;
  }
}

/**
 * pointer_list_remove_pointer_free
 * Removes an element of a pointer list corresponding to the specified element
 * Free the element using the free_function given in parameters
 * Return 1 on success, 0 on error or non valid element
 */
int pointer_list_remove_pointer_free(struct _pointer_list * pointer_list, void * element, void (* free_function)(void * elt)) {
  size_t index;
  if (pointer_list != NULL) {
    for (index=0; index<pointer_list->size; index++) {
      if (pointer_list->list[index] == element) {
        free_function(element);
        return pointer_list_remove_at(pointer_list, index);
      }
    }
    return 0;
  } else {
    return 0;
  }
}
