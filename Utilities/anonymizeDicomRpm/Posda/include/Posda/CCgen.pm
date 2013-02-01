#!/usr/bin/perl -w
#$Source: /home/bbennett/pass/archive/Posda/include/Posda/CCgen.pm,v $
#$Date: 2008/06/24 14:19:13 $
#$Revision: 1.3 $
#
#Copyright 2008, Bill Bennett
# Part of the Posda package
# Posda may be copied only under the terms of either the Artistic License or the
# GNU General Public License, which may be found in the Posda Distribution,
# or at http://posda.com/License.html
#
use strict;
package Posda::CCgen;
sub new {
  my($class) = @_;
  my $this = {
     header => "",
     local => "",
     body => "",
     footer => "",
     indent => "",
     f_ind => 0,
     i_ind => 0,
  };
  return bless $this, $class;
}
sub add_header {
  my($this, $line) = @_;
  $this->{local} .= "$this->{indent}$line";
}
sub add_locals {
  my($this, $line) = @_;
  $this->{local} .= "$this->{indent}$line";
}
sub add_body {
  my($this, $line) = @_;
  $this->{body} .= "$this->{indent}$line";
}
sub add_footer {
  my($this, $line) = @_;
  $this->{footer} .= "$this->{indent}$line";
}
sub render{
  my($this) = @_;
  return "$this->{header}$this->{local}$this->{body}$this->{footer}";
}
sub add_indent{
  my($this, $indent) = @_;
  $this->{indent} = $indent . $this->{indent};
}
sub sub_indent{
  my($this, $indent) = @_;
  if($this->{indent} =~ /^$indent(.*)$/){
    $this->{indent} = $1;
  }
}
sub gimme_f{
  my($this) = @_;
  $this->{f_ind} += 1;
  $this->{local} .= "$this->{indent}float f$this->{f_ind};\n";
  return "f$this->{f_ind}";
}
sub gimme_i{
  my($this) = @_;
  $this->{i_ind} += 1;
  $this->{local} .= "$this->{indent}int i$this->{i_ind};\n";
  return "i$this->{i_ind}";
}
1;
