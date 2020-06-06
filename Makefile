CFLAGS=-std=c11 -g -static

kccObj: kcc.c

test: kccObj
	./kcc.sh

clean:
	rm -f kccObj *.o *~ tmp*

.PHONY: test clean
