#ifndef STR_H
#define STR_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Get the size of the string
 */
size_t str_length(const char *str);

/*
 * Compare the two strings
 */
int str_compare(const char *str1, const char *str2);

/*
 * Search for the needle in the haystack
 */
const char *str_search(const char *haystack, const char *needle);

#ifdef __cplusplus
}
#endif

#endif /* STR_H */
