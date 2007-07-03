#!/usr/bin/ruby -w
##############################################################################
#
# File x11/DpkgGenericBuildAll.rb
#
# Author Andy Southgate 2007
#
# This file contains original work by Andy Southgate.  The author and his
# employer (Mushware Limited) irrevocably waive all of their copyright rights
# vested in this particular version of this file to the furthest extent
# permitted.  The author and Mushware Limited also irrevocably waive any and
# all of their intellectual property rights arising from said file and its
# creation that would otherwise restrict the rights of any party to use and/or
# distribute the use of, the techniques and methods used herein.  A written
# waiver can be obtained via http://www.mushware.com/.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
# $Id: GenericBuildAll.rb,v 1.3 2007/06/30 16:05:49 southa Exp $
# $Log: GenericBuildAll.rb,v $

commands = [
"echo `test -f Makefile && make distclean`",
"perl autogen.pl adanaxis --type=full --dist=genericdpkg",
"./configure",
"make debian-release-unsigned",
"make distclean",
"perl autogen.pl adanaxis --type=demo --dist=genericdpkg",
"./configure",
"make debian-release-unsigned",
"make distclean",
"perl autogen.pl adanaxis --type=gpl --dist=genericdpkg",
"./configure",
"make debian-release-unsigned",
"ls -lrt ../*.deb",
"echo Done."
]

for command in commands
  puts "+++ Executing #{command}"
  system(command) or raise "+++Command failed"
end
