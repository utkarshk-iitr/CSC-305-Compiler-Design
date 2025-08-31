parser: src/parser.y src/lexer.l
	bison -d -v -w src/parser.y -o src/parser.tab.c
	flex -o src/lex.yy.c src/lexer.l
	g++ -w src/parser.tab.c src/lex.yy.c -o src/parser

clean:
	rm -f src/parser src/lex.yy.c src/parser.tab.c src/parser.tab.h src/parser.output
