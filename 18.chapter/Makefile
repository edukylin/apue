all: term cchar size break uclc stop baudrate linectl restart isatty ttyname getpass ttymode winsz ttyraw

winsz: winsz.o apue.o
	gcc -Wall -g $^ -o $@

winsz.o: winsz.c ../apue.h
	gcc -Wall -g -c $< -o $@

getpass: getpass.o apue.o
	gcc -Wall -g $^ -o $@

getpass.o: getpass.c ../apue.h
	gcc -Wall -g -c $< -o $@

ttyname: ttyname.o apue.o
	gcc -Wall -g $^ -o $@

ttyname.o: ttyname.c ../apue.h
	gcc -Wall -g -c $< -o $@

isatty: isatty.o apue.o
	gcc -Wall -g $^ -o $@

isatty.o: isatty.c ../apue.h
	gcc -Wall -g -c $< -o $@

restart: restart.o apue.o
	gcc -Wall -g $^ -o $@

restart.o: restart.c ../apue.h
	gcc -Wall -g -c $< -o $@

linectl: linectl.o apue.o
	gcc -Wall -g $^ -o $@

linectl.o: linectl.c ../apue.h
	gcc -Wall -g -c $< -o $@

baudrate: baudrate.o apue.o
	gcc -Wall -g $^ -o $@

baudrate.o: baudrate.c ../apue.h
	gcc -Wall -g -c $< -o $@

stop: stop.o apue.o
	gcc -Wall -g $^ -o $@

stop.o: stop.c ../apue.h
	gcc -Wall -g -c $< -o $@

uclc: uclc.o apue.o
	gcc -Wall -g $^ -o $@

uclc.o: uclc.c ../apue.h
	gcc -Wall -g -c $< -o $@

break: break.o apue.o
	gcc -Wall -g $^ -o $@

break.o: break.c ../apue.h
	gcc -Wall -g -c $< -o $@

size: size.o apue.o
	gcc -Wall -g $^ -o $@

size.o: size.c ../apue.h
	gcc -Wall -g -c $< -o $@

cchar: cchar.o apue.o
	gcc -Wall -g $^ -o $@

cchar.o: cchar.c ../apue.h
	gcc -Wall -g -c $< -o $@

term: term.o print_iflag.o print_oflag.o print_cflag.o print_lflag.o print_cchar.o print_speed.o apue.o 
	gcc -Wall -g $^ -o $@

term.o: term.c ../apue.h
	gcc -Wall -g -c $< -o $@

print_iflag.o: print_iflag.c ../apue.h
	gcc -Wall -g -c $< -o $@

# can NOT put print_flag.awk on top, otherwise, Make will create a rule:
# print_flag.awk.c -> print_flag.awk, which will clean our print_flag.awk
# and lead make -B failed due to can not find print_flag.awk
#
#print_iflag.c: print_flag.awk iflag.sym
print_iflag.c: iflag.sym
	./print_flag.awk -v FUNC_NAME=input -v MACRO_FILE=iflag.sym > print_iflag.c

print_oflag.o: print_oflag.c ../apue.h
	gcc -Wall -g -c $< -o $@

print_oflag.c: oflag.sym
	./print_flag.awk -v FUNC_NAME=output -v MACRO_FILE=oflag.sym > print_oflag.c

print_cflag.o: print_cflag.c ../apue.h
	gcc -Wall -g -c $< -o $@

print_cflag.c: cflag.sym
	./print_flag.awk -v FUNC_NAME=control -v MACRO_FILE=cflag.sym > print_cflag.c

print_lflag.o: print_lflag.c ../apue.h
	gcc -Wall -g -c $< -o $@

print_lflag.c: lflag.sym
	./print_flag.awk -v FUNC_NAME=local -v MACRO_FILE=lflag.sym > print_lflag.c

print_cchar.o: print_cchar.c ../apue.h
	gcc -Wall -g -c $< -o $@

print_cchar.c: cchar.sym
	./print_char.awk -v FUNC_NAME=control -v MACRO_FILE=cchar.sym > print_cchar.c

print_speed.o: print_speed.c ../apue.h
	gcc -Wall -g -c $< -o $@

print_speed.c: speed.sym
	./print_speed.awk -v MACRO_FILE=speed.sym > print_speed.c

ttyraw: ttyraw.o tty.o print_lflag.o print_iflag.o print_cflag.o print_oflag.o apue.o
	gcc -Wall -g $^ -o $@

ttyraw.o: ttyraw.c ../tty.h ../apue.h
	gcc -Wall -g -c $< -o $@

ttymode: ttymode.o tty.o print_lflag.o print_iflag.o print_cflag.o print_oflag.o apue.o
	gcc -Wall -g $^ -o $@

ttymode.o: ttymode.c ../tty.h ../apue.h
	gcc -Wall -g -c $< -o $@

tty.o: ../tty.c ../tty.h ../apue.h 
	gcc -Wall -g -c $< -o $@ -DPRINT_FLAG

log.o: ../log.c ../log.h
	gcc -Wall -g -c $< -o $@

apue.o: ../apue.c ../apue.h 
	gcc -Wall -g -c $< -o $@ -D__USE_BSD

clean: 
	@echo "start clean..."
	-rm -f *.o core.* *.log *.swp print_iflag.c print_oflag.c print_cflag.c print_lflag.c print_cchar.c print_speed.c term cchar size break uclc stop baudrate linectl restart isatty ttyname getpass ttymode winsz ttyraw
	@echo "end clean"

.PHONY: clean
