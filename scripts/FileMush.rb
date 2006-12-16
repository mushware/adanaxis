##############################################################################
#
# File scripts/FileMush.rb
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
# $Id: FileMush.rb,v 1.3 2006/11/06 19:27:51 southa Exp $
# $Log: FileMush.rb,v $
# Revision 1.3  2006/11/06 19:27:51  southa
# Mushfile handling
#
# Revision 1.2  2006/11/06 12:56:31  southa
# MushFile work
#
# Revision 1.1  2006/11/05 09:32:13  southa
# Mush file generation
#

class FileMush
  @@c_idString = 'MUSH'
  @@c_nativeVersion = [0, 0, 1, 0]
  @@c_chunkData = 'DATA'
  @@c_chunkDirectory = 'DIRC'
  @@c_chunkMessage = 'MSG '
  @@c_chunkSequence = 'SEQN'
  
  @@c_headerString = <<EOS
Mushware (http://www.mushware.com/) repository file.

This file is subject to copyright restrictions, and may contain files
distributed under licence from third parties.
EOS
  def initialize(inParams = {})
    @m_filename = inParams[:filename] || raise(RuntimeError, 'No :filename supplied')
    @m_mode = inParams[:mode] || raise(RuntimeError, 'No :mode supplied')
    @m_file = nil
    @m_sequenceNum = inParams[:sequence_number] || 256
  end

  def mOpen
    raise(RuntimeError, "MushFile '@m_filename' already open") if @m_file
    case @m_mode
      when :read
        @m_file = File.open(@m_filename, "rb")
      when :write
        @m_file = File.open(@m_filename, "wb")
        @m_directory = []
    end
  end
  
  def mAlign(inValue)
    4 * ((inValue + 3) / 4)
  end
  
  def mNumber(inNum)
    [0, inNum].pack("LL")
  end
  
  def mNumberRead
    return @m_file.read(8).unpack("LL")[1]
  end
  
  def mNumberGet(inString)
    return inString.unpack("LL")[1]
  end
  
  def mString(inString)
    retVal = mNumber(inString.length)
    retVal += inString
    while retVal.size % 4 != 0
      retVal << 0.chr
    end
    retVal
  end
  
  def mChunkWrite(inName)
    content = []
    yield(content)
    content = content.join
    while content.size % 4 != 0
      content << 0.chr
    end
    @m_file << mNumber(content.size + 4)
    @m_file << inName
    @m_file << content
  end
  
  def mHeaderWrite
    @m_file << @@c_idString
    @@c_nativeVersion.each do |versChar|
      @m_file.putc(versChar)
    end
    
    mChunkWrite(@@c_chunkMessage) do |chunk|
      chunk << @@c_headerString
    end
    mChunkWrite(@@c_chunkSequence) do |chunk|
      chunk << mNumber(@m_sequenceNum)
    end
    
  end
  
  def mDataEncrypt(ioData, inKeyNum)
    keyData = MushSecretKeys.Lookup(inKeyNum)
    keySize = keyData.size
    puts "Unusual key size #{keySize}" unless keySize == 65536
    ioData.size.times do |i|
      ioData[i] ^= keyData[i % keySize]
    end
  end
  
  def mDataWrite
    mChunkWrite(@@c_chunkData) do |chunk|
      @m_directory.each do |dirEntry|
        File.open(dirEntry[:src_filename]) do |file|
          readSize = dirEntry[:filesize]
          data = file.read(readSize)
          
          mDataEncrypt(data, dirEntry[:key_number]) if dirEntry[:key_number] != 0
          
          while data.size % 4 != 0
            data += 0.chr
          end
          chunk << data
          print '.'
          STDOUT.flush
        end
      end
    end
    puts '.'
  end

  def mDirectoryWrite
    offset = 0
    mChunkWrite(@@c_chunkDirectory) do |chunk|
      @m_directory.each do |dirEntry|
        chunk << mNumber(offset)
        chunk << mNumber(dirEntry[:filesize])
        chunk << mString(dirEntry[:dest_filename])
        chunk << mNumber(dirEntry[:key_number])
        chunk << mNumber(0) # Spare
        chunk << mNumber(0) # Spare
        offset += mAlign(dirEntry[:filesize])
      end
    end
  end
  
  def mCommit
    raise(RuntimeError, "MushFile '@m_filename' not open") unless @m_file
    @m_file.seek(0)
    mHeaderWrite
    mDirectoryWrite
    mDataWrite
  end
  
  def mClose
    if @m_file
      mCommit if @m_mode == :write
      @m_file.close 
    end
    @m_file = nil
  end

  def mFileAdd(inSrcFilename, inDestFilename, inKeyNum)
    fileStat = File.stat(inSrcFilename)
    raise(RuntimeError, "Cannot open file #{inSrcFilename}") unless fileStat

    @m_directory.push({
      :src_filename => inSrcFilename,
      :dest_filename => inDestFilename,
      :filesize => fileStat.size,
      :key_number => inKeyNum
    })
    
  end

  def mRawDump
    puts "File #{@m_filename} size #{@m_file.stat.size} bytes"
    @m_file.seek(0)
    i=0
    @m_file.each_byte do |byte|
      case byte
        when 0..31
          print "[#{byte}]"
        when 127..255
          print "[#{byte}]"
        else
          print byte.chr
      end
      i+=1
      break if i>1000
    end
    puts
  end

  def mNumberTake(ioData)
    retVal = ioData.unpack('LL')[1]
    ioData[0..7] = ''
    retVal
  end

  def mStringTake(ioData)
    stringLength = mNumberTake(ioData)
    retVal = ioData[0..stringLength]
    ioData[0..mAlign(stringLength)-1] = ''
    retVal
  end

  def mDirectoryInfo(inContent)
    retVal = []
    content = inContent.dup
    while content.size > 0
      offset = mNumberTake(content)
      size = mNumberTake(content)
      filename = mStringTake(content)
      retVal << "Filename: #{filename} size: #{size} offset: #{offset}"
    end
    retVal
  end

  def mChunkInfo
    retVal = []
    chunkSize = mNumberRead
    chunkID = @m_file.read(4)
    retVal << "Chunk ID #{chunkID} size #{chunkSize}"

    content = @m_file.read(chunkSize - 4)
    
    case chunkID
      when @@c_chunkData
        retVal << "(Data area)"
      when @@c_chunkDirectory
        retVal += mDirectoryInfo(content)
      when @@c_chunkMessage
        retVal << content
      when @@c_chunkSequence
        retVal << "Sequence number: #{mNumberGet(content)}"
    end
    
    retVal
  end

  def mInfo
    retVal = []
    retVal << "File #{@m_filename} size #{@m_file.stat.size} bytes"
    @m_file.seek(0)
    retVal << "ID: '"+@m_file.read(4)+"'"
    version = []
    4.times { version << @m_file.getc }
    retVal << "Version: "+version.join('.')
    
    while !@m_file.eof?
      retVal += mChunkInfo
    end
    
    retVal
  end

  def self.cOpenRead(inFilename)
    fileMush = FileMush.new(
      :filename => inFilename,
      :mode => :read)
    fileMush.mOpen
    yield(fileMush)
    fileMush.mClose
  end

  def self.cOpenWrite(inFilename)
    fileMush = FileMush.new(
      :filename => inFilename,
      :mode => :write)
    fileMush.mOpen
    yield(fileMush)
    fileMush.mClose
  end
  
  def self.cRawDump(inFilename)
    cOpenRead(inFilename) do |mushFile|
      mushFile.mRawDump
    end
  end

  def self.cInfo(inFilename)
    retVal = []
    cOpenRead(inFilename) do |mushFile|
      retVal = mushFile.mInfo
    end
    return retVal
  end
end
