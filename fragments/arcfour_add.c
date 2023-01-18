#include "arcfour_internal.h"
#include <assert.h>

void arcfour_add_key_bytes(
   arcfour_context *a, void const *key, size_t key_bytes
) {
   #define KEY(k) (((unsigned char const *)key)[k])
   size_t ki= 0;
   unsigned char *sb= a->sbox;
   int i= a->i, j= a->j, k= a->k;
   if (k != SBOX_SIZE) {
      unsigned char *kp= a->key_prefix;
      assert(k < SBOX_SIZE);
      while (key_bytes) {
         unsigned char kb;
         j= j + sb[i] + (kb= KEY(ki++)) & SBOX_SIZE_MASK;
         --key_bytes;
         if (k < KEY_PREFIX_MAXBYTES) kp[k]= kb;
         ++k;
         SWAP(sb[i], sb[j]);
         i= i + 1 & SBOX_SIZE_MASK;
         if (k == SBOX_SIZE) break;
      }
      a->k= k;
   }
   while (key_bytes--) {
      j= j + sb[i] + KEY(ki++) & SBOX_SIZE_MASK;
      SWAP(sb[i], sb[j]);
      i= i + 1 & SBOX_SIZE_MASK;
   }
   #undef KEY
   a->i= i; a->j= j;
}
