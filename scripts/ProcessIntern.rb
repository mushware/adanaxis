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
        headerBlock << "    Mushware::tRubyValue #{line}(void) { return m_klass#{line}; }"
      end
      ids.each do |line|
        headerBlock << "    Mushware::tRubyID #{line}(void) { return m_#{line}; }"
      end
      values.each do |line|
        headerBlock << "    Mushware::tRubyValue #{line}(void) { return m_#{line}; }"
      end
      
      headerBlock << "private:"
      classes.each do |line|
        headerBlock << "    Mushware::tRubyValue m_klass#{line};"
      end
      ids.each do |line|
        headerBlock << "    Mushware::tRubyID m_#{line}; }"
      end
      values.each do |line|
        headerBlock << "    Mushware::tRubyValue m_#{line};"
      end
      
      @m_sp.mBlockReplace("%declarations", headerBlock, suggestedLine)
    else
      initBlock = []
      classes.each do |line|
        initBlock << "    m_klass#{line} = MushRubyUtil::Class(\"#{line}\");"
      end
      ids.each do |line|
        initBlock << "    m_#{line} = MushRubyUtil::SymbolID(\"#{line}\");"
      end
      values.each do |line|
        initBlock << "    m_#{line} = MushRubyUtil::SymbolID(\"#{line}\");"
      end
      @m_sp.mBlockReplace("%initialisations", initBlock, -1)
    end    

    @m_sp.mSave
  end
end

process = FileProcess.new
process.mProcess(ARGV[0], ARGV[1])
