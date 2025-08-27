lexer: src/lex.yy.c
	g++ src/lex.yy.c -o src/lexer
	chmod +x run.sh

src/lex.yy.c: src/lex.l
	flex -o src/lex.yy.c src/lex.l

clean:
	rm -f src/lex.yy.c src/lexer

