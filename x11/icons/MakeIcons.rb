#!/usr/bin/ruby -w
##############################################################################
#
# File x11/icons/MakeIcons.rb
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
# $Id: MakeIcons.rb,v 1.4 2007/07/03 12:49:40 southa Exp $
# $Log: MakeIcons.rb,v $
# Revision 1.4  2007/07/03 12:49:40  southa
# Autocopy xpm variants
#
# Revision 1.3  2007/06/30 16:02:14  southa
# Generic packaging
#
# Revision 1.2  2007/06/30 11:45:47  southa
# X11 release
#
# Revision 1.1  2007/06/29 11:03:13  southa
# Created
#

# Mandriva packages

require 'ftools'

path = File.dirname(__FILE__)

for suffix in ["demo", "gpl", "stub"]
  for size in ["16","32","48"]
    File.copy(path+"/adanaxis#{size}x#{size}.xpm", path+"/adanaxis#{suffix}#{size}x#{size}.xpm")
    File.copy(path+"/adanaxis-#{size}.png", path+"/adanaxis#{suffix}-#{size}.png")
  end
end

for name in ["adanaxis", "adanaxisdemo", "adanaxisgpl"]
  system("cd #{path} && tar cjf #{name}-icons.tar.bz2 #{name}-??.png") or raise "+++ Command failed"
end

puts "Done."
