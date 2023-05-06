/* v2023.126 */

#include <fmt2023_5tce3liwv5jz99as9fhhugjdh.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

struct insertion_sequence {
   size_t name_bytecount, expansion_bytecount;
   struct insertion_sequence *older;
   char const *name, *expansion;
};

struct fmt2023_ctx {
   int no_write, next_size_known, cmd_introducer;
   size_t next_size;
   char const *stop;
   char *outpos;
   struct insertion_sequence *insertions;
   va_list *args;
};

static void fmt2023_expand(struct fmt2023_ctx *o, char const *format) {
   int trigger, no_write = o->no_write;
   struct insertion_sequence *insertions = o->insertions;
   /* Consider the terminating null character to be part of the format string.
    * This automatically terminates the current output string once all of the
    * format string's bytes have been processed. */
   size_t remaining = strlen(format) + 1;
   if (!(trigger = o->cmd_introducer) && insertions) {
      trigger = o->cmd_introducer = *insertions->name;
   }
   while (remaining) {
      /* Format string not yet exhausted. */
      char const *source;
      size_t bytes;
      if (trigger) {
         if (*format == trigger) {
            /* Possibly at the introducing name character of an insertion
             * sequence. */
            struct insertion_sequence *i;
            for (i = insertions; i; i = i->older) {
               /* Try to locate insertion sequence with matching name. */
               if (
                  remaining >= i->name_bytecount
                  && !memcmp(format, i->name, i->name_bytecount)
               ) {
                  /* Found. */
                  source = i->expansion; bytes = i->expansion_bytecount;
                  format += i->name_bytecount; remaining -= i->name_bytecount;
                  goto append_bytes;
               }
            }
            /* No matching name. Consider current character as a literal one
             * rather than being part of an insertion sequence. */
            if (
               remaining > 1
               && (source = memchr(format + 1, trigger, remaining - 1))
            ) {
               goto append_literally_until_source;
            }
         } else if (source = memchr(format, trigger, remaining)) {
            /* A possible insertion sequence starts later into the format
             * string. Append the text before there as literal text. */
            assert(source > format);
            /* Append prefix of unprocessed part of the format string up to
             * the next possible insertion sequence at <source>. */
            append_literally_until_source:
            bytes = source - format; source = format;
            format += bytes; remaining -= bytes;
            goto append_bytes;
         }
         /* No further possible insertion sequence found. */
      }
      /* No further insertion sequence can possibly exist in the format
       * string.
       *
       * Append the rest of the format string literally. */
      source = format; bytes = remaining; remaining = 0;
      /* Append bytes to the result string (only virtually in case of
       * 'no_write' mode). */
      append_bytes:
      if (o->outpos + bytes > o->stop) o->no_write = no_write = 1;
      if (!no_write) (void)memcpy(o->outpos, source, bytes);
      o->outpos += bytes;
   }
}

static int fmt2023_worker(
   struct fmt2023_ctx *o, struct insertion_sequence *nsq
) {
   for (;;) {
      char const *cmd;
      if (cmd = va_arg(*o->args, char const *)) {
         switch (*cmd) {
            case '\v':
               o->next_size = va_arg(*o->args, size_t); o->next_size_known = 1;
               break;
            case '\r':
               {
                  void **saveloc = va_arg(*o->args, void **);
                  *saveloc = o->outpos;
               }
               break;
            case '\n':
               nsq->name = va_arg(*o->args, char const *);
               nsq->expansion = o->outpos;
               nsq->expansion_bytecount = 0;
               goto register_insertion;
            case '\f':
               cmd = va_arg(*o->args, char const *);
               fmt2023_expand(o, cmd);
               o->insertions->expansion_bytecount=
                  o->outpos - 1 - o->insertions->expansion
               ;
               break;
            default:
               nsq->name = cmd;
               nsq->expansion = va_arg(*o->args, void *);
               nsq->expansion_bytecount=
                  o->next_size_known
                  ? (o->next_size_known = 0 , o->next_size)
                  : strlen(nsq->expansion)
               ;
               register_insertion:
               nsq->name_bytecount = strlen(nsq->name);
               nsq->older = o->insertions;
               o->insertions = nsq;
               return 1;
         }
      } else {
         cmd = va_arg(*o->args, char const *);
         fmt2023_expand(o, cmd);
         return 0;
      }
   }
}

/* Recursion helper, using minimal stack frame. */
static void fmt2023_recurser(struct fmt2023_ctx *o) {
   struct insertion_sequence i;
   if (fmt2023_worker(o, &i)) fmt2023_recurser(o);
}

extern size_t vfmt2023(char *buffer, size_t buffer_size, va_list args) {
   struct fmt2023_ctx o;
   o.args = &args;
   o.no_write = !(o.outpos = buffer);
   o.next_size_known = 0;
   o.insertions = 0;
   o.cmd_introducer = '\0';
   o.stop = buffer + buffer_size;
   fmt2023_recurser(&o);
   assert(o.outpos >= buffer);
   return (size_t)(o.outpos - buffer);
}
