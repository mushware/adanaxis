##############################################################################
#
# File scripts/ProcessIntern.rb
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
# $Id: ProcessIntern.rb,v 1.2 2006/10/12 22:04:46 southa Exp $
# $Log: ProcessIntern.rb,v $
# Revision 1.2  2006/10/12 22:04:46  southa
# Collision events
#
# Revision 1.1  2006/10/09 16:00:15  southa
# Intern generation
#

$LOAD_PATH.push File.dirname($0)
require 'SourceProcess.rb'

class FileProcess

  def mName(inName)
    inName.gsub('@', 'AT')
  end
  
  def mProcess(filename, params)
    @m_sp = SourceProcess.new(
      :filename => filename,
      :params => params
    )
    @m_sp.mLoad
    extName = File.extname(filename)
    classes = []
    ids = []
    values = []
    
    dataFilename = filename.sub(extName, '.h')
    suggestedLine = @m_sp.mEvalData('data1', binding, dataFilename)
    
    if extName == '.h'
      headerBlock = []
      
      headerBlock << "public:"
      classes.each do |line|
        headerBlock << "    MushRubyValue& #{line}(void) { return m_klass#{line}; }"
      end
      ids.each do |line|
        headerBlock << "    Mushware::tRubyID #{mName(line)}(void) { return m_#{mName(line)}; }"
      end
      values.each do |line|
        headerBlock << "    Mushware::tRubyValue #{line}(void) { return m_#{line}; }"
      end
      
      headerBlock << "private:"
      classes.each do |line|
        headerBlock << "    MushRubyValue m_klass#{line};"
      end
      ids.each do |line|
        headerBlock << "    Mushware::tRubyID m_#{mName(line)};"
      end
      values.each do |line|
        headerBlock << "    Mushware::tRubyValue m_#{line};"
      end
      
      @m_sp.mBlockReplace("%declarations", headerBlock, suggestedLine)
    else
      initBlock = []
      classes.each do |line|
        initBlock << "    m_klass#{line} = MushRubyValue(MushRubyUtil::Class(\"#{line}\"));"
      end
      ids.each do |line|
        initBlock << "    m_#{mName(line)} = MushRubyIntern::SymbolID(\"#{line}\");"
      end
      values.each do |line|
        initBlock << "    m_#{line} = MushRubyIntern::SymbolID(\"#{line}\");"
      end
      @m_sp.mBlockReplace("%initialisations", initBlock, -1)
    end    

    @m_sp.mSave
  end
end

process = FileProcess.new
process.mProcess(ARGV[0], ARGV[1])
