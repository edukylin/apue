all: coredump testsig demosig execsig lostsig interwait errnomt getpwnam_r localtime_r cldsig blocksig killsig alrmsig alrmsleep breaksig sigset sigjmp suspendsig waitsig syncsig sigabrt systemsig jobsig stpsig signame sleep cpalrm dash

dash: dash.o apue.o
	gcc -Wall -g $^ -o $@

dash.o: dash.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

cpalrm: cpalrm.o apue.o
	gcc -Wall -g $^ -o $@

cpalrm.o: cpalrm.c ../apue.h
	gcc -Wall -g -c $< -o $@

sleep: sleep.o apue.o
	gcc -Wall -g $^ -o $@

sleep.o: sleep.c ../apue.h
	gcc -Wall -g -c $< -o $@

signame: signame.o apue.o
	gcc -Wall -g $^ -o $@

signame.o: signame.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99 -D_GNU_SOURCE

stpsig: stpsig.o apue.o
	gcc -Wall -g $^ -o $@

stpsig.o: stpsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

jobsig: jobsig.o apue.o
	gcc -Wall -g $^ -o $@

jobsig.o: jobsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

systemsig: systemsig.o apue.o
	gcc -Wall -g $^ -o $@

systemsig.o: systemsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

sigabrt: sigabrt.o apue.o
	gcc -Wall -g $^ -o $@

sigabrt.o: sigabrt.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

syncsig: syncsig.o apue.o
	gcc -Wall -g $^ -o $@

syncsig.o: syncsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

waitsig: waitsig.o apue.o
	gcc -Wall -g $^ -o $@

waitsig.o: waitsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

suspendsig: suspendsig.o apue.o
	gcc -Wall -g $^ -o $@

suspendsig.o: suspendsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

sigjmp: sigjmp.o apue.o
	gcc -Wall -g $^ -o $@

sigjmp.o: sigjmp.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

sigset: sigset.o apue.o
	gcc -Wall -g $^ -o $@

sigset.o: sigset.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

breaksig: breaksig.o apue.o
	gcc -Wall -g $^ -o $@

breaksig.o: breaksig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

alrmsleep: alrmsleep.o apue.o
	gcc -Wall -g $^ -o $@

alrmsleep.o: alrmsleep.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

alrmsig: alrmsig.o apue.o
	gcc -Wall -g $^ -o $@

alrmsig.o: alrmsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

killsig: killsig.o apue.o
	gcc -Wall -g $^ -o $@

killsig.o: killsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

blocksig: blocksig.o apue.o
	gcc -Wall -g $^ -o $@

blocksig.o: blocksig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

cldsig: cldsig.o apue.o
	gcc -Wall -g $^ -o $@

cldsig.o: cldsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

localtime_r: localtime_r.o apue.o
	gcc -Wall -g $^ -o $@

localtime_r.o: localtime_r.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

getpwnam_r: getpwnam_r.o apue.o
	gcc -Wall -g $^ -o $@

getpwnam_r.o: getpwnam_r.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

errnomt: errnomt.o apue.o
	gcc -Wall -g $^ -o $@ -pthread

errnomt.o: errnomt.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

interwait: interwait.o apue.o
	gcc -Wall -g $^ -o $@

interwait.o: interwait.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

lostsig: lostsig.o apue.o
	gcc -Wall -g $^ -o $@

lostsig.o: lostsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

execsig: execsig.o apue.o
	gcc -Wall -g $^ -o $@

execsig.o: execsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

demosig: demosig.o apue.o
	gcc -Wall -g $^ -o $@

demosig.o: demosig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

testsig: testsig.o apue.o
	gcc -Wall -g $^ -o $@

testsig.o: testsig.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

coredump: coredump.o apue.o
	gcc -Wall -g $^ -o $@

coredump.o: coredump.c ../apue.h
	gcc -Wall -g -c $< -o $@ -std=c99

log.o: ../log.c ../log.h
	gcc -Wall -g -c $< -o $@

apue.o: ../apue.c ../apue.h 
	gcc -Wall -g -c $< -o $@ -D__USE_BSD

clean: 
	@echo "start clean..."
	-rm -f *.o core.* *.log *~ *.swp coredump testsig demosig execsig lostsig interwait errnomt getpwnam_r localtime_r cldsig blocksig killsig alrmsig alrmsleep breaksig sigset sigjmp suspendsig waitsig syncsig sigabrt systemsig jobsig stpsig signame sleep cpalrm dash
	@echo "end clean"

.PHONY: clean
