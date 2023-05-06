/* #include <fmt2023_5tce3liwv5jz99as9fhhugjdh.h> */

#ifndef HEADER_5TCE3LIWV5JZ99AS9FHHUGJDH_INCLUDED
#ifdef __cplusplus
   extern "C" {
#endif

/* fmt2023 - yet another sprintf() replacement idea.
 *
 * I have had so many of those ideas, one worse than the other, that I started
 * naming them by the year when the next brainstorm hit me.
 *
 * Version 2023.5
 * Copyright (c) 2023 Guenther Brunthaler. All rights reserved.
 *
 * This source file is free software.
 * Distribution is permitted under the terms of the LGPLv3. */

#include <stddef.h>
#include <stdarg.h>

/* Expands one or more format strings into a given memory buffer. All
 * formatted strings will be null-terminated. There is no additional padding
 * between the formatted output strings.
 *
 * The function never fails. If the buffer is too small, it automatically
 * switches to "no write" mode and stops writing to the buffer. In this case,
 * there is no guarantee how much if anything has been written. This mode
 * can also be enforced by passing a null pointer as <buffer>.
 *
 * In any case, the function returns the number of bytes which *would* have
 * been written if the buffer was large enough. This number includes the
 * trailing null byte. Think of "strlen(buffer) + 1" in case of success.
 *
 * As long as the return value is not larger than <buffer_size>, then
 * everything has been written to the buffer and the formatting operation has
 * thus been successful.
 *
 * The variable arguments control the formatting operation. All arguments
 * come as pairs:
 *
 * NULL, <final_format>: Stop processing the argument list and use
 * <final_format> as the last format string to be processed.
 *
 * "\v", <bytes>: Set size_t value <bytes> as an override for the next
 * insertion string definition. This means that insertion sequence does not
 * need to be a null terminated string, but can be anyting binary. Think of
 * "void *" as a mnemonic.
 *
 * "\n", <name>, "\f", <format>: Create a new insertion sequence <name> by
 * expanding format string <format>. The result will *then* be appended at the
 * current output position as a null-terminated string. If <name> should
 * already be referenced during the expansion of <format>, it will expand to
 * an empty string. Use of "\f" in any other constellation than explained here
 * will result in undefined behavior.
 *
 * "\r", <addr>: Write the current output address to a pointer variable with
 * address <addr>. This allows to store the starting addresses of the next
 * string to be formatted, avoiding the need to search for null bytes in the
 * buffer as string separators within the formatted result. "\r" is frequently
 * used after a series of "\f" instructions in order to communicate the
 * address of the final output string to the caller. In case of "no write"
 * mode, the written pointer values have no significance and must be ignored.
 * Think of "report" as a mnemonic.
 *
 * <name>, <expansion>: The normal way to specify an insertion sequence.
 * <name> must be a null-terminated string identifying the sequence. Actually
 * it is more than just a name; it is a substring to search within a format
 * string, replacing all ocurrences of the substring with the string at
 * <expansion>. The latter one is normally a null-terminated string, but a
 * preceding "\v" can override this, so anything binary including null bytes
 * can be expanded as well. There is no restriction what <name> can be other
 * that it cannot start with one of the special-function characters. However,
 * for efficiency purposes, all insertion names must start with the same
 * characters. Thus, one could use "%1", "%2", "%(10)" etc. as names, or
 * rather "<name1>", "<name2>", but both styles cannot be mixed within the
 * same function invocation. There is no escape mechanism by default. But it
 * is easy to provide one. One could define an insertion sequence "%%" which
 * expands to a single "%". Then one could write "The expression '%1 %% of %2'
 * means %1 percent of the quantity %2.".
 *
 * Text after the special-function characters like "\v" is allowed but will be
 * ignored. It could be used to pass hints to a human translator, for
 * instance.
 *
 * The format string is expanded by scanning for the first character of an
 * insertion sequence name (which must all be the same). Then all insertion
 * sequence names defined so far are checked whether one matches the prefix
 * of the yet-unprocessed rest of the format string. If so, its associated
 * expansion string contents are appended to the output buffer. Otherwise, the
 * format introduction character loses its special meaning and is copied to
 * the output buffer literally.
 *
 * No sophisticated search algorithm is used to locate the named insertion
 * sequences. A simple linear search backwards is done instead. This means
 * that names defined later will be found faster. And in case of duplicate
 * names, only the last instance of the name defined so far will be found.
 * This can even be exploited for "redefining" names if multiple format
 * strings are used. */
size_t vfmt2023(char *buffer, size_t buffer_size, va_list args);
size_t sfmt2023(char *buffer, size_t buffer_size, ...);

#ifdef __cplusplus
   }
#endif
#endif /* !HEADER_5TCE3LIWV5JZ99AS9FHHUGJDH_INCLUDED */
