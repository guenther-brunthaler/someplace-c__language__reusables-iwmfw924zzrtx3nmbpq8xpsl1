/* Provides: printf_ck-8vhdcbazmmjse6ivqlvjvptcw */
/* Requires: stdio.h-8vagj4enqe40ubxmmurd7q25x */
/* Requires: stdarg.h-8vc3k18lhrgxrla3kkzv3wevw */
/* Requires: write_error-8vgmhc1xta7fci49cg3cai435 */

static void printf_ck(char const *format, ...) {
   int rc;
   {
      va_list args;
      va_start(args, format);
      rc = vprintf(format, args);
      va_end(args);
   }
   if (rc < 0) raise_write_error();
}

