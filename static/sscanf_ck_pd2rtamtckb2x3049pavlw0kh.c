/* Provides: sscanf_ck-pd2rtamtckb2x3049pavlw0kh */
/* Requires: stdio.h-8vagj4enqe40ubxmmurd7q25x */
/* Requires: string.h-8vbaylzhw8ud12b892hgml1mf */
/* Requires: stdarg.h-8vc3k18lhrgxrla3kkzv3wevw */
/* Requires: assert.h-8vdn7fihgdlw3y9arnm3t02zm */
/* Requires: die-8vfxhrv9wgqn63mgii11qadc3 */

/* sscanf() with error checking.
 *
 * The format <conversion> string must end with "%n", and a reference to the
 * variable which receives that assignment must also be passed as <len_ref>.
 * The function will use this value to verify that the conversions consumed all
 * of the <source> string and that no unconverted data remains at its end. */
static void sscanf_ck(
   int *len_ref, char const *source, char const *conversion, ...
) {
   va_list args;
   assert(len_ref);
   *len_ref = -1;
   assert( \
      strstr(conversion, "%n") \
      && (strstr(conversion, "%n") - conversion) + strlen("%n") \
         == strlen(conversion) \
   );
   va_start(args, conversion);
   if (
      vsscanf(source, conversion, args) < 0
      || (unsigned)*len_ref != strlen(source)
   ) {
      die("Inappropriately formatted input \"%s\"!", source);
   }
   va_end(args);
}

