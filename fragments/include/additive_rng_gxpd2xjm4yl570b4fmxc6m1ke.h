/* #include <additive_rng_gxpd2xjm4yl570b4fmxc6m1ke.h> */

#ifndef HEADER_GXPD2XJM4YL570B4FMXC6M1KE_INCLUDED
#ifdef __cplusplus
   extern "C" {
#endif

#include <stddef.h>

#define RND_ARRAY_SIZE 55

typedef struct {
   unsigned long state[RND_ARRAY_SIZE];
   int i;
} random_context;

typedef struct {
   unsigned downshift, bitmask, beyond;
   random_context *rng;
} random_range;

/* Initialize and seed an instance of the additive random number generator.
 *
 * The <seed> can be anything and any size, binary or text. */
void random_init(random_context *rng, void const *seed, size_t seed_bytes);

/* Calculates parameter for efficiently calculating a random number between
 * 0 (inclusive) and <range> (exclusive). */
void random_mkrange(random_range *r, random_context *rng, int range);

/* Return the next random number according to the specified value range. */
int random(random_range const range);

#ifdef __cplusplus
   }
#endif
#endif /* !HEADER_GXPD2XJM4YL570B4FMXC6M1KE_INCLUDED */
