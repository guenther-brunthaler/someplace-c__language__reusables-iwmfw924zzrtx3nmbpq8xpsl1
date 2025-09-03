/* Set *<is_big_endian> to 1 for big endian byte order.
 * Set *<is_big_endian> to 0 for little endian byte order.
 * Return 0 and do not touch *<error> on success.
 * Return 1 and set *<error> message on failure. */
extern int big_not_little_endian(char const **error, int *is_big_endian) {
   int lastbytedir = 0, lastbyte, lastbit;
   unsigned long x;
   #if 0
      #define TEST_OTHER_ENDIANNESS_BKETFY1ARAVQC4B3SEFSB8VK4
   #endif
   #ifndef TEST_OTHER_ENDIANNESS_BKETFY1ARAVQC4B3SEFSB8VK4
      unsigned char const *bstr = (void *)&x;
   #endif
   lastbyte = lastbit = -1;
   for (x = 1; x != 0; x += x) {
      int byteval, byte, bit;
      #ifdef TEST_OTHER_ENDIANNESS_BKETFY1ARAVQC4B3SEFSB8VK4
         unsigned long y = x;
         unsigned char *bstr = (void *)&y;
         {
            int L = 0, R = (int)(unsigned)(sizeof y) - 1;
            while (L < R) {
               unsigned char t = bstr[L];
               bstr[L++] = bstr[R]; bstr[R--] = t;
            }
         }
      #endif
      for (byte = 0; (byteval = bstr[byte]) == 0; ++byte) {
         assert(byte < (int)(unsigned)sizeof x);
      }
      for (bit = 0; (byteval & 1) == 0; ++bit) {
         assert(bit < CHAR_BIT);
         byteval >>= 1;
      }
      if (lastbyte >= 0 && lastbyte != byte) {
         int bytedir = byte - lastbyte;
         if (lastbytedir == 0) lastbytedir = bytedir;
         else if (bytedir != lastbytedir) {
            *error = "Inconsistent byte order"; goto failure;
         }
      }
      lastbyte = byte;
      if (lastbit >= 0 && lastbit != bit) {
         if (bit != (lastbit == CHAR_BIT - 1 ? 0 : lastbit + 1)) {
            *error = "Inconsistent bit order"; goto failure;
         }
      }
      lastbit = bit;
   }
   if (lastbytedir == -1) *is_big_endian = 1; /* Big Endian. */
   else if (lastbytedir != 1) *is_big_endian = 0; /* Little Endian. */
   else {
      *error = "Unsupported weird endianness";
      failure:
      return 1;
   }
   return 0;
}
