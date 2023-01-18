#include <additive_rng_gxpd2xjm4yl570b4fmxc6m1ke.h>
#include <arcfour_n2pvvr03sdmwzv42z4f2cq3g3.h>
#include <limits.h>
#include <assert.h>

#define RND_ARRAY_SPECIAL_INDEX 24

void random_init(random_context *rng, void const *seed, size_t seed_bytes) {
   {
      arcfour_context a;
      arcfour_init(&a);
      arcfour_add_key_bytes(&a, seed, seed_bytes);
      arcfour_set_key_from_added_key_bytes(&a);
      arcfour_drop(&a, 3072); /* Warm up. */
      /* Randomize state array. */
      arcfour_fill(&a, rng->state, sizeof rng->state);
   }
   rng->i= 0;
   {
      int i;
      for (i= RND_ARRAY_SIZE; i-- ; ) if (rng->state[i] & 1) return;
      /* Very unlikely that we came here. But not completely impossible. */
      rng->state[RND_ARRAY_SIZE / 2]+= 1; /* Make one element odd. */
   }
}

void random_mkrange(random_range *r, random_context *rng, int range) {
   unsigned bits, mask;
   assert(range >= 1);
   for (bits= mask= 1; (unsigned)range > mask; mask+= mask + 1) ++bits;
   r->downshift= sizeof *rng->state * CHAR_BIT - bits;
   r->bitmask= mask;
   r->beyond= (unsigned)range;
   r->rng= rng;
}

int random(random_range const range) {
   /* Additive random number generator with rejection sampling. */
   random_context *rng= range.rng;
   int i= rng->i;
   for (;;) {
      int j;
      unsigned candidate;
      if (
         (
            j= i + (RND_ARRAY_SIZE - RND_ARRAY_SPECIAL_INDEX)
         ) >= RND_ARRAY_SIZE
      ) {
         j-= RND_ARRAY_SIZE;
         assert(j < RND_ARRAY_SIZE);
      }
      candidate= (unsigned)(
         (rng->state[i]+= rng->state[j]) >> range.downshift & range.bitmask
      );
      if (++i == RND_ARRAY_SIZE) i= 0;
      assert(i < RND_ARRAY_SIZE);
      if (candidate >= range.beyond) continue;
      rng->i= i;
      return (int)candidate;
   }
}
