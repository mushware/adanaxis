#!/usr/bin/ruby -w



class Docs
  def initialize
    @natDocsVarName = 'NATURALDOCS_PATH'
    @natDocsPath = ENV[@natDocsVarName]
    unless @natDocsPath : abort "Set the environment variable #{@natDocsVarName} to the directory NaturalDocs (www.naturaldocs.org) is installed in and try again"; end
    @natDocsCommand = "perl #{@natDocsPath}/NaturalDocs"
    @outputPath = Dir.pwd+'/natdocs'
    @genTypeIsFile = true
    @genTypeName = @genTypeIsFile ? 'file' : 'web'
  end

  def mBanner
    puts "Generating documentation of type '#{@genTypeName}'"
  end

  def mDoxygen
    system "doxygen Doxyfile.txt"
  end

  def mNaturalDocs(path, dataPaths)
    sourcePrefix = ' --input ';
    sourceCommand = sourcePrefix + dataPaths.join(sourcePrefix)
    command = "cd #{path}; #{@natDocsCommand} #{sourceCommand} --output FramedHTML #{@outputPath} --exclude-input doxygen --project #{@natDocsPath}/core-app --rebuild"
    puts "command=#{command}"

    %w{files index index.html javascript menu.html styles search}.each do |leafName|
      system 'rm -rf '+@outputPath+'/'+leafName
    end

    unless File.directory?(@outputPath) : Dir.mkdir @outputPath; end
    result = system(command)
    puts "result=#{result}"
  end
end

docs = Docs.new
docs.mBanner

dataPaths = []

topLevelPath = File.dirname(Dir.pwd)
Dir.foreach(topLevelPath) do |leafName| 
  if leafName =~ /^data-/
    dataPaths.push topLevelPath+'/'+leafName+"/mushruby"
  end
end

puts "Using data directories ", dataPaths.join(', ')

docs.mDoxygen
docs.mNaturalDocs(topLevelPath, dataPaths)

puts 'Done.'