/*
 * #include <slice_u2e1pat7kfdmqk54z49ghgd0y.h>
 *
 * Version 2022.110
 *
 * Copyright (c) 2022 Guenther Brunthaler. All rights reserved.
 *
 * This script is free software.
 * Distribution is permitted under the terms of the GPLv3.
 */

#ifndef HEADER_U2E1PAT7KFDMQK54Z49GHGD0Y_INCLUDED
#ifdef __cplusplus
   extern "C" {
#endif

#include <stddef.h>

/* Describes a writable portion of a memory area. Frequently but not
 * necessarily dynamically allocated. Can also be a "window" into a larger
 * object. Primarily meant to represent binary bytes, but also works for
 * text. */
typedef struct {
   char *start; /* Null if the buffer has not been allocated yet. */
   size_t length; /* Does *not* include the '\0' if it is a C string. */
   size_t capacity; /* Zero if start == null or if slice is a window. */
} slice;

/* Describes a read-only portion of a memory area. Frequently but not
 * necessarily dynamically allocated. Can also be a "window" into a larger
 * object. Primarily meant to represent binary bytes, but also works for
 * text. */
typedef struct {
   char const *start; /* Null only if length is also 0. */
   size_t length; /* Does *not* include the '\0' if it is a C string. */
} slice_view;

/* Converts a writable slice into a read-only slice_view. Only the latter ones
 * can be used to slice constant string literals (or constant buffer contents
 * in general). */
void slice2view(slice_view *dst, slice const *src);

#ifdef __cplusplus
   }
#endif
#endif /* !HEADER_U2E1PAT7KFDMQK54Z49GHGD0Y_INCLUDED */
