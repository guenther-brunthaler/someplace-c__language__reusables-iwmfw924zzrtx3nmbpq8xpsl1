#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
   char *data;
   size_t length, capacity;
} bdesc;

static void buffer_reallocate(bdesc *buffer, size_t new_capacity) {
   assert(new_capacity != buffer->capacity);
   #ifndef DEBUG
      if (new_capacity < buffer->capacity) {
         (void)memset(
               buffer->data + new_capacity, NASTY_BYTE_VALUE
            ,  buffer->capacity - new_capacity
         );
      }
   #endif
   if (new_capacity) {
      char *nbuf;
      if (!(nbuf= realloc(buffer->data, new_capacity))) {
         error("Memory allocation error!");
      }
      #ifndef DEBUG
         if (new_capacity > buffer->capacity) {
            (void)memset(
                  nbuf + buffer->capacity, NASTY_BYTE_VALUE
               ,  new_capacity - buffer->capacity
            );
         }
      #endif
      buffer->data= nbuf;
      buffer->capacity= new_capacity;
   } else {
      buffer->length= buffer->capacity= 0;
      free(buffer->data);
   }
}

static void buffer_vacate(bdesc *buffer) {
   if (buffer->capacity) buffer_reallocate(buffer, 0);
}

static void bdesc_dtor(void) {
   bdesc *buffer= unlink_resource();
   buffer_vacate(buffer);
   #ifndef DEBUG
      buffer->data= NASTY_PTR_VALUE;
      buffer->length= buffer->capacity= NASTY_SIZE_VALUE;
   #endif
}

static void o0_buffer_new(resource *r, bdesc *buffer) {
   buffer->data= 0;
   buffer->length= buffer->capacity= 0;
   add_resource(r, bdesc_dtor, buffer);
}

static void buffer_grow(bdesc *buffer, size_t target_length) {
   assert(target_length > buffer->capacity);
   {
      size_t new_capacity= 128;
      while (new_capacity < target_length) new_capacity+= new_capacity;
      buffer_reallocate(buffer, new_capacity);
   }
   buffer->length= target_length;
}

static void raise_read_error(void) {
   error("Read error!");
}

static int readline_ck(bdesc *buffer) {
   size_t i, end;
   int c;
   char *b;
   i= 0; end= buffer->capacity; b= buffer->data;
   while ((c= getchar()) != EOF) {
      if (i == end) {
         buffer_grow(buffer, i + 1);
         end= buffer->capacity; b= buffer->data;
      }
      assert(i < end);
      if (c == '\n') goto got_eol;
      b[i++]= (char)c;
   }
   if (ferror(stdin)) raise_read_error();
   assert(feof(stdin));
   got_eol:
   b[buffer->length= i]= '\0';
   return !!i;
}

static void raise_write_error(void) {
   error("Write error!");
}

static void raise_strtointeger_error(void) {
   error("Failure converting string into integer");
}

static long strtol_ck(
   char const *restrict str, char **restrict endptr, int base
) {
   long result;
   char *end= 0;
   result= strtol(str, &end, base);
   if (!end || *str) raise_strtointeger_error();
   if (endptr) *endptr= end;
   return result;
}

static long strtol_whole(char const *restrict str, int base) {
   long result;
   char *end;
   result= strtol_ck(str, &end, base);
   if (*end) raise_strtointeger_error();
   return result;
}
