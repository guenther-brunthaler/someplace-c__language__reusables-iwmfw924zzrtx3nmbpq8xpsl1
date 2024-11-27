/*
 * #include <slice_u2e1pat7kfdmqk54z49ghgd0y.h>
 *
 * Version 2024.332
 * Copyright (c) 2022-2024 Guenther Brunthaler. All rights reserved.
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
 * The '\0' terminator of C strings is normally put within "allocated" right
 * after "active", so that "active" == strlen(start). */
typedef struct {
   char *start; /* If NULL then yet unallocated buffer. */
   size_t active; /* Must be <= allocated but only if allocated != 0. */
   size_t allocated; /* If non-zero or start == NULL: Slice is resizable. */
} slice;

/* Describes a read-only portion of a memory area. Frequently but not
 * necessarily dynamically allocated. Can also be a "window" into a larger
 * object. Primarily meant to represent binary bytes, but also works for
 * text. */
typedef struct {
   char const *start; /* Null only if active is also 0. */
   size_t active; /* Does *not* include the '\0' if it is a C string. */
} slice_view;

/* Converts a writable slice into a read-only slice_view. Only the latter ones
 * can be used to slice constant string literals (or constant buffer contents
 * in general). */
void slice2view(slice_view *dst, slice const *src);

/* Writes '\0' right after the "active" portion of the buffer. Returns the new
 * "start" in case the buffer had to be grown, otherwise the unchanged one. */
char *slice0t(slice *text);

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
