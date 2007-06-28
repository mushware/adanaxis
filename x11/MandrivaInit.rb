#!/usr/bin/ruby -w
##############################################################################
#
# File x11/MandrivaInit.rb
#
# Author Andy Southgate 2007
#
# This file contains original work by Andy Southgate.  The author and his
# employer (Mushware Limited) irrevocably waive all of their copyright rights
# vested in this particular version of this file to the furthest extent
# permitted.  The author and Mushware Limited also irrevocably waive any and
# all of their intellectual property rights arising from said file and its
# creation that would otherwise restrict the rights of any party to use and/or
# distribute the use of, the techniques and methods used herein.  A written
# waiver can be obtained via http://www.mushware.com/.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
# $Id: DebianInit.rb,v 1.3 2007/06/27 11:56:44 southa Exp $
# $Log: DebianInit.rb,v $
# Revision 1.3  2007/06/27 11:56:44  southa
# Debian packaging
#
# Revision 1.2  2007/06/26 16:27:51  southa
# X11 tweaks
#
# Revision 1.1  2007/06/26 10:46:07  southa
# Created
#

require 'optparse'

class DebianInit
  def initialize
    @m_develPackages = %w{
autoconf2.5
automake
binutils
libmesaglut3-devel
gcc
gcc-c++
glibc-devel
libexpat0-devel
libjpeg62-devel
libmesagl1-devel
libmesaglu1-devel
libpcre0-devel
libSDL1.2-devel
libSDL_mixer1.2-devel
libtiff3-devel
make
}

    @m_packagingPackages = %w{
autoconf2.5
automake
dh-make
debhelper
devscripts
fakeroot
gnupg
lintian
linda
pbuilder
debian-policy
developers-reference
}

    @m_userPackages = %w{
kate
kdevelop
kdegames
kdegraphics
kscreensaver
xscreensaver-gl
mc
    }

    @m_nvidiaKernelPackages = %w{
gcc
kernel-source-2.6
    }

    @m_nvidiaUserPackages = %w{
nvidia-glx
nvidia-settings
nvidia-xconfig
    }

   @m_yes = false
  end

  def mPackagesInstall(inPackages)
    failures = []
    flags = " --auto"
    flags += " --yes" if @m_yes
    inPackages.each do |package|
      command = "sudo urpmi #{flags} #{package}"
      puts ": Executing #{command}"
      unless system(command)
        failures << package
        puts "********** Failed #{command}"
      end
    end

    if failures != []
      failures.each do |package|
        puts "**************** Package #{package} failed to install"
      end
    end
    return failures == []
  end

  def mDevelInstall
    mPackagesInstall(@m_develPackages)
  end

  def mPackagingInstall
    mPackagesInstall(@m_packagingPackages)
  end

  def mUserInstall
    mPackagesInstall(@m_userPackages)
  end

  def mNVidiaInstall
    mSourcesSetup
    #mPackagesInstall(@m_nvidiaKernelPackages) or raise("++++Package installation failed")
    #system("sudo urpmi.update -a") or raise("++++Command failed")
    # system("sudo urpmi kernel") or raise("++++Command failed")

    system("sudo urpmi --auto nvidia97xx-kernel-`uname -r`") or raise("++++Command failed")
    puts "Get and install driver from NVidia web site:"
    puts "http://nvidia.com/content/drivers/drivers.asp"
return
    mPackagesInstall(@m_nvidiaUserPackages) or raise("++++Package installation failed")
    system("sudo nvidia-xconfig") or raise("++++Command failed")
    system("sudo dpkg-reconfigure xserver-xorg") or raise("++++Command failed")
    system("sudo sh -c 'grep -q ^nvidia /etc/modules || echo nvidia >> /etc/modules'") or raise("++++Command failed")
    system("sudo modprobe nvidia") or raise("++++Command failed")
    puts "Now type 'sudo invoke-rc.d gdm restart' to restart your X Session"
  end

  def mBashrcAppend
    unless system("grep -q 'Mushware appends' ~/.bashrc")
      File.open(ENV['HOME']+"/.bashrc", "a") do |file|
        file.puts <<EOS
# Mushware appends
export CVSROOT=:pserver:southa@ispanak.local:/cvs
export PATH="$PATH:$HOME/local/bin"
export MANPATH="$MANPATH:$HOME/local/share/man"
alias h=history
EOS
      end
    end
  end

  def mSourcesSetup
    system("sudo urpmi.addmedia main ftp://ftp.lip6.fr/pub/linux/distributions/Mandrakelinux/official/2007.1/i586/media/main/release with media_info/synthesis.hdlist.cz")
    system("sudo urpmi.addmedia --update main_updates ftp://ftp.lip6.fr/pub/linux/distributions/Mandrakelinux/official/2007.1/i586/media/main/updates with media_info/synthesis.hdlist.cz")
    system("sudo urpmi.addmedia contrib ftp://ftp.lip6.fr/pub/linux/distributions/Mandrakelinux/official/2007.1/i586/media/contrib/release with media_info/synthesis.hdlist.cz") 
    system("sudo urpmi.addmedia --update contrib_updates ftp://ftp.lip6.fr/pub/linux/distributions/Mandrakelinux/official/2007.1/i586/media/contrib/updates with media_info/synthesis.hdlist.cz")
    system("sudo urpmi.addmedia non-free ftp://ftp.lip6.fr/pub/linux/distributions/Mandrakelinux/official/2007.1/i586/media/non-free/release with media_info/synthesis.hdlist.cz")
  end

  def mYesSet(inValue)
    @m_yes = inValue
  end
end

debianInit = DebianInit.new

installDevel = false
installPackaging = false
installUser = false
installNVidia = false
appendBashrc = false

OptionParser.new do |opts|
  action = false
  opts.banner = "Usage: #{$0} [options]"

  opts.on("--yes", "DO NOT USE THIS OPTION!  It answers yes to all of the safety prompts") do
    debianInit.mYesSet(true)
    action = true
  end

  opts.on("--devel", "Install build-requires packages") do
    installDevel = true
  end

  opts.on("--packaging", "Install packaging packages (for producing .deb)") do
    installPackaging = true
  end

  opts.on("--user", "Install user packages (for convenience)") do
    installUser = true
  end

  opts.on("--nvidia", "Install NVidia drivers") do
    installNVidia = true
  end

  opts.on("--bashrc", "Append to .bashrc") do
    appendBashrc = true
  end

  opts.on("--all", "Installs all devel, packaging and user packages") do
    installDevel = true
    installPackaging = true
    installUser = true
  end

  opts.separator ""
  opts.separator "This script sets up a base installation of debian 4.0 to build this archive."
  opts.separator "Unless you are Andy Southgate, you probably don't want to run this as-is."
  opts.separator "Prerequisites:"
  opts.separator "Your user ID in /etc/sudoers:"
  opts.separator ">su root"
  opts.separator ">visudoers"
  opts.separator ">exit"
  opts.separator "Ruby installed"
  opts.separator ">sudo apt-get install ruby"
end.parse!

debianInit.mDevelInstall if installDevel
debianInit.mPackagingInstall if installPackaging
debianInit.mUserInstall if installUser
debianInit.mNVidiaInstall if installNVidia
debianInit.mBashrcAppend if appendBashrc

puts "#{$0} done."
