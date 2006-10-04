##############################################################################
#
# File scripts/SourceProcess.rb
#
# Author Andy Southgate 2006
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
# $Id$
# $Log$

$LOAD_PATH.push File.dirname($0)
require 'SourceProcess.rb'

class FileProcess
  def mProcess(filename, params)
    @m_sp = SourceProcess.new(
      :filename => filename,
      :params => params
    )
    @m_sp.mLoad
    ids = []
    values = []
    @m_sp.mEvalData('data1', binding)
  end
end

process = FileProcess.new
process.mProcess(ARGV[0], ARGV[1])
