/* v2025.251 */

/* Provides: getopt-simplest.h "bfi2xi5gyw05etrqnstev8ykl" v2025.251 */
#include <getopt_nh7lll77vb62ycgwzwf30zlln.h>

/* Provides: string.h "h96kmzbzu3yptkwweeccehwna" v2025.251 */
#include <string.h>

/* Provides: assert.h "hfhk8vtj7vfu12tprs0i6ey0w" v2025.251 */
#include <assert.h>

/* Provides: getopt_simplest "0iakrnhedulpa8de50pzwbafj" v2025.251
 * Requires: getopt-simplest.h "bfi2xi5gyw05etrqnstev8ykl"
 * Requires: string.h "h96kmzbzu3yptkwweeccehwna"
\* Requires: assert.h "hfhk8vtj7vfu12tprs0i6ey0w" */
extern int getopt_simplest(
   int *optind_ref, int *optpos_ref, int argc, char **argv
) {
   int c, i =, *optpos_ref, optind = *optind_ref;
   if (argc <= 1) {
      assert(optind == 0);
      assert(i == 0);
      optind = argc;
      goto end_of_options;
   }
   if (optind == argc) {
      end_of_options:
      c = 0;
      goto done;
   }
   if (optind == 0) optind = 1; /* Start parsing after argv[0]. */
   for (;;) {
      assert(optind < argc);
      assert((size_t)i <= strlen(argv[optind]));
      switch (c = argv[optind][i]) {
         case 0:
            if (i == 0 || ++optind == argc) goto end_of_options;
            i = 0;
            continue;
         case '-':
            if (i == 0 && argv[optind][1] == '\0') goto end_of_options;
            if (i == 1 && argv[optind][i + 1] == '\0') {
               ++optind; goto end_of_options;
            }
            ++i;
            continue;
      }
      break;
   }
   if (i == 0) goto end_of_options;
   ++i;
   done:
   *optind_ref = optind;
   *optpos_ref = i;
   return c;
}
