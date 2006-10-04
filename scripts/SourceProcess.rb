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
# $Id: SourceProcess.rb,v 1.1 2006/10/03 15:28:21 southa Exp $
# $Log: SourceProcess.rb,v $
# Revision 1.1  2006/10/03 15:28:21  southa
# Source process directives
#

class SourceProcess
  def initialize(params = {})
    @m_filename = params[:filename] || ""
    @m_commentMarker = params[:comment_marker] || "//"
    @m_content = []
  end
  
  def mLoad
    @m_backupFilename = @m_filename + '.bak'
    @m_content = IO.readlines(@m_filename)
    @m_content.each { |line| line.chomp! }
    
    File.open(@m_backupFilename, "w") do |file|
      @m_content.each do |line|
        file.print(line, 10.chr) # Enforce Unix line endings
      end
    end
  end
  
  def mEvalData(inDataName, inBinding, inFilename = nil)
    filename = inFilename || @m_filename
    dataName = inDataName
    beginExp = Regexp.new(":#{dataName}begin")
    endExp = Regexp.new(":#{dataName}end")
    toEval = ""
    state = 0
    lineNum=1
    IO.foreach(filename) do |line|
      case state
      when 0:
        lineNum += 1
        if line =~ beginExp
          state = 1
        end
        
      when 1:
        if line =~ endExp
          state = 2
        else
          toEval += line
        end
        
      when 2:
        if (line =~ beginExp || line =~ endExp)
          raise RuntimeError, "Multiple #{dataName}begin/#{dataName}end markers in #{filename}"
        end
      end # of case
    end # of foreach
      
    raise RuntimeError, "Could not detect #{dataName}begin/#{dataName}end markers in #{filename}" if state != 2
    
    eval(toEval, inBinding, filename, lineNum)
  end
  
  def mBlockStartMarker(inBlockID)
    "#{@m_commentMarker}#{inBlockID} {"
  end
  
  def mBlockEndMarker(inBlockID)
    "#{@m_commentMarker}#{inBlockID} }"
  end
  
  def mBlockReplace(inBlockID, inContent, inSuggestedLine)
    startExp = Regexp.new('^\s*'+Regexp::quote(mBlockStartMake(inBlockID)))
    endExp = Regexp.new('^\s*'+Regexp::quote(mBlockEndMake(inBlockID))+'\s*([0-9a-zA-Z+/]*)')
  end
end
