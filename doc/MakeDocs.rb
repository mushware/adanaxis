#!/usr/bin/ruby -w

class Docs
  def initialize
    @natDocsVarName = 'NATURALDOCS_PATH'
    @natDocsPath = ENV[@natDocsVarName].dup
    @natDocsPath.sub!(/\/$/, '')
    unless @natDocsPath : abort "Set the environment variable #{@natDocsVarName} to the directory NaturalDocs (www.naturaldocs.org) is installed in and try again"; end
    @natDocsCommand = "perl '#{@natDocsPath}/NaturalDocs'"
    @collectPath = Dir.pwd+'/collect'
    @outputPath = Dir.pwd+'/natdocs'
    @genTypeIsFile = false
    if ARGV.index('--file')
      @genTypeIsFile = true
    end
    @genTypeName = @genTypeIsFile ? 'file' : 'web'
  end

  def mCopy(fromName, toName)
    content = []
    File.open(fromName) do |file|
      content = file.readlines
    end
    File.open(toName, "w") do |file|
      content.each do |line|
        unless @genTypeIsFile
          line.sub!('file:', 'http://www.mushware.com/')
        end
        file << line
      end
    end
  end
     
  def mGetFiles(inDirs)
    Dir.mkdir @collectPath unless File.directory?(@collectPath)
    inDirs.each do |dirName|
      Dir.foreach(dirName) do |leafName|
        if leafName =~ /.*\.rb/
          mCopy(dirName+'/'+leafName, @collectPath+'/'+leafName)
        end
      end
    end
  end

  def mBanner
    puts "Generating documentation of type '#{@genTypeName}'"
  end

  def mDoxygen
    puts "Generating doxygen"
    system 'rm -rf doxygen'
    system 'doxygen Doxyfile.txt'
    puts "Doxygen complete"
  end

  def mNaturalDocs(path, dataPaths)
    sourcePrefix = ' --input ';
    sourceCommand = " --input '#{@collectPath}' "
    command = "cd '#{path}'; #{@natDocsCommand} #{sourceCommand} --output FramedHTML '#{@outputPath}' --project #{@natDocsPath}/core-app --rebuild"
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

docs.mGetFiles(dataPaths)

unless ARGV.index('--nodox')
  docs.mDoxygen
end
docs.mNaturalDocs(topLevelPath, dataPaths)

dateStr = Time.now.strftime('%Y-%m-%d')
system "tar czf natdocs-#{dateStr}.tgz natdocs"
system "tar czf doxygen-#{dateStr}.tgz doxygen"

puts 'Done.'
