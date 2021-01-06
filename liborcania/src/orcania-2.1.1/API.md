# Orcania library

Potluck with different functions for different purposes that can be shared among C programs.

This is a small library intended to provide low-level functionalities in my other libraries and programs.

The functionalities are divided into 4 categories:

## String functions

- Wrappers for `string.h`: functions like `strcpy`, `strcmp` or `strchr` that will not segfault if a parameter is `NULL`
- `split_string` and afiliated functions: split a string using a separator match or join a split string

## Pointer list structure

Simple structure to store and manipulate any kind of pointer in an array.

## Base64 functions

Encode, decode in base64 and base64url format.

## Memory functions

Replace glib `malloc/realloc/free` functions with user-defined memory functions.
