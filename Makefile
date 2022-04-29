LEXERS = src/lexer.c includes/lexer.h
PARSERS = src/parser.c includes/parser.h includes/lexer.h
TESTER = test/test_parser.c includes/parser.h

viz1:
	@gcc -o code_gen src/codegen_pseudo.c src/parser.c src/lexer.c src/deep_copy.c src/static_checker.c includes/static_checker.h `pkg-config --libs --cflags glib-2.0` && cat test/test1 | ./code_gen

run_test1: test_parser
	@cat test/test1 | ./test_parser > test/test1_out.txt

test_parser: $(TESTER) parser.o lexer.o deep_copy.o src/static_checker.c
	@gcc -o test_parser test/test_parser.c parser.o lexer.o deep_copy.o src/static_checker.c includes/static_checker.h `pkg-config --libs --cflags glib-2.0`;
	@rm *.o
	
lexer.o: $(LEXERS)
	@gcc -c src/lexer.c

deep_copy.o: src/deep_copy.c includes/deep_copy.h includes/parser.h
	@gcc -c src/deep_copy.c

parser.o: $(PARSERS) deep_copy.o includes/deep_copy.h
	@gcc -c src/parser.c

.PHONY: clean

clean:
	rm test_parser test/*.txt nx_test.png
