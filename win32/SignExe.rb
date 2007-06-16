#!ruby -w

keyPrefix="J:\\mushware"
toolPath='C:/Program Files/Microsoft Visual Studio .NET 2003/Common7/Tools/Bin'

fileList = []
fileList << Dir.glob("../VisualC/project/Release/*.exe")
fileList << Dir.glob("*.exe")

fileList.each do |filename|
  puts "Sign #{filename}?"
  if STDIN.getc == 121
    system("\"#{toolPath}/SignCode.exe\""+
         " -spc \"#{keyPrefix}cert.spc\" -v \"#{keyPrefix}key.pvk\" -i \"http://www.mushware.com/\""+
         " -n \"Mushware installer/exe\" -t \"http://timestamp.verisign.com/scripts/timstamp.dll\""+
         " \"#{filename}\""
          ) or raise "Failed"
  end        
    system("\"#{toolPath}/ChkTrust.exe\" \"#{filename}\""
          ) or raise "Failed"
  
end

puts "Done."
