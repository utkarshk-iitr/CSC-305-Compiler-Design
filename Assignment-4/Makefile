parser: src/parser.y src/lexer.l
	bison -d -v -Wno-all src/parser.y -o src/parser.tab.c
	flex -o src/lex.yy.c src/lexer.l
	g++ -w src/parser.tab.c src/lex.yy.c -o src/parser
	chmod +x run.sh

codegen: src/codegen.cpp
	g++ -std=c++17 -o src/codegen src/codegen.cpp

run:
	./run_codegen.sh

all: parser codegen run

compile:
	cd output/x86 && \
	nasm -f elf32 test1_x86.asm -o test1.o && \
	gcc -m32 test1.o -o test1_x86 && \
	./test1_x86

clean:
	rm -f src/parser src/lex.yy.c src/parser.tab.c src/parser.tab.h src/parser.output src/codegen
