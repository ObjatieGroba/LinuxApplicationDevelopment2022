GENERATES = prog README
TRASH = *.o *~ o.* *.a *.so *.tmp_output.txt
CFLAGS=-fPIC

all:    README prog prog-a prog-so test

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

prog:   const.o fun.o prog.o

prog-a:   liboutput_static.a prog.o
	cc prog.o -L. -loutput_static -o $@

prog-so:   liboutput.so prog.o
	cc prog.o -L. -loutput -o $@

README: prog
	./$< 2> $@

fun.o:  outlib.h

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

test: test-1 test-2 test-3

test-1: prog prog-a prog-so
	./prog > o1.tmp_output.txt
	./prog-a > o2.tmp_output.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so > o3.tmp_output.txt
	cmp o1.tmp_output.txt o2.tmp_output.txt
	cmp o1.tmp_output.txt o3.tmp_output.txt

test-2: prog prog-a prog-so
	./prog p > o1.tmp_output.txt
	./prog-a p > o2.tmp_output.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so p > o3.tmp_output.txt
	cmp o1.tmp_output.txt o2.tmp_output.txt
	cmp o1.tmp_output.txt o3.tmp_output.txt

test-3: prog prog-a prog-so
	./prog 1 2 3 > o1.tmp_output.txt
	./prog-a 1 2 3 > o2.tmp_output.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 2 3 > o3.tmp_output.txt
	cmp o1.tmp_output.txt o2.tmp_output.txt
	cmp o1.tmp_output.txt o3.tmp_output.txt
