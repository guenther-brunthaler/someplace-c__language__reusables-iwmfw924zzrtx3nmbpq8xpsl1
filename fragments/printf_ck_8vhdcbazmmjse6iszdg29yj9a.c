/* Provides: printf_ck-8vhdcbazmmjse6iszdg29yj9a */
/* Requires: stdio.h-8vagj4enqe40ubxjpqrpvyr05 */
/* Requires: stdarg.h-8vc3k18lhrgxrla08gacsd4w1 */
/* Requires: write_error-8vgmhc1xta7fci46nvmjk7kf7 */

extern void printf_ck(char const *format, ...) {
   int rc;
   {
      va_list args;
      va_start(args, format);
      rc = vprintf(format, args);
      va_end(args);
   }
   if (rc < 0) raise_write_error();
}
