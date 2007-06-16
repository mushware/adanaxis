#!ruby -w
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

keyPrefix="J:\\mushware"
toolPath='C:/Program Files/Microsoft Visual Studio .NET 2003/Common7/Tools/Bin'

fileList = Dir.glob("../VisualC/project/Release/*.exe")
fileList += Dir.glob("*.exe")

fileList.each do |filename|
  puts "Sign #{filename}?"
  if STDIN.gets[0] == 121
    system("\"#{toolPath}/SignCode.exe\""+
         " -spc \"#{keyPrefix}cert.spc\" -v \"#{keyPrefix}key.pvk\" -i \"http://www.mushware.com/\""+
         " -n \"Mushware installer/exe\" -t \"http://timestamp.verisign.com/scripts/timstamp.dll\""+
         " -a sha1 \"#{filename}\""
          ) or raise "Failed"
  end        
  system("\"#{toolPath}/ChkTrust.exe\" -q \"#{filename}\""
        ) or puts "**** ChkTrust.exe Failed"
  
end

puts "Done."
