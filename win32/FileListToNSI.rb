
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
