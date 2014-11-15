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

${OBJ}: config.mk

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

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/vtclock

.PHONY: all options clean dist install uninstall
