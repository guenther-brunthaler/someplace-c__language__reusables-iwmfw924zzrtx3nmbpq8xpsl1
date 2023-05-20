# Provides: cscript_prefix-0ztbnt1k9mi9qavqmwbgbavkl
#! /bin/sh
: v2022.179.2; set -e; cleanup() {
	rc=$?; test "$TD" && rm -r -- "$TD"
	test $rc = 0 || $report "\"$0\" failed!" >& 2
}
report=echo; TD=; trap cleanup 0; trap 'exit $?' INT QUIT HUP TERM
bn=${0##*/}; TD=`mktemp -d -- "${TMPDIR:-/tmp}/$bn.XXXXXXXXXX"`
{ printf '.POSIX:\n.c:\n\t$(CC) -D NDEBUG -O $(CFLAGS) '
echo '$(LDFLAGS) -o $@ $< -lm'; } > "$TD"/Makefile
sed '1,/exit$/ s/.*//' < "$0" > "$TD/$bn.c"; (cd -- "$TD" && make -s "$bn")
rm -- "$TD"/Makefile; report=:; "$TD/$bn" ${1+"$@"} && exit || exit
