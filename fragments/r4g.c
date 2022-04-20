resource *rlist;

extern void release(void *until) {
   while (rlist != until) (*rlist->action)();
}

extern void add_resource(resource *r, void (*action)(void), void *ivars) {
   r->ivars= ivars; r->action= action;
   r->link= rlist; rlist= r;
}

extern void *unlink_resource(void) {
   resource *r= rlist;
   rlist= r->link;
   #ifndef NDEBUG
      r->link= NASTY_PTR_VALUE;
   #endif
   return r;
}

extern void error(char const *msg) {
   (void)fputs(msg, stderr);
   (void)fputc('\n', stderr);
   release(0);
   exit(EXIT_FAILURE);
}
