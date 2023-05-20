#! /bin/sh

# Script-level linkage editor.
#
# Version 2023.140.1
# Copyright (c) 2023 Guenther Brunthaler. All rights reserved.
#
# This script is free software.
# Distribution is permitted under the terms of the GPLv3.

exec perl -x -- "$0" ${1+"$@"}

#! The actual perl-script.
#line 14

use strict;
use warnings qw(all);
use autodie;
use open ':locale';
use Getopt::Std;

getopts('') or die;
my($u, $pfx, $sfx);
while (defined($_ = <>)) {
   chomp;
   if (
      /
         (?<pfx> ^ | .* [^0-9a-np-z]+ )
         (?<id> [0-9a-np-z]{25} )
         (?<sfx> [^0-9a-np-z] .* | $)
      /x
   ) {
   	$pfx = $+{pfx}; $sfx = $+{sfx};
   	$u = qx"base35uuid -c $+{id}"; chomp $u;
   	$u =~ s/[^-]*$/001999fdcdd9/;
   	$u = qx"base35uuid -c $u"; chomp $u;
   	$_ = $pfx . $u . $sfx;
   }
   print $_, "\n";
}
