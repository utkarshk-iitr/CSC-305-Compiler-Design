# Define compiler and tools
LEX = flex
BISON = bison
CC = gcc
CFLAGS = -w

# Output executable name
EXEC = parser

# Source files
LEX_FILE = lexer.l
YACC_FILE = parser.y

# Default target
all: $(EXEC)

# Rule to compile the parser and scanner
$(EXEC): $(YACC_FILE) $(LEX_FILE)
	$(BISON) -d -v -Wno-all $(YACC_FILE)
	$(LEX) $(LEX_FILE)
	$(CC) $(CFLAGS) parser.tab.c lex.yy.c -o $(EXEC) -lfl

# Clean build files
clean:
	rm -f $(EXEC) lex.yy.c parser.tab.c parser.tab.h parser.output
