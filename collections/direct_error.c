/* This is a collection of resource list implementatation functions which
 * write error messages immediately to stderr rather than just storing the
 * error messages an delegate display of it to some error display resource.
 *
 * Also, there is no error nesting count or error condition flag. Therefore,
 * this implementation cannot handle transactions other than always rolling
 * them back in action handlers. Committing transactions must be done in the
 * main program code outside of action handlers.
 *
 * Some conventions used here:
 *
 * + Functions which wrap pre-existing standard API functions and add error
 *   checking (call die() in case of errors) use the same name with _ck
 *   appended.
 *
 * + Functions which check for errors and add some resources to the resource
 *   list have _trk at the end of their names. Exceptions are mark_trk() and
 *   release_trk() which provide support functions for the resource list.
 *
 * + Error messages passed to die() which do not end with an punctuation
 *   character will be displayed by perror(), otherwise only the messages
 *   themselves will be written to standard error.
 *
 * Version 2025.251
 * Copyright (c) 2025 Guenther Brunthaler. All rights reserved.
 *
 * This source file is free software.
\* Distribution is permitted under the terms of the GPLv3. */

/* Provides: stdio.h "gqqiypaw4uwwi7bnygtx58n8k" v2025.251 */
#include <stdio.h>

/* Provides: stddef.h "cb3sxy4z9qsncgg47kyhtv9sk" v2025.251 */
#include <stddef.h>

/* Provides: stdlib.h "h2cvvdvwkvp49is0n4xxr170u" v2025.251 */
#include <stdlib.h>

/* Provides: string.h "h96kmzbzu3yptkwweeccehwna" v2025.251 */
#include <string.h>

/* Provides: assert.h "hfhk8vtj7vfu12tprs0i6ey0w" v2025.251 */
#include <assert.h>

/* Provides: extern-as-static "ct8tlrqyg1kvazbtltc4q5yct" v2025.251 */
#if 01
   /* Make "extern" definitions actually "static".
    *
    * Use this when copying multiple "extern" definitions into the source text
    * of an application made of a single source file. This might allow the
   \* compiler or linker to perform additional optimizations. */
   #define extern static
#endif

/* Provides: resource "0j5v5lysz017ceu3p6hq2t8qk" v2025.251 */
typedef struct resource_tag resource;
struct resource_tag {
   resource *link; /* Next older resource. */
   void *ivars; /* Instance variables of resource object. */
   /* Destructor or other kind of cleanup-time action. */
   void (*action)(
      resource **rlist /* Address of pointer to first resource list entry. */
   );
};

/* Provides: get_rlist "4b4rf68q6t1xem3a0wkut1an8" v2025.251
\* Requires: resource "0j5v5lysz017ceu3p6hq2t8qk" */
extern resource **get_rlist(void) {
   /* Change first "0" into "01" in order to enable multithreading support. */
   #if 0 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
      _Thread_local /* Multi-threaded; requires C11 or newer. */
   #else
      static /* Single threaded. */
   #endif
   resource *rlist; /* Currently allocated resources. */
   return &rlist;
}

/* Provides: mark_tracked "nyaay1n43hkx9qe0ennprd9cg" v2025.251
 * Requires: resource "0j5v5lysz017ceu3p6hq2t8qk"
 * Requires: get_rlist "4b4rf68q6t1xem3a0wkut1an8"
 *
 * Get a handle for release_tracked_until() to only release resources newer
\* than now. */
extern resource *mark_tracked(void) {
   return *get_rlist();
}

/* Provides: release_tracked_until "q0mzr8clpu6xpi4tqanq8f534" v2025.251
 * Requires: resource "0j5v5lysz017ceu3p6hq2t8qk"
 * Requires: get_rlist "4b4rf68q6t1xem3a0wkut1an8"
 *
\* Pass NULL in order to release all resources. */
extern void release_tracked_until(resource *stop) {
   resource **rlist = get_rlist();
   while (*rlist != stop) (*(*rlist)->action)(rlist);
}

/* Provides: die "qm5t8wzj1sx7g08avdqdeqxnq" v2025.251
 * Requires: stdio.h "gqqiypaw4uwwi7bnygtx58n8k"
 * Requires: stdlib.h "h2cvvdvwkvp49is0n4xxr170u"
\* Requires: string.h "h96kmzbzu3yptkwweeccehwna" */
extern void die(char const *emsg) {
   size_t len;
   if (((len = strlen(emsg)) != 0) && strspn(&emsg[len - 1], ".!?") != 0) {
      (void)fputs(emsg, stderr); (void)fputc('\n', stderr);
   } else {
      perror(emsg);
   }
   release_tracked_until(NULL);
   exit(EXIT_FAILURE);
}

/* Provides: malloc_ck "rk2sy4idplk9s62lt1eixve7r" v2025.251
 * Requires: die "qm5t8wzj1sx7g08avdqdeqxnq"
\* Requires: stdlib.h "h2cvvdvwkvp49is0n4xxr170u" */
extern void *malloc_ck(size_t bytes) {
   void *p;
   if ((p = malloc(bytes)) == NULL) die("Memory allocation failure");
   return p;
}

