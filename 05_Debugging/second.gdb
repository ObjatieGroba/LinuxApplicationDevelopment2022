set pagination off

b range.c:22
command 1
	echo @@@
    print {m,n,s}
    cont
end

set $count = 0

b range.c:23 if $count++ >= 27 && $count <= 35
command 2
	echo @@@
    print i
    cont
end

r -100 100 3
q
