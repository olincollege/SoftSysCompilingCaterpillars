lexer.o: lexer.c lexer.h
	gcc -c lexer.c

parser.o: parser.c parser.h lexer.h
	gcc -c parser.c

test_parser: parser.o lexer.o test_parser.c parser.h
	gcc -o test_parser test_parser.c parser.o lexer.o

run_test3:
	cat test3 | ./test_parser

run_test4:
	cat test4 | ./test_parser
