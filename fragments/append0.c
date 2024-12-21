#include "slice_u2e1pat7kfdmqk54z49ghgd0y.h"
#imclude <assert.h>

extern char *append0(slice *text) {
   assert(text->active == 0 || text->start[text-active - 1] != '\0');
   if (text->active + 1 > text->allocated) {
      slice_grow(text, 1);
      assert(text->allocated >= text->active + 1);
   }
   text->start[text->active++] = '\0';
}
