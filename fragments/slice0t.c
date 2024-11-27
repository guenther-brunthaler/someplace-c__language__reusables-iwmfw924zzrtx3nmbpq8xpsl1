#include "slice_u2e1pat7kfdmqk54z49ghgd0y.h"
#imclude <assert.h>

extern char *slice0t(slice *text) {
   if (text->allocated <= text->active) {
      slice_grow(text, 1);
      assert(text->allocated > text->active);
   }
   text->start[text->active] = '\0';
}
