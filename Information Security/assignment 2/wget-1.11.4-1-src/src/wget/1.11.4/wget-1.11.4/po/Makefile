# Makefile for program source directory in GNU NLS utilities package.
# Copyright (C) 1995, 1996, 1997 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
#
# This file file be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU Public License
# but which still want to provide support for the GNU gettext functionality.
# Please note that the actual code is *not* freely available.

PACKAGE = wget
VERSION = 1.11.4

SHELL = /bin/sh


top_builddir = ..

srcdir = ../../wget-1.11.4-src/po
top_srcdir = ../../wget-1.11.4-src
VPATH = ../../wget-1.11.4-src/po

prefix = c:/progra~1/wget
exec_prefix = ${prefix}
datadir = $(prefix)/share
localedir = $(datadir)/locale
gnulocaledir = $(prefix)/share/locale
gettextsrcdir = $(prefix)/share/gettext/po
subdir = po

DESTDIR =

INSTALL = /bin/install.exe -cp
INSTALL_DATA = /bin/install.exe -cp

CC = gcc
GMSGFMT = PATH=../src:$$PATH /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = PATH=../src:$$PATH /usr/bin/xgettext
MSGMERGE = PATH=../src:$$PATH msgmerge

DEFS = -DHAVE_CONFIG_H
CFLAGS =  -Wall -Wpointer-arith -O3 -fms-extensions -mms-bitfields -fno-exceptions -fomit-frame-pointer -march=i386 -ffast-math  -Wstrict-prototypes  
CPPFLAGS =   -D__USE_MINGW_ACCESS -D_LARGEFILE_SOURCE=1 -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64 -DENABLE_RELOCATABLE -DINSTALLPREFIX=\"$(prefix)\" -DINSTALLDIR=\"$(bindir)\" -DEXEEXT=\"$(EXEEXT)\" -DNO_XMALLOC       -ID:/Progra~1/GnuWin32/include     

INCLUDES = -I.. -I$(top_srcdir)/intl

COMPILE = $(CC) -c $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) $(XCFLAGS)

POFILES =  be.po bg.po ca.po cs.po da.po de.po el.po en_GB.po eo.po es.po et.po eu.po fi.po fr.po ga.po gl.po he.po hr.po hu.po id.po it.po ja.po nb.po nl.po pl.po pt.po pt_BR.po ro.po ru.po sk.po sl.po sr.po sv.po tr.po uk.po vi.po zh_CN.po zh_TW.po
GMOFILES =  be.gmo bg.gmo ca.gmo cs.gmo da.gmo de.gmo el.gmo en_GB.gmo eo.gmo es.gmo et.gmo eu.gmo fi.gmo fr.gmo ga.gmo gl.gmo he.gmo hr.gmo hu.gmo id.gmo it.gmo ja.gmo nb.gmo nl.gmo pl.gmo pt.gmo pt_BR.gmo ro.gmo ru.gmo sk.gmo sl.gmo sr.gmo sv.gmo tr.gmo uk.gmo vi.gmo zh_CN.gmo zh_TW.gmo
DISTFILES = ChangeLog Makefile.in.in POTFILES.in $(PACKAGE).pot \
$(POFILES) $(GMOFILES) $(SOURCES)

POTFILES = \
	../../wget-1.11.4-src/src/cmpt.c \
	../../wget-1.11.4-src/src/connect.c \
	../../wget-1.11.4-src/src/convert.c \
	../../wget-1.11.4-src/src/cookies.c \
	../../wget-1.11.4-src/src/ftp-basic.c \
	../../wget-1.11.4-src/src/ftp-ls.c \
	../../wget-1.11.4-src/src/ftp-opie.c \
	../../wget-1.11.4-src/src/ftp.c \
	../../wget-1.11.4-src/src/gen-md5.c \
	../../wget-1.11.4-src/src/getopt.c \
	../../wget-1.11.4-src/src/gnu-md5.c \
	../../wget-1.11.4-src/src/hash.c \
	../../wget-1.11.4-src/src/host.c \
	../../wget-1.11.4-src/src/html-parse.c \
	../../wget-1.11.4-src/src/html-url.c \
	../../wget-1.11.4-src/src/http.c \
	../../wget-1.11.4-src/src/init.c \
	../../wget-1.11.4-src/src/log.c \
	../../wget-1.11.4-src/src/main.c \
	../../wget-1.11.4-src/src/mswindows.c \
	../../wget-1.11.4-src/src/netrc.c \
	../../wget-1.11.4-src/src/openssl.c \
	../../wget-1.11.4-src/src/progress.c \
	../../wget-1.11.4-src/src/ptimer.c \
	../../wget-1.11.4-src/src/recur.c \
	../../wget-1.11.4-src/src/res.c \
	../../wget-1.11.4-src/src/retr.c \
	../../wget-1.11.4-src/src/spider.c \
	../../wget-1.11.4-src/src/url.c \
	../../wget-1.11.4-src/src/utils.c \
	../../wget-1.11.4-src/src/version.c \
	../../wget-1.11.4-src/src/xmalloc.c

CATALOGS =  be.gmo bg.gmo ca.gmo cs.gmo da.gmo de.gmo el.gmo en_GB.gmo eo.gmo es.gmo et.gmo eu.gmo fi.gmo fr.gmo ga.gmo gl.gmo he.gmo hr.gmo hu.gmo id.gmo it.gmo ja.gmo nb.gmo nl.gmo pl.gmo pt.gmo pt_BR.gmo ro.gmo ru.gmo sk.gmo sl.gmo sr.gmo sv.gmo tr.gmo uk.gmo vi.gmo zh_CN.gmo zh_TW.gmo
CATOBJEXT = .gmo
INSTOBJEXT = .mo

