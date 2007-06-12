#!/usr/bin/ruby -w
##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com/.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2007.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
#
# $Id$
# $Log$

class MushObject
  def self.mush_reader(*inArgs)
    inArgs.each do |arg|
      argName = arg.to_s
      
      if argName.sub!(/^m_/, "m")
        argName[1, 1] = argName[1, 1].upcase
      end
      class_eval(<<-EOS, __FILE__, __LINE__+1)
        def #{argName}
          @#{arg}
        end
EOS
    end
  end

  def self.mush_writer(*inArgs)
    inArgs.each do |arg|
      argName = arg.to_s
      
      if argName.sub!(/^m_/, "m")
        argName[1, 1] = argName[1, 1].upcase
      end
      class_eval(<<-EOS, __FILE__, __LINE__+1)
        def #{argName}Set(inParam)
          @#{arg} = inParam
        end
EOS
    end
  end
  
  def self.mush_accessor(*inArgs)
    mush_reader(*inArgs)
    mush_writer(*inArgs)
  end
end
