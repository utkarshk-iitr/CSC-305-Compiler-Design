%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <vector>

	#define MAX_ARGS 100
    #define DATA_TYPE_LEN 64
    #define ID_LEN 64
    #define TYPE_LEN 32
    #define TABLE_LEN 128

    void yyerror(const char *s);
    int search_symbol_table(char *);
    void assign_type(char *str);
    void insert_symbol_table(char c , const char* text);
    void insert_const_symbol_table(char c , const char* text);
    void print_symbol_table(void);
    void print_constant_symbol_table(void);

    extern int yylex();
    extern int yylineno;
    extern char *yytext;  

    int count_symbol = 0;
    int count_constant_symbol = 0;

    char data_type[DATA_TYPE_LEN];

    struct symbol_table_struct {
        char identifier_name[ID_LEN]; 
        char datatype[DATA_TYPE_LEN];
        char type[TYPE_LEN];
        int lineno;
    }; 

    struct const_table_struct {
        char constant_value[DATA_TYPE_LEN];
        char constant_type[TYPE_LEN];
        int lineno;
    };
    
	struct argument_list {
        char *arg[MAX_ARGS];
        int count;
    } arg_list;

    const_table_struct constant_table[TABLE_LEN];
    symbol_table_struct symbol_table[TABLE_LEN];

    void insert_symbol_table(char c,const char *yytext) {
        if(yytext == NULL) return;

        if(count_symbol >= TABLE_LEN) {
            fprintf(stderr, "Symbol table capacity exceeded at line %d\n", yylineno);
            return;
        }

        if (search_symbol_table(yytext) == 0) {
            symbol_table[count_symbol].identifier_name = yytext;
            symbol_table[count_symbol].lineno = yylineno;

            switch (c) {
                case 'H' :
                    symbol_table[count_symbol].datatype = data_type;
                    symbol_table[count_symbol].type = "HEADER";
                    break;
                case 'K' : 
                    symbol_table[count_symbol].datatype = yytext;
                    symbol_table[count_symbol].type = "KEYWORD";
                    break;
                case 'V' :
                    symbol_table[count_symbol].datatype = data_type;
                    symbol_table[count_symbol].type = "VARIABLE";
                    break;
                case 'C' : 
                    symbol_table[count_symbol].datatype = "CONST";
                    symbol_table[count_symbol].type = "CONSTANT";
                    break;
                case 'F' :
                    symbol_table[count_symbol].datatype = data_type;
                    symbol_table[count_symbol].type = "FUNCTION";
                    break;
                case 'G' :
                    symbol_table[count_symbol].datatype = "GOTO";
                    symbol_table[count_symbol].type = "LABEL";
                    break;
                case 'P' :
                    symbol_table[count_symbol].datatype = data_type;
                    symbol_table[count_symbol].type = "POINTER";
                    break;
                case 'f' :
                    symbol_table[count_symbol].datatype = data_type;
                    symbol_table[count_symbol].type = "POINTER";
                    break;
                case 'E' :
                    symbol_table[count_symbol].datatype = data_type;
                    symbol_table[count_symbol].type = "ENUM";
                }
            }

            count_symbol++;
        }
    }

    void insert_const_symbol_table(char c,const char *yytext) {
        if(yytext == NULL) return;

        if(count_constant_symbol >= TABLE_LEN) {
            fprintf(stderr, "Constant symbol table capacity exceeded at line %d\n", yylineno);
            return;
        }
        
        constant_table[count_const].constant_value = yytext;
        constant_table[count_const].lineno = yylineno;

        switch (c) {
            case 'I' : 
                constant_table[count_const].constant_type = "INTEGER_CONST";
                break;
            case 'F' :
                constant_table[count_const].constant_type = "FLOAT_CONST";
                break;
            case 'E' :
                constant_table[count_const].constant_type = "EXPONENTIAL_CONST";
                break;
            case 'R' :
                constant_table[count_const].constant_type = "REAL_CONST";
                break;
            case 'S' :
                constant_table[count_const].constant_type = "STRING_CONST";
                break;
            case 'C' :
                constant_table[count_const].constant_type = "CHARACTER_CONST";
        }

        count_constant_symbol++;
    }

    
    void string_type(char *return_type, char *given_type) {
        if (given_type == "int") {
            return_type = "INT";
        } 
        else if (given_type == "float") {
            return_type = "FLOAT";
        } 
        else if (given_type == "double") {
            return_type = "DOUBLE";
        }
        else if (given_type == "char") {
            return_type = "CHAR";
        } 
        else if (given_type == "long") {
            return_type = "LONG";
        }
        else if (given_type == "void") {
            return_type = "VOID";	
        }
        else if (given_type == "struct") {
            return_type = "STRUCT";
        }
		    else if (given_type == "unknown") {
            return_type = "UNKNOWN";
        }
        else {
            return_type = "UNKNOWN";
        }
    }

%}
