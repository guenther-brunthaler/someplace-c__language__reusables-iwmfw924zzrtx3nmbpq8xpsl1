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
 * Version 2025.246
 * Copyright (c) 2025 Guenther Brunthaler. All rights reserved.
 *
 * This source file is free software.
\* Distribution is permitted under the terms of the GPLv3. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct resource_tag resource;
struct resource_tag {
   resource *link; /* Next older resource. */
   void *ivars; /* Instance variables of resource object. */
   /* Destructor or other kind of cleanup-time action. */
   void (*action)(
      resource **rlist /* Address of pointer to first resource list entry. */
   );
};

static resource **get_rlist(void) {
   /* Change first "0" into "01" in order to enable multithreading support. */
   #if 0 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
      _Thread_local /* Multi-threaded; requires C11 or newer. */
   #else
      static /* Single threaded. */
   #endif
   resource *rlist; /* Currently allocated resources. */
   return &rlist;
}

/* Get a handle for release_trk() to only release resources new than now. */
static resource *mark_trk(void) {
   return *get_rlist();
}

/* Pass NULL in order to release all resources. */
static void release_trk(resource *stop) {
   resource **rlist = get_rlist();
   while (*rlist != stop) (*(*rlist)->action)(rlist);
}

static void die(char const *emsg) {
   size_t len;
   if (((len = strlen(emsg)) != 0) && strspn(&emsg[len - 1], ".!?") != 0) {
      (void)fputs(emsg, stderr); (void)fputc('\n', stderr);
   } else {
      perror(emsg);
   }
   release_trk(NULL);
   exit(EXIT_FAILURE);
}

static void *malloc_ck(size_t bytes) {
   void *p;
   if ((p = malloc(bytes)) == NULL) die("Memory allocation failure");
   return p;
}

static void *realloc_ck(void *p, size_t new_sz) {
   if ((p = realloc(p, new_sz)) == NULL) {
      die("Failure resizing memory block");
   }
   return p;
}

/* Buffer managment. */

typedef struct {
   char *start;
   size_t active, allocated;
} slice;

struct slice_rsrc {
   slice obj;
   resource tracker;
};

static void slice_dtor(void) {
   struct slice_rsrc *sr;
   if ((sr = rlist->ivars)->obj.allocated != 0) free(sr->obj.start);
   rlist = sr->tracker.link; free(sr);
}

static slice *slice_alloc_trk(void) {
   struct slice_rsrc *r = malloc_ck(sizeof *r);
   r->obj.start = NULL; r->obj.allocated = r->obj.active = 0;
   r->tracker.ivars = r; r->tracker.action = &slice_dtor;
   r->tracker.link = rlist; rlist = &r->tracker; return &r->obj;
}

static void slice_grow(slice *sl, size_t larger) {
   size_t nsz = 1;
   assert(larger > sl->allocated); /* No unnecessary invocations! */
   while (nsz < larger) nsz += nsz;
   sl->start = realloc_ck(sl->start, nsz); sl->allocated = nsz;
}

static void slice_fit(slice *sl) {
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

static void read_error(void) {
   die("Read error");
}

static void write_error(void) {
   die("Write error");
}

/* Repeat reading until <bytes_wanted> bytes have been read. Returns the
 * number of bytes actually read, which will only be less than <bytes_wanted>
 * if EOF has been encountered. Ensure there are no read errors. */
static size_t try_fread_most(void *dst, size_t bytes_wanted, FILE *input) {
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
