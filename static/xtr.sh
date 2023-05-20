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
# $files{$pathname}->{file} == $pathname.
# $files{$pathname}->{provides} == $id || undef.
# $files{$pathname}->{lno} == $providing_line_number || undef.
# $names{$human_comprehensible_name} == $id.
# $canon{$id} == $human_comprehensible_name;
# $defs{$id} == $files{$pathname} || undef.
# $prqs{$id} == \%prerequisites_of_id.
my(%names, %canon, %files, %defs, %prqs, $id, $me, $name, $type);

use constant root_id => '9wnmpjka6u5ik9sqa6y47yytz';

sub add_req($$) {
   my($who, $req) = @_;
   $prqs{$who} = {} unless exists $prqs{$who};
   $prqs{$who}->{$req} = undef;
}

while (defined($_ = <>)) {
   chomp;
   if (
      /
         .* (?<type>Provides | Requires | Within-Group): \s*
         (?<name> [^:\s]+? [0-9a-z] ) [^0-9a-z]+
         (?<id> [0-9a-np-z]{25} )
         (?: [^0-9a-np-z] | $) .*
      /x
   ) {
      $files{$ARGV} = {file => $ARGV} unless exists $files{$ARGV};
      $id = $+{id};
      my $xx = {
            P => sub {
               if (exists $defs{$id}) {
                  die qq'Multiple definitions of same ID $id'
                     . qq' in "$ARGV" line $. and'
                     . qq' "$defs{$id}->{file}" line $defs{$id}->{lno}!'
                  ;
               }
               if ($files{$ARGV}->{provides}) {
                  die qq'Multiple "Provides:" in file "$ARGV" are forbidden'
                     . qq' (lines $. and  $files{$ARGV}->{lno})!'
                  ;
               }
               $files{$ARGV}->{provides} = $id;
               $files{$ARGV}->{lno} = $.;
               $defs{$id} = $files{$ARGV};
               add_req $id, "^$id"; add_req "${id}\$", $id;
            }
         ,  W => sub {
               unless ($me = $files{$ARGV}->{provides}) {
                  die qq'"Requires:" in file "$ARGV" line $. '
                     . qq' is forbidden without a prior "Provides:"'
                     . ' within the same file!'
                  ;
               }
               add_req $me, "^$id"; add_req "${id}\$", $me;
            }
         ,  R => sub {
               unless ($me = $files{$ARGV}->{provides}) {
                  die qq'"Requires:" in file "$ARGV" line $.'
                     . qq' is forbidden without a prior "Provides:"'
                     . ' within the same file!'
                  ;
               }
               add_req $me, "${id}\$";
            }
      };
      $xx = $xx->{$type = substr $+{type}, 0, 1};
      &$xx;
      $names{$name} = $id unless exists $names{$name = $+{name}};
      $canon{$id} = $name unless exists $canon{$id};
      if ($canon{$id} ne $name) {
         die(
            qq'Different names "$name" and "$canon{$id}"'
            . " used for the same ID $id!"
         );
      }
      $me = lc $name;
      $me =~ s/[^a-z0-9_]/_/g;
      $me =~ s/__+/_/g;
      $me =~ s/^_//; $me =~ s/_$//;
      if ($me eq '') {
         die qq'Invalid name "$name" used for ID $id in "$ARGV" line $.!';
      }
      if ($type eq 'P' && $id ne root_id) {
         unless (
            $ARGV =~ /
               (?: ^ | [^[:alnum:]] )
               $id
               (?: [^[:alnum:]] | $) .*
            /x
         ) {
            die(qq'File name "$ARGV" must contain ID "$id"!');
         }
         unless (
            $ARGV =~ /(?: ^ | [^[:alnum:]] ) $me (?: [^[:alnum:]] | $) .*/x
         ) {
            die(qq'File name "$ARGV" does not contain name "$me"!');
         }
      }
   }
}
=not
{
   use Data::Dumper;
   print Data::Dumper::Dumper([
         names => \%names, canon => \%canon, files => \%files
      ,  defs => \%defs, prqs => \%prqs
   ]), "\n";
}
=cut
