all: tattrsize tconcurr mattrshare mattrtype tattrtimeout rwattrshare cattrshare flock getenv static key cancel signal fork pread putenv sleep getenv.bsd

getenv.bsd: getenv.bsd.o apue.o
	gcc -Wall -g $^ -o $@ -pthread

getenv.bsd.o: getenv.bsd.c ../apue.h
	gcc -Wall -g -c $< -o $@

sleep: sleep.o apue.o
	gcc -Wall -g $^ -o $@ -pthread

sleep.o: sleep.c ../apue.h
	gcc -Wall -g -c $< -o $@

putenv: putenv.o apue.o
	gcc -Wall -g $^ -o $@ -pthread

putenv.o: putenv.c ../apue.h
	gcc -Wall -g -c $< -o $@

pread: pread.o apue.o
	gcc -Wall -g $^ -o $@ -pthread

pread.o: pread.c ../apue.h
	gcc -Wall -g -c $< -o $@

fork: fork.o apue.o
	gcc -Wall -g $^ -o $@ -pthread

fork.o: fork.c ../apue.h
	gcc -Wall -g -c $< -o $@

signal: signal.o apue.o
	gcc -Wall -g $^ -o $@ -pthread

signal.o: signal.c ../apue.h
	gcc -Wall -g -c $< -o $@ -DUSE_PTHREAD

cancel: cancel.o 
	gcc -Wall -g $^ -o $@ -pthread

cancel.o: cancel.c 
	gcc -Wall -g -c $< -o $@

key: key.o 
	gcc -Wall -g $^ -o $@ -pthread

key.o: key.c 
	gcc -Wall -g -c $< -o $@

static: static.o
	g++ -Wall -g $^ -o $@ -pthread

static.o: static.c
	g++ -Wall -g -c $< -o $@

getenv: getenv.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

getenv.o: getenv.c ../apue.h
	gcc -Wall -g -c $< -o $@

flock: flock.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

flock.o: flock.c ../apue.h
	gcc -Wall -g -c $< -o $@ -D_GNU_SOURCE

cattrshare: cattrshare.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

cattrshare.o: cattrshare.c ../apue.h
	gcc -Wall -g -c $< -o $@

rwattrshare: rwattrshare.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

rwattrshare.o: rwattrshare.c ../apue.h
	gcc -Wall -g -c $< -o $@

tattrtimeout: tattrtimeout.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

tattrtimeout.o: tattrtimeout.c ../apue.h
	gcc -Wall -g -c $< -o $@ -D_GNU_SOURCE

mattrtype: mattrtype.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

mattrtype.o: mattrtype.c ../apue.h
	gcc -Wall -g -c $< -o $@ -D_GNU_SOURCE

mattrshare: mattrshare.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

mattrshare.o: mattrshare.c ../apue.h
	gcc -Wall -g -c $< -o $@

tconcurr: tconcurr.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

tconcurr.o: tconcurr.c ../apue.h
	gcc -Wall -g -c $< -o $@

tattrsize: tattrsize.o apue.o 
	gcc -Wall -g $^ -o $@ -pthread

tattrsize.o: tattrsize.c ../apue.h
	gcc -Wall -g -c $< -o $@

log.o: ../log.c ../log.h
	gcc -Wall -g -c $< -o $@

apue.o: ../apue.c ../apue.h 
	gcc -Wall -g -c $< -o $@ -D__USE_BSD -DUSE_PTHREAD

clean: 
	@echo "start clean..."
	-rm -f *.o core.* *.log *~ *.swp tattrsize tconcurr mattrshare mattrtype tattrtimeout rwattrshare cattrshare flock getenv static key cancel signal fork pread putenv sleep getenv.bsd
	@echo "end clean"

.PHONY: clean
