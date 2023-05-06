/* v2023.126 */

#include <fmt2023_5tce3liwv5jz99as9fhhugjdh.h>

extern size_t sfmt2023(char *buffer, size_t buffer_size, ...) {
   size_t result;
   va_list args;
   va_start(args, buffer_size);
   result = vfmt2023(buffer, buffer_size, args);
   va_end(args);
   return result;
}
