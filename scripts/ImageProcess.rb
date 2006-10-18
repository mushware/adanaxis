##############################################################################
#
# File scripts/ImageProcess.rb
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
# $Id: ImageProcess.rb,v 1.1 2006/10/05 15:39:17 southa Exp $
# $Log: ImageProcess.rb,v $
# Revision 1.1  2006/10/05 15:39:17  southa
# Explosion handling
#

require 'RMagick'

class ImageProcess
  def initialize(inParams = {})
    @m_copyright = inParams[:copyright] || "Andy Southgate/Mushware Limited http://www.mushware.com"
  end
  
  def mDump
    puts "   Format: #{@m_img.format}"
    puts "   Geometry: #{@m_img.columns}x#{@m_img.rows}"
    puts "   Class: " + case @m_img.class_type
                            when Magick::DirectClass
                                "DirectClass"
                            when Magick::PseudoClass
                                "PseudoClass"
                        end
    puts "   Depth: #{@m_img.depth} bits-per-pixel"
    puts "   Colors: #{@m_img.number_colors}"
    puts "   Filesize: #{@m_img.filesize}"
    puts "   Resolution: #{@m_img.x_resolution.to_i}x#{@m_img.y_resolution.to_i} "+
        "pixels/#{@m_img.units == Magick::PixelsPerInchResolution ?
        "inch" : "centimeter"}"
    if @m_img.properties.length > 0
        puts "   Properties:"
        @m_img.properties { |name,value|
            puts %Q|      #{name} = "#{value}"|
        }
    end
  end
  
  def mLoad(inFilename)
    @m_img = Magick::Image::read(inFilename).first
  end
  
  def mSave(inFilename)
    @m_img[:Copyright] = @m_copyright
    @m_img.compression = Magick::NoCompression
    @m_img.write(inFilename) {
      compression = Magick::NoCompression
    }
  end

  def mScale(inXSize, inYSize)
    @m_img.resize!(inXSize, inYSize)
  end
  
  def mThreshold(inThreshold)
    @m_img = @m_img.black_threshold(Magick::MaxRGB * inThreshold)
  end
  
  def mAlphaFromLuminance
    draw = Magick::Draw.new
    @m_img = @m_img.composite(@m_img, 0, 0, Magick::CopyOpacityCompositeOp)
  end
  
end

