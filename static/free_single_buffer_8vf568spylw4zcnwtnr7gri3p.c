/* Provides: free_single_buffer-8vf568spylw4zcnwtnr7gri3p */
/* Requires: stdlib.h-p68c8i02e9jtk0r1qzlaw60zy */

static void *all_dynamically_allocated_resources;

static void free_all_resources(void) {
   free(all_dynamically_allocated_resources);
}
