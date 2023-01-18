#include "arcfour_internal.h"
#include <assert.h>

void arcfour_init(arcfour_context *a) {
   unsigned char *sb= a->sbox;
   int i;
   for (i= SBOX_SIZE; i--; ) sb[i]= (unsigned char)i;
   a->i= a->j= a->k= 0;
}

void arcfour_set_key_from_added_key_bytes(arcfour_context *a) {
   unsigned char *sb= a->sbox;
   int i= a->i, j= a->j, k= a->k;
   if (k != SBOX_SIZE && k) {
      unsigned char *kp= a->key_prefix;
      int ki= 0, kn= k;
      assert(k < SBOX_SIZE);
      do {
         j= j + sb[i] + kp[ki] & SBOX_SIZE_MASK;
         if (++ki == kn) ki= 0;
         SWAP(sb[i], sb[j]);
         i= i + 1 & SBOX_SIZE_MASK;
      } while (++k != SBOX_SIZE);
      while (kn) kp[--kn]= 0; /* Wipe key remains from buffer. */
      a->k= k;
   }
   a->i= a->j= 0;
}
