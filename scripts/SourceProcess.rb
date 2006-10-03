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

class SourceProcess
  def initialize(params = {})
    @m_filename = params[:filename] || ""
    @m_content = []
  end
  
  def mLoad
    @m_backupFilename = @m_filename + '.bak'
    @m_content = IO.readlines(@m_filename)
    @m_content.each { |line| line.chomp! }
    
    IO.open(@m_backupFilename, "w") do |io|
      @m_content.each do |line|
        io.print(line, 10.chr) # Enforce Unix line endings
      end
    end
end
