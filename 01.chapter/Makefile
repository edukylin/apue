all: myls myecho ourecho pid shell shell_s error uid conf conf.out tmpname limit option clock

myls: myls.o apue.o
	gcc -Wall -g $^ -o $@

myls.o: myls.c ../apue.h 
	gcc -Wall -g -c $< -o $@

myecho: myecho.o apue.o
	gcc -Wall -g $^ -o $@

myecho.o: myecho.c ../apue.h
	gcc -Wall -g -c $< -o $@

ourecho: ourecho.o apue.o
	gcc -Wall -g $^ -o $@

ourecho.o: ourecho.c ../apue.h
	gcc -Wall -g -c $< -o $@

pid: pid.o apue.o
	gcc -Wall -g $^ -o $@

pid.o: pid.c ../apue.h
	gcc -Wall -g -c $< -o $@

shell_s: shell.c ../apue.c  ../log.c
	gcc -Wall -g $^ -static -o $@ -std=c99

shell: shell.o apue.o log.o
	gcc -Wall -g $^ -o $@

shell.o: shell.c ../apue.h ../log.h
	gcc -Wall -g -c $< -o $@ -std=c99

error: error.o apue.o
	gcc -Wall -g $^ -o $@

error.o: error.c ../apue.h
	gcc -Wall -g -c $< -o $@

uid: uid.o apue.o
	gcc -Wall -g $^ -o $@

uid.o: uid.c ../apue.h
	gcc -Wall -g -c $< -o $@

conf: conf.o apue.o
	gcc -Wall -g $^ -o $@

conf.o: conf.c ../apue.h
	gcc -Wall -g -c $< -o $@

conf.c: conf.awk sysconf.sym pathconf.sym
	./$^ > $@

conf.out: conf.out.o apue.o
	gcc -Wall -g $^ -o $@

conf.out.o: conf.awk.c ../apue.h
	gcc -Wall -g -c $< -o $@

option: option.o apue.o
	gcc -Wall -g $^ -o $@

option.o: option.c ../apue.h
	gcc -Wall -g -c $< -o $@

option.c: option.awk
	./option.awk > option.c

tmpname: tmpname.o
	gcc -Wall -g $^ -o $@

tmpname.o: tmpname.c
	gcc -Wall -g -c $< -o $@

limit: limit.o 
	gcc -Wall -g $^ -o $@

limit.o: limit.c
	gcc -Wall -g -c $< -o $@

apue.o: ../apue.c ../apue.h 
	gcc -Wall -g -c $< -o $@

log.o: ../log.c ../log.h 
	gcc -Wall -g -c $< -o $@

clock: clock.o
	gcc -Wall -g $^ -o $@

clock.o: clock.c
	gcc -Wall -g -c $< -o $@

clean: 
	@echo "start clean..."
	-rm -f *.o core.* *.log *~ *.swp myls myecho ourecho pid shell shell_s error uid conf conf.c conf.out tmpname limit option option.c clock
	@echo "end clean"

.PHONY: clean
