
require 'FileUtils'
require 'Find'

infile = ARGV[0]
outfile = ARGV[1]
appname = ARGV[2]

puts "Generating installer file '#{infile}' from '#{outfile}'"

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
  case line
    when /@INSTFILES@/:  dirNames.map { |name| "CreateDirectory \"$INSTDIR\\#{name}\"\n"} + fileNames.map { |name| "File \"/oname=#{name}\" \"..\\release\\#{appname}\\#{name}\"\n" }
    when /@UNINSTFILES@/: fileNames.map { |name| "Delete \"$INSTDIR\\#{name}\"\n" } + dirNames.reverse.map { |name| "RmDir \"$INSTDIR\\#{name}\"\n" }
    else line
  end
end

content.flatten!

File.open(outfile, "w") do |file|
  content.each { |line| file << line }
end

