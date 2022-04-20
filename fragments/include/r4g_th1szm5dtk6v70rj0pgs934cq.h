/*
 * #include <r4g_th1szm5dtk6v70rj0pgs934cq.h>
 *
 * Version 2022.110
 *
 * Copyright (c) 2022 Guenther Brunthaler. All rights reserved.
 *
 * This script is free software.
 * Distribution is permitted under the terms of the GPLv3.
 */

#ifndef HEADER_TH1SZM5DTK6V70RJ0PGS934CQ_INCLUDED
#ifdef __cplusplus
	extern "C" {
#endif

typedef struct resource resource;
struct resource {
   void *ivars;
   resource *link;
   void (*action)(void);
};

extern resource *rlist;

void release(void *until);
void add_resource(resource *r, void (*action)(void), void *ivars);
void *unlink_resource(void);
void error(char const *msg);

#ifdef __cplusplus
	}
#endif
#endif /* !HEADER_TH1SZM5DTK6V70RJ0PGS934CQ_INCLUDED */
