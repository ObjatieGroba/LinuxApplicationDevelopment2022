set pagination off

b range.c:22
command 1
	echo @@@
    print {m,n,s}
    cont
end

b range.c:23 if i % 5 == 0
command 2
	echo @@@
    print i
    cont
end

r 1 12
q
