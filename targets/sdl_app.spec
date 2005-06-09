%define name MUSH_APP_PACKAGE
%define version MUSH_APP_VERSION
%define release MUSH_APP_RELEASE
%define RUNFILE %{_bindir}/MUSH_APP_PACKAGE
%define RUNFILESAFE %{_bindir}/MUSH_APP_PACKAGE-recover

Summary: MUSH_APP_NAME
Name: %{name}
Version: %{version}
Release: %{release}
Source0: http://www.mushware.com/files/%{name}-%{version}.tar.bz2
URL: http://www.mushware.com/
Copyright: GPL
Group: Games/Other
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
Prefix: %{_prefix}
MUSH_BUILD_REQUIRES
Provides: %{name}-%{version}-%{release}

%description
Tesseract Trainer generates a full screen real time display of a rotating
tesseract - the equivalent of the cube in 4 dimensions. This app also adds
point textures, which give you a feel of what each of the eight faces are
doing. There's a stereoscopic option which adds 3D depth to the projection
from 4D, music and numerous options to play with. I'm very keen to get
feedback as to whether anyone can 'see' the 4D effect here.

The application contains a number of interesting features.  Point textures
convey the orientation of each of the faces as the hypercube rotates.  The
two invariant planes of the rotation are shown.  Any number of faces can be
drawn, so each can be followed in turn.  The facets of each face can be
textured, and faces on each axis are shown in different colours to distinguish
them.  A manual is provided in PDF format, together with key control help
whilst the application is running.  Display resolution can be selected to
match the display.  Finally, some experimental seven-time music creates a bit
of atmosphere.

%prep
rm -rf ${RPM_BUILD_ROOT}

%setup -q

%build
%configure --program-transform-name=""
# App seen to segfault when throwing an exception if omit-frame-pointers is used
CXXFLAGS=`echo $CXXFLAGS | sed 's/-fomit-frame-pointer//'`
make CXXFLAGS="$CXXFLAGS"

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc README COPYING NEWS AUTHORS data-MUSH_APP_PACKAGE/About_Tesseract_Trainer.pdf
%{_datadir}/MUSH_APP_PACKAGE
%{_bindir}/MUSH_APP_PACKAGEbinary
%{RUNFILE}
%{RUNFILESAFE}
%{_mandir}/man6/%{name}*.6*

%post
rm -f %{RUNFILE}
echo #!/bin/sh > %{RUNFILE}
echo cd %{_datadir}/%{name}/system >> %{RUNFILE}
echo exec %{_bindir}/MUSH_APP_PACKAGEbinary >> %{RUNFILE}
chmod 0755 %{RUNFILE}
rm -f %{RUNFILESAFE}
echo #!/bin/sh > %{RUNFILESAAFE}
echo cd %{_datadir}/%{name}/system >> %{RUNFILESAFE}
echo "exec %{_bindir}/MUSH_APP_PACKAGEbinary \"load('start_safe.txt')\"" >> %{RUNFILESAFE}
chmod 0755 %{RUNFILESAFE}

%postun 

%changelog
* Tue Jun  9 2005 Andy Southgate <andy.southgate@mushware.com> 0.1.4-1
- Initial generic RPM
