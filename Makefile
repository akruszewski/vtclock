# vtclock - terminal toy clock
# See LICENSE file for copyright and license details.

include config.mk

SRC = vtclock.c
OBJ = ${SRC:.c=.o}

all: options vtclock

options:
	@echo vtclock build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

config.h:
		@echo creating $@ from config.def.h
		@cp config.def.h $@

${OBJ}: config.mk config.h

vtclock: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f vtclock ${OBJ} vtclock-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p vtclock-${VERSION}
	@cp -R LICENSE Makefile README config.mk ${SRC} vtclock-${VERSION}
	@tar -cf vtclock-${VERSION}.tar vtclock-${VERSION}
	@gzip vtclock-${VERSION}.tar
	@rm -rf vtclock-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f vtclock ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/vtclock
	@chmod u+s ${DESTDIR}${PREFIX}/bin/vtclock
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < vtclock.1 > ${DESTDIR}${MANPREFIX}/man1/vtclock.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/vtclock.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/vtclock

.PHONY: all options clean dist install uninstall
