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
# $Id: DpkgGenericBuildAll.rb,v 1.2 2007/07/03 13:56:39 southa Exp $
# $Log: DpkgGenericBuildAll.rb,v $
# Revision 1.2  2007/07/03 13:56:39  southa
# Generic dpkg release
#
# Revision 1.1  2007/07/03 13:45:03  southa
# Generic dpkg release
#

commands = [
"rm -rf ../*deb",
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
"make debian-release-unsigned"
]

for command in commands
  puts "+++ Executing #{command}"
  system(command) or raise "+++Command failed"
end

Dir.glob('../*deb') do |file|
  newFile = file.sub(/(\d+\.\d+\.\d+-\d+)/, '\1generic')
  File.rename(file, newFile)
end
system('ls -lrt ../*deb')
puts "Done."

