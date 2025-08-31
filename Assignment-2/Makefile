all: parser

parser: parser.y lexer.l
	bison -d -v -Wno-all parser.y
	flex lexer.l
	g++ -w parser.tab.c lex.yy.c -o parser -lfl

clean:
	rm -f parser lex.yy.c parser.tab.c parser.tab.h parser.output
