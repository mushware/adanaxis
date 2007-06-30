#!/usr/bin/ruby -w
##############################################################################
#
# File x11/GenericBuildAll.rb
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
# $Id: GenericBuildAll.rb,v 1.2 2007/06/30 16:04:05 southa Exp $
# $Log: GenericBuildAll.rb,v $
# Revision 1.2  2007/06/30 16:04:05  southa
# Generic packaging
#

commands = [
"rm -rf ~/rpm/BUILD/*/* ~/rpm/RPMS/*/* ~/rpm/tmp/* ~/rpm/SOURCES/* ~/rpm/SPECS/* ~/rpm/SRPMS/*",
"echo `test -f Makefile && make distclean`",
"rm -rf *.spec *.tar.gz *.tar.bz2 ~/rpm/BUILD/*/* ~/rpm/tmp/*",
"perl autogen.pl adanaxis --type=full --dist=genericrpm",
"./configure",
"make rpm",
"make distclean",
"rm -rf *.spec *.tar.gz *.tar.bz2 ~/rpm/BUILD/*/* ~/rpm/tmp/*",
"perl autogen.pl adanaxis --type=demo --dist=genericrpm",
"./configure",
"make rpm",
"make distclean",
"rm -rf *.spec *.tar.gz *.tar.bz2 ~/rpm/BUILD/*/* ~/rpm/tmp/*",
"perl autogen.pl adanaxis --type=gpl --dist=genericrpm",
"./configure",
"make rpm",
"ls -lR ~/rpm/RPMS/*",
"echo Done."
]

for command in commands
  puts "+++ Executing #{command}"
  system(command) or raise "+++Command failed"
end
