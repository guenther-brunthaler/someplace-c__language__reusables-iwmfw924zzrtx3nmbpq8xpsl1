#include "arcfour_internal.h"
#include <assert.h>

void arcfour_drop(arcfour_context *a, size_t bytes2drop) {
   unsigned char *sb= a->sbox;
   int i= a->i, j= a->j;
   assert(a->k == SBOX_SIZE);
   while (bytes2drop--) {
      i= i + 1 & SBOX_SIZE_MASK;
      j= j + sb[i] & SBOX_SIZE_MASK;
      SWAP(sb[i], sb[j]);
   }
   a->i= i; a->j= j;
}