.SUFFIXES:
.SUFFIXES: .c .o .po .pox .gmo .mo .msg

.c.o:
	$(COMPILE) $<

.po.pox:
	$(MAKE) $(PACKAGE).pot
	$(MSGMERGE) $< $(srcdir)/$(PACKAGE).pot -o $*.pox

.po.mo:
	$(MSGFMT) -o $@ $<

.po.gmo:
	file=$(srcdir)/`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<


all: all-yes

all-yes: $(CATALOGS)
all-no:

$(srcdir)/$(PACKAGE).pot: $(POTFILES)
	$(XGETTEXT) --default-domain=$(PACKAGE) --directory=$(top_srcdir) \
	  --add-comments --keyword=_ --keyword=N_ \
	  --files-from=$(srcdir)/POTFILES.in
	rm -f $(srcdir)/$(PACKAGE).pot
	mv $(PACKAGE).po $(srcdir)/$(PACKAGE).pot

install.mo: install
install: install-exec install-data
install-exec:
install-data: install-data-yes
install-data-no: all
install-data-yes: all
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  case "$$cat" in \
	    *.gmo) destdir=$(DESTDIR)$(gnulocaledir);; \
	    *)     destdir=$(DESTDIR)$(localedir);; \
	  esac; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  dir=$$destdir/$$lang/LC_MESSAGES; \
	  $(top_srcdir)/mkinstalldirs $$dir; \
	  if test -r $$cat; then \
	    $(INSTALL_DATA) $$cat $$dir/$(PACKAGE)$(INSTOBJEXT); \
	    echo "installing $$cat as $$dir/$(PACKAGE)$(INSTOBJEXT)"; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$cat $$dir/$(PACKAGE)$(INSTOBJEXT); \
	    echo "installing $(srcdir)/$$cat as" \
		 "$$dir/$(PACKAGE)$(INSTOBJEXT)"; \
	  fi; \
	  if test -r $$cat.m; then \
	    $(INSTALL_DATA) $$cat.m $$dir/$(PACKAGE)$(INSTOBJEXT).m; \
	    echo "installing $$cat.m as $$dir/$(PACKAGE)$(INSTOBJEXT).m"; \
	  else \
	    if test -r $(srcdir)/$$cat.m ; then \
	      $(INSTALL_DATA) $(srcdir)/$$cat.m \
		$$dir/$(PACKAGE)$(INSTOBJEXT).m; \
	      echo "installing $(srcdir)/$$cat as" \
		   "$$dir/$(PACKAGE)$(INSTOBJEXT).m"; \
	    else \
	      true; \
	    fi; \
	  fi; \
	done
	if test "$(PACKAGE)" = "gettext"; then \
	  $(INSTALL_DATA) $(srcdir)/Makefile.in.in \
			  $(gettextsrcdir)/Makefile.in.in; \
	else \
	  : ; \
	fi

# Define this as empty until I found a useful application.
installcheck:

uninstall:
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  dir=$(DESTDIR)$(localedir)/$$lang/LC_MESSAGES; \
	  rm -f $$dir/$(PACKAGE)$(INSTOBJEXT); \
	  rm -f $$dir/$(PACKAGE)$(INSTOBJEXT).m; \
	  dir=$(DESTDIR)$(gnulocaledir)/$$lang/LC_MESSAGES; \
	  rm -f $$dir/$(PACKAGE)$(INSTOBJEXT); \
	  rm -f $$dir/$(PACKAGE)$(INSTOBJEXT).m; \
	done
	rm -f $(gettextsrcdir)/po-Makefile.in.in

check: all

cat-id-tbl.o: ../intl/libgettext.h

dvi info tags TAGS ID:

mostlyclean:
	rm -f core core.* *.pox $(PACKAGE).po *.old.po
	rm -fr *.o

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES *.mo *.gmo *.msg

maintainer-clean: distclean
	@echo "!! This command is intended for maintainers to use;"
	@echo "!! it deletes files that may require special tools to rebuild."
	rm -f $(GMOFILES)

realclean: maintainer-clean

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: update-po $(DISTFILES)
	dists="$(DISTFILES)"; \
	for file in $$dists; do \
	  ln $(srcdir)/$$file $(distdir) 2> /dev/null \
	    || cp -p $(srcdir)/$$file $(distdir); \
	done

update-po: Makefile
	$(MAKE) $(PACKAGE).pot
	PATH=`pwd`/../src:$$PATH; \
	cd $(srcdir); \
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  mv $$lang.po $$lang.old.po; \
	  echo "$$lang:"; \
	  if $(MSGMERGE) $$lang.old.po $(PACKAGE).pot -o $$lang.po; then \
	    rm -f $$lang.old.po; \
	  else \
	    echo "msgmerge for $$cat failed!"; \
	    rm -f $$lang.po; \
	    mv $$lang.old.po $$lang.po; \
	  fi; \
	done

POTFILES: POTFILES.in
	( if test 'x$(srcdir)' != 'x.'; then \
	    posrcprefix='$(top_srcdir)/'; \
	  else \
	    posrcprefix="../"; \
	  fi; \
	  rm -f $@-t $@ \
	    && (sed -e '/^#/d' -e '/^[ 	]*$$/d' \
		    -e "s@.*@	$$posrcprefix& \\\\@" < $(srcdir)/$@.in \
		| sed -e '$$s/\\$$//') > $@-t \
	    && chmod a-w $@-t \
	    && mv $@-t $@ )

Makefile: Makefile.in.in ../config.status POTFILES
	cd .. \
	  && CONFIG_FILES=$(subdir)/$@.in CONFIG_HEADERS= \
	       $(SHELL) ./config.status

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
