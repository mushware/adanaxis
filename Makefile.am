SUBDIRS = @TOP_SUBDIRS@

release: install-strip
	(cd $(top_srcdir)/ic2data;$(SHELL) MakeRelease.sh)

binball: release
	(cd $(top_srcdir)/release;tar cpvzf ../ic2-bin.tar.gz *)
