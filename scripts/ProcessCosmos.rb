##############################################################################
#
# File scripts/ProcessCosmos.rb
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
# $Id: ProcessCosmos.rb,v 1.2 2006/11/05 09:32:13 southa Exp $
# $Log: ProcessCosmos.rb,v $
# Revision 1.2  2006/11/05 09:32:13  southa
# Mush file generation
#
# Revision 1.1  2006/10/18 13:22:09  southa
# World rendering
#

$LOAD_PATH.push File.dirname($0)
require 'ImageProcess.rb'

class ProcessCosmos
  def initialize(inParams = {})
    @m_controlFile = inParams[:control_file] || 'no filename supplied'
    @m_srcPath = inParams[:source_path] || '.'
    @m_destPath = inParams[:destination_path] || '.'
    @m_blackThreshold = inParams[:black_threshold] || 0.0
  end
  
  def mSrcFilenameMake(inNum, inNumZeroes)
    filename = @m_srcPath + '/' + @m_srcPrefix + '000'[1..inNumZeroes] + inNum.to_s + @m_srcSuffix
    filename.sub(/^\.\//, '')
  end
  
  def mDestFilenameMake(inNum)
    filename = @m_destPath + '/' + @m_destPrefix + inNum.to_s + @m_destSuffix
    filename.sub(/^\.\//, '')
  end
  
  def mProcessFile(inNum, inSrcFilename, inDestFilename)
    puts "File #{inNum} file #{inSrcFilename} -> #{inDestFilename}"
    die "Source and Destination filenames identical" if File.expand_path(inSrcFilename) == File.expand_path(inDestFilename)
    @m_im = ImageProcess.new(:copyright => "NASA http://www.nasa.gov, Andy Southgate/Mushware Limited http://www.mushware.com")
    @m_im.mLoad(inSrcFilename)
    @m_im.mScale(256, 256)
    @m_im.mThreshold(@m_blackThreshold) if @m_blackThreshold > 0.0
    @m_im.mAlphaFromLuminance
    @m_im.mSave(inDestFilename)
  end
  
  def mProcess(inParams = {})
    @m_srcRegexp = inParams[:source_regexp] || /\.jpe?g$/
    @m_destPrefix = inParams[:destination_prefix] || "copyright-"
    @m_destSuffix = inParams[:destination_suffix] || '.tiff'
    
    @m_srcFilenames = []

    i=0
    Dir.foreach(@m_srcPath) do |filename|
      if filename =~ @m_srcRegexp
        @m_srcFilenames << [i, "#{@m_srcPath}/#{filename}"]
        i += 1
      end
    end

    @m_srcFilenames.each do |entry|
      mProcessFile(entry[0], entry[1], mDestFilenameMake(entry[0]))
    end
  end
end
