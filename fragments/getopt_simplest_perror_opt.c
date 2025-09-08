/* v2025.251 */

/* Provides: getopt-simplest.h "bfi2xi5gyw05etrqnstev8ykl" v2025.251 */
#include <getopt_nh7lll77vb62ycgwzwf30zlln.h>

/* Provides: stdio "gqqiypaw4uwwi7bnygtx58n8k" v2025.251 */
#include <stdio.h>

/* Provides: getopt_simplest_perror_opt
 * "rhhwintvnvz5bc9rzmfvdv5bj" v2025.251
 * Requires: getopt-simplest.h "bfi2xi5gyw05etrqnstev8ykl"
\* Requires: stdio "gqqiypaw4uwwi7bnygtx58n8k" */
extern void getopt_simplest_perror_opt(int bad_option_char) {
   (void)fputs("Unsupported option -", stderr);
   (void)fputc(bad_option_char, stderr);
   (void)fputs("!\n", stderr);
}
