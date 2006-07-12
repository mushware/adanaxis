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
    puts "Generating doxygen"
    system 'rm -rf doxygen'
    system 'doxygen Doxyfie.txt'
    puts "Doxygen complete"
  end

  def mNaturalDocs(path, dataPaths)
    sourcePrefix = ' --input ';
    sourceCommand = sourcePrefix + dataPaths.join(sourcePrefix)
    command = "cd #{path}; #{@natDocsCommand} #{sourceCommand} --output FramedHTML #{@outputPath} --exclude-input doxygen --project #{@natDocsPath}/core-app --rebuild"
    puts "command=#{command}"

    %w{files files2 index index.html javascript menu.html styles search doxygen}.each do |leafName|
      system 'rm -rf '+@outputPath+'/'+leafName
    end

    Dir.mkdir @outputPath unless File.directory?(@outputPath)

    result = system(command)
    unless (result)
      puts "NaturalDocs returned #{result}"
    end

    if @genTypeIsFile
      (1..100).each do |i|
        filename = "#{@outputPath}/files"
        filename += i.to_s if i > 1
        File.symlink("#{@outputPath}/../doxygen", "#{filename}/doxygen") if File.directory?(filename)
      end
    end
  end
end

docs = Docs.new
docs.mBanner

dataPaths = []

topLevelPath = File.dirname(Dir.pwd)
Dir.foreach(topLevelPath) do |leafName| 
  if leafName =~ /^data-/
    [topLevelPath+'/'+leafName+'/ruby', topLevelPath+'/'+leafName+'/mushruby'].each do |dirName|
      File.directory?(dirName) && dataPaths.push(dirName)
    end
  end
end

puts "Using data directories ", dataPaths.join(', ')

unless ARGV.index('--nodox')
  docs.mDoxygen
end
docs.mNaturalDocs(topLevelPath, dataPaths)

puts 'Done.'