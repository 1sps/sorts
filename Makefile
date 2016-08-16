# Makefile for sorts

# St: 2016-08-11 Thu 06:57 PM
# Up: 2016-08-15 Mon 11:05 PM

#
# NOTES
# ------
#
# This Makefile is a temporary one, and needs to be updated with a better
# version.



bubble: msortlib.c bubble.c
	gcc -Wall bubble.c msortlib.c -o bubble

sel: msortlib.c selection.c
	gcc -Wall selection.c msortlib.c -o sel

ins: msortlib.c insertion.c
	gcc -Wall insertion.c msortlib.c -o ins

quick: msortlib.c quick.c
	gcc -Wall quick.c msortlib.c -o quick

merge: msortlib.c merge.c
	gcc -Wall merge.c msortlib.c -o merge
clean:
	-rm bubble
	-rm sel
	-rm ins
	-rm quick


# EOF
