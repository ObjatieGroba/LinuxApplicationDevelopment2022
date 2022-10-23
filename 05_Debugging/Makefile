all:	first second

range:	range.c
	cc range.c -g -O0 -o range

first:	first.gdb range
	gdb -x first.gdb ./range | grep '^@@@' | cut -c 4-

second:	first.gdb range
	gdb -x second.gdb ./range | grep '^@@@' | cut -c 4-

clean:
	rm range
