/*
 * #include <slice_u2e1pat7kfdmqk54z49ghgd0y.h>
 *
 * Version 2025.162
 * Copyright (c) 2022-2025 Guenther Brunthaler. All rights reserved.
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
 * object. Primarily meant to represent binary bytes, but also works for text.
 * For text that is a C string, the '\0' terminator must be the last byte of
 * the <active> section of the buffer, so that (<active> - 1) ==
 * strlen(<start>). */
typedef struct {
   char *start; /* If NULL then yet unallocated buffer. */
   size_t active; /* Must be <= <allocated> but only if <allocated> != 0. */
   size_t allocated; /* If != 0 or <start> == NULL: Slice is reallocatable. */
} slice;

/* Describes a read-only portion of a memory area. Frequently but not
 * necessarily dynamically allocated. Can also be a "window" into a larger
 * object. Primarily meant to represent binary bytes, but also works for
 * text. */
typedef struct {
   char const *start; /* Null only if <active> is also 0. */
   size_t active; /* Includes the '\0' if <start> is a C string. */
} slice_view;

/* Converts a writable slice into a read-only slice_view. Only the latter ones
 * can be used to slice constant string literals (or constant buffer contents
 * in general). */
void slice2view(slice_view *dst, slice const *src);

/* Appends '\0' to the current <active> buffer portion in order to establish
 * (<active> - 1) == strlen(<start>). This will convert non-terminated text
 * contents of previous size <active> into a C string. Must not be called if
 * the buffer is already null-terminated. Returns the new <start> in case the
 * buffer had to be reallocated, otherwise the unchanged one. */
char *append0(slice *text);

/* Reallocate the slice. <minimum_new_size> must be larger than its current
 * <allocated> size and also larger than its currently <active> size. The
 * actual allocation size may be larger than requested in order to support
 * efficient incremental growth. Use slice_fit() to get rid of any excess
 * memory that might have been allocated. */
void slice_grow(slice *bytes, size_t minimum_new_size);

/* Shrink the slice by reallocating it if <allocated> is larger than <active>.
 * This will remove any excess memory allocated for the slice by a series of
 * previous calls to slice_grow(). slice_fit() should be called as soon as an
 * incrementally growing buffer has reached its final size, or at least a size
 * which is not expected to grow further anytime soon. */
void slice_fit(slice *bytes);

#ifdef __cplusplus
   }
#endif
#endif /* !HEADER_U2E1PAT7KFDMQK54Z49GHGD0Y_INCLUDED */
