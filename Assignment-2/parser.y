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

    void print_symbol_table() {
        printf("\nSYMBOL TABLE\n");
        printf("-----------------------------------------------------------------\n");
        printf("| %-15s | %-20s | %-10s | Line No |\n", "Identifier", "Type", "Data Type");
        printf("-----------------------------------------------------------------\n");
        for (int i = 0; i < count_symbol; i++) {
            printf("| %-15s | %-20s | %-10s | %-7d |\n",
                   symbol_table[i].identifier_name,
                   symbol_table[i].type,
                   symbol_table[i].datatype,
                   symbol_table[i].lineno);
        }
        printf("-----------------------------------------------------------------\n");
    }

    void print_constant_table() {
        printf("\nConstant Symbol Table:\n");
        printf("-----------------------------------------------------------------\n");
        printf("| %-27s | %-20s | Line no. |\n", "Constant Value", "Constant Type");
        printf("-----------------------------------------------------------------\n");
        for (int i = 0; i < count_const; i++) {
            printf("| %-27s | %-20s | %-8d |\n",
                   constant_table[i].constant_value,
                   constant_table[i].constant_type, 
                   constant_table[i].lineno);
        }
        printf("-----------------------------------------------------------------\n");
    }

%}

%union {
    char *str;
}

/* Literals & identifiers */
%token <str> ID
%token <str> DECIMAL_LITERAL HEXA_LITERAL OCTAL_LITERAL EXP_LITERAL REAL_LITERAL FLOAT_LITERAL
%token <str> STRING_LITERAL CHARACTER_LITERAL INCLUDE INVALID_ID

/* C/C++ like keywords */
%token AUTO STRUCT BOOL BREAK CASE CONTINUE GOTO DO DEFAULT IF ELSE ELIF FOR CONST TRUE FALSE
%token STATIC SWITCH WHILE VOID RETURN SIZEOF FLOAT INT DOUBLE EXTERN SHORT LONG CHAR ENUM
%token REGISTER SIGNED TYPEDEF UNION UNSIGNED VOLATILE
%token CLASS PUBLIC PRIVATE PROTECTED NULLPTR NAMESPACE VIRTUAL CATCH

/* Punctuation & brackets */
%token RBRACE LBRACE LBRACKET RBRACKET LPARENTHESES RPARENTHESES DOT COMMA COLON SEMICOLON

/* Operators */
%token PLUS MINUS STAR DIVIDE MODULO AMPERSAND OR XOR EXCLAMATION TILDE EQUALS
%token LESS_THAN GREATER_THAN QUESTION_MARK
%token INCREMENT DECREMENT

/* Logical / relational operators */
%token REL_AND REL_OR REL_EQUALS REL_NOT_EQ LESS_EQUALS GREATER_EQUALS

/* Assignment variants */
%token ASSIGN_PLUS ASSIGN_MINUS ASSIGN_STAR ASSIGN_DIV ASSIGN_MOD
%token ASSIGN_AND ASSIGN_OR ASSIGN_XOR

/* Shifts/arrow */
%token LEFT_SHIFT RIGHT_SHIFT LEFT_SHIFT_EQ RIGHT_SHIFT_EQ LAMBDA_ARROW VARIABLE_ARGS

%type <str>
    primary_expression postfix_expression argument_expression_list unary_expression
    unary_operator cast_expression multiplicative_expression additive_expression
    shift_expression relational_expression equality_expression and_expression
    exclusive_or_expression inclusive_or_expression logical_and_expression
    logical_or_expression conditional_expression assignment_expression
    assignment_operator expression constant_expression declaration

%type <str>
    declaration_specifiers init_declarator_list init_declarator
    storage_class_specifier type_specifier struct_or_union_specifier
    struct_or_union struct_declaration_list struct_declaration
    specifier_qualifier_list struct_declarator_list struct_declarator
    enum_specifier enumerator_list enumerator type_qualifier declarator

%type <str>
    direct_declarator pointer type_qualifier_list parameter_type_list
    parameter_list parameter_declaration identifier_list type_name
    abstract_declarator direct_abstract_declarator initializer
    initializer_list statement labeled_statement compound_statement

%type <str>
    declaration_list statement_list expression_statement
    selection_statement iteration_statement jump_statement
    translation_unit external_declaration function_definition


void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int search_symbol_table(const char *id) {
	for(int i=count_symbol-1; i>=0; i--) {
		if(symbol_table[i].identifier_name == id) {
			return 1;
			break;
		}
	}

	return 0;
}

void assign_type(char *str) {
	data_type = str;
}


int main() {
    yyparse();
    print_symbol_table();
    printf("\n");
    print_constant_table();
}
