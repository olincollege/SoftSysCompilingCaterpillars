LEXERS = src/lexer.c includes/lexer.h
PARSERS = src/parser.c includes/parser.h includes/lexer.h
TESTER = test/test_parser.c includes/parser.h

viz3: run_test3 test/test3_out.txt
	@cat test/test3_out.txt | python3 test/visualizer.py > test/viz3_out.txt && xdg-open nx_test.png

run_test3: test_parser
	@cat test/test3 | ./test_parser > test/test3_out.txt

test_parser: $(TESTER) parser.o lexer.o deep_copy.o
	@gcc -o test_parser test/test_parser.c parser.o lexer.o deep_copy.o;
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
