lexer.o: lexer.c lexer.h
	gcc -c lexer.c

parser.o: parser.c parser.h lexer.h
	gcc -c parser.c

test_parser: parser.o lexer.o test_parser.c
	gcc -o test_parser test_parser.c

test:
	cat test3 | ./test_parser