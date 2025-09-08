/* v2025.251 */

/* Provides: getopt-simplest.h "bfi2xi5gyw05etrqnstev8ykl" v2025.251 */
#include <getopt_nh7lll77vb62ycgwzwf30zlln.h>

/* Provides: stdio.h "gqqiypaw4uwwi7bnygtx58n8k" v2025.251 */
#include <stdio.h>

/* Provides: getopt_simplest_perror_missing_arg
 * "p5fcgpnze5wex3la43kzrukd1" v2025.251
 * Requires: getopt-simplest.h "bfi2xi5gyw05etrqnstev8ykl"
\* Requires: stdio.h "gqqiypaw4uwwi7bnygtx58n8k" */
extern void getopt_simplest_perror_missing_arg(int option_char) {
   (void)fputs("Missing mandatory argument for option -", stderr);
   (void)fputc(option_char, stderr);
   (void)fputs("!\n", stderr);
}
