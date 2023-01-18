/* #include <arcfour_n2pvvr03sdmwzv42z4f2cq3g3.h> */

#ifndef HEADER_N2PVVR03SDMWZV42Z4F2CQ3G3_INCLUDED
#ifdef __cplusplus
   extern "C" {
#endif

#include <stddef.h>

#define SBOX_SIZE_LOG2 8
#define SBOX_SIZE (1 << SBOX_SIZE_LOG2)
#define KEY_PREFIX_MAXBYTES (SBOX_SIZE / 2)

typedef struct {
   unsigned char sbox[SBOX_SIZE];
   /* Caches initial key bytes. Will be zero-wiped at end of key setup. */
   unsigned char key_prefix[KEY_PREFIX_MAXBYTES];
   int i, j, k;
} arcfour_context;

/* Initialize an ARCFOUR context. After this, key bytes might be added.
 * Finally, a key setup must be done. */
void arcfour_init(arcfour_context *a);

/* Add more bytes of the key.
 *
 * May be called multiple times, or never at all for an empty key. This is not
 * the actual key setup, but rather queues the key data for the key setup
 * later. (Actually, the key data will be processed immediately. However, the
 * key setup must be run later in order to complete the key setup procedure.)
 *
 * As a backwards-compatible extension over the original ARCFOUR key setup,
 * this allows to add more than 256 bytes of key material, and all of them
 * will be processed.
 *
 * Note however that the internal state is limited to a size of 1683 bits.
 * Adding more full-entropy key data will tweak the internal state more, but
 * it can not become more secure than adding 1683 full-entropy key bits.
 * However, if the key does not have full entropy, it actually helps if it is
 * longer than the internal state.
 *
 * This can also be used for MAC calculation. In this case, feed the MAC key
 * first, followed by the data to be integrity-protected, then complete the
 * key setup. Drop at least the initial 768 bytes of the pseudorandom stream,
 * then fill a buffer with pseudorandom data as the MAC. */
void arcfour_add_key_bytes(
   arcfour_context *a, void const *key, size_t key_bytes
);

/* Key setup. This uses any key bytes added before as the key. Key setup
 * is required before any of the encryption functions can be called. */
void arcfour_set_key_from_added_key_bytes(arcfour_context *a);

/* Drop <bytes2drop> bytes of the pseudorandom stream. Only allowed after key
 * setup. It is recommended to drop at least the initial 768 bytes of the
 * pseudorandom stream because they are not very secure. In order to be even
 * more safe, drop the initial 3072 bytes. */
void arcfour_drop(arcfour_context *a, size_t bytes2drop);

/* Generate more pseudorandom bytes and use them to fill the buffer. Only
 * allowed after key setup. */
void arcfour_fill(arcfour_context *a, void *block, size_t block_bytes);

/* Generate more pseudorandom bytes and encrypt or decrypt (works as a toggle)
 * the buffer by XOR'ing the bytes with buffer contents. Only allowed after
 * key setup. */
void arcfour_crypt(arcfour_context *a, void *block, size_t block_bytes);

#ifdef __cplusplus
   }
#endif
#endif /* !HEADER_N2PVVR03SDMWZV42Z4F2CQ3G3_INCLUDED */
