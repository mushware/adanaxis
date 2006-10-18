# $Id$
# $Log$

$LOAD_PATH.push File.dirname($0)
require 'ImageProcess.rb'

class ProcessCosmos
  def initialize(inParams = {})
    @m_controlFile = inParams[:control_file] || 'no filename supplied'
    @m_srcPath = inParams[:source_path] || '.'
    @m_destPath = inParams[:destination_path] || '.'
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
    @m_im = ImageProcess.new
    @m_im.mLoad(inSrcFilename)
    @m_im.mScale(256, 256)
    @m_im.mAlphaFromLuminance
    #@m_im.mThreshold(0.1)
    @m_im.mSave(inDestFilename)
  end
  
  def mProcess(inParams = {})
    @m_srcRegexp = inParams[:source_regexp] || /\.jp(e)g$/
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