/* Provides: realloc_ck "tj8442d0ztppda37jw9ydmqlh" v2025.251
 * Requires: die "qm5t8wzj1sx7g08avdqdeqxnq"
\* Requires: stdlib.h "h2cvvdvwkvp49is0n4xxr170u" */
extern void *realloc_ck(void *p, size_t new_sz) {
   if ((p = realloc(p, new_sz)) == NULL) {
      die("Failure resizing memory block");
   }
   return p;
}

/* Buffer managment. */

/* Provides: slice "03lw9y1azsmah795p9ttny2yp" v2025.251
\* Requires: stddef.h "cb3sxy4z9qsncgg47kyhtv9sk" */
typedef struct {
   char *start;
   size_t active, allocated;
} slice;

/* Provides: new_tracked_slice "0l5yxz0bdi1vx9k2unjtp7igc" v2025.251
 *
 * Requires: slice "03lw9y1azsmah795p9ttny2yp"
\* Requires: resource "0j5v5lysz017ceu3p6hq2t8qk" */
struct slice_rsrc {
   slice obj;
   resource tracker;
};

/* Requires: stdlib.h "h2cvvdvwkvp49is0n4xxr170u"
\* Requires: resource "0j5v5lysz017ceu3p6hq2t8qk" */
static void slice_dtor(resource **rlist) {
   struct slice_rsrc *sr;
   if ((sr = (*rlist)->ivars)->obj.allocated != 0) free(sr->obj.start);
   *rlist = sr->tracker.link; free(sr);
}

/* Requires: resource "0j5v5lysz017ceu3p6hq2t8qk"
 * Requires: slice "03lw9y1azsmah795p9ttny2yp"
 * Requires: get_rlist "4b4rf68q6t1xem3a0wkut1an8"
\* Requires: malloc_ck "rk2sy4idplk9s62lt1eixve7r" */
extern slice *new_tracked_slice(void) {
   resource **rlist = get_rlist();
   struct slice_rsrc *r = malloc_ck(sizeof *r);
   r->obj.start = NULL; r->obj.allocated = r->obj.active = 0;
   r->tracker.ivars = r; r->tracker.action = &slice_dtor;
   r->tracker.link = *rlist; *rlist = &r->tracker; return &r->obj;
}

/* Provides: slice_grow "10vripgxlib98zaq0b3cpae6t" v2025.251
 * Requires: slice "03lw9y1azsmah795p9ttny2yp"
 * Requires: realloc_ck "tj8442d0ztppda37jw9ydmqlh"
 * Requires: stdlib.h "h2cvvdvwkvp49is0n4xxr170u"
\* Requires: assert.h "hfhk8vtj7vfu12tprs0i6ey0w" */
extern void slice_grow(slice *sl, size_t larger) {
   size_t nsz = 1;
   assert(larger > sl->allocated); /* No unnecessary invocations! */
   while (nsz < larger) nsz += nsz;
   sl->start = realloc_ck(sl->start, nsz); sl->allocated = nsz;
}

/* Provides: slice_fit "1a341l35tb9lf0jb4dg5endtf" v2025.251
 * Requires: slice "03lw9y1azsmah795p9ttny2yp"
 * Requires: realloc_ck "tj8442d0ztppda37jw9ydmqlh"
 * Requires: stdlib.h "h2cvvdvwkvp49is0n4xxr170u"
\* Requires: assert.h "hfhk8vtj7vfu12tprs0i6ey0w" */
extern void slice_fit(slice *sl) {
   assert(sl->allocated > sl->active); /* No unnecessary invocations! */
   assert(sl->allocated != 0); /* Only buffers can be fitted, not views.*/
   if (sl->active == 0) {
      free(sl->start); sl->start = NULL; sl->allocated = 0;
   } else {
      sl->start = realloc_ck(sl->start, sl->active);
      sl->allocated = sl->active;
   }
}

/* Input/Output.*/

/* Provides: read_error "1kqs2xa1bx342pqvu6l2ijyt6" v2025.251
\* Requires: die "qm5t8wzj1sx7g08avdqdeqxnq" */
extern void read_error(void) {
   die("Read error");
}

/* Provides: write_error "1yarz7z0v2caciq9cjcjqam92" v2025.251
\* Requires: die "qm5t8wzj1sx7g08avdqdeqxnq" */
extern void write_error(void) {
   die("Write error");
}

/* Provides: try_fread_most "29mwf3s3amjhckcvq40sbmurb" v2025.251
 * Requires: read_error "1kqs2xa1bx342pqvu6l2ijyt6"
 * Requires: stdio.h "gqqiypaw4uwwi7bnygtx58n8k"
 *
 * Repeat reading until <bytes_wanted> bytes have been read. Returns the
 * number of bytes actually read, which will only be less than <bytes_wanted>
\* if EOF has been encountered. Ensure there are no read errors. */
extern size_t try_fread_most(void *dst, size_t bytes_wanted, FILE *input) {
   size_t read_total = 0;
   do {
      size_t read = fread(dst, 1, bytes_wanted, input);
      if (ferror(input)) read_error();
      read_total += read;
      if ((bytes_wanted -= read) == 0) break;
      dst = (char *)dst + read;
   } while (!feof(input));
   return read_total;
}
