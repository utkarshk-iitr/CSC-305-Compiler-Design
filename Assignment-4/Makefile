parser: src/parser.y src/lexer.l
	bison -d -v -Wno-all src/parser.y -o src/parser.tab.c
	flex -o src/lex.yy.c src/lexer.l
	g++ -std=c++17 -w -o src/codegen src/codegen.cpp src/parser.tab.c src/lex.yy.c
	chmod +x run.sh

codegen: parser

tac_optimizer: src/tac_optimizer.cpp
	g++ -std=c++17 -o src/tac_optimizer src/tac_optimizer.cpp

all: parser tac_optimizer

compile:
	cd output && \
	nasm -f elf32 output1.txt -o output1.o && \
	gcc -m32 output1.o -o output1 && \
	./output1

clean:
	rm -f src/parser src/lex.yy.c src/parser.tab.c src/parser.tab.h src/parser.output src/codegen src/tac_optimizer
