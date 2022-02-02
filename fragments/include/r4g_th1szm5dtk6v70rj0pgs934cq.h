/* #include <r4g_th1szm5dtk6v70rj0pgs934cq.h> */

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

void release_c1(void *until);
void add_resource_c0(resource *r, void (*action)(void), void *ivars);
void *unlink_resource_c0(void);
void error_c1(char const *msg);

#ifdef __cplusplus
	}
#endif
#endif /* !HEADER_TH1SZM5DTK6V70RJ0PGS934CQ_INCLUDED */
