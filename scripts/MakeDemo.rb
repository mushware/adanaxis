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

releaseDir = ARGV[0]
resourcesDir = ARGV[1]
raise "Usage: #{$0} <release directory> <resources directory>" unless releaseDir && resourcesDir
puts "Converting to demo in #{releaseDir}"

demoSpaces = %w{ . .. intro1 level1 level2 level3 level4 level5 menu1 }

Dir.foreach("#{resourcesDir}/spaces") do |dirName|
  unless demoSpaces.index(dirName)
    thisPath = "#{resourcesDir}/spaces/#{dirName}"
    if File.directory?(thisPath)
      File.delete(thisPath+"/space.rb")
      File.delete(thisPath+"/dialogues.xml")
      puts "Disabled space #{dirName} for demo"
    end
  end
end

rmList = %w{ mush/voice-full.mush }

rmList.each do |filename|
  File.delete("#{resourcesDir}/#{filename}")
  puts "Deleted file #{filename} for demo"
end

raise "Append failed" unless system ("echo \"next='level5' # Added for demo\" >> \"#{resourcesDir}/spaces/level5/manifest.txt\"")
puts "Appended to level5 manifest for demo"
