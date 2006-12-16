##############################################################################
#
# File scripts/ProcessMush.rb
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
# $Id: ProcessMush.rb,v 1.1 2006/11/05 09:32:13 southa Exp $
# $Log: ProcessMush.rb,v $
# Revision 1.1  2006/11/05 09:32:13  southa
# Mush file generation
#

$LOAD_PATH.push File.dirname($0)
require 'FileMush.rb'

class ProcessMush
  def initialize(inParams = {})
    @m_srcPath = inParams[:source_path] || '.'
    @m_destPath = inParams[:destination_path] || '.'
    @m_mushFile = inParams[:mush_file] || 'output.mush'
    @m_keyNum = inParams[:key_number] || 0
  end
  
  def mSrcFilenameMake(inName)
    filename = @m_srcPath + '/' + inName
    filename.sub(/^\.\//, '')
  end
  
  def mDestFilenameMake(inName)
    filename = @m_destPath + '/' + inName
    filename.sub(/^\.\//, '')
  end
  
  def mProcessFile(inMushFile, inSrcFilename, inDestFilename)
    puts "File #{inSrcFilename} -> mush::#{@m_mushFile}:/#{inDestFilename} [key #{@m_keyNum}]"
    inMushFile.mFileAdd(inSrcFilename, inDestFilename, @m_keyNum)
  end
  
  def mProcess(inParams = {})
    @m_srcRegexp = inParams[:source_regexp] || /^(mush|artb|sdog)-/
    
    @m_srcFilenames = []

    Dir.foreach(@m_srcPath) do |filename|
      if filename =~ @m_srcRegexp
        @m_srcFilenames << filename
      end
    end

    FileMush.cOpenWrite(@m_mushFile) do |mushFile|
      @m_srcFilenames.each do |entry|
        mProcessFile(mushFile, mSrcFilenameMake(entry), mDestFilenameMake(entry))
      end
    end

    FileMush.cInfo(@m_mushFile).each do |line|
      puts line
    end
    FileMush.cRawDump(@m_mushFile)
  end
end
