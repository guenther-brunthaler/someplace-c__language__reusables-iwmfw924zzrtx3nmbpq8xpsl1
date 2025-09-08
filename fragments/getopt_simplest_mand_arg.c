/* v2025.251 */

/* Provides: getopt-simplest.h "bfi2xi5gyw05etrqnstev8ykl" v2025.251 */
#include <getopt_nh7lll77vb62ycgwzwf30zlln.h>

/* Provides: assert.h "hfhk8vtj7vfu12tprs0i6ey0w" v2025.251 */
#include <assert.h>

/* Provides: getopt_simplest_mand_arg "kmtkp3nhyhhsl4khbszdhlakb" v2025.251
 * Requires: getopt-simplest.h "bfi2xi5gyw05etrqnstev8ykl"
\* Requires: assert.h "hfhk8vtj7vfu12tprs0i6ey0w" */
extern char const *getopt_simplest_mand_arg(
   int *optind_ref, int *optpos_ref, int argc, char **argv
) {
   int i = *optpos_ref, optind = *optind_ref;
   char const *arg;
   assert(optind >= 1);
   assert(optind <= argc);
   if (i == 0 || optind == argc) return 0;
   if (argv[optind][i]) {
      arg = argv[optind] + i;
   } else {
      arg = argv[++optind];
   }
   *optind_ref = optind + 1;
   *optpos_ref = 0;
   return arg;
}
