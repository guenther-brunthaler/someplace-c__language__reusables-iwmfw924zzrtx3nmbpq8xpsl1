/* Provides: no_options-pdg0ldk70utdx0dz67379ge3c */
/* Requires: string.h-8vbaylzhw8ud12b892hgml1mf */
/* Requires: die-8vfxhrv9wgqn63mgii11qadc3 */

/* Set <i> to first argument after any program name and options. Only "--" is
 * supported. */
static void no_options(int *i_ref, int argc, char *const *argv) {
   int i;
   if ((i = 0) < argc && ++i < argc) {
      if (argv[i][0] ==  '-') {
         if (!strcmp(argv[i], "--")) {
            ++i;
         } else if (argv[i][1]) {
            die("Unsupported option -%c", argv[i][1]);
         }
      }
   }
   *i_ref = i;
}

