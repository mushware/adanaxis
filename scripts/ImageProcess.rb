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
# $Id: ImageProcess.rb,v 1.3 2006/10/19 15:41:35 southa Exp $
# $Log: ImageProcess.rb,v $
# Revision 1.3  2006/10/19 15:41:35  southa
# Item handling
#
# Revision 1.2  2006/10/18 13:22:09  southa
# World rendering
#
# Revision 1.1  2006/10/05 15:39:17  southa
# Explosion handling
#

require 'RMagick'

class ImageProcess
  def initialize(inParams = {})
    @m_copyright = inParams[:copyright] || "Andy Southgate/Mushware Limited http://www.mushware.com"
  end
  
  def mDump
  end
  
  def mLoad(inFilename)
    @m_img = Magick::Image::read(inFilename).first
  end
  
  def mSave(inFilename)
    @m_img[:Copyright] = @m_copyright
    @m_img.compression = Magick::JPEGCompression
    # @m_img.compression = Magick::NoCompression
    @m_img.write(inFilename) {
        quality = 85
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

