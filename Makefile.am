# -*-makefile-*-
AUTOMAKE_OPTIONS=1.6
SUBDIRS = @TOP_SUBDIRS@
DIST_SUBDIRS = @TOP_SUBDIRS@
RUNFILE=${DESTDIR}${bindir}/ic2
GZIPFILE=ic2-@IC_VERSION@.tar.gz
BZIPFILE=ic2-@IC_VERSION@.tar.bz2

DATAMAKEFILE=ic2data/Makefile.am

EXTRA_DIST=core-app.pbproj/project.pbxproj ic2 MakeRelease.sh \
ic2.spec.mdk ic2.spec.mdk.in \
ic2.spec.suse ic2.spec.suse.in \
ic2.spec.redhat ic2.spec.redhat.in \
ic2.spec

release: install-strip
	(cd $(top_srcdir);$(SHELL) MakeRelease.sh)

mac-release: release
	(cd $(top_srcdir);$(SHELL) macosx/MakeInstaller.sh @IC_UNDERSCORE_VERSION@)

win32-release: release
	(cd $(top_srcdir);$(SHELL) win32/MakeInstaller.sh @IC_UNDERSCORE_VERSION@)

makefiles-withdata:
	sed -e 's/_nodist_/_dist_/' $(DATAMAKEFILE) > tempMakefile
	mv -f tempMakefile $(DATAMAKEFILE)

makefiles-withoutdata:
	sed -e 's/_dist_/_nodist_/' $(DATAMAKEFILE) > tempMakefile
	mv -f tempMakefile $(DATAMAKEFILE)

x11-release $(GZIPFILE): ic2.spec makefiles-withoutdata dist
	rm -f ic2-src-@IC_UNDERSCORE_VERSION@.tar.gz
	rm -f ic2-data-@IC_UNDERSCORE_VERSION@.tar.gz
	cp -p COPYING ic2data/COPYING
	tar cpvf ic2-data-@IC_UNDERSCORE_VERSION@.tar ic2data/COPYING
	rm ic2data/COPYING
	find ic2data -path './data/system/ic2*' -prune -o \
           -path '*CVS' -prune -o \
           -name 'ic2.exe' -prune -o \
           -name 'ic2' -prune -o \
           -name '.*' -prune -o \
           -type f -name '*' \
           -exec tar rpvf ic2-data-@IC_UNDERSCORE_VERSION@.tar {} \;
	gzip ic2-data-@IC_UNDERSCORE_VERSION@.tar
	cp -p ic2-@IC_VERSION@.tar.gz ic2-src-@IC_UNDERSCORE_VERSION@.tar.gz
	$(MAKE) makefiles-withdata dist

$(BZIPFILE):$(GZIPFILE)
	rm -f $(BZIPFILE)
	gunzip -c $(GZIPFILE) | bzip2 --best > $(BZIPFILE)

mdk-rpm:
	cp -f ic2.spec.mdk ic2.spec
	$(MAKE) $(BZIPFILE)
	rpm -ta $(BZIPFILE)

redhat-rpm:
	cp -f ic2.spec.redhat ic2.spec
	$(MAKE) $(BZIPFILE)
	rpm -ta $(BZIPFILE)

suse-rpm:
	cp -f ic2.spec.suse ic2.spec
	$(MAKE) $(BZIPFILE)
	rpm -ta $(BZIPFILE)

install-exec-hook:
	rm -f $(RUNFILE)
	echo #!/bin/sh > $(RUNFILE)
	echo cd $(DESTDIR)$(pkgdatadir)/system >> $(RUNFILE)
	echo $(DESTDIR)$(bindir)/ic2binary >> $(RUNFILE)
	chmod 0755 $(RUNFILE)


