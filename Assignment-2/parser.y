%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

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
            case 'H' :
                constant_table[count_const].constant_type = "HEXADECIMAL_CONST";
                break;
            case 'R' :
                constant_table[count_const].constant_type = "REAL_CONST";
                break;
            case 'S' :
                constant_table[count_const].constant_type = "STRING_CONST";
                break;
            case 'O' :
                constant_table[count_const].constant_type = "OCTAL_CONST";
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
        else if (given_type == "enum") {
            return_type = "ENUM";
        }
        else if (given_type == "union") {
            return_type = "UNION";
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
%token IDENTIFIER DECIMAL_LITERAL EXPONENT_LITERAL DOUBLE_LITERAL STRING_LITERAL CHARACTER_LITERAL

/* Operators */
%token PLUS MINUS STAR DIVIDE MODULUS AND OR XOR 
%token EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%token INCREMENT DECREMENT
%token BITWISE_AND BITWISE_OR BITWISE_XOR TILDE LEFT_SHIFT RIGHT_SHIFT

/* Logical */
%token LOGICAL_AND LOGICAL_NOT LOGICAL_OR

/* Assignment variants */
%token ASSIGN PLUS_EQUAL MINUS_EQUAL STAR_EQUAL DIV_EQUAL MOD_EQUAL
%token AND_EQUAL OR_EQUAL XOR_EQUAL LEFT_SHIFT_EQ RIGHT_SHIFT_EQ

/* Punctuation & brackets */
%token RCURLY LCURLY RSQUARE LSQUARE RROUND LROUND
%token DOT COMMA COLON SEMICOLON ARROW QUESTION_MARK

/* extras */
%token INCLUDE SCOMMENT SIZEOF
%token DELIMITER WHITESPACE

/* keywords */
%token RETURN IF ELIF ELSE CASE SWITCH DEFAULT
%token FOR WHILE DO UNTIL BREAK CONTINUE GOTO
%token INT BOOL CHAR DOUBLE LONG STRING VOID CONST FUNCTION AUTO
%token NULL NULLPTR STATIC CLASS STRUCT TRUE FALSE
%token CLASS STRUCT PUBLIC PRIVATE PROTECTED 
%token COUT CIN ENDL NEW DELETE

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

%start translation_unit
%%

class_specifier
    : struct_or_class IDENTIFIER LEFT_CURLY unified_member_list RIGHT_CURLY
    | struct_or_class LEFT_CURLY unified_member_list RIGHT_CURLY
    | struct_or_class IDENTIFIER
    ;

struct_or_class:
      STRUCT
    | CLASS
    ;

unified_member_list:
      /* empty */
    | unified_member_list unified_member
    ;

unified_member
    : access_specifier COLON                     /* public:, private:, protected: */
    | declaration SEMICOLON                      /* C-style field declaration */
    | specifier_qualifier_list struct_declarator_list SEMICOLON  /* C struct-style */
    | function_definition                        /* method definition */
    ;

access_specifier
    : PUBLIC
    | PRIVATE
    | PROTECTED
    ;

struct_declarator_list
    : struct_declarator
    | struct_declarator_list COMMA struct_declarator
    ;

struct_declarator
    : declarator
    | COLON constant_expression
    | declarator COLON constant_expression
    ;

constant:
        DECIMAL_LITERAL      //{ insert_symtab('L', $1); add_const($1, "INT"); }
    |   EXPONENT_LITERAL     //{ insert_symtab('L', $1); add_const($1, "FLOAT"); }
    |   DOUBLE_LITERAL       //{ insert_symtab('L', $1); add_const($1, "FLOAT"); }
    |   STRING_LITERAL       //{ insert_symtab('L', $1); add_const($1, "STRING"); }
    |   CHARACTER_LITERAL    //{ insert_symtab('L', $1); add_const($1, "CHAR"); }
    ;

primary_expression:
        IDENTIFIER          { $$ = strdup($1); }
    |   constant
    |   STRING_LITERAL     
    |   LEFT_ROUND expression RIGHT_ROUND
    ;

postfix_expression:
        primary_expression
    |   postfix_expression LEFT_SQUARE expression RIGHT_SQUARE
    |   postfix_expression LEFT_ROUND RIGHT_ROUND
    |   postfix_expression LEFT_ROUND argument_expression_list RIGHT_ROUND
    {//printf("Function call= %s\n",$1);
		char type_str[10];
        get_type_string(type_str, "unknown");
 
        assign_type(type_str);
        insert_symtab('F', $1);
		for (int i = 0; i < argList.count_arg; i++) {
            //printf("%s", argList.args[i]);
            if (i < argList.count_arg - 1){} //printf(", ");
        }
        //printf("\n");
	}
    |   postfix_expression DOT IDENTIFIER
    |   postfix_expression ARROW IDENTIFIER
    |   postfix_expression INCREMENT
    |   postfix_expression DECREMENT
    ;

argument_expression_list:
        assignment_expression
        { 
            if (argList.count_arg < MAX_ARGS) {
                argList.args[argList.count_arg++] = strdup($1);
            }
        }
    |   argument_expression_list COMMA assignment_expression
        { 
            if (argList.count_arg < MAX_ARGS) {
                argList.args[argList.count_arg++] = strdup($3);
            }
        }
    ;

unary_expression:
        postfix_expression
    |   INCREMENT unary_expression
    |   DECREMENT unary_expression
    |   unary_operator cast_expression
    |   SIZEOF unary_expression
    |   SIZEOF LEFT_ROUND type_name RIGHT_ROUND
    |   new_expression
    |   delete_expression
    ;

unary_operator:
      STAR
    | PLUS
    | BITWISE_AND
    | MINUS
    | TILDE
    | LOGICAL_NOT
    ;

cast_expression:
        unary_expression
    |   LEFT_ROUND type_name RIGHT_ROUND cast_expression
    ;

multiplicative_expression:
        cast_expression
    |   multiplicative_expression STAR cast_expression
    |   multiplicative_expression DIVIDE cast_expression
    |   multiplicative_expression MODULUS cast_expression
    ;

additive_expression:
        multiplicative_expression
    |   additive_expression PLUS multiplicative_expression
    |   additive_expression MINUS multiplicative_expression
    ;

shift_expression:
        additive_expression
    |   shift_expression LEFT_SHIFT additive_expression
    |   shift_expression RIGHT_SHIFT additive_expression
    ;

relational_expression:
        shift_expression
    |   relational_expression LESS_THAN shift_expression
    |   relational_expression GREATER_THAN shift_expression
    |   relational_expression LESS_EQUAL shift_expression
    |   relational_expression GREATER_EQUAL shift_expression
    ;

equality_expression:
        relational_expression
    |   equality_expression EQUAL relational_expression
    |   equality_expression NOT_EQUAL relational_expression
    ;

and_expression:
        equality_expression
    |   and_expression BITWISE_AND equality_expression
    ;

exclusive_or_expression:
        and_expression
    |   exclusive_or_expression BITWISE_XOR and_expression
    ;

inclusive_or_expression:
        exclusive_or_expression
    |   inclusive_or_expression BITWISE_OR exclusive_or_expression
    ;

logical_and_expression:
        inclusive_or_expression
    |   logical_and_expression LOGICAL_AND inclusive_or_expression
    ;

logical_or_expression:
        logical_and_expression
    |   logical_or_expression LOGICAL_OR logical_and_expression
    ;

conditional_expression:
        logical_or_expression
    |   logical_or_expression QUESTION_MARK expression COLON conditional_expression
    ;

assignment_expression:
        conditional_expression
    |   unary_expression assignment_operator assignment_expression
    ;

assignment_operator:
      ASSIGN
    | PLUS_EQUAL
    | MINUS_EQUAL
    | STAR_EQUAL
    | DIV_EQUAL
    | MOD_EQUAL
    | AND_EQUAL
    | OR_EQUAL
    | XOR_EQUAL
    | LEFT_SHIFT_EQ
    | RIGHT_SHIFT_EQ
    ;

expression:
        assignment_expression
    |   expression COMMA assignment_expression
    ;

constant_expression:
        conditional_expression
    ;

declaration:
        declaration_specifiers SEMICOLON
    |   declaration_specifiers init_declarator_list SEMICOLON
    {
        //printf("declaration  = %s\n", $2);
        char type_str[10];
        get_type_string(type_str, $1);

        char *token = strtok($2, ",");
        while (token != NULL) {
            char *var_name = token;
            char *value = strchr(token, '=');

            if (value) {
                *value = '\0';  
                value++;  
            }

            assign_type(type_str);

            int pointer_level = 0;
            while (*var_name == '*') {
                pointer_level++;
                var_name++;  
            }
			assign_type(type_str);
            if (pointer_level > 0) {
                insert_symtab('P',var_name);
            } else {
                insert_symtab('V',var_name);
            }

            token = strtok(NULL, ",");
        }
    }
    ;

storage:
      AUTO
    | STATIC
    ;

type_specifier:
      VOID
    | CHAR
    | INT
    | LONG
    | DOUBLE
    | BOOL
    | STRING
    | CONST
    | STRUCT
    | FUNCTION
    | CLASS
    ;

declaration_specifiers:
        storage
    |   storage declaration_specifiers
    |   type_specifier
    |   type_specifier declaration_specifiers
    |   CONST
    |   CONST declaration_specifiers
    ;


init_declarator_list:
        init_declarator
    { 
        $$ = strdup($1);  
        //printf("init_declarator = %s\n", $$);
    }
    |   init_declarator_list COMMA init_declarator
    { 
        $$ = malloc(strlen($1) + strlen($3) + 2); 
        sprintf($$, "%s,%s", $1, $3);  
        free($1); free($3);
        //printf("init_declarator_list = %s\n", $$);
    }
    ;

init_declarator:
        declarator
    { 
        $$ = strdup($1); 
        //printf("declarator = %s\n", $$);
    }
    |   declarator ASSIGN initializer
    { 
        $$ = malloc(strlen($1) + strlen($3) + 2);  
        sprintf($$, "%s=%s", $1, $3);  
        free($1); free($3);
        //printf("init_declarator with initializer = %s\n", $$);
    }
    ;

initializer:
        assignment_expression
    |   LEFT_CURLY initializer_list RIGHT_CURLY
    |   LEFT_CURLY initializer_list COMMA RIGHT_CURLY
    ;

initializer_list:
        initializer
    |   initializer_list COMMA initializer
    ;

declaration_list:
        declaration
    |   declaration_list declaration
    |   error SEMICOLON {yyerrok;}
    ;

translation_unit:
        external_declaration
    |   translation_unit external_declaration
    ;

external_declaration:
        function_definition
    |   declaration
    ;

function_definition:
        declaration_specifiers declarator declaration_list compound_statement
    |   declaration_specifiers declarator compound_statement
    {   //printf("Function is there: %s %s\n",$1,$2);
		char type_str[10];
      	get_type_string(type_str,$1);
      	assign_type(type_str);
      	insert_symtab('F',$2);
	}
    |   declarator declaration_list compound_statement
	|   declarator compound_statement
    ;

declarator: 
        pointer direct_declarator
    { 
		//printf("Pointer direct declarator\n");
        $$ = malloc(strlen($1) + strlen($2) + 1); 
        sprintf($$, "%s%s", $1, $2); 
		//printf("it is $$: %s\n",$$); 
        free($1); free($2);
    }
    |   direct_declarator
    { 
        $$ = strdup($1);  
		//printf("Direct declarator %s\n",$$);
    }
    ;

parameter_list:
        parameter_declaration
    |   parameter_list COMMA parameter_declaration
    ;

parameter_declaration:
        declaration_specifiers declarator
    {
		// char type_str[10];
        // get_type_string(type_str, $1);
        // printf("Variable declaration: %s = %s\n", $1, $2); 
        // assign_type(type_str);
        // insert_symtab('V', $2);
		char type_str[10];
        get_type_string(type_str, $1);

        char *token = strtok($2, ",");
        while (token != NULL) {
            char *var_name = token;
            char *value = strchr(token, '=');

            if (value) {
                *value = '\0';  
                value++;  
            }

            assign_type(type_str);

            int pointer_level = 0;
            while (*var_name == '*') {
                pointer_level++;
                var_name++;  
            }
			assign_type(type_str);
            if (pointer_level > 0) {
                insert_symtab('f',var_name);
            } else {
                insert_symtab('V',var_name);
            }

            token = strtok(NULL, ",");
        } 
	}
    |   declaration_specifiers
    |   declaration_specifiers abstract_declarator
    ;

type_name: 
        specifier_qualifier_list
	|   specifier_qualifier_list abstract_declarator
	;

pointer:
        STAR    { $$ = strdup("*"); }
    |   STAR pointer
    { 
        $$ = malloc(strlen($2) + 2); 
        sprintf($$, "*%s", $2);  
        free($2);
    }
    |   STAR type_qualifier_list
    |   STAR type_qualifier_list pointer
    ;

specifier_qualifier_list: 
        type_specifier specifier_qualifier_list
	|   type_specifier
	|   CONST specifier_qualifier_list
	|   CONST
	;

type_qualifier_list: 
        CONST
	|   type_qualifier_list CONST
	;

compound_statement:
        LEFT_CURLY RIGHT_CURLY
    |   LEFT_CURLY declaration_list statement_list RIGHT_CURLY
    |   LEFT_CURLY statement_declaration_list RIGHT_CURLY
    |   LEFT_CURLY statement_list RIGHT_CURLY
	|   LEFT_CURLY declaration_list RIGHT_CURLY
    ;

statement_list:
        statement
    |   statement_list statement
    |   error SEMICOLON {yyerrok;}
    ;

statement:
        compound_statement
    |   labeled_statement
    |   io_statement
    |   expression_statement
    |   selection_statement
    |   iteration_statement
    |   jump_statement
    ;

io_statement: 
        output_statement SEMICOLON
    |   input_statement SEMICOLON
    ;

output_statement: 
        COUT output_chain
    ;

output_chain: 
        LEFT_SHIFT output_item
    |   output_chain LEFT_SHIFT output_item
    ;

output_item: 
        expression
    |   ENDL
    ;

input_statement:
        CIN input_chain
    ;

input_chain:
        RIGHT_SHIFT IDENTIFIER
    |   input_chain RIGHT_SHIFT IDENTIFIER
    ;

labeled_statement:
        IDENTIFIER COLON statement
    |   CASE constant_expression COLON statement
    |   DEFAULT COLON statement
    ;

expression_statement:
        SEMICOLON
    |   expression SEMICOLON
    ;

selection_statement:
        IF LEFT_ROUND expression RIGHT_ROUND statement if_rest
    |   SWITCH LEFT_ROUND expression RIGHT_ROUND statement
    ;

if_rest:
        /* empty */                                                                                  /* if without else */
    |   ELSE statement
    |   ELIF LEFT_ROUND expression RIGHT_ROUND statement if_rest                                   /* elif followed by more elif/else */
    ;

iteration_statement:
        WHILE LEFT_ROUND expression RIGHT_ROUND statement
    |   UNTIL LEFT_ROUND expression RIGHT_ROUND statement
    |   DO statement WHILE LEFT_ROUND expression RIGHT_ROUND SEMICOLON
    |   FOR LEFT_ROUND expression_statement expression_statement RIGHT_ROUND statement
    |   FOR LEFT_ROUND declaration expression_statement RIGHT_ROUND statement
    ;

jump_statement:
        GOTO IDENTIFIER SEMICOLON
    { 
      	insert_symtab('G',$2);
	}
    |   CONTINUE SEMICOLON
    |   BREAK SEMICOLON
    |   RETURN expression SEMICOLON
    |   RETURN SEMICOLON
    ;

new_expression:
        NEW type_name
    |   NEW type_name LEFT_ROUND argument_expression_list RIGHT_ROUND
    ;

delete_expression:
        DELETE unary_expression
    |   DELETE LEFT_SQUARE RIGHT_SQUARE unary_expression
    ;

statement_declaration_list: 
        statement_list statement_declaration_list
	|   declaration_list statement_declaration_list
	|   statement_list
	|   declaration_list
	;

direct_declarator: 
        IDENTIFIER
	|   LEFT_ROUND declarator RIGHT_ROUND
    { 
		$$ = strdup($2);
	}
	|   direct_declarator LEFT_CURLY constant_expression RIGHT_CURLY
	|   direct_declarator LEFT_CURLY 
	|   direct_declarator LEFT_ROUND parameter_list RIGHT_ROUND
	|   direct_declarator LEFT_ROUND identifier_list RIGHT_ROUND
	|   direct_declarator LEFT_ROUND RIGHT_ROUND
	;

identifier_list:
        IDENTIFIER
	|   identifier_list COMMA IDENTIFIER
	;


abstract_declarator: 
        pointer
	|   direct_abstract_declarator
	|   pointer direct_abstract_declarator
	;

direct_abstract_declarator:
	    LEFT_ROUND abstract_declarator RIGHT_ROUND
	|   LEFT_SQUARE RIGHT_SQUARE
	|   LEFT_SQUARE constant_expression RIGHT_SQUARE
	|   direct_abstract_declarator LEFT_SQUARE RIGHT_SQUARE
	|   direct_abstract_declarator LEFT_SQUARE constant_expression RIGHT_SQUARE
	|   LEFT_ROUND RIGHT_ROUND
	|   LEFT_ROUND parameter_list RIGHT_ROUND
	|   direct_abstract_declarator LEFT_ROUND RIGHT_ROUND
	|   direct_abstract_declarator LEFT_ROUND parameter_list RIGHT_ROUND
	;

%%


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
