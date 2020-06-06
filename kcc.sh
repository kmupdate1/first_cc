#!/bin/sh

assert() {
	expected="$1"
	input="$2"

	gcc -o kccObj kcc.c
	./kccObj "$input" > object.s
	gcc -o object object.s
	./object
	actual="$?"

	if [ "$actual" = "$expected" ]; then
		echo "$input => $actual"
	else
		echo "$input => $expected expected, but got $actual"
		exit 1
	fi
}

assert 0 0
assert 42 42

echo OK

rm object
rm object.s
rm kccObj
