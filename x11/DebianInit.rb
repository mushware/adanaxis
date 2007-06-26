#!/usr/bin/ruby -w
##############################################################################
#
# File x11/DebianInit.rb
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
# $Id: ProcessIntern.rb,v 1.3 2006/11/05 09:32:13 southa Exp $
# $Log: ProcessIntern.rb,v $

require 'optparse'

class DebianInit
  def initialize
    @m_develPackages = %w{
autoconf
automake
freeglut3-dev
g++      
gcc
libc6-dev
libexpat1-dev
libjpeg62-dev
libpcre3-dev
libsdl1.2-dev
libsdl-mixer1.2-dev
libtiff4-dev
manpages-dev
}
# Also:
# libgl1-mesa-dev (pulled in by freeglut3-dev)
# libglu1-mesa-dev (pulled in by freeglut3-dev)
# libogg-dev (pulled in by libsdl-mixer1.2-dev)
# libvorbis-dev (pulled in by libsdl-mixer1.2-dev)

    @m_packagingPackages = %w{
autoconf
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
c-cpp-reference
kate
kate-plugins
kde
kde-devel-extras
kdevelop
kdegames
kdegraphics
kscreensaver
rss-glx
shermans-aquarium
xscreensaver-gl
    }
   @m_yes = false
  end

  def mPackagesInstall(inPackages)
    failures = []
    flags = ""
    flags += " --yes" if @m_yes
    inPackages.each do |package|
      command = "sudo apt-get install#{flags} #{package}"
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

  def mYesSet(inValue)
    @m_yes = inValue
  end
end

debianInit = DebianInit.new

installDevel = false
installPackaging = false
installUser = false

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

  opts.on("--all", "Installs all packages required by this archive") do
    installDevel = true
    installPackaging = true
    installUser = true
  end

  opts.separator ""
  opts.separator "This script sets up a base installation of debian 4.0 to build this archive.  Unless you are Andy Southgate, you probably don't want to run this as-is."
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

puts "#{$0} done."
