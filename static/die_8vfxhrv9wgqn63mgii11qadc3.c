/* Provides: die-8vfxhrv9wgqn63mgii11qadc3 */
/* Requires: stdlib.h-p68c8i02e9jtk0r1qzlaw60zy */
/* Requires: stdio.h-8vagj4enqe40ubxmmurd7q25x */
/* Requires: stdarg.h-8vc3k18lhrgxrla3kkzv3wevw */

static void die(char const *format, ...) {
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
