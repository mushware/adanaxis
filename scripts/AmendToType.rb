#!/usr/bin/ruby -w
##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com/. This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2007.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
#
# $Id: AmendToType.rb,v 1.3 2007/06/15 12:45:49 southa Exp $
# $Log: AmendToType.rb,v $
# Revision 1.3  2007/06/15 12:45:49  southa
# Prerelease work
#
# Revision 1.2  2007/06/12 14:13:09  southa
# Demo creation
#
# Revision 1.1  2007/06/12 13:36:22  southa
# Demo configuration
#

require 'optparse'
require 'ftools'

$LOAD_PATH.push File.dirname($0)
require 'MushObject.rb'

class AmendToType < MushObject
  def initialize(inParams = {})
    @m_params = inParams.dup
  end

  mush_accessor :m_releaseDir, :m_resourcesDir, :m_name, :m_type

  def mAdanaxisToDemo
    File.copy('targets/app.COPYING', "#{@m_resourcesDir}/COPYING") or raise "Licence copy failed"
    puts "Replaced COPYING file with demo licence"
    
    skipDirs = %w{ . .. intro1 menu1 demoend1 }

    Dir.foreach("#{@m_resourcesDir}/spaces") do |dirName|
      unless skipDirs.index(dirName)
        thisPath = "#{@m_resourcesDir}/spaces/#{dirName}"
        if File.directory?(thisPath)
          if File.file?(thisPath+"/demo_manifest.txt")
            File.delete(thisPath+"/manifest.txt")
            File.rename(thisPath+"/demo_manifest.txt", thisPath+"/manifest.txt")
            puts "Switched to demo manifest in #{dirName}"
          else
            File.delete(thisPath+"/space.rb")
            File.delete(thisPath+"/dialogues.xml")
            puts "Disabled space #{dirName} for demo"
          end
        end
      end
    end

    rmList = %w{ mush/voice-full.mush }

    rmList.each do |filename|
      File.delete("#{@m_resourcesDir}/#{filename}")
      puts "Deleted file #{filename} for demo"
    end
    
    startFilename = "#{@m_resourcesDir}/system/start.txt"
    
    File.open(startFilename, "r+") do |file|
      content = file.readlines
      content.collect! { |x| x.gsub(/adanaxisrecords\.xml/, 'adanaxisdemorecords.xml') }
      file.rewind
      file.print content
    end
    puts "Changed records filename in start.txt"
    
    
  end
  
  def mAdanaxisToFull
    File.copy('targets/commercial.COPYING', "#{@m_resourcesDir}/COPYING") or raise "Licence copy failed"
    puts "Replaced COPYING file with commercial licence"
  end
  
  def mBanner
    puts "#{$0} started at "+Time.now.asctime
    instance_variables.each do |var|
      puts "#{var}="+eval(var).to_s
    end
  end
  
  def mProcess
    mBanner
    if @m_type == :demo
      mAdanaxisToDemo
    else
      mAdanaxisToFull
    end
  end
end

amend = AmendToType.new

OptionParser.new do |opts|
  opts.banner = "Usage: #{$0} [options]"

  opts.on("--releasedir PATH", "Path to the release directory") do |path|
    amend.mReleaseDirSet(path)
  end
  opts.on("--resourcesdir PATH", "Path to the resources directory") do |path|
    amend.mResourcesDirSet(path)
  end
  opts.on("--type TYPE", "Type (demo,full)", [:demo, :full]) do |type|
    amend.mTypeSet(type)
  end
  opts.on("--name NAME", "Name of application") do |name|
    amend.mNameSet(name)
  end
end.parse!

amend.mProcess

puts "#{$0} done."