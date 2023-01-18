#include "arcfour_internal.h"
#include <assert.h>

void arcfour_fill(arcfour_context *a, void *block, size_t block_bytes) {
   unsigned char *sb= a->sbox;
   size_t bi= 0;
   int i= a->i, j= a->j;
   assert(a->k == SBOX_SIZE);
   #define block_set(i, val) ( \
      ((unsigned char *)block)[i]= (unsigned char)(val) \
   )
   while (block_bytes--) {
      int si, sj;
      i= i + 1 & SBOX_SIZE_MASK;
      j= j + sb[i] & SBOX_SIZE_MASK;
      si= sb[i]; sb[i]= sj= sb[j]; sb[j]= si;
      block_set(bi++, sb[si + sj & SBOX_SIZE_MASK]);
   }
   #undef block_set
   a->i= i; a->j= j;
}
