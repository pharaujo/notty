cc=gcc

all: notty.c
	gcc -o notty notty.c

clean:
	rm -f notty

install:
	cp notty /usr/local/bin/
