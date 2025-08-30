%{
    #include <iostream>
    #include <string.h>
    #include <iomanip>
    #include <string>

	#define MAX_ARGS 100
    
    void yyerror(const char *s);
    int search_symtab(char *);
    void assign_type(char *str);

    extern int yylex();
    extern int yylineno;
    extern char *yytext;  

    int count_symbol = 0;
    int count_constant_symbol = 0;

    char data_type[64];

    struct symbol_table_struct {
        char identifier_name[10]; 
        char datatype[64];
        char type[32];
        int lineno;
    }; 

    struct const_table_struct {
        char constant_value[64];
        char constant_type[32];
        int lineno;
    };
    
	struct argument_list {
        char *arg[MAX_ARGS];
        int count;
    } arg_list;

    const_table_struct constant_table[128];
    symbol_table_struct symbol_table[128];

    void insert_symbol_table(char c,const char *yytext) {
        if(yytext == NULL) return;

        if(count_symbol >= 128) {
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

    void insert_const_symbol_table(char c,const char *yytext) {
        if(yytext == NULL) return;

        if(count_constant_symbol >= 128) {
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
            case 'S' :
                constant_table[count_const].constant_type = "STRING_CONST";
                break;
            case 'C' :
                constant_table[count_const].constant_type = "CHARACTER_CONST";
        }

        count_constant_symbol++;
    }

    void str_type(char *return_type, char *given_type) {
        if (given_type == "int") {
            return_type = "INT";
        }
        else if (given_type == "bool") {
            return_type = "BOOL";
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
        else if (given_type == "string") {
            return_type = "STRING";
        }
        else if (given_type == "struct") {
            return_type = "STRUCT";
        }
        else if (given_type == "class") {
            return_type = "CLASS";
        }
        else if (given_type == "function") {
            return_type = "FUNCTION";
        }
        else {
            return_type = "UNKNOWN";
        }
    }


    void print_symbol_table() {
        cout << "\nSYMBOL TABLE\n";
        cout << "-----------------------------------------------------------------\n";
        cout << "| " << left << setw(15) << "Identifier"
            << " | " << setw(20) << "Type"
            << " | " << setw(10) << "Data Type"
            << " | Line No |\n";
        cout << "-----------------------------------------------------------------\n";

        for (const auto &sym : symbol_table) {
            cout << "| " << setw(15) << sym.identifier_name
                << " | " << setw(20) << sym.type
                << " | " << setw(10) << sym.datatype
                << " | " << setw(7) << sym.lineno << " |\n";
        }

        cout << "-----------------------------------------------------------------\n";
    }

    void print_constant_table() {
        cout << "\nConstant Symbol Table:\n";
        cout << "-----------------------------------------------------------------\n";
        cout << "| " << left << setw(27) << "Constant Value"
            << " | " << setw(20) << "Constant Type"
            << " | Line no. |\n";
        cout << "-----------------------------------------------------------------\n";

        for (const auto &con : constant_table) {
            cout << "| " << setw(27) << con.constant_value
                << " | " << setw(20) << con.constant_type
                << " | " << setw(8) << con.lineno << " |\n";
        }

        cout << "-----------------------------------------------------------------\n";
    }

%}

%union {
    char *str;
}


%token<str> PLUS MINUS STAR DIVIDE MODULUS ASSIGN INCREMENT DECREMENT
%token<str> EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%token<str> BITWISE_AND BITWISE_OR BITWISE_XOR TILDE LEFT_SHIFT RIGHT_SHIFT
%token<str> LOGICAL_NOT LOGICAL_OR LOGICAL_AND
%token<str> PLUS_EQUAL MINUS_EQUAL STAR_EQUAL DIV_EQUAL MOD_EQUAL
%token<str> AND_EQUAL OR_EQUAL XOR_EQUAL LEFT_SHIFT_EQ RIGHT_SHIFT_EQ
%token<str> LEFT_CURLY RIGHT_CURLY LEFT_SQUARE RIGHT_SQUARE LEFT_ROUND RIGHT_ROUND
%token<str> DOT COMMA COLON SEMICOLON ARROW QUESTION_MARK
%token<str> RETURN SIZEOF IF ELIF ELSE CASE SWITCH DEFAULT
%token<str> FOR WHILE DO UNTIL BREAK CONTINUE GOTO
%token<str> INT BOOL CHAR DOUBLE LONG STRING VOID CONST FUNCTION AUTO
%token<str> STATIC CLASS STRUCT PUBLIC PRIVATE PROTECTED
%token<str> COUT CIN ENDL NEW DELETE
%token<str> NULLPTR TRUE FALSE //INVALID_IDENTIFIER INCLUDE
%token<str> IDENTIFIER DECIMAL_LITERAL EXPONENT_LITERAL DOUBLE_LITERAL STRING_LITERAL CHARACTER_LITERAL

%type<str> translation_unit external_declaration declaration declaration_specifiers
%type<str> storage_specifier type_specifier type_qualifier init_declarator_list init_declarator
%type<str> declarator direct_declarator pointer function_definition parameter_type_list_opt
%type<str> parameter_type_list parameter_list parameter_declaration class_specifier
%type<str> member_specification member_declaration member_declarator_list member_declarator
%type<str> access_specifier_label compound_statement declaration_list statement_list
%type<str> statement labelled_statement expression_statement selection_statement if_rest
%type<str> iteration_statement for_init_statement for_cond_opt for_iter_opt jump_statement
%type<str> expression_opt io_statement insertion_list extraction_list insertion_item
%type<str> extraction_item expression assignment_expression assignment_operator
%type<str> conditional_expression logical_or_expression logical_and_expression inclusive_or_expression
%type<str> exclusive_or_expression and_expression equality_expression relational_expression
%type<str> shift_expression additive_expression multiplicative_expression cast_expression
%type<str> unary_expression unary_operator postfix_expression primary_expression
%type<str> argument_expression_list_opt argument_expression_list constant_expression_opt
%type<str> constant_expression type_name abstract_declarator_opt abstract_declarator
%type<str> direct_abstract_declarator new_expression new_initializer_opt delete_expression
%type<str> lambda_expression initializer initializer_list

%start translation_unit
%%  

translation_unit:
    /* empty */
    | translation_unit external_declaration
    ;

external_declaration:
      declaration
    | function_definition
    | class_specifier
    ;

declaration:
      declaration_specifiers SEMICOLON
    | declaration_specifiers init_declarator_list SEMICOLON
    ;

declaration_specifiers:
      storage_specifier
    | type_specifier
    | type_qualifier
    | declaration_specifiers storage_specifier
    | declaration_specifiers type_specifier
    | declaration_specifiers type_qualifier
    ;

storage_specifier:
      AUTO
    | STATIC
    ;

type_specifier:
      VOID
    | CHAR
    | INT
    | LONG
    | BOOL
    | DOUBLE
    | STRING
    | CLASS IDENTIFIER
    | STRUCT IDENTIFIER
    | IDENTIFIER
    ;

type_qualifier:
      CONST
    ;

init_declarator_list:
      init_declarator
    | init_declarator_list COMMA init_declarator
    ;

init_declarator:
      declarator
    | declarator ASSIGN initializer
    ;

declarator:
      direct_declarator
    | pointer declarator
    ;

direct_declarator:
      IDENTIFIER
    | LEFT_ROUND declarator RIGHT_ROUND
    | direct_declarator LEFT_SQUARE DECIMAL_LITERAL RIGHT_SQUARE
    | direct_declarator LEFT_ROUND parameter_type_list_opt RIGHT_ROUND
    ;

pointer:
      STAR
    | BITWISE_AND
    | STAR pointer
    ;

/* Functions and parameters */
function_definition:
      declaration_specifiers declarator compound_statement
    | declaration_specifiers declarator declaration_list compound_statement
    ;

parameter_type_list_opt:
      /* empty */
    | parameter_type_list
    ;

parameter_type_list:
      parameter_list
    ;

parameter_list:
      parameter_declaration
    | parameter_list COMMA parameter_declaration
    ;

parameter_declaration:
      declaration_specifiers declarator
    | declaration_specifiers
    ;

/* Class / Struct */
class_specifier:
      CLASS IDENTIFIER LEFT_CURLY member_specification RIGHT_CURLY
    | STRUCT IDENTIFIER LEFT_CURLY member_specification RIGHT_CURLY
    ;

member_specification:
      /* empty */
    | member_specification member_declaration
    | member_specification access_specifier_label
    ;

member_declaration:
      declaration_specifiers member_declarator_list SEMICOLON
    | declaration_specifiers SEMICOLON
    ;

member_declarator_list:
      member_declarator
    | member_declarator_list COMMA member_declarator
    ;

member_declarator:
      declarator
    | declarator ASSIGN constant_expression
    ;

access_specifier_label:
      PUBLIC COLON
    | PRIVATE COLON
    | PROTECTED COLON
    ;

/* Statements */
compound_statement:
      LEFT_CURLY RIGHT_CURLY
    | LEFT_CURLY statement_list RIGHT_CURLY
    | LEFT_CURLY declaration_list RIGHT_CURLY
    | LEFT_CURLY declaration_list statement_list RIGHT_CURLY
    ;

declaration_list:
      declaration
    | declaration_list declaration
    ;

statement_list:
      statement
    | statement_list statement
    ;

statement:
      expression_statement
    | compound_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | io_statement
    | labelled_statement
    ;

labelled_statement:
      CASE constant_expression COLON statement
    | DEFAULT COLON statement
    ;

expression_statement:
      SEMICOLON
    | expression SEMICOLON
    ;

selection_statement:
      IF LEFT_ROUND expression RIGHT_ROUND statement if_rest
    | SWITCH LEFT_ROUND expression RIGHT_ROUND statement
    ;

if_rest:
        /* empty */
    | ELIF LEFT_ROUND expression RIGHT_ROUND statement if_rest
    | ELSE statement
    ;

iteration_statement:
      WHILE LEFT_ROUND expression RIGHT_ROUND statement
    | UNTIL LEFT_ROUND expression RIGHT_ROUND statement
    | DO statement WHILE LEFT_ROUND expression RIGHT_ROUND SEMICOLON
    | FOR LEFT_ROUND for_init_statement for_cond_opt for_iter_opt RIGHT_ROUND statement
    ;

for_init_statement:
      SEMICOLON
    | expression_statement
    | declaration
    ;

for_cond_opt:
      /* empty */
    | expression
    ;

for_iter_opt:
      /* empty */
    | expression
    ;

jump_statement:
      GOTO IDENTIFIER SEMICOLON
    | CONTINUE SEMICOLON
    | BREAK SEMICOLON
    | RETURN expression_opt SEMICOLON
    ;

expression_opt:
      /* empty */
    | expression
    ;

/* IO */
io_statement:
      COUT insertion_list SEMICOLON
    | CIN extraction_list SEMICOLON
    ;

insertion_list:
      insertion_item
    | insertion_list LEFT_SHIFT insertion_item
    ;

extraction_list:
      extraction_item
    | extraction_list RIGHT_SHIFT extraction_item
    ;

insertion_item:
      expression
    | ENDL
    | IDENTIFIER
    ;

extraction_item:
      IDENTIFIER
    ;

/* Expressions */
expression:
      assignment_expression
    | expression COMMA assignment_expression
    ;

assignment_expression:
      conditional_expression
    | unary_expression assignment_operator assignment_expression
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

conditional_expression:
      logical_or_expression
    | logical_or_expression QUESTION_MARK expression COLON conditional_expression
    ;

logical_or_expression:
      logical_and_expression
    | logical_or_expression LOGICAL_OR logical_and_expression
    ;

logical_and_expression:
      inclusive_or_expression
    | logical_and_expression LOGICAL_AND inclusive_or_expression
    ;

inclusive_or_expression:
      exclusive_or_expression
    | inclusive_or_expression BITWISE_OR exclusive_or_expression
    ;

exclusive_or_expression:
      and_expression
    | exclusive_or_expression BITWISE_XOR and_expression
    ;

and_expression:
      equality_expression
    | and_expression BITWISE_AND equality_expression
    ;

equality_expression:
      relational_expression
    | equality_expression EQUAL relational_expression
    | equality_expression NOT_EQUAL relational_expression
    ;

relational_expression:
      shift_expression
    | relational_expression LESS_THAN shift_expression
    | relational_expression GREATER_THAN shift_expression
    | relational_expression LESS_EQUAL shift_expression
    | relational_expression GREATER_EQUAL shift_expression
    ;

shift_expression:
      additive_expression
    | shift_expression LEFT_SHIFT additive_expression
    | shift_expression RIGHT_SHIFT additive_expression
    ;

additive_expression:
      multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
    ;

multiplicative_expression:
      cast_expression
    | multiplicative_expression STAR cast_expression
    | multiplicative_expression DIVIDE cast_expression
    | multiplicative_expression MODULUS cast_expression
    ;

cast_expression:
      unary_expression
    | LEFT_ROUND type_name RIGHT_ROUND cast_expression
    ;

unary_expression:
      postfix_expression
    | INCREMENT unary_expression
    | DECREMENT unary_expression
    | unary_operator cast_expression
    | SIZEOF unary_expression
    | SIZEOF LEFT_ROUND type_name RIGHT_ROUND
    ;

unary_operator:
      PLUS
    | MINUS
    | TILDE
    | LOGICAL_NOT
    | BITWISE_AND
    | STAR
    ;

postfix_expression:
      primary_expression
    | postfix_expression LEFT_SQUARE expression RIGHT_SQUARE
    | postfix_expression LEFT_ROUND argument_expression_list_opt RIGHT_ROUND
    | postfix_expression DOT IDENTIFIER
    | postfix_expression ARROW IDENTIFIER
    | postfix_expression INCREMENT
    | postfix_expression DECREMENT
    ;

primary_expression:
      IDENTIFIER
    | DECIMAL_LITERAL
    | CHARACTER_LITERAL
    | STRING_LITERAL
    | EXPONENT_LITERAL
    | DOUBLE_LITERAL
    | NULLPTR
    | TRUE
    | FALSE
    | LEFT_ROUND expression RIGHT_ROUND
    ;

/* Arguments */
argument_expression_list_opt:
      /* empty */
    | argument_expression_list
    ;

argument_expression_list:
      assignment_expression
    | argument_expression_list COMMA assignment_expression
    ;

constant_expression_opt:
      /* empty */
    | constant_expression
    ;

/* Constants */
constant_expression:
      conditional_expression
    ;

/* Type names */
type_name:
      declaration_specifiers abstract_declarator_opt
    ;

abstract_declarator_opt:
      /* empty */
    | abstract_declarator
    ;

abstract_declarator:
	  pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator:
	  LEFT_ROUND abstract_declarator RIGHT_ROUND
	| LEFT_SQUARE constant_expression_opt RIGHT_SQUARE
	| direct_abstract_declarator LEFT_SQUARE constant_expression_opt RIGHT_SQUARE
	| LEFT_ROUND parameter_type_list_opt RIGHT_ROUND
	| direct_abstract_declarator LEFT_ROUND parameter_type_list_opt RIGHT_ROUND
	;


/* New/Delete */
new_expression:
      NEW type_name new_initializer_opt
    ;

new_initializer_opt:
      /* empty */
    | LEFT_ROUND argument_expression_list_opt RIGHT_ROUND
    ;

/* Delete */
delete_expression:
      DELETE cast_expression
    ;

/* Lambda using FUNCTION token */
lambda_expression:
      FUNCTION LEFT_ROUND parameter_type_list_opt RIGHT_ROUND compound_statement
    | FUNCTION LEFT_ROUND parameter_type_list_opt RIGHT_ROUND ARROW type_name compound_statement
    ;

/* Misc */
initializer:
      assignment_expression
    | LEFT_CURLY initializer_list RIGHT_CURLY
    ;

initializer_list:
      initializer
    | initializer_list COMMA initializer
    ;

%%

void yyerror(const char *s) {
    cerr<<"Error at line "<<yylineno<<": "<<s<<endl;
}

int search_symtab(char *id_name) {
	for(int i=count_sym-1; i>=0; i--) {
		if(strcmp(symbol_table[i].identifier_name, id_name)==0) {
			return 1;
			break;
		}
	}
	return 0;
}

void assign_type(char *str) {
	strcpy(d_type, str);
}

int main() {
    yyparse();
    print_symbol_table();
    cout<<endl;
    print_constant_table();
}