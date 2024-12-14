CC=g++
CFLAGS=-Wall -Wextra -g

btree: main.cpp
	${CC} ${CFLAGS} -o btree main.cpp

clean:
	rm btree
