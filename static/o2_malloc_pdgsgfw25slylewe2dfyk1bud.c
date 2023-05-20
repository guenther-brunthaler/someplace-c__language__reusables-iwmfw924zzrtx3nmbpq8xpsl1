/* Provides: o2_malloc-pdgsgfw25slylewe2dfyk1bud */
/* Requires: stdlib.h-p68c8i02e9jtk0r18n9hz1g3w */
/* Requires: die-8vfxhrv9wgqn63me01kn2eege */

static void *o2_malloc(size_t bytes) {
   void *p;
   if (!(p = malloc(bytes))) {
      die(
         "Failed to allocate "
         #if !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901
            "%lu"
         #else
            "%z"
         #endif
         " bytes of memory!"
         #if !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901
            , (unsigned long)bytes
         #else
            , bytes
         #endif
      );
   }
   return p;
}
