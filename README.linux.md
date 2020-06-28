README for Linux
================

2020-06-28 state of play
========================

The repos haven't yet been refactored since the move to Github so it takes a
bit of effort to build Adanaxis, but it can be done.  Here's an example for
ArchLinux 2020.06.01 below:

    sudo pacman -S expat glu libogg libtiff libvorbis libx11 libxext pcre sdl sdl_mixer freeglut

    git clone https://github.com/mushware/adanaxis
    cd adanaxis/
    git checkout ADANAXIS_1_2_5_RELEASE_X11
    mkdir src/MushSecret
    cd ..
    git clone https://github.com/mushware/adanaxis-core-keys
    mv adanaxis-core-keys core-keys
    git clone https://github.com/mushware/adanaxis-data
    cd adanaxis-data
    git checkout IMPORTED_FROM_CVS
    cd ..
    cp -R adanaxis-data/* adanaxis
    cp -R adanaxis-data adanaxis/data-adanaxis
    git clone https://github.com/mushware/adanaxis-mushruby
    cp -R adanaxis-mushruby adanaxis/mushruby
    cp -R adanaxis-mushruby adanaxis/data-adanaxis/mushruby
    cd adanaxis
    curl https://aur.archlinux.org/cgit/aur.git/plain/gcc-4.7.patch?h=adanaxis-gpl | patch --strip=1
    curl https://aur.archlinux.org/cgit/aur.git/plain/const.patch?h=adanaxis-gpl | patch --strip=1
    perl autogen.pl adanaxis -dist=genericdpkg --type=full && true # (fails first time round)
    automake --add-missing
    perl autogen.pl adanaxis -dist=genericdpkg --type=full
    ./configure
    make
    sudo make install
    adanaxis

Builds from master or the packaging itself have not been tested yet.  It'll
all be redone for Travis CI so no need to update distros just yet.

Legacy content
==============

Building from source on Mandrake Linux 8.2
==========================================

These instructions are based on building Mushware source on a Mandrake Linux
installation.  Mandrake Linux 8.2 was installed using the default settings.

The glxinfo command should print information, and not tell you that GLX is
disabled.  If it does, you may have to add a line loading the glx module
to the file /etc/XF86Config.

Download the files <app-name>-<version>.tar.gz into your home directory.

    tar xvzf <app-name>-<version>.tar.gz
    cd <app-name>-<version>
    ./configure

Configure is likely to fail first time round, but it will tell you what's
missing..  The following steps were required for configure to complete.

Open the software manager from Start Menu->Configuration->Packaging->Software
Manager.  Search for and install the following packages, and allow the
software manager to install the dependencies.

    gcc-c++
    XFree86-devel
    libMesaGLU1-devel
    libMesaglut3-devel
    libpcre0-devel
    libexpat1_95-devel
    libungif4-devel
    libtiff3-devel
    libSDL1.2-devel
    libalsa1-devel
    libesound0-devel
    libsmpeg0.4-devel
    libogg0-devel
    libvorbis0-devel
    libSDL_mixer1.2-devel

Then

    ./configure
    make
    make install

Building from source on RedHat Linux 7.3
========================================

These instructions are based on building the Mushware source on a RedHat Linux
installation.  RedHat Linux 7.3 was installed using the 'GNOME' setting.

Download the files <app-name>-<version>.tar.gz into your home directory.

    tar xvzf <app-name>-<version>.tar.gz
    cd <app-name>-<version>
    ./configure

Configure is likely to fail first time round, but it will tell you what's
missing..  The following steps were required for configure to complete.

Insert the RedHat CD 2.  Answer 'Yes' when asked to run autorun, or run it
manually.  Gnome RPM should start.  Choose Operations->Install... from the
menu.  This application reads package details from the CD in the background,
so the file list may take a while to complete.  Install the following
packages:

    Development->Languages->cpp-2.96-110
    Development->Languages->gcc-2.96-110
    Development->Languages->gcc-c++-2.96-110
    Development->Libraries->glibc-devel-2.2.5-34
    Development->Libraries->libstdc++-devel-2.96-110
    Development->System->glibc-kernheaders-2.4-7.14
    Development->Tools->binutils-2.1.1.93.0.2-11

    Development->Libraries->XFree86-devel-4.2.0-8
    System Environment->Libraries->glut-3.7-4
    Development->Libraries->glut-devel-3.7-4

    Development->Libraries->pcre-devel-3.9-2
    Development->Libraries->expat-devel-1.95.2-2
    Development->Libraries->libungif-devel-4.1.0-10
    Development->Libraries->libtiff-devel-3.5.7-2
    Development->Libraries->SDL-devel-1.2.3-7
    Development->Libraries->smpeg-devel-0.4.4-9
    Development->Libraries->libogg-devel-1.0rc3-1
    Development->Libraries->libvorbis-devel-1.0rc3-1
    Development->Libraries->SDL_mixer-devel-1.2.1-4

If the installers issues a warning about dependencies, find those packages
and install the as well.

    ./configure
    make
    make install

Building from source on SUSE Linux personal 8.0
===============================================

These instructions are based on building the Mushware source on a SUSE Linux
installation.  SUSE Linux 8.0 was installed using the 'Default + office'
setting.

Use the command 3Ddiag to check that your system is correctly configured
for 3D rendering.  The glxinfo command should print information, and not
tell you that GLX is disabled.

Download the files <app-name>-<version>.tar.gz into your home directory.

    tar xvzf <app-name>-<version>.tar.gz
    cd <app-name>-<version>
    ./configure

Configure is likely to fail first time round, but it will tell you what's
missing..  The following steps were required for configure to complete.

    Open the YAST2 application from Start Menu->System->YAST2
    (enter password as prompted)
    Choose Install/Remove software
    Install the following packages:
    Development/Tools -> package make
    Development/Languages/C and C++ -> package gcc
    Development/Languages/C and C++ -> package gpp
    Development/Libraries/X11 -> package xdevel
    Development/Libraries/X11 -> package expat
    Development/Libraries/C and C++ -> package alsa-devel
    Development/Libraries/C and C++ -> package esound-devel
    Development/Libraries/C and C++ -> package vorbis-devel
    Productivity/Multimedia/Video/Players -> package smpeg
    System/Libraries -> package SDL_mixer

Install the mesa, SDL, smpeg and ogg devel packages.  Couldn't find these
on my CD, so got them from:

    ftp://ftp.suse.com/pub/suse/i386/8.0/suse/x3d2/mesa-devel-4.0.1-118.i386.rpm
    ftp://ftp.suse.com/pub/suse/i386/8.0/suse/x3d2/mesaglu-devel-4.0.1-118.i386.rpm
    ftp://ftp.suse.com/pub/suse/i386/8.0/suse/x3d2/mesaglut-devel-4.0.1-118.i386.rpm
    ftp://ftp.suse.com/pub/suse/i386/8.0/suse/d4/SDL-devel-1.2.3-227.i386.rpm
    ftp://ftp.suse.com/pub/suse/i386/8.0/suse/gra3/smpeg-devel-0.4.4-322.i386.rpm
    ftp://ftp.suse.com/pub/suse/i386/8.0/suse/d4/libogg-devel-1.0rc3-73.i386.rpm

(Paste the URL into Konqueror, click 'Open' when asked to 'Open using
KPackage'.  Click 'Install' when KPackage starts.)

    ./configure
    make
    make install

Generating RPMs
===============

Install the rpm-build package if necessary.

    mkdir -p ~/rpm/{BUILD,RPMS/i586,RPMS/noarch,SOURCES,SRPMS,SPECS,tmp}

    # Create these files:

    rm -f ~/.rpmrc
    echo buildarchtranslate: i386: i586 >> ~/.rpmrc
    echo buildarchtranslate: i486: i586 >> ~/.rpmrc
    echo buildarchtranslate: i586: i586 >> ~/.rpmrc
    echo buildarchtranslate: i686: i586 >> ~/.rpmrc


    rm -f ~/.rpmmacros
    echo %_topdir               $HOME/rpm >> ~/.rpmmacros
    echo %_tmppath              $HOME/rpm/tmp >> ~/.rpmmacros
    echo %_signature            gpg >> ~/.rpmmacros
    echo %_gpg_name             <app-name> >> ~/.rpmmacros
    echo %_gpg_path             ~/.gnupg >> ~/.rpmmacros
    echo %distribution          <app-name> >> ~/.rpmmacros
    echo %vendor                Mushware Limited >> ~/.rpmmacros
