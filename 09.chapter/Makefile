all: grpid grpmaster grpslave grpmaste grpmast grpslav grpmas grpsla session tty pty telnetd telnets telnety telnetl telnetc sigcatch crypt shell tsh tcsetpgrp placetaker returnback orphan

orphan: orphan.o apue.o
	gcc -Wall -g $^ -o $@ 

orphan.o: orphan.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99 -D_GNU_SOURCE

returnback: returnback.o
	gcc -Wall -g $^ -o $@ 

returnback.o: returnback.c 
	gcc -Wall -g -c $< -o $@ -std=c99 -D_GNU_SOURCE

placetaker: placetaker.o
	gcc -Wall -g $^ -o $@ 

placetaker.o: placetaker.c 
	gcc -Wall -g -c $< -o $@ -std=c99 -D_GNU_SOURCE

tcsetpgrp: tcsetpgrp.o
	gcc -Wall -g $^ -o $@ 

tcsetpgrp.o: tcsetpgrp.c 
	gcc -Wall -g -c $< -o $@ -std=c99 -D_GNU_SOURCE

tsh: tsh.o apue.o
	gcc -Wall -g $^ -o $@ 

tsh.o: tsh.c 
	gcc -Wall -g -c $< -o $@ -std=c99 -D_GNU_SOURCE

shell: shell.o apue.o log.o
	gcc -Wall -g $^ -o $@ 

shell.o: ../01.chapter/shell.c 
	gcc -Wall -g -c $< -o $@ -std=c99 -DUSE_TIOCSPGRP

crypt: crypt.o apue.o
	gcc -Wall -g $^ -o $@ -lcrypt

crypt.o: crypt.c 
	gcc -Wall -g -c $< -o $@ -D_XOPEN_SOURCE #-std=c99

sigcatch: sigcatch.o apue.o
	gcc -Wall -g $^ -o $@

sigcatch.o: sigcatch.c 
	gcc -Wall -g -c $< -o $@ -std=c99 -D_POSIX_SOURCE

telnetc: telnetc.o apue.o
	gcc -Wall -g $^ -o $@

telnetc.o: telnet/telnetc.c 
	gcc -Wall -g -c $< -o $@ #-std=c99

telnetl: telnetl.o apue.o
	gcc -Wall -g $^ -o $@ -lutil

telnetl.o: telnet/telnetl.c 
	gcc -Wall -g -c $< -o $@ #-std=c99

telnety: telnety.o apue.o log.o #pty_fun.o
	gcc -Wall -g $^ -o $@ -lutil

telnety.o: telnet/telnety.c 
	gcc -Wall -g -c $< -o $@ #-std=c99

telnets: telnets.o pty_fun.o apue.o
	gcc -Wall -g $^ -o $@

telnets.o: telnet/telnets.c ../pty_fun.h
	gcc -Wall -g -c $< -o $@ #-std=c99

telnetd: telnetd.o pty_fun.o apue.o
	gcc -Wall -g $^ -o $@

telnetd.o: telnet/telnetd.c ../pty_fun.h
	gcc -Wall -g -c $< -o $@ #-std=c99

pty_fun.o: ../pty_fun.c ../pty_fun.h
	gcc -Wall -g -c $< -o $@ -D_GNU_SOURCE #-std=c99

pty: pty.o apue.o
	gcc -Wall -g $^ -o $@ -lutil

pty.o: pty.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

tty: tty.o apue.o
	gcc -Wall -g $^ -o $@

tty.o: tty.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

session: session.o apue.o
	gcc -Wall -g $^ -o $@

session.o: session.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

grpsla: grpsla.o apue.o
	gcc -Wall -g $^ -o $@

grpsla.o: grpsla.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

grpmas: grpmas.o apue.o
	gcc -Wall -g $^ -o $@

grpmas.o: grpmas.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99 -DUSE_SYSTEM

grpslav: grpslav.o apue.o
	gcc -Wall -g $^ -o $@

grpslav.o: grpslav.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

grpmast: grpmast.o apue.o
	gcc -Wall -g $^ -o $@

grpmast.o: grpmast.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99 -DUSE_SYSTEM

grpmaste: grpmaste.o apue.o
	gcc -Wall -g $^ -o $@

grpmaste.o: grpmaste.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99 #-DUSE_SYSTEM

grpslave: grpslave.o apue.o
	gcc -Wall -g $^ -o $@

grpslave.o: grpslave.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

grpmaster: grpmaster.o apue.o
	gcc -Wall -g $^ -o $@

grpmaster.o: grpmaster.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99 #-DUSE_SYSTEM

grpid: grpid.o apue.o
	gcc -Wall -g $^ -o $@

grpid.o: grpid.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

log.o: ../log.c ../log.h
	gcc -Wall -g -c $< -o $@

apue.o: ../apue.c ../apue.h 
	gcc -Wall -g -c $< -o $@ -D__USE_BSD

clean: 
	@echo "start clean..."
	-rm -f *.o core.* *.log *~ *.swp grpid grpmaster grpslave grpmaste grpmast grpslav grpmas grpsla session tty pty telnetd telnets telnety telnetl telnetc sigcatch crypt shell tsh tcsetpgrp placetaker returnback orphan
	@echo "end clean"

.PHONY: clean
