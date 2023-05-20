#! /bin/sh

# Script-level linkage editor.
#
# Version 2023.140
# Copyright (c) 2023 Guenther Brunthaler. All rights reserved.
#
# This script is free software.
# Distribution is permitted under the terms of the GPLv3.

exec perl -x -- "$0" ${1+"$@"}

#! The actual perl-script.
use strict;
use warnings qw(all);
use autodie;
use open ':locale';
use Getopt::Std;

getopts('') or die;
while (defined($_ = <>)) {
   chomp;
   print if
      s/
         .* (Provides | Requires | Within-Group): \s*
         ( [^:\s]+? [0-9a-z] ) [^0-9a-z]+
         ( [0-9a-np-z]{25} )
         (?: [^0-9a-np-z] | $) .*
      /$1:$2:$3:$ARGV\n/x
      && (
         s/^R[^:]*/R/
         || s/^P[^:]*/D/
         || s/^W[^:]*/G/
      )
   ;
}
