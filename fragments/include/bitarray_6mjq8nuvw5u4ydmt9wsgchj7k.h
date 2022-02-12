/* #include <bitarray_6mjq8nuvw5u4ydmt9wsgchj7k.h> */

#ifndef HEADER_6MJQ8NUVW5U4YDMT9WSGCHJ7K_INCLUDED

/*
 * Bit-Array helper macros.
 *
 * The macros accept parameter "a" as arguments, which must be a "char" array
 * or pointer.
 *
 * You need to define two macros with the same name as the actual
 * "a" plus the suffix "_first_index" and "_last_index" appended to that name.
 *
 * a_first_index specifies the index you want to use for accessing the first
 * element of the bit array.
 *
 * a_last_index specifies the index you want to use for accessing the last
 * element of the bit array.
 *
 * a_first_index and a_last_index may be negative. If both are constants,
 * bitarray_char_size(a) which returns the byte size of the bit array may be
 * used as an array size constant for a "char" array.
 *
 * In either case, the bitget() and bitassign() macros can be used to read and
 * write the bit values from/to the bit array.
 *
 * Version 2022.43
 *
 * Copyright (c) 2022 Guenther Brunthaler. All rights reserved.
 *
 * This source file is free software.
 * Distribution is permitted under the terms of the GPLv3.
 */

#if 0
/* Example for a 0-based 256-element bit-array stored in "char"-array
 * "myvar". */
#define myvar_first_index 0
#define myvar_last_index 255
static char myvar[bitarray_char_size(myvar)];
#endif

#define baseindex(a) a ## _first_index
#define maxindex(a) a ## _last_index

#define bitarray_char_size(a) ((maxindex(a) + 1 - baseindex(a) + 8 - 1) >> 3)

#define bitget(a, i) ( \
   !!( \
      (unsigned)(a)[(i) - baseindex(a) >> 3] & 1 << ((i) - baseindex(a) & 7) \
   ) \
)

#define bitassign(a, i, v) do { \
   unsigned \
         i_ = (i) - baseindex(a) \
      ,  bitmask= 1u << (i_ & 7) \
      ,  pack= (unsigned)(a)[i_>>= 3] & ~bitmask \
   ; \
   if (v) pack|= bitmask; \
   (a)[i_]= (char)pack; \
} while (0)

#endif /* !HEADER_6MJQ8NUVW5U4YDMT9WSGCHJ7K_INCLUDED */
