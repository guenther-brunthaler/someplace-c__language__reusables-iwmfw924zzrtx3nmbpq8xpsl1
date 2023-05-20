/* Provides: free_single_buffer-8vf568spylw4zcntgllvlt34m */
/* Requires: stdlib.h-p68c8i02e9jtk0r18n9hz1g3w */

static void *all_dynamically_allocated_resources;

static void free_all_resources(void) {
   free(all_dynamically_allocated_resources);
}
