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
		echo "$input => $actual OK!"
	else
		echo "$input => $expected expected, but got $actual"
	fi
}

echo "usage : <input stream> => <expected results>"

assert 0 0
assert 42 42
assert 7 "12-8+3"

rm object
rm object.s
rm kccObj
