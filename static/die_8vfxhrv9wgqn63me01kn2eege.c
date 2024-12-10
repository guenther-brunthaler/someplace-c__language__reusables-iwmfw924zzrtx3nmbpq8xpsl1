/* Provides: die-8vfxhrv9wgqn63me01kn2eege */
/* Requires: stdlib.h-p68c8i02e9jtk0r18n9hz1g3w */
/* Requires: stdio.h-8vagj4enqe40ubxjpqrpvyr05 */
/* Requires: stdarg.h-8vc3k18lhrgxrla08gacsd4w1 */

extern void die(char const *format, ...) {
   {
      va_list args;
      va_start(args, format);
      (void)vfprintf(stderr, format, args);
      va_end(args);
   }
   (void)fputc('\n', stderr);
   free_all_resources();
   exit(EXIT_FAILURE);
}
