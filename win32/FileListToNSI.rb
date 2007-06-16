##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited 2007.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
#
# $Id: MakeInstaller.sh,v 1.10 2007/06/16 08:26:50 southa Exp $
# $Log: MakeInstaller.sh,v $

require 'FileUtils'
require 'Find'

infile = ARGV[0]
outfile = ARGV[1]
appName = ARGV[2]
instName = ARGV[3]
outFilename= ARGV[4]

puts "Generating #{appName} installer file '#{infile}' from '#{outfile}'"
puts "Installed name '#{instName}', installer filename '#{outFilename}'"
content = File.new(infile).readlines

fileNames = []
dirNames = []

Find.find('../release') do |f|
  if File.basename(f) != 'Makefile.am'
    splitNames = f.split('/')
    if splitNames[3..-1]
      leafName = splitNames[3..-1].join('\\')
      if leafName != ""
        if File.stat(f).file?
          fileNames.push leafName
        elsif File.stat(f).directory?
          dirNames.push leafName
        end
      end
    end
  end
end

content.collect! do |line|
  loop do
    line = case line
      when /@INSTFILES@/:  dirNames.map { |name| "CreateDirectory \"$INSTDIR\\#{name}\"\n"} + fileNames.map { |name| "File \"/oname=#{name}\" \"..\\release\\#{appName}\\#{name}\"\n" }
      when /@UNINSTFILES@/: fileNames.map { |name| "Delete \"$INSTDIR\\#{name}\"\n" } + dirNames.reverse.map { |name| "RmDir \"$INSTDIR\\#{name}\"\n" }
      when /(.*)@NSI_APP_NAME@(.*)/: $1+instName+$2+"\n"
      when /(.*)@NSI_OUTFILE@(.*)/: $1+outFilename+$2+"\n"
      else break(line)
    end
  end
end

content.flatten!

File.open(outfile, "w") do |file|
  content.each { |line| file << line }
end
