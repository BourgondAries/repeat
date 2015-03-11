primary:
	gcc -O2 -std=c99 -Wall -Wextra main.c -o repeat

install:
	mv repeat /usr/bin/repeat

complete:
	make primary
	make install