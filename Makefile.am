SUBDIRS = @TOP_SUBDIRS@

release: install-strip
	(cd $(top_srcdir)/contractor;$(SHELL) MakeRelease.sh)

databall: release
	(cd $(top_srcdir)/release;tar cpvzf ../ic2-data.tar.gz *)
