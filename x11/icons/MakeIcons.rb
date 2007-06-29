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
# $Id: MandrivaInit.rb,v 1.2 2007/06/28 15:15:18 southa Exp $
# $Log: MandrivaInit.rb,v $

# Mandriva packages

require 'ftools'

for size in ["16","32","48"]
  File.copy("adanaxis-#{size}.png", "adanaxisdemo-#{size}.png")
  File.copy("adanaxis-#{size}.png", "adanaxisgpl-#{size}.png")
end

for name in ["adanaxis", "adanaxisdemo", "adanaxisgpl"]
  system("tar cjf #{name}-icons.tar.bz2 #{name}-??.png") or raise "+++ Command failed"
end

puts "Done."
