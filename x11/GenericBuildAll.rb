#!/usr/bin/ruby -w
##############################################################################
#
# File x11/DebianInit.rb
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
# $Id: MandrivaBuildAll.rb,v 1.2 2007/06/30 11:45:46 southa Exp $
# $Log: MandrivaBuildAll.rb,v $
# Revision 1.2  2007/06/30 11:45:46  southa
# X11 release
#
# Revision 1.1  2007/06/29 16:48:30  southa
# Mandriva build
#
# Revision 1.1  2007/06/27 19:54:17  southa
# X11 release
#

commands = [
"rm -rf ~/rpm/BUILD/*/* ~/rpm/RPMS/*/* ~/rpm/tmp/* ~/rpm/SOURCES/* ~/rpm/SPECS/* ~/rpm/SRPMS/*",
"echo `test -f Makefile && make distclean`",
"rm -rf *.spec *.tar.gz *.tar.bz2 ~/rpm/BUILD/*/* ~/rpm/tmp/*",
"perl autogen.pl adanaxis --type=full --dist=mandriva",
"./configure",
"make rpm",
"make distclean",
"rm -rf *.spec *.tar.gz *.tar.bz2 ~/rpm/BUILD/*/* ~/rpm/tmp/*",
"perl autogen.pl adanaxis --type=demo --dist=mandriva",
"./configure",
"make rpm",
"make distclean",
"rm -rf *.spec *.tar.gz *.tar.bz2 ~/rpm/BUILD/*/* ~/rpm/tmp/*",
"perl autogen.pl adanaxis --type=gpl --dist=mandriva",
"./configure",
"make rpm",
"ls -lR ~/rpm/RPMS/*",
"echo Done."
]

for command in commands
  puts "+++ Executing #{command}"
  system(command) or raise "+++Command failed"
end
