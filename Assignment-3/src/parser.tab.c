/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 8 "src/parser.y"

    #include <bits/stdc++.h>
    #include <fstream>
    #include <string>
    #include <cstring>
    #include <vector>
    #include <unordered_map>
    #include <map>
    #include <cstdlib>
    using namespace std;

    struct Node {
        vector<string> code;
        vector<string> syn;
        string place;
        string type;
        string kind;
        int argCount = 0;
        Node() : place(""), type("") , kind("") {}
        Node(string p, string t, string k) : place(p), type(t), kind(k) {}
    };

    struct Symbol {
        string name;
        string type;
        string kind;
        bool isFunction = false;
        int paramCount = 0;
        vector<string> dim;
        bool isDeclared = true;
        Symbol() : name(""), type(""), kind(""), isFunction(false), paramCount(0), isDeclared(true) {}
        Symbol(string n, string t, string k,vector<string> s, bool f=false, int p=0) : name(n), type(t), kind(k),dim(s), isFunction(f), paramCount(p) {}
    };

    struct funcInfo {
        string place;
        string kind;
        string returnType;
        bool hasReturn = false;
        vector<string> paramTypes;
        int paramCount = 0;
        funcInfo() : returnType("void"), hasReturn(false) {}
    };

    struct memberInfo {
        string place;
        int offset;
        string type;
        string kind;
    };

    unordered_map<string, funcInfo> funcTable;
    unordered_map<string, unordered_map<string,memberInfo>> classTable;
    vector< unordered_map<string, Symbol> > symStack;

    unordered_map<string,int> typeSize = {
        {"int", 4}, {"char", 1}, {"bool", 1}, {"double", 8}, {"string", 8}, {"nullptr", 8}
    };
    
    vector<string> errors;
    static string currentFunction = "global";
    static int globalTemp = 0, globalLabel = 0;
    static int localTemp = 0, localLabel = 0;
    static int classOffset = 0;
    static string lastDeclType = "int";
    static string lastClassType = "";
    static string lastUsage = "rvalue";

    Node* finalRoot = nullptr;

    string newTemp() {
        if (currentFunction == "global") {
            return "global.t" + to_string(++globalTemp);
        } else {
            return currentFunction + ".t" + to_string(++localTemp);
        }
    }
    string newLabel() {
        if (currentFunction == "global") {
            return "global.L" + to_string(++globalLabel);
        } else {
            return currentFunction + ".L" + to_string(++localLabel);
        }
    }

    ofstream dbgfile("debug.txt");
    void dbg(const string &msg) {
        dbgfile << "Debug: " << msg << endl;
    }

    extern bool is_type_name(char const* s) {
        return typeSize.find(s) != typeSize.end();
    }

    void pushScope() {
        symStack.emplace_back();
    }
    void popScope() {
        if (!symStack.empty()) 
            symStack.pop_back();
    }

    Symbol* lookupSymbol(const string &name) {
        for (int i = (int)symStack.size()-1; i >= 0; --i) {
            auto &m = symStack[i];
            auto it = m.find(name);
            if (it != m.end()) return &it->second;
        }
        return nullptr;
    }

    funcInfo* lookupFunction(const string &name) {
        auto it = funcTable.find(name);
        if (it != funcTable.end()) return &(it->second);
        return nullptr;
    }   
    
    bool declareSymbol(const string &name, const string &type, const string k="",vector<string> syn=vector<string>(),bool isFunc=false, int params=0) {
        if (symStack.empty()) pushScope();
        auto &cur = symStack.back();
        if (cur.find(name) != cur.end()) {
            return false;
        }
        Symbol s; 
        s.name = name; s.type = type; s.kind = k; 
        s.dim = syn;
        s.isFunction = isFunc;
        s.paramCount = params;
        s.isDeclared = true;
        cur[name] = s;
        return true;
    }

    extern int yylineno;
    void yyerror(string s) {
        errors.push_back(string("Error at line ") + to_string(yylineno) + " : " + s);
    }

    void check_access(Symbol* sym) {
        if(sym==nullptr) return;
        if(sym->kind.find("private") != string::npos){
            yyerror("Can't access private member '" + sym->name + "'.");
        }
        else if(sym->kind.find("protected") != string::npos){
            yyerror("Can't access protected member '" + sym->name + "'.");
        }
    }

    void check_func_access(funcInfo* sym) {
        if(sym==nullptr) return;
        if(sym->kind.find("private") != string::npos){
            yyerror("Can't access private member function '" + sym->place + "'.");
        }
        else if(sym->kind.find("protected") != string::npos){
            yyerror("Can't access protected member function '" + sym->place + "'.");
        }
    }

    bool check_compatibility(const string &t1, const string &t2, const string &baseop) {
        if(baseop==""){
            return t1==t2;
        }
        
        if(baseop=="*" || baseop=="/"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            if(t1=="double" && t2=="double") return true;
            return false;
        }

        if(baseop=="%" || baseop=="<<" || baseop==">>"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            return false;
        }

        if(baseop=="&" || baseop=="^" || baseop=="|"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            if(t1=="bool" && t2=="bool") return true;
            return false;
        }

        if(baseop=="+"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            if(t1=="double" && t2=="double") return true;
            if(t1=="string" && t2=="string") return true;
            if(t1.back()=='*' && t2=="int") return true;
            return false;
        }

        if(baseop=="-"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            if(t1=="double" && t2=="double") return true;
            if(t1.back()=='*' && t2=="int") return true;
            return false;
        }
        return false;
    }

    bool check_unary_comp(const string &t, const string &op) {
        if(op=="&") return true;
        if(op=="*"){
            if(t.back()=='*') return true;
            return false;
        }
        if(op=="+" || op=="-"){
            if(t=="int" || t=="long" || t=="double") return true;
            return false;
        }
        if(op=="~"){
            if(t=="int" || t=="long") return true;
            return false;
        }
        if(op=="!"){
            if(t=="bool") return true;
            return false;
        }
        if(op=="++" || op=="--"){
            if(t=="int" || t=="long" || t=="double") return true;
            return false;
        }
        return true;
    }

    bool check_casting(const string &from, const string &to, const string &s="") {
        if(from==to) return true;
        if(from=="int"){
            if(to=="double" || to=="char" || to=="bool" || to=="string" || to=="long") return true;
            return false;
        } 
        if(from=="double"){
            if(to=="int" || to=="char" || to=="bool" || to=="string" || to=="long") return true;
            return false;
        }
        if(from=="long"){
            if(to=="int" || to=="char" || to=="bool" || to=="string" || to=="double") return true;
            return false;
        }
        if(from=="char"){
            if(to=="int" || to=="bool" || to=="string" || to=="double" || to=="long") return true;
            return false;
        }   
        if(from=="bool"){
            if(to=="int" || to=="char" || to=="string" || to=="double" || to=="long") return true;
            return false;
        }
        if(from=="string"){
            if(to=="int"){
                try {
                    size_t pos;
                    stoi(s, &pos);
                    return pos == s.size();
                } 
                catch (...) {
                    return false;
                }
            }
            if(to=="double"){
                try {
                    size_t pos;
                    stod(s, &pos);
                    return pos == s.size();
                } 
                catch (...) {
                    return false;
                }
            }
            if(to=="long"){
                try {
                    size_t pos;
                    stol(s, &pos);
                    return pos == s.size();
                } 
                catch (...) {
                    return false;
                }
            }
            if(to=="char") return false;
            if(to=="bool") return true;
            return false;
        }
        
        if(from.back()=='*' && to.back()=='*') return true;
        return false;
    }

    extern int yylex();
    extern int yyparse();


#line 365 "src/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INCLUDE = 3,                    /* INCLUDE  */
  YYSYMBOL_TYPEDEF = 4,                    /* TYPEDEF  */
  YYSYMBOL_TYPE_NAME = 5,                  /* TYPE_NAME  */
  YYSYMBOL_PLUS = 6,                       /* PLUS  */
  YYSYMBOL_MINUS = 7,                      /* MINUS  */
  YYSYMBOL_STAR = 8,                       /* STAR  */
  YYSYMBOL_DIVIDE = 9,                     /* DIVIDE  */
  YYSYMBOL_MODULUS = 10,                   /* MODULUS  */
  YYSYMBOL_ASSIGN = 11,                    /* ASSIGN  */
  YYSYMBOL_INCREMENT = 12,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 13,                 /* DECREMENT  */
  YYSYMBOL_EQUAL = 14,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 15,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 16,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 17,              /* GREATER_THAN  */
  YYSYMBOL_LESS_EQUAL = 18,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 19,             /* GREATER_EQUAL  */
  YYSYMBOL_BITWISE_AND = 20,               /* BITWISE_AND  */
  YYSYMBOL_BITWISE_OR = 21,                /* BITWISE_OR  */
  YYSYMBOL_BITWISE_XOR = 22,               /* BITWISE_XOR  */
  YYSYMBOL_LEFT_SHIFT = 23,                /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 24,               /* RIGHT_SHIFT  */
  YYSYMBOL_ARROW = 25,                     /* ARROW  */
  YYSYMBOL_LOGICAL_NOT = 26,               /* LOGICAL_NOT  */
  YYSYMBOL_LOGICAL_AND = 27,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 28,                /* LOGICAL_OR  */
  YYSYMBOL_PLUS_EQUAL = 29,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 30,               /* MINUS_EQUAL  */
  YYSYMBOL_STAR_EQUAL = 31,                /* STAR_EQUAL  */
  YYSYMBOL_DIV_EQUAL = 32,                 /* DIV_EQUAL  */
  YYSYMBOL_MOD_EQUAL = 33,                 /* MOD_EQUAL  */
  YYSYMBOL_AND_EQUAL = 34,                 /* AND_EQUAL  */
  YYSYMBOL_OR_EQUAL = 35,                  /* OR_EQUAL  */
  YYSYMBOL_XOR_EQUAL = 36,                 /* XOR_EQUAL  */
  YYSYMBOL_LEFT_SHIFT_EQ = 37,             /* LEFT_SHIFT_EQ  */
  YYSYMBOL_RIGHT_SHIFT_EQ = 38,            /* RIGHT_SHIFT_EQ  */
  YYSYMBOL_LROUND = 39,                    /* LROUND  */
  YYSYMBOL_RROUND = 40,                    /* RROUND  */
  YYSYMBOL_LCURLY = 41,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 42,                    /* RCURLY  */
  YYSYMBOL_LSQUARE = 43,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 44,                   /* RSQUARE  */
  YYSYMBOL_SEMICOLON = 45,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 46,                     /* COLON  */
  YYSYMBOL_COMMA = 47,                     /* COMMA  */
  YYSYMBOL_DOT = 48,                       /* DOT  */
  YYSYMBOL_QUESTION_MARK = 49,             /* QUESTION_MARK  */
  YYSYMBOL_TILDE = 50,                     /* TILDE  */
  YYSYMBOL_FUNCTION = 51,                  /* FUNCTION  */
  YYSYMBOL_IF = 52,                        /* IF  */
  YYSYMBOL_ELSE = 53,                      /* ELSE  */
  YYSYMBOL_SWITCH = 54,                    /* SWITCH  */
  YYSYMBOL_CASE = 55,                      /* CASE  */
  YYSYMBOL_DEFAULT = 56,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 57,                     /* WHILE  */
  YYSYMBOL_DO = 58,                        /* DO  */
  YYSYMBOL_FOR = 59,                       /* FOR  */
  YYSYMBOL_GOTO = 60,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 61,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 62,                     /* BREAK  */
  YYSYMBOL_RETURN = 63,                    /* RETURN  */
  YYSYMBOL_UNTIL = 64,                     /* UNTIL  */
  YYSYMBOL_SIZEOF = 65,                    /* SIZEOF  */
  YYSYMBOL_VOID = 66,                      /* VOID  */
  YYSYMBOL_INT = 67,                       /* INT  */
  YYSYMBOL_DOUBLE = 68,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 69,                      /* CHAR  */
  YYSYMBOL_BOOL = 70,                      /* BOOL  */
  YYSYMBOL_LONG = 71,                      /* LONG  */
  YYSYMBOL_TRUE = 72,                      /* TRUE  */
  YYSYMBOL_FALSE = 73,                     /* FALSE  */
  YYSYMBOL_NULLPTR = 74,                   /* NULLPTR  */
  YYSYMBOL_AUTO = 75,                      /* AUTO  */
  YYSYMBOL_STATIC = 76,                    /* STATIC  */
  YYSYMBOL_CONST = 77,                     /* CONST  */
  YYSYMBOL_CLASS = 78,                     /* CLASS  */
  YYSYMBOL_STRUCT = 79,                    /* STRUCT  */
  YYSYMBOL_PUBLIC = 80,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 81,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 82,                 /* PROTECTED  */
  YYSYMBOL_DELETE = 83,                    /* DELETE  */
  YYSYMBOL_NEW = 84,                       /* NEW  */
  YYSYMBOL_CIN = 85,                       /* CIN  */
  YYSYMBOL_COUT = 86,                      /* COUT  */
  YYSYMBOL_ENDL = 87,                      /* ENDL  */
  YYSYMBOL_IDENTIFIER = 88,                /* IDENTIFIER  */
  YYSYMBOL_INVALID_IDENTIFIER = 89,        /* INVALID_IDENTIFIER  */
  YYSYMBOL_DECIMAL_LITERAL = 90,           /* DECIMAL_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 91,            /* DOUBLE_LITERAL  */
  YYSYMBOL_EXPONENT_LITERAL = 92,          /* EXPONENT_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 93,         /* CHARACTER_LITERAL  */
  YYSYMBOL_LOWER_THAN_ELSE = 94,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_primary_expression = 96,        /* primary_expression  */
  YYSYMBOL_constant = 97,                  /* constant  */
  YYSYMBOL_postfix_expression = 98,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 99,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 100,         /* unary_expression  */
  YYSYMBOL_unary_operator = 101,           /* unary_operator  */
  YYSYMBOL_new_expression = 102,           /* new_expression  */
  YYSYMBOL_new_square = 103,               /* new_square  */
  YYSYMBOL_delete_expression = 104,        /* delete_expression  */
  YYSYMBOL_cast_expression = 105,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 106, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 107,      /* additive_expression  */
  YYSYMBOL_shift_expression = 108,         /* shift_expression  */
  YYSYMBOL_relational_expression = 109,    /* relational_expression  */
  YYSYMBOL_equality_expression = 110,      /* equality_expression  */
  YYSYMBOL_and_expression = 111,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 112,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 113,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 114,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 115,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 116,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 117,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 118,      /* assignment_operator  */
  YYSYMBOL_expression = 119,               /* expression  */
  YYSYMBOL_constant_expression = 120,      /* constant_expression  */
  YYSYMBOL_declaration = 121,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 122,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 123,     /* init_declarator_list  */
  YYSYMBOL_pointer_opt = 124,              /* pointer_opt  */
  YYSYMBOL_pointer_list = 125,             /* pointer_list  */
  YYSYMBOL_init_declarator = 126,          /* init_declarator  */
  YYSYMBOL_initializer = 127,              /* initializer  */
  YYSYMBOL_initializer_list = 128,         /* initializer_list  */
  YYSYMBOL_square_list = 129,              /* square_list  */
  YYSYMBOL_static_opt = 130,               /* static_opt  */
  YYSYMBOL_type_specifier = 131,           /* type_specifier  */
  YYSYMBOL_struct_or_class_specifier = 132, /* struct_or_class_specifier  */
  YYSYMBOL_133_1 = 133,                    /* $@1  */
  YYSYMBOL_struct_or_class = 134,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 135, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 136,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 137,   /* access_specifier_label  */
  YYSYMBOL_member_declaration = 138,       /* member_declaration  */
  YYSYMBOL_139_2 = 139,                    /* $@2  */
  YYSYMBOL_struct_declarator_list = 140,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 141,        /* struct_declarator  */
  YYSYMBOL_const_opt = 142,                /* const_opt  */
  YYSYMBOL_parameter_list = 143,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 144,    /* parameter_declaration  */
  YYSYMBOL_statement = 145,                /* statement  */
  YYSYMBOL_io_statement = 146,             /* io_statement  */
  YYSYMBOL_cout_expression = 147,          /* cout_expression  */
  YYSYMBOL_insertion_list = 148,           /* insertion_list  */
  YYSYMBOL_cin_expression = 149,           /* cin_expression  */
  YYSYMBOL_extraction_list = 150,          /* extraction_list  */
  YYSYMBOL_labeled_statement = 151,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 152,       /* compound_statement  */
  YYSYMBOL_153_3 = 153,                    /* $@3  */
  YYSYMBOL_statement_list = 154,           /* statement_list  */
  YYSYMBOL_block_item = 155,               /* block_item  */
  YYSYMBOL_expression_statement = 156,     /* expression_statement  */
  YYSYMBOL_selection_statement = 157,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 158,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 159,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 160,           /* jump_statement  */
  YYSYMBOL_translation_unit = 161,         /* translation_unit  */
  YYSYMBOL_external_declaration = 162,     /* external_declaration  */
  YYSYMBOL_function_header = 163,          /* function_header  */
  YYSYMBOL_function_definition = 164,      /* function_definition  */
  YYSYMBOL_return_type = 165               /* return_type  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1068

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  192
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  327

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   349


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   381,   381,   413,   418,   430,   440,   455,   461,   467,
     473,   479,   488,   493,   551,   577,   629,   657,   698,   717,
     739,   757,   778,   781,   796,   811,   846,   857,   867,   870,
     877,   880,   883,   886,   889,   892,   899,   912,   926,   935,
     950,   957,   968,   971,   988,   991,  1004,  1018,  1036,  1039,
    1053,  1071,  1074,  1088,  1106,  1109,  1121,  1133,  1145,  1161,
    1164,  1177,  1194,  1197,  1214,  1217,  1234,  1237,  1254,  1257,
    1274,  1277,  1293,  1298,  1320,  1323,  1351,  1354,  1357,  1360,
    1363,  1366,  1369,  1372,  1375,  1378,  1381,  1388,  1393,  1406,
    1415,  1424,  1433,  1438,  1449,  1455,  1463,  1468,  1477,  1521,
    1585,  1633,  1685,  1739,  1879,  1888,  1895,  1913,  1927,  1945,
    1948,  1955,  1958,  1961,  1964,  1967,  1970,  1976,  1984,  1983,
    2003,  2009,  2020,  2024,  2034,  2040,  2048,  2055,  2062,  2072,
    2072,  2077,  2092,  2097,  2107,  2116,  2119,  2126,  2130,  2141,
    2153,  2156,  2159,  2162,  2165,  2168,  2171,  2178,  2181,  2188,
    2195,  2203,  2209,  2215,  2225,  2232,  2240,  2252,  2266,  2271,
    2271,  2281,  2284,  2294,  2297,  2300,  2304,  2307,  2313,  2328,
    2359,  2372,  2383,  2394,  2410,  2430,  2433,  2440,  2446,  2452,
    2458,  2464,  2476,  2479,  2491,  2494,  2497,  2500,  2509,  2535,
    2583,  2592,  2597
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INCLUDE", "TYPEDEF",
  "TYPE_NAME", "PLUS", "MINUS", "STAR", "DIVIDE", "MODULUS", "ASSIGN",
  "INCREMENT", "DECREMENT", "EQUAL", "NOT_EQUAL", "LESS_THAN",
  "GREATER_THAN", "LESS_EQUAL", "GREATER_EQUAL", "BITWISE_AND",
  "BITWISE_OR", "BITWISE_XOR", "LEFT_SHIFT", "RIGHT_SHIFT", "ARROW",
  "LOGICAL_NOT", "LOGICAL_AND", "LOGICAL_OR", "PLUS_EQUAL", "MINUS_EQUAL",
  "STAR_EQUAL", "DIV_EQUAL", "MOD_EQUAL", "AND_EQUAL", "OR_EQUAL",
  "XOR_EQUAL", "LEFT_SHIFT_EQ", "RIGHT_SHIFT_EQ", "LROUND", "RROUND",
  "LCURLY", "RCURLY", "LSQUARE", "RSQUARE", "SEMICOLON", "COLON", "COMMA",
  "DOT", "QUESTION_MARK", "TILDE", "FUNCTION", "IF", "ELSE", "SWITCH",
  "CASE", "DEFAULT", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK",
  "RETURN", "UNTIL", "SIZEOF", "VOID", "INT", "DOUBLE", "CHAR", "BOOL",
  "LONG", "TRUE", "FALSE", "NULLPTR", "AUTO", "STATIC", "CONST", "CLASS",
  "STRUCT", "PUBLIC", "PRIVATE", "PROTECTED", "DELETE", "NEW", "CIN",
  "COUT", "ENDL", "IDENTIFIER", "INVALID_IDENTIFIER", "DECIMAL_LITERAL",
  "DOUBLE_LITERAL", "EXPONENT_LITERAL", "CHARACTER_LITERAL",
  "LOWER_THAN_ELSE", "$accept", "primary_expression", "constant",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "new_expression", "new_square", "delete_expression",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "pointer_opt",
  "pointer_list", "init_declarator", "initializer", "initializer_list",
  "square_list", "static_opt", "type_specifier",
  "struct_or_class_specifier", "$@1", "struct_or_class",
  "struct_or_class_member_list", "struct_or_class_member",
  "access_specifier_label", "member_declaration", "$@2",
  "struct_declarator_list", "struct_declarator", "const_opt",
  "parameter_list", "parameter_declaration", "statement", "io_statement",
  "cout_expression", "insertion_list", "cin_expression", "extraction_list",
  "labeled_statement", "compound_statement", "$@3", "statement_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "for_init_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_header",
  "function_definition", "return_type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-185)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-111)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     950,   -18,   207,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,    -1,   -31,    92,    46,    14,   131,
    -185,    71,  -185,    34,  -185,    36,  -185,     6,   -17,     1,
    -185,  -185,   207,  -185,   106,  -185,    89,  -185,  -185,    97,
    -185,   102,    99,   920,   920,     7,  -185,    -1,  -185,   135,
    -185,  -185,  -185,   334,    83,  -185,  -185,  -185,  -185,   975,
     975,  -185,  -185,   423,  -185,   109,  -185,  -185,  -185,   597,
     207,  -185,  -185,  -185,  -185,  -185,  -185,  -185,     0,   332,
     920,  -185,  -185,  -185,    68,   104,    96,    77,   123,   140,
     164,   170,   165,   -14,  -185,  -185,  -185,  -185,   150,   154,
     920,  -185,   920,  -185,   151,  -185,   166,   175,   528,   176,
     115,   159,   172,   647,   179,   196,   198,   178,  -185,    -5,
    -185,  -185,  -185,   180,   181,  -185,  -185,   241,  -185,  -185,
    -185,  -185,  -185,  -185,   -25,  -185,   139,   920,  -185,  -185,
     -24,   189,   459,   186,  -185,   190,  -185,  -185,   144,   702,
     920,   146,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,   920,  -185,   920,   920,   920,   920,   920,
     920,   920,   920,   920,   920,   920,   920,   920,   920,   920,
     920,   920,   920,   920,  -185,   920,  -185,   191,  -185,   371,
    -185,   920,   920,   182,    25,   205,  -185,  -185,  -185,    24,
     920,   920,   212,   738,   220,  -185,  -185,   920,  -185,  -185,
    -185,  -185,  -185,   207,  -185,  -185,   920,   211,   215,   920,
     920,   209,  -185,  -185,   -20,  -185,     9,  -185,  -185,  -185,
    -185,  -185,    68,    68,   104,   104,    96,    96,    96,    96,
      77,    77,   123,   140,   164,   170,   165,   110,  -185,   -21,
    -185,  -185,   213,   214,   216,  -185,  -185,  -185,   207,    71,
     -11,    -6,   218,  -185,  -185,   793,  -185,  -185,    18,  -185,
     920,  -185,  -185,   829,  -185,  -185,  -185,  -185,  -185,  -185,
      10,   920,  -185,   920,  -185,   920,  -185,   920,  -185,  -185,
    -185,  -185,  -185,   528,   528,   920,   884,   528,  -185,  -185,
    -185,  -185,    38,  -185,  -185,  -185,    -1,   210,  -185,    26,
     528,    27,  -185,  -185,  -185,    39,  -185,   528,   219,  -185,
     528,  -185,    -1,  -185,  -185,  -185,  -185
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   117,   111,   113,   115,   112,   116,   114,
     109,   121,   120,   186,     0,   136,    95,     0,     0,     0,
     182,     0,   184,     0,   191,     0,    97,    98,     0,     0,
      92,   135,     0,   192,    94,   185,     0,     1,   183,   159,
     190,     0,     0,     0,     0,    99,    90,     0,    96,   100,
      91,   118,   158,     0,     0,   187,    32,    33,    31,     0,
       0,    30,    35,     0,    34,     0,    10,    11,     9,     0,
       0,     2,     5,     8,     7,     6,    12,     3,    22,    42,
       0,    29,    28,    44,    48,    51,    54,    59,    62,    64,
      66,    68,    70,    72,    74,   101,    42,    89,     0,     0,
       0,    93,     0,   122,     0,   166,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,    87,     0,
     164,   163,   146,     0,     0,   140,   141,     0,   161,   142,
     143,   144,   145,   188,     0,   137,     0,     0,    23,    24,
       0,     0,     0,     0,    41,    37,    18,    19,     0,     0,
       0,     0,    76,    80,    81,    77,    78,    79,    84,    86,
      85,    82,    83,     0,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   108,     0,   103,     0,   102,     0,
     165,     0,     0,     0,   110,     0,   178,   179,   180,     0,
       0,     0,   154,     0,   149,   157,   167,     0,   147,   148,
     160,   162,   189,     0,   139,     4,     0,     0,     0,     0,
       0,    36,    17,    14,     0,    20,     0,    16,    75,    45,
      46,    47,    49,    50,    52,    53,    56,    55,    57,    58,
      60,    61,    63,    65,    67,    69,    71,     0,   105,     0,
     107,   119,     0,     0,     0,   123,   124,   125,     0,     0,
       0,     0,     0,   176,   175,     0,   177,   181,     0,   155,
       0,   151,   150,     0,    88,   138,    43,    26,    27,    40,
       0,     0,    15,     0,    13,     0,   104,     0,   126,   127,
     128,   129,   131,     0,     0,     0,     0,     0,   156,   152,
     153,    38,     0,    21,    73,   106,     0,   168,   170,     0,
       0,     0,   171,    39,   134,     0,   132,     0,     0,   173,
       0,   130,     0,   169,   172,   174,   133
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -185,  -185,  -185,  -185,  -185,     3,  -185,  -185,  -185,  -185,
     -61,    19,    -7,   -46,   -10,    80,    86,    88,    85,    87,
    -185,   -41,   -42,  -185,   -58,   171,   -47,  -185,  -185,  -185,
     254,    -3,  -185,  -185,  -185,  -185,   240,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,   -43,    95,  -185,    72,
    -104,  -185,  -185,  -185,  -185,  -185,  -185,   -19,  -185,  -185,
     160,  -184,  -185,  -185,  -185,  -185,  -185,   262,   100,  -185,
      -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    76,    77,    78,   224,    79,    80,    81,   221,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,   118,   163,   119,    98,    13,    14,    28,    33,
      29,   314,   186,   249,    45,    15,    16,    17,   103,    18,
     189,   255,   256,   257,   306,   315,   316,    32,   134,   135,
     121,   122,   123,   204,   124,   202,   125,   126,    53,   127,
     128,   129,   130,   131,   265,   132,    19,    20,    21,    22,
      23
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,    95,    40,    97,   193,   140,   120,    26,   144,    48,
     264,    30,   146,   147,   182,   212,   215,    43,    99,   164,
     282,   286,   213,   207,    24,   148,   287,   283,    46,   293,
      47,    56,    57,    58,   294,   183,   207,    59,    60,   149,
     206,   207,   207,   150,   101,    61,    31,    96,   151,    44,
     100,    62,   136,   284,   301,   199,   207,   207,   297,    97,
     188,   141,   138,   139,    63,   207,   318,   320,   145,   267,
     105,   207,    96,   207,   207,    64,   165,   166,   167,   140,
     120,   296,   313,    96,   321,   207,   322,    27,     3,    49,
      65,    35,   226,   172,   173,   174,   175,    66,    67,    68,
      26,    10,    36,    96,   229,   230,   231,   225,    69,    70,
     168,   169,    39,    71,    48,    72,    73,    74,    75,   170,
     171,   228,    41,   133,    42,   247,   236,   237,   238,   239,
      51,    37,     1,   260,   261,     2,     3,   176,   177,    52,
     218,    54,   268,   248,    55,   217,   102,   263,   142,     4,
       5,     6,     7,     8,     9,   276,   285,   207,   279,   269,
     178,   272,   280,   234,   235,   274,   240,   241,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,   179,   232,   233,   307,
     308,   180,   181,   312,   184,   185,   190,     4,     5,     6,
       7,     8,     9,   195,   196,   191,   319,    10,  -110,    11,
      12,   136,     3,   323,   192,   194,   325,   197,   200,    96,
     201,   203,    96,   302,   205,   208,   209,   214,   298,   216,
     219,   300,   222,   220,   227,   250,   270,   309,   311,   262,
     292,   303,   104,   273,   304,   305,  -110,    56,    57,    58,
     266,   277,   281,    59,    60,   278,   291,   295,   242,   288,
     289,    61,   290,   317,   324,   243,   245,    62,   244,   246,
      34,   187,    50,     4,     5,     6,     7,     8,     9,   326,
      63,    38,    39,   210,   258,   275,   105,   211,    96,   259,
       0,    64,     0,   106,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,   113,   114,    65,  -110,  -110,  -110,
    -110,  -110,  -110,    66,    67,    68,     0,    10,  -110,     0,
       0,     0,     0,     0,    69,    70,   115,   116,     0,   117,
       0,    72,    73,    74,    75,   104,     0,     0,     0,  -110,
      56,    57,    58,   152,     0,     0,    59,    60,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,     0,
      62,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,     0,     0,    63,     0,    39,     3,     0,     0,   105,
       0,     0,     0,     0,    64,     0,   106,     0,     0,     0,
       0,   107,   108,   109,   110,   111,   112,   113,   114,    65,
    -110,  -110,  -110,  -110,  -110,  -110,    66,    67,    68,     0,
      10,  -110,     0,   251,     0,     0,     0,    69,    70,   115,
     116,     0,   117,     0,    72,    73,    74,    75,     3,    56,
      57,    58,     0,     0,     0,    59,    60,     4,     5,     6,
       7,     8,     9,    61,     0,     0,     0,     0,    31,    62,
       0,   252,   253,   254,     0,     0,     0,     0,     0,     0,
       0,     0,    63,     0,     3,    56,    57,    58,     0,     0,
       0,    59,    60,    64,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,     0,     0,    65,     4,
       5,     6,     7,     8,     9,    66,    67,    68,   137,     0,
       0,     0,     0,     0,     0,     0,    69,    70,     0,    64,
       0,    71,     0,    72,    73,    74,    75,     0,     0,     0,
       0,     0,     0,     0,    65,     4,     5,     6,     7,     8,
       9,    66,    67,    68,    56,    57,    58,     0,     0,     0,
      59,    60,    69,    70,     0,     0,     0,    71,    61,    72,
      73,    74,    75,     0,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,     0,    39,
       0,     0,     0,   105,     0,     0,     0,     0,    64,     0,
     106,     0,     0,     0,     0,   107,   108,   109,   110,   111,
     112,   113,   114,    65,     0,     0,     0,     0,     0,     0,
      66,    67,    68,    56,    57,    58,     0,     0,     0,    59,
      60,    69,    70,   115,   116,     0,   117,    61,    72,    73,
      74,    75,     0,    62,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
     143,     0,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,    56,    57,    58,     0,     0,     0,    59,
      60,     0,    65,     0,     0,     0,     0,    61,     0,    66,
      67,    68,     0,    62,     0,     0,     0,     0,     0,     0,
      69,    70,     0,     0,     0,    71,    63,    72,    73,    74,
      75,     0,   198,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    57,
      58,     0,    65,     0,    59,    60,     0,     0,     0,    66,
      67,    68,    61,     0,     0,     0,     0,     0,    62,     0,
      69,    70,     0,     0,     0,    71,     0,    72,    73,    74,
      75,    63,   223,     0,    56,    57,    58,     0,     0,     0,
      59,    60,    64,     0,     0,     0,     0,     0,    61,     0,
       0,     0,     0,     0,    62,     0,     0,    65,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    63,     0,     0,
       0,     0,     0,     0,     0,    69,    70,     0,    64,     0,
      71,     0,    72,    73,    74,    75,     0,     0,     0,    56,
      57,    58,     0,    65,     0,    59,    60,     0,     0,     0,
      66,    67,    68,    61,     0,     0,     0,     0,     0,    62,
       0,    69,    70,     0,     0,   271,    71,     0,    72,    73,
      74,    75,    63,     0,     0,    56,    57,    58,   105,     0,
       0,    59,    60,    64,     0,     0,     0,     0,     0,    61,
       0,     0,     0,     0,     0,    62,     0,     0,    65,     0,
       0,     0,     0,     0,     0,    66,    67,    68,    63,     0,
       0,     0,     0,     0,     0,     0,    69,    70,     0,    64,
       0,    71,     0,    72,    73,    74,    75,     0,     0,     0,
      56,    57,    58,     0,    65,     0,    59,    60,     0,     0,
       0,    66,    67,    68,    61,     0,     0,     0,     0,     0,
      62,     0,    69,    70,     0,     0,   299,    71,     0,    72,
      73,    74,    75,    63,   310,     0,    56,    57,    58,     0,
       0,     0,    59,    60,    64,     0,     0,     0,     0,     0,
      61,     0,     0,     0,     0,     0,    62,     0,     0,    65,
       0,     1,     0,     0,     2,     3,    66,    67,    68,    63,
       0,     0,     0,     0,     0,     0,     0,    69,    70,     0,
      64,     0,    71,     0,    72,    73,    74,    75,     0,     0,
       0,    56,    57,    58,     0,    65,     0,    59,    60,     0,
       0,     0,    66,    67,    68,    61,     0,     0,     0,     0,
       0,    62,     0,    69,    70,     0,     0,     0,    71,     0,
      72,    73,    74,    75,   137,     0,     4,     5,     6,     7,
       8,     9,     0,     0,     0,    64,    10,  -110,    11,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,     0,     0,     0,     0,     0,     0,    66,    67,    68,
       0,     0,     0,     0,     0,     0,     0,     0,    69,    70,
       0,     0,     0,    71,     0,    72,    73,    74,    75
};

static const yytype_int16 yycheck[] =
{
       2,    43,    21,    44,   108,    63,    53,     8,    69,     8,
     194,    14,    12,    13,    28,    40,    40,    11,    11,    80,
      40,    42,    47,    47,    42,    25,    47,    47,    45,    40,
      47,     6,     7,     8,    40,    49,    47,    12,    13,    39,
      45,    47,    47,    43,    47,    20,    77,    44,    48,    43,
      43,    26,    54,    44,    44,   113,    47,    47,    40,   100,
     102,    63,    59,    60,    39,    47,    40,    40,    70,    45,
      45,    47,    69,    47,    47,    50,     8,     9,    10,   137,
     127,   265,    44,    80,    45,    47,    47,    88,     5,    88,
      65,    45,   150,    16,    17,    18,    19,    72,    73,    74,
       8,    76,    88,   100,   165,   166,   167,   149,    83,    84,
       6,     7,    41,    88,     8,    90,    91,    92,    93,    23,
      24,   163,    88,    40,    88,   183,   172,   173,   174,   175,
      41,     0,     1,   191,   192,     4,     5,    14,    15,    42,
     142,    39,   200,   185,    45,   142,    11,   194,    39,    66,
      67,    68,    69,    70,    71,   216,    46,    47,   219,   201,
      20,   203,   220,   170,   171,   207,   176,   177,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,    22,   168,   169,   293,
     294,    21,    27,   297,    44,    41,    45,    66,    67,    68,
      69,    70,    71,    88,    45,    39,   310,    76,    77,    78,
      79,   213,     5,   317,    39,    39,   320,    45,    39,   216,
      24,    23,   219,   281,    46,    45,    45,    88,   270,    40,
      44,   273,    88,    43,    88,    44,    24,   295,   296,    57,
     259,   283,     1,    23,   285,   287,     5,     6,     7,     8,
      45,    40,    43,    12,    13,    40,   258,    39,   178,    46,
      46,    20,    46,    53,    45,   179,   181,    26,   180,   182,
      16,   100,    32,    66,    67,    68,    69,    70,    71,   322,
      39,    19,    41,    42,   189,   213,    45,   127,   285,   189,
      -1,    50,    -1,    52,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    76,    77,    -1,
      -1,    -1,    -1,    -1,    83,    84,    85,    86,    -1,    88,
      -1,    90,    91,    92,    93,     1,    -1,    -1,    -1,     5,
       6,     7,     8,    11,    -1,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    39,    -1,    41,     5,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    50,    -1,    52,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      76,    77,    -1,    42,    -1,    -1,    -1,    83,    84,    85,
      86,    -1,    88,    -1,    90,    91,    92,    93,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    66,    67,    68,
      69,    70,    71,    20,    -1,    -1,    -1,    -1,    77,    26,
      -1,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    50,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    50,
      -1,    88,    -1,    90,    91,    92,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    83,    84,    -1,    -1,    -1,    88,    20,    90,
      91,    92,    93,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    83,    84,    85,    86,    -1,    88,    20,    90,    91,
      92,    93,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    -1,    65,    -1,    -1,    -1,    -1,    20,    -1,    72,
      73,    74,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    84,    -1,    -1,    -1,    88,    39,    90,    91,    92,
      93,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    -1,    65,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    39,    40,    -1,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    50,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    50,    -1,
      88,    -1,    90,    91,    92,    93,    -1,    -1,    -1,     6,
       7,     8,    -1,    65,    -1,    12,    13,    -1,    -1,    -1,
      72,    73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    83,    84,    -1,    -1,    87,    88,    -1,    90,    91,
      92,    93,    39,    -1,    -1,     6,     7,     8,    45,    -1,
      -1,    12,    13,    50,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    50,
      -1,    88,    -1,    90,    91,    92,    93,    -1,    -1,    -1,
       6,     7,     8,    -1,    65,    -1,    12,    13,    -1,    -1,
      -1,    72,    73,    74,    20,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    83,    84,    -1,    -1,    87,    88,    -1,    90,
      91,    92,    93,    39,    40,    -1,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    50,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    65,
      -1,     1,    -1,    -1,     4,     5,    72,    73,    74,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,
      50,    -1,    88,    -1,    90,    91,    92,    93,    -1,    -1,
      -1,     6,     7,     8,    -1,    65,    -1,    12,    13,    -1,
      -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    83,    84,    -1,    -1,    -1,    88,    -1,
      90,    91,    92,    93,    39,    -1,    66,    67,    68,    69,
      70,    71,    -1,    -1,    -1,    50,    76,    77,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     5,    66,    67,    68,    69,    70,    71,
      76,    78,    79,   121,   122,   130,   131,   132,   134,   161,
     162,   163,   164,   165,    42,   165,     8,    88,   123,   125,
     126,    77,   142,   124,   125,    45,    88,     0,   162,    41,
     152,    88,    88,    11,    43,   129,    45,    47,     8,    88,
     131,    41,    42,   153,    39,    45,     6,     7,     8,    12,
      13,    20,    26,    39,    50,    65,    72,    73,    74,    83,
      84,    88,    90,    91,    92,    93,    96,    97,    98,   100,
     101,   102,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   100,   116,   120,    11,
      43,   126,    11,   133,     1,    45,    52,    57,    58,    59,
      60,    61,    62,    63,    64,    85,    86,    88,   117,   119,
     121,   145,   146,   147,   149,   151,   152,   154,   155,   156,
     157,   158,   160,    40,   143,   144,   165,    39,   100,   100,
     119,   165,    39,    43,   105,   165,    12,    13,    25,    39,
      43,    48,    11,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   118,   105,     8,     9,    10,     6,     7,
      23,    24,    16,    17,    18,    19,    14,    15,    20,    22,
      21,    27,    28,    49,    44,    41,   127,   120,   117,   135,
      45,    39,    39,   145,    39,    88,    45,    45,    45,   119,
      39,    24,   150,    23,   148,    46,    45,    47,    45,    45,
      42,   155,    40,    47,    88,    40,    40,   100,   165,    44,
      43,   103,    88,    40,    99,   117,   119,    88,   117,   105,
     105,   105,   106,   106,   107,   107,   108,   108,   108,   108,
     109,   109,   110,   111,   112,   113,   114,   119,   117,   128,
      44,    42,    80,    81,    82,   136,   137,   138,   142,   163,
     119,   119,    57,   121,   156,   159,    45,    45,   119,   117,
      24,    87,   117,    23,   117,   144,   105,    40,    40,   105,
     119,    43,    40,    47,    44,    46,    42,    47,    46,    46,
      46,   165,   152,    40,    40,    39,   156,    40,   117,    87,
     117,    44,   119,   117,   116,   117,   139,   145,   145,   119,
      40,   119,   145,    44,   126,   140,   141,    53,    40,   145,
      40,    45,    47,   145,    45,   145,   141
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    96,    97,    97,    97,    97,    97,
      97,    97,    98,    98,    98,    98,    98,    98,    98,    98,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     101,   101,   101,   101,   101,   101,   102,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   106,   106,   107,   107,
     107,   108,   108,   108,   109,   109,   109,   109,   109,   110,
     110,   110,   111,   111,   112,   112,   113,   113,   114,   114,
     115,   115,   116,   116,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   119,   119,   120,
     121,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     126,   126,   126,   126,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   131,   131,   131,   131,   131,   133,   132,
     134,   134,   135,   135,   136,   136,   137,   137,   137,   139,
     138,   138,   140,   140,   141,   142,   142,   143,   143,   144,
     145,   145,   145,   145,   145,   145,   145,   146,   146,   147,
     148,   148,   148,   148,   149,   150,   150,   151,   152,   153,
     152,   154,   154,   155,   155,   155,   156,   156,   157,   157,
     158,   158,   158,   158,   158,   159,   159,   160,   160,   160,
     160,   160,   161,   161,   162,   162,   162,   162,   163,   163,
     164,   164,   165
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     3,     4,     3,     3,     2,     2,
       1,     3,     1,     2,     2,     2,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     3,     4,
       4,     2,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     1,     3,     1,     0,     2,     1,     1,     2,
       2,     3,     4,     4,     3,     1,     3,     4,     3,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       1,     1,     0,     2,     1,     1,     2,     2,     2,     0,
       5,     2,     1,     3,     1,     1,     0,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     3,     3,     2,     2,     3,     2,     2,     0,
       4,     1,     2,     1,     1,     2,     1,     2,     5,     7,
       5,     5,     7,     6,     7,     1,     1,     3,     2,     2,
       2,     3,     1,     2,     1,     2,     1,     4,     4,     5,
       2,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* primary_expression: IDENTIFIER  */
#line 382 "src/parser.y"
    {
        dbg("primary_expression -> IDENTIFIER");
        Node* n = new Node();
        string name = string((yyvsp[0].str));
        n->place = name;
        Symbol* sym = lookupSymbol(name);
        dbg("");
        dbg("Looking up symbol: " + name);
        dbg("");
        if (!sym) {
            dbg("Symbol not found: " + name);
            yyerror("Use of undeclared identifier '" + name + "'.");
            n = nullptr;
        } 
        else{
            check_access(sym);
            dbg("");
            dbg("Found symbol: " + name);
            dbg("Type: " + sym->type);
            dbg("Kind: " + sym->kind);
            dbg("Dimensions: " + to_string(sym->dim.size()));
            for (const auto& d : sym->dim) {
                dbg(" - " + d);
            }
            dbg("");
            n->kind = sym->kind;
            n->type = sym->type;
            n->syn = sym->dim;
        }
        (yyval.node) = n;
    }
#line 1958 "src/parser.tab.c"
    break;

  case 3: /* primary_expression: constant  */
#line 414 "src/parser.y"
    { 
        dbg("primary_expression -> constant");
        (yyval.node) = (yyvsp[0].node);
    }
#line 1967 "src/parser.tab.c"
    break;

  case 4: /* primary_expression: LROUND expression RROUND  */
#line 419 "src/parser.y"
    {
        dbg("primary_expression -> ( expression )");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1976 "src/parser.tab.c"
    break;

  case 5: /* constant: DECIMAL_LITERAL  */
#line 431 "src/parser.y"
    {
        dbg("constant -> DECIMAL_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "int", "const");
        n->argCount = stoi(string((yyvsp[0].str)));
        dbg("");
        dbg("Integer constant value: " + to_string(n->argCount));
        dbg("");
        (yyval.node) = n;
    }
#line 1990 "src/parser.tab.c"
    break;

  case 6: /* constant: CHARACTER_LITERAL  */
#line 441 "src/parser.y"
    {
        dbg("constant -> CHARACTER_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "char", "const");
        dbg("");
        dbg("Character constant value: " + string(1, (yyvsp[0].str)[1]));
        dbg("");
        (yyval.node) = n;
    }
#line 2003 "src/parser.tab.c"
    break;

  case 7: /* constant: EXPONENT_LITERAL  */
#line 456 "src/parser.y"
    {
        dbg("constant -> EXPONENT_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "double", "const");
        (yyval.node) = n;
    }
#line 2013 "src/parser.tab.c"
    break;

  case 8: /* constant: DOUBLE_LITERAL  */
#line 462 "src/parser.y"
    {
        dbg("constant -> DOUBLE_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "double", "const");
        (yyval.node) = n;
    }
#line 2023 "src/parser.tab.c"
    break;

  case 9: /* constant: NULLPTR  */
#line 468 "src/parser.y"
    {
        dbg("constant -> NULLPTR");
        Node* n = new Node("0", "nullptr", "const");
        (yyval.node) = n;
    }
#line 2033 "src/parser.tab.c"
    break;

  case 10: /* constant: TRUE  */
#line 474 "src/parser.y"
    {
        dbg("constant -> TRUE");
        Node* n = new Node("1", "bool", "const");
        (yyval.node) = n;
    }
#line 2043 "src/parser.tab.c"
    break;

  case 11: /* constant: FALSE  */
#line 480 "src/parser.y"
    {
        dbg("constant -> FALSE");
        Node* n = new Node("0", "bool", "const");
        (yyval.node) = n;
    }
#line 2053 "src/parser.tab.c"
    break;

  case 12: /* postfix_expression: primary_expression  */
#line 489 "src/parser.y"
    { 
        dbg("postfix_expression -> primary_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 2062 "src/parser.tab.c"
    break;

  case 13: /* postfix_expression: postfix_expression LSQUARE expression RSQUARE  */
#line 494 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression [ expression ]");
        Node* base = (yyvsp[-3].node); 
        Node* idx = (yyvsp[-1].node);
        Node* n = new Node();

        if(!base || !idx) {
            yyerror("Invalid array subscript operation.");
        }
        else{

        if(base->type.back()!='*'){
            yyerror("Subscripted value is not an array or pointer.");
        }
        if(idx->type!="int"){
            yyerror("Index is not an integer.");
        }
        if(base->kind.find("const")!=string::npos){
            yyerror("Cannot modify a const value.");
        }
        if(base->syn.empty()){
            yyerror("Too many dimensions for array.");
        }
        n->code = base->code;
        n->code.insert(n->code.end(), idx->code.begin(), idx->code.end());

        int p=1;
        dbg("");
        dbg("Array dimensions: ");
        dbg(to_string(base->syn.size()));

        for(auto x:base->syn)
        { 
            dbg("Dimension size: " + x);
            p = p * stoi(x);
        }
        dbg("");
        
        p /= stoi(base->syn.front());
        string offset = newTemp();
        
        string type = base->type.substr(0,base->type.size()-base->syn.size());
        
        n->code.push_back(offset + " = " + idx->place + " * " + to_string(p));
        n->code.push_back(offset + " = " + offset +" * "+to_string(typeSize[type]));
        n->place = newTemp();
        n->code.push_back(n->place + " = " + base->place + " + " + offset);
        n->type = base->type.substr(0,base->type.size()-1);
        n->kind = base->kind;
        n->syn = vector<string>(base->syn.begin()+1, base->syn.end());
        
        if(n->syn.empty()){
            n->place = "*" + n->place;
        }
        }
        (yyval.node) = n;
    }
#line 2124 "src/parser.tab.c"
    break;

  case 14: /* postfix_expression: postfix_expression LROUND RROUND  */
#line 552 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression ( )");
        Node* fun = (yyvsp[-2].node);
        funcInfo* s = lookupFunction(fun->place);
        check_func_access(s);
        if(!s){
            yyerror("Call to non-function '" + fun->place + "'.");
        }
        if(s->paramCount != 0){
            yyerror("Call to function '" + fun->place + "' with incorrect number of arguments.");
        }

        Node* n = new Node();
        n->code = fun->code;
        n->type = s->returnType;

        if(fun->type=="void"){
            n->code.push_back("call " + fun->place + ", 0;");
        }
        else{
            n->place = newTemp();
            n->code.push_back(n->place + " = call " + fun->place + ", 0;");
        }
        (yyval.node) = n;
    }
#line 2154 "src/parser.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression LROUND argument_expression_list RROUND  */
#line 578 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression ( argument_expression_list )");
        Node* fun = (yyvsp[-3].node);
        string name = fun->place;
        string original = fun->place;
        Node* args = (yyvsp[-1].node);

        dbg("");
        dbg("argCount is:" + to_string(args->argCount));
        for(int i = 0; i < args->argCount;i++)
        {
            dbg("type is " + args->syn[i]);
            name += "_" + args->syn[i];
            
        }
        dbg("name is: " + name);

        funcInfo* s = lookupFunction(name);
        if(s)
            dbg("YES");
        dbg("");
        check_func_access(s);
        Node* n = new Node();
        if(!s){
            yyerror("Function '" + original + "' with given argument types not found.");
        }
        else if (s->paramCount != args->argCount) {
            yyerror("Call to function '" + original + "' with incorrect number of arguments.");
        }
        if(s)
        {
            for(int i=0; i<args->argCount; i++){
                if(s->paramTypes[i]!=args->syn[i]){
                    yyerror("Type mismatch in argument " + to_string(i+1) + " of function '" + original + "'.");
                }
            }
            n->code = fun->code;
            n->type = s->returnType;
            n->code.insert(n->code.end(), args->code.begin(), args->code.end());
            
            if(s->returnType=="void") {
                n->type = "";
                n->code.push_back("call " + original + ", " + to_string(args->argCount));
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = call " + original + ", " + to_string(args->argCount));
            }
        }
        (yyval.node) = n;
    }
#line 2210 "src/parser.tab.c"
    break;

  case 16: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 629 "src/parser.y"
                                            {
        dbg("postfix_expression -> postfix_expression . IDENTIFIER");
            Node* obj = (yyvsp[-2].node);
            if(obj->type!="struct" && obj->type!="class"){
                yyerror("Dot operator can only be applied to struct or class.");
            }
            string nm = obj->place + "." + string((yyvsp[0].str));
            Symbol* s = lookupSymbol(nm);
            funcInfo* f = lookupFunction(nm);

            Node* n = new Node();
            if(s){
                check_access(s);
                n->type = s->type;
                n->kind = s->kind;
            }
            else if(f){
                check_func_access(f);
                n->type = f->returnType;
            }
            else{
                yyerror("No member or function named '" + nm+"'.");
            }
            n->code = obj->code;
            n->place = newTemp();
            n->code.push_back(n->place + " = " + nm);
            (yyval.node) = n;
      }
#line 2243 "src/parser.tab.c"
    break;

  case 17: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 657 "src/parser.y"
                                              {
        dbg("postfix_expression -> postfix_expression ARROW IDENTIFIER");
          Node* obj = (yyvsp[-2].node);
          if(obj->type.back()!='*'){
              yyerror("Arrow operator can only be applied to pointer.");
          }

            Symbol* sym = lookupSymbol(obj->type.substr(0,obj->type.size()-1));
            if(!sym){
                yyerror("Pointer must be to struct or class.");
            }
            if(sym->type!="struct" && sym->type!="class"){
                yyerror("Pointer must be to struct or class.");
            }

            Node* n = new Node();
            n->code = obj->code;
            string tmp = newTemp();
            n->code.push_back(tmp + " = *" + obj->place);
            string nm = obj->place + "->" + string((yyvsp[0].str));
            Symbol* s = lookupSymbol(nm);
            funcInfo* f = lookupFunction(nm);
            n->code = obj->code;
            if(s){
                check_access(s);
                n->type = s->type;
                n->kind = s->kind;
                // string offset = newTemp();
                // n->code.push_back(offset + " = " + n->place + " + " + to_string(paramCount));
            }
            else if(f){
                check_func_access(f);
                n->type = f->returnType;
            }
            else{
                yyerror("No member or function named '" + nm+"'.");
            }
            n->place = newTemp();
            n->code.push_back(n->place + " = " + tmp + "." + string((yyvsp[0].str)));
            (yyval.node) = n;
      }
#line 2289 "src/parser.tab.c"
    break;

  case 18: /* postfix_expression: postfix_expression INCREMENT  */
#line 698 "src/parser.y"
                                       {
          dbg("postfix_expression -> postfix_expression ++");
          Node* v = (yyvsp[-1].node);
          if(check_unary_comp(v->type,"++")){
              yyerror("Invalid type '" + v->type + "' for increment.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          string old = newTemp();
            n->code.push_back(old + " = " + v->place);          // load old value from address
            n->code.push_back(v->place + " = " + old + " + 1;");      // store back incremented value
            n->place = old;
          n->type = v->type;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 2313 "src/parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression DECREMENT  */
#line 717 "src/parser.y"
                                       { 
            dbg("postfix_expression -> postfix_expression --");
          Node* v = (yyvsp[-1].node);
          if(check_unary_comp(v->type,"--")){
              yyerror("Invalid type '" + v->type + "' for decrement.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          string old = newTemp();
            n->code.push_back(old + " = " + v->place);          // load old value from address
            n->code.push_back(v->place + " = " + old + " - 1;");      // store back incremented value
            n->place = old;
          n->type = v->type;
          (yyval.node) = n;
      }
#line 2336 "src/parser.tab.c"
    break;

  case 20: /* argument_expression_list: assignment_expression  */
#line 740 "src/parser.y"
    {
        dbg("argument_expression_list -> assignment_expression");
        Node* e = (yyvsp[0].node);
        if(e->place.empty()) {
            yyerror("Void expression cannot be used as function argument.");
        }
        Node* n = new Node();
        n->code = e->code;
        n->syn.push_back(e->type);
        n->argCount = 1;
        n->code.push_back("param " + e->place);
        n->type = e->type;
        dbg("");
        dbg("argcount is "+ to_string(n->argCount)+", type is "+n->type);
        dbg("");
        (yyval.node) = n;
    }
#line 2358 "src/parser.tab.c"
    break;

  case 21: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 758 "src/parser.y"
    {
        dbg("argument_expression_list -> argument_expression_list , assignment_expression");
        Node* e = (yyvsp[0].node);
        if(e->place.empty()){
            yyerror("Void expression cannot be used as function argument.");
        }
        Node* n = (yyvsp[-2].node);
        n->code.insert(n->code.end(), e->code.begin(), e->code.end());
        n->argCount = n->argCount + 1;
        n->syn.push_back(e->type);
        n->code.push_back("param " + e->place);
        dbg("");
        dbg("argcount is " + to_string(n->argCount) + ", type is " + e->type);
        dbg("");
        (yyval.node) = n;
    }
#line 2379 "src/parser.tab.c"
    break;

  case 22: /* unary_expression: postfix_expression  */
#line 778 "src/parser.y"
                             { 
        dbg("unary_expression -> postfix_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2387 "src/parser.tab.c"
    break;

  case 23: /* unary_expression: INCREMENT unary_expression  */
#line 781 "src/parser.y"
                                     {
          dbg("unary_expression -> ++ unary_expression");
          Node* v = (yyvsp[0].node);
          if(!check_unary_comp(v->type,"++")){
              yyerror("Invalid type '" + v->type + "' for increment.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " + 1;");
          (yyval.node) = n;
      }
#line 2407 "src/parser.tab.c"
    break;

  case 24: /* unary_expression: DECREMENT unary_expression  */
#line 796 "src/parser.y"
                                     {
            dbg("unary_expression -> -- unary_expression");
          Node* v = (yyvsp[0].node);
          if(!check_unary_comp(v->type,"--")){
              yyerror("Invalid type '" + v->type + "' for decrement.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " - 1;");
          (yyval.node) = n;
      }
#line 2427 "src/parser.tab.c"
    break;

  case 25: /* unary_expression: unary_operator cast_expression  */
#line 811 "src/parser.y"
                                         {
            dbg("unary_expression -> unary_operator cast_expression");
          Node* rhs = (yyvsp[0].node);
          Node* n = new Node();
          n->code = rhs->code;
          string op = string((yyvsp[-1].str));
          if(!check_unary_comp(rhs->type,op)){
              yyerror("Invalid operation '" + op + "' on type '" + rhs->type + "'.");
            }
          if (op == "&") {
              n->place = newTemp();
              n->code.push_back(n->place + " = &" + rhs->place);
              n->type = rhs->type + "*";
          } else if (op == "*") {
              n->place = newTemp();
              n->code.push_back(n->place + " = *" + rhs->place);
              n->type = rhs->type.substr(0, rhs->type.size() - 1);
          } else if (op == "+") {
              n->place = rhs->place;
              n->type = rhs->type;
          } else if (op == "-") {
              n->place = newTemp();
              n->code.push_back(n->place + " = 0 - " + rhs->place);
              n->type = rhs->type;
          } else if (op == "~") {
              n->place = newTemp();
              n->code.push_back(n->place + " = ~" + rhs->place);
              n->type = rhs->type;
          } else if (op == "!") {
              n->place = newTemp();
              n->code.push_back(n->place + " = !" + rhs->place);
              n->type = "bool";
          }
          (yyval.node) = n;
      }
#line 2467 "src/parser.tab.c"
    break;

  case 26: /* unary_expression: SIZEOF LROUND unary_expression RROUND  */
#line 846 "src/parser.y"
                                               {
          dbg("unary_expression -> sizeof ( unary_expression )");
          Node* n = new Node(); 
          n->place = newTemp(); 
            n->code = (yyvsp[-1].node)->code;
            string t = (yyvsp[-1].node)->type;
            if(t.back()=='*') t = "nullptr";
          n->code.push_back(n->place + " = " + to_string(typeSize[t]));
            n->type = "int";
          (yyval.node) = n;
      }
#line 2483 "src/parser.tab.c"
    break;

  case 27: /* unary_expression: SIZEOF LROUND return_type RROUND  */
#line 857 "src/parser.y"
                                           {
            dbg("unary_expression -> sizeof ( type_name )");
          Node* n = new Node(); 
          n->place = newTemp(); 
            string t = (yyvsp[-1].str);
            if(t.back()=='*') t = "nullptr";
          n->code.push_back(n->place + " = " + to_string(typeSize[t]));
            n->type = "int";
          (yyval.node) = n;
      }
#line 2498 "src/parser.tab.c"
    break;

  case 28: /* unary_expression: delete_expression  */
#line 867 "src/parser.y"
                            { 
        dbg("unary_expression -> delete_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2506 "src/parser.tab.c"
    break;

  case 29: /* unary_expression: new_expression  */
#line 870 "src/parser.y"
                         { 
        dbg("unary_expression -> new_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2514 "src/parser.tab.c"
    break;

  case 30: /* unary_operator: BITWISE_AND  */
#line 877 "src/parser.y"
                      { 
        dbg("unary_operator -> &");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2522 "src/parser.tab.c"
    break;

  case 31: /* unary_operator: STAR  */
#line 880 "src/parser.y"
               { 
        dbg("unary_operator -> *");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2530 "src/parser.tab.c"
    break;

  case 32: /* unary_operator: PLUS  */
#line 883 "src/parser.y"
               { 
        dbg("unary_operator -> +");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2538 "src/parser.tab.c"
    break;

  case 33: /* unary_operator: MINUS  */
#line 886 "src/parser.y"
                { 
        dbg("unary_operator -> -");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2546 "src/parser.tab.c"
    break;

  case 34: /* unary_operator: TILDE  */
#line 889 "src/parser.y"
                { 
        dbg("unary_operator -> ~");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2554 "src/parser.tab.c"
    break;

  case 35: /* unary_operator: LOGICAL_NOT  */
#line 892 "src/parser.y"
                      { 
        dbg("unary_operator -> !");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2562 "src/parser.tab.c"
    break;

  case 36: /* new_expression: NEW return_type new_square  */
#line 899 "src/parser.y"
                                     {
            dbg("new_expression -> NEW type_specifier pointer_opt new_square");
          Node* n = new Node();
            string tmp = newTemp();
            string w = string((yyvsp[-1].str));
            if(string((yyvsp[-1].str)).back()=='*') w = "nullptr";
            n->code = (yyvsp[0].node)->code;
            n->place = newTemp();
            n->code.push_back(tmp+ " = " + (yyvsp[0].node)->place + " * " + to_string(typeSize[w]));
            n->code.push_back(n->place + " = call malloc, "+tmp);
            n->type = string((yyvsp[-1].str)) + (yyvsp[0].node)->type + "*";
          (yyval.node) = n;
      }
#line 2580 "src/parser.tab.c"
    break;

  case 37: /* new_expression: NEW return_type  */
#line 912 "src/parser.y"
                          {
            dbg("new_expression -> NEW return_type");
          Node* n = new Node();
          n->place = newTemp();
          string w = string((yyvsp[0].str));
          if(string((yyvsp[0].str)).back()=='*') w = "nullptr";
          n->code.push_back(n->place + " = call malloc, "+to_string(typeSize[w]));
          n->type = string((yyvsp[0].str)) + "*";
          (yyval.node) = n;
      }
#line 2595 "src/parser.tab.c"
    break;

  case 38: /* new_square: LSQUARE expression RSQUARE  */
#line 926 "src/parser.y"
                                     { 
            dbg("new_square -> [ expression ]");
            Node* n = new Node();
            n->code = (yyvsp[-1].node)->code;
            n->place = (yyvsp[-1].node)->place;
            n->type = "*";
            n->argCount = 1;
            (yyval.node) = n; 
        }
#line 2609 "src/parser.tab.c"
    break;

  case 39: /* new_square: new_square LSQUARE expression RSQUARE  */
#line 935 "src/parser.y"
                                                { 
            dbg("new_square -> new_square [ expression ]");
            Node* n = (yyvsp[-3].node); Node* e = (yyvsp[-1].node);
            n->code.insert(n->code.end(), e->code.begin(), e->code.end());
            string temp1 = newTemp();
            n->code.push_back(temp1 + " = " + n->place + " * "+e->place);
            n->place = temp1;
            n->type = n->type + "*";
            n->argCount = n->argCount + 1;
            (yyval.node) = n;
          }
#line 2625 "src/parser.tab.c"
    break;

  case 40: /* delete_expression: DELETE LSQUARE RSQUARE cast_expression  */
#line 950 "src/parser.y"
                                                 {
          dbg("delete_expression -> DELETE [ ] cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("call free, " + (yyvsp[0].node)->place);
          (yyval.node) = n;
      }
#line 2637 "src/parser.tab.c"
    break;

  case 41: /* delete_expression: DELETE cast_expression  */
#line 957 "src/parser.y"
                                 {
            dbg("delete_expression -> DELETE cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("call free, " + (yyvsp[0].node)->place);
          (yyval.node) = n;
      }
#line 2649 "src/parser.tab.c"
    break;

  case 42: /* cast_expression: unary_expression  */
#line 968 "src/parser.y"
                           { 
        dbg("cast_expression -> unary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2657 "src/parser.tab.c"
    break;

  case 43: /* cast_expression: LROUND return_type RROUND cast_expression  */
#line 971 "src/parser.y"
                                                    {
            dbg("cast_expression -> ( type_name ) cast_expression");
            string a = (yyvsp[-2].str); Node* b = (yyvsp[0].node);
            if(!check_casting(b->type,a)){
                yyerror("Unable to cast from '" + b->type + "' to '" + a + "'.");
            }
            Node* n = new Node();
            n->code = b->code;
            n->place = newTemp();
            n->code.push_back(n->place + " = " + b->type + "_to_"+ a +" "+ b->place);
            n->type = a;
          (yyval.node) = n;
      }
#line 2675 "src/parser.tab.c"
    break;

  case 44: /* multiplicative_expression: cast_expression  */
#line 988 "src/parser.y"
                          { 
        dbg("multiplicative_expression -> cast_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2683 "src/parser.tab.c"
    break;

  case 45: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 991 "src/parser.y"
                                                         {
        dbg("multiplicative_expression -> multiplicative_expression * cast_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          if(!check_compatibility(a->type,b->type,"*")){
            yyerror("Type incompatibility in multiply.");
          }
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " * " + b->place);
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2701 "src/parser.tab.c"
    break;

  case 46: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 1004 "src/parser.y"
                                                           {
        dbg("multiplicative_expression -> multiplicative_expression / cast_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          if(!check_compatibility(a->type,b->type,"/")){
            yyerror("Type incompatibility in divide.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " / " + b->place);
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2720 "src/parser.tab.c"
    break;

  case 47: /* multiplicative_expression: multiplicative_expression MODULUS cast_expression  */
#line 1018 "src/parser.y"
                                                            {
        dbg("multiplicative_expression -> multiplicative_expression % cast_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          if(!check_compatibility(a->type,b->type,"%")){
            yyerror("Type incompatibility in modulus.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " % " + b->place);
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2739 "src/parser.tab.c"
    break;

  case 48: /* additive_expression: multiplicative_expression  */
#line 1036 "src/parser.y"
                                    { 
        dbg("additive_expression -> multiplicative_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2747 "src/parser.tab.c"
    break;

  case 49: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 1039 "src/parser.y"
                                                             {
            dbg("additive_expression -> additive_expression + multiplicative_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          if(!check_compatibility(a->type,b->type,"+")){
            yyerror("Type incompatibility in plus.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " + " + b->place);
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2766 "src/parser.tab.c"
    break;

  case 50: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 1053 "src/parser.y"
                                                              {
            dbg("additive_expression -> additive_expression - multiplicative_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          if(!check_compatibility(a->type,b->type,"-")){
            yyerror("Type incompatibility in minus.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " - " + b->place);
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2785 "src/parser.tab.c"
    break;

  case 51: /* shift_expression: additive_expression  */
#line 1071 "src/parser.y"
                              { 
        dbg("shift_expression -> additive_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2793 "src/parser.tab.c"
    break;

  case 52: /* shift_expression: shift_expression LEFT_SHIFT additive_expression  */
#line 1074 "src/parser.y"
                                                          {
            dbg("shift_expression -> shift_expression << additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          if(!check_compatibility(a->type,b->type,"<<")){
            yyerror("Type incompatibility in left shift.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " << " + b->place);
          n->type = a->type; 
          (yyval.node) = n;
      }
#line 2812 "src/parser.tab.c"
    break;

  case 53: /* shift_expression: shift_expression RIGHT_SHIFT additive_expression  */
#line 1088 "src/parser.y"
                                                           {
            dbg("shift_expression -> shift_expression >> additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          if(!check_compatibility(a->type,b->type,">>")){
            yyerror("Type incompatibility in right shift.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " >> " + b->place);
          n->type = a->type; 
          (yyval.node) = n;
      }
#line 2831 "src/parser.tab.c"
    break;

  case 54: /* relational_expression: shift_expression  */
#line 1106 "src/parser.y"
                           { 
        dbg("relational_expression -> shift_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2839 "src/parser.tab.c"
    break;

  case 55: /* relational_expression: relational_expression GREATER_THAN shift_expression  */
#line 1109 "src/parser.y"
                                                              {
          dbg("relational_expression -> relational_expression > shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " > " + b->place);
          n->type = "bool"; (yyval.node) = n;
      }
#line 2856 "src/parser.tab.c"
    break;

  case 56: /* relational_expression: relational_expression LESS_THAN shift_expression  */
#line 1121 "src/parser.y"
                                                           {
          dbg("relational_expression -> relational_expression < shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " < " + b->place);
          n->type = "bool"; (yyval.node) = n;
      }
#line 2873 "src/parser.tab.c"
    break;

  case 57: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 1133 "src/parser.y"
                                                            {
            dbg("relational_expression -> relational_expression <= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " <= " + b->place);
          n->type = "bool"; (yyval.node) = n;
      }
#line 2890 "src/parser.tab.c"
    break;

  case 58: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 1145 "src/parser.y"
                                                               {
            dbg("relational_expression -> relational_expression >= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " >= " + b->place);
          n->type = "bool"; (yyval.node) = n;
      }
#line 2907 "src/parser.tab.c"
    break;

  case 59: /* equality_expression: relational_expression  */
#line 1161 "src/parser.y"
                                { 
        dbg("equality_expression -> relational_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2915 "src/parser.tab.c"
    break;

  case 60: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 1164 "src/parser.y"
                                                          {
            dbg("equality_expression -> equality_expression == relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in equality expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " == " + b->place);
          n->type = "bool"; 
          (yyval.node) = n;
      }
#line 2933 "src/parser.tab.c"
    break;

  case 61: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 1177 "src/parser.y"
                                                              {
            dbg("equality_expression -> equality_expression != relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(a->type != b->type){
              yyerror("Type incompatibility in equality expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " != " + b->place);
          n->type = "bool"; 
          (yyval.node) = n;
      }
#line 2951 "src/parser.tab.c"
    break;

  case 62: /* and_expression: equality_expression  */
#line 1194 "src/parser.y"
                              { 
        dbg("and_expression -> equality_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2959 "src/parser.tab.c"
    break;

  case 63: /* and_expression: and_expression BITWISE_AND equality_expression  */
#line 1197 "src/parser.y"
                                                         {
            dbg("and_expression -> and_expression & equality_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(!check_compatibility(a->type,b->type,"&")){
                yyerror("Type incompatibility in bitwise AND expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " & " + b->place);
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2977 "src/parser.tab.c"
    break;

  case 64: /* exclusive_or_expression: and_expression  */
#line 1214 "src/parser.y"
                         { 
        dbg("exclusive_or_expression -> and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2985 "src/parser.tab.c"
    break;

  case 65: /* exclusive_or_expression: exclusive_or_expression BITWISE_XOR and_expression  */
#line 1217 "src/parser.y"
                                                             {
            dbg("exclusive_or_expression -> exclusive_or_expression ^ and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(!check_compatibility(a->type,b->type,"^")){
                yyerror("Type incompatibility in bitwise XOR expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " ^ " + b->place);
            n->type = a->type;
          (yyval.node) = n;
      }
#line 3003 "src/parser.tab.c"
    break;

  case 66: /* inclusive_or_expression: exclusive_or_expression  */
#line 1234 "src/parser.y"
                                  { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3011 "src/parser.tab.c"
    break;

  case 67: /* inclusive_or_expression: inclusive_or_expression BITWISE_OR exclusive_or_expression  */
#line 1237 "src/parser.y"
                                                                     {
            dbg("inclusive_or_expression -> inclusive_or_expression | exclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(!check_compatibility(a->type,b->type,"|")){
              yyerror("Type incompatibility in bitwise OR expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " | " + b->place);
            n->type = a->type;
          (yyval.node) = n;
      }
#line 3029 "src/parser.tab.c"
    break;

  case 68: /* logical_and_expression: inclusive_or_expression  */
#line 1254 "src/parser.y"
                                  { 
        dbg("logical_and_expression -> inclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3037 "src/parser.tab.c"
    break;

  case 69: /* logical_and_expression: logical_and_expression LOGICAL_AND inclusive_or_expression  */
#line 1257 "src/parser.y"
                                                                     {
            dbg("logical_and_expression -> logical_and_expression && inclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(a->type!="bool" || b->type!="bool"){
                yyerror("Type incompatibility in logical AND expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " && " + b->place);
          n->type = "bool"; 
          (yyval.node) = n;
      }
#line 3055 "src/parser.tab.c"
    break;

  case 70: /* logical_or_expression: logical_and_expression  */
#line 1274 "src/parser.y"
                                 { 
        dbg("logical_or_expression -> logical_and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3063 "src/parser.tab.c"
    break;

  case 71: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 1277 "src/parser.y"
                                                                  {
            dbg("logical_or_expression -> logical_or_expression || logical_and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(a->type!="bool" || b->type!="bool"){
              yyerror("Type incompatibility in logical OR expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " || " + b->place);
          n->type = "bool"; 
          (yyval.node) = n;
      }
#line 3081 "src/parser.tab.c"
    break;

  case 72: /* conditional_expression: logical_or_expression  */
#line 1294 "src/parser.y"
    { 
        dbg("conditional_expression -> logical_or_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3090 "src/parser.tab.c"
    break;

  case 73: /* conditional_expression: logical_or_expression QUESTION_MARK expression COLON conditional_expression  */
#line 1298 "src/parser.y"
                                                                                      {
            dbg("conditional_expression -> logical_or_expression ? expression : conditional_expression");
          Node* cond = (yyvsp[-4].node); Node* e1 = (yyvsp[-2].node); Node* e2 = (yyvsp[0].node);
          Node* n = new Node();
          string Lfalse = newLabel();
          string Lend = newLabel();
          n->code = cond->code;
          n->place = newTemp();
          n->code.push_back("ifFalse " + cond->place + " goto " + Lfalse);
          n->code.insert(n->code.end(), e1->code.begin(), e1->code.end());
          n->code.push_back(n->place + " = " + e1->place);
          n->code.push_back("goto " + Lend);
          n->code.push_back(Lfalse + ":");
          n->code.insert(n->code.end(), e2->code.begin(), e2->code.end());
          n->code.push_back(n->place + " = " + e2->place);
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 3113 "src/parser.tab.c"
    break;

  case 74: /* assignment_expression: conditional_expression  */
#line 1320 "src/parser.y"
                                 { 
        dbg("assignment_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3121 "src/parser.tab.c"
    break;

  case 75: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 1323 "src/parser.y"
                                                                     {
            dbg("assignment_expression -> unary_expression assignment_operator assignment_expression");
          Node* left = (yyvsp[-2].node); 
          Node* right = (yyvsp[0].node);
          Node* n = new Node();
          n->code = left->code; 
          n->code.insert(n->code.end(),right->code.begin(),right->code.end());
          string op = string((yyvsp[-1].str));
            string baseop = op.substr(0,op.size()-1);
          if (!check_compatibility(left->type,right->type,baseop)) {
              yyerror("Type incompatibility in assignment to '" + left->place + "'.");
          }
          if(left->kind.find("const")!=string::npos){
              yyerror("Cannot assign to const variable '" + left->place + "'.");
          }
          if (op == "=") {
              n->code.push_back(left->place + " = " + right->place);
          } 
          else {
              n->code.push_back(left->place + " = " + left->place + " " + baseop + " " + right->place);
          }
          (yyval.node) = n;
      }
#line 3149 "src/parser.tab.c"
    break;

  case 76: /* assignment_operator: ASSIGN  */
#line 1351 "src/parser.y"
                 { 
        dbg("assignment_operator -> =");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3157 "src/parser.tab.c"
    break;

  case 77: /* assignment_operator: STAR_EQUAL  */
#line 1354 "src/parser.y"
                     { 
        dbg("assignment_operator -> *=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3165 "src/parser.tab.c"
    break;

  case 78: /* assignment_operator: DIV_EQUAL  */
#line 1357 "src/parser.y"
                    { 
        dbg("assignment_operator -> /=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3173 "src/parser.tab.c"
    break;

  case 79: /* assignment_operator: MOD_EQUAL  */
#line 1360 "src/parser.y"
                    { 
        dbg("assignment_operator -> %=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3181 "src/parser.tab.c"
    break;

  case 80: /* assignment_operator: PLUS_EQUAL  */
#line 1363 "src/parser.y"
                     { 
        dbg("assignment_operator -> +=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3189 "src/parser.tab.c"
    break;

  case 81: /* assignment_operator: MINUS_EQUAL  */
#line 1366 "src/parser.y"
                      { 
        dbg("assignment_operator -> -=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3197 "src/parser.tab.c"
    break;

  case 82: /* assignment_operator: LEFT_SHIFT_EQ  */
#line 1369 "src/parser.y"
                        { 
        dbg("assignment_operator -> <<=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3205 "src/parser.tab.c"
    break;

  case 83: /* assignment_operator: RIGHT_SHIFT_EQ  */
#line 1372 "src/parser.y"
                         { 
        dbg("assignment_operator -> >>=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3213 "src/parser.tab.c"
    break;

  case 84: /* assignment_operator: AND_EQUAL  */
#line 1375 "src/parser.y"
                    { 
        dbg("assignment_operator -> &=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3221 "src/parser.tab.c"
    break;

  case 85: /* assignment_operator: XOR_EQUAL  */
#line 1378 "src/parser.y"
                    { 
        dbg("assignment_operator -> ^=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3229 "src/parser.tab.c"
    break;

  case 86: /* assignment_operator: OR_EQUAL  */
#line 1381 "src/parser.y"
                   { 
        dbg("assignment_operator -> |=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3237 "src/parser.tab.c"
    break;

  case 87: /* expression: assignment_expression  */
#line 1389 "src/parser.y"
    { 
        dbg("expression -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3246 "src/parser.tab.c"
    break;

  case 88: /* expression: expression COMMA assignment_expression  */
#line 1394 "src/parser.y"
        {
            dbg("expression -> expression , assignment_expression");
            Node* n = new Node();
            n->code = (yyvsp[-2].node)->code;
            n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
            n->place = (yyvsp[0].node)->place;
            (yyval.node) = n;
        }
#line 3259 "src/parser.tab.c"
    break;

  case 89: /* constant_expression: conditional_expression  */
#line 1407 "src/parser.y"
    { 
        dbg("constant_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3268 "src/parser.tab.c"
    break;

  case 90: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 1416 "src/parser.y"
    {
        dbg("declaration -> declaration_specifiers init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3277 "src/parser.tab.c"
    break;

  case 91: /* declaration_specifiers: static_opt const_opt type_specifier  */
#line 1424 "src/parser.y"
                                          {
        dbg("declaration_specifiers -> static_opt const_opt type_specifier");
        lastDeclType = string((yyvsp[-2].str))+string((yyvsp[-1].str))+string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
	}
#line 3287 "src/parser.tab.c"
    break;

  case 92: /* init_declarator_list: init_declarator  */
#line 1434 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3296 "src/parser.tab.c"
    break;

  case 93: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1439 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator_list , init_declarator");
        Node* n = (yyvsp[-2].node);
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        (yyval.node) = n;
    }
#line 3307 "src/parser.tab.c"
    break;

  case 94: /* pointer_opt: pointer_list  */
#line 1450 "src/parser.y"
    {
        dbg("pointer_opt -> pointer_list");
        (yyval.str) = (yyvsp[0].str);
    }
#line 3316 "src/parser.tab.c"
    break;

  case 95: /* pointer_opt: %empty  */
#line 1455 "src/parser.y"
    {
        dbg("pointer_opt -> <empty>");
        (yyval.str) = strdup("");
    }
#line 3325 "src/parser.tab.c"
    break;

  case 96: /* pointer_list: pointer_list STAR  */
#line 1464 "src/parser.y"
    {
        dbg("pointer_list -> pointer_list *");
        (yyval.str) = strdup((string("*")+string((yyvsp[-1].str))).c_str());
    }
#line 3334 "src/parser.tab.c"
    break;

  case 97: /* pointer_list: STAR  */
#line 1469 "src/parser.y"
    {
        dbg("pointer_list -> *");
        (yyval.str) = strdup("*");
    }
#line 3343 "src/parser.tab.c"
    break;

  case 98: /* init_declarator: IDENTIFIER  */
#line 1478 "src/parser.y"
    {
        dbg("init_declarator -> IDENTIFIER ");

        if(lastDeclType.find("const")!=string::npos){
            yyerror("Const variable '" + string((yyvsp[0].str)) + "' must be initialized.");
        }
        Node* n = new Node();
        n->place = string((yyvsp[0].str));
        // n->code = {n->place + " = " + '0'};
        n->type = lastDeclType;
        n->kind = "";

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,7);
            n->kind += "static";
        }
        n->argCount = 0;
        if(lastClassType == "")
        {
            bool ok = declareSymbol(n->place, n->type, n->kind);
            if (!ok) {
                yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
            }
        }
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize[n->type];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared variable: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");

        (yyval.node) = n;
    }
#line 3391 "src/parser.tab.c"
    break;

  case 99: /* init_declarator: IDENTIFIER square_list  */
#line 1522 "src/parser.y"
    {    
        dbg("init_declarator -> IDENTIFIER square_list ");
        if(lastDeclType.find("const")!=string::npos){
            yyerror("Const variable '" + string((yyvsp[-1].str)) + "' must be initialized.");
        }
        Node* n = new Node();
        n->place = string((yyvsp[-1].str));
        n->code = (yyvsp[0].node)->code;
        n->argCount = (yyvsp[0].node)->argCount;
        n->type = lastDeclType;
        n->kind = "array";
        n->syn = (yyvsp[0].node)->syn;

        dbg("");
        dbg("Array dimensions: ");
        for (const auto& dim : n->syn) {
            dbg(" - " + dim);
        }
        dbg("");
        if(n->type.find("static")!=string::npos){
            n->type.erase(0,7);
            n->kind += " static";
        }
        for(int i = 0; i < (yyvsp[0].node)->argCount; i++)
        {
            n->type += "*";
        }

        if(lastClassType == "")
        {
            bool ok = declareSymbol(n->place, n->type, n->kind, n->syn);
            if (!ok) {
                yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
            }
        }
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                int p = 1;
                for(int i = 0; i < n->argCount; i++)
                {
                    p *= stoi(n->syn[i]);
                }
                classOffset += p * typeSize[n->type.substr(0, n->type.size() - n->argCount)];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared array: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        for(int i = 0; i < n->argCount; i++)
        {
            dbg("Dimension " + to_string(i+1) + ": " + n->syn[i]);
        }
        dbg("");
        (yyval.node) = n;
    }
#line 3459 "src/parser.tab.c"
    break;

  case 100: /* init_declarator: pointer_list IDENTIFIER  */
#line 1586 "src/parser.y"
    {    
        dbg("init_declarator -> pointer_list IDENTIFIER ");

        if(lastDeclType.find("const")!=string::npos){
            yyerror("Const variable '" + string((yyvsp[-1].str)) + "' must be initialized.");
        }

        Node* n = new Node();
        n->place = string((yyvsp[0].str));
        n->code = {};
        n->argCount = 0;
        string stars = string((yyvsp[-1].str));
        n->type = lastDeclType + stars;
        n->kind = "pointer";

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,7);
            n->kind += " static";
        }
        
        if(lastClassType == "")
        {
            bool ok = declareSymbol(n->place, n->type, n->kind);
            if (!ok) {
                yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
            }
        }
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize["nullptr"];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared pointer: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");
        (yyval.node) = n;
    }
#line 3510 "src/parser.tab.c"
    break;

  case 101: /* init_declarator: IDENTIFIER ASSIGN assignment_expression  */
#line 1634 "src/parser.y"
    {
        dbg("init_declarator -> IDENTIFIER = assignment_expression ");
        Node* n = new Node();
        string name = string((yyvsp[-2].str));
        n->place = name;
        n->type = lastDeclType;
        n->code = (yyvsp[0].node)->code;
        n->argCount = 0;
        n->kind = "";

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,7);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,6);
            n->kind += "const";
        }
        n->code.push_back(n->place + " = " + (yyvsp[0].node)->place);

        if(n->type != (yyvsp[0].node)->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        if(lastClassType == "")
        {
            bool ok = declareSymbol(n->place,n->type,n->kind);
            if (!ok) {
                yyerror("Duplicate declaration of '" + name + "' in same scope.");
            }
        }
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize[n->type];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared variable: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");
        (yyval.node) = n;
    }
#line 3565 "src/parser.tab.c"
    break;

  case 102: /* init_declarator: pointer_list IDENTIFIER ASSIGN assignment_expression  */
#line 1686 "src/parser.y"
    {
        dbg("init_declarator -> pointer_list IDENTIFIER = assignment_expression ");
        Node* n = new Node();
        string name = string((yyvsp[-2].str));
        n->place = name;
        string stars = string((yyvsp[-3].str));
        
        n->type = lastDeclType + stars;
        n->code = (yyvsp[0].node)->code;
        n->code.push_back(n->place + " = " + (yyvsp[0].node)->place);
        n->argCount = 0;
        n->kind = "pointer";

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,7);
            n->kind += " static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,6);
            n->kind += " const";
        }
        
        if ((yyvsp[0].node)->type!=n->type){
            yyerror("Type mismatch in initialization of '" + name + "'."); 
        }

        if(lastClassType == "")
        {
            bool ok = declareSymbol(n->place,n->type,n->kind);
            if (!ok) {
                yyerror("Duplicate declaration of '" + name + "' in same scope.");
            }
        }
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize["nullptr"];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared pointer: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");
        (yyval.node) = n;
    }
#line 3622 "src/parser.tab.c"
    break;

  case 103: /* init_declarator: IDENTIFIER square_list ASSIGN initializer  */
#line 1740 "src/parser.y"
    {
        dbg("init_declarator -> IDENTIFIER square_list = initializer ");
        Node* n = new Node();
        string name = string((yyvsp[-3].str));
        n->place = name;
        n->type = lastDeclType;
        n->kind = "array";
        n->syn = (yyvsp[-2].node)->syn;
        n->argCount = (yyvsp[-2].node)->argCount;
        n->code = (yyvsp[-2].node)->code;
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        
        if(n->type.find("static")!=string::npos){
            n->type.erase(0,7);
            n->kind += " static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,6);
            n->kind += " const";
        }

        int p = 1;
        for(int i = 0; i < n->argCount; i++)
        {
            n->type += "*";
            p = p * stoi((yyvsp[-2].node)->syn[i]);
        }

        if(lastDeclType != (yyvsp[0].node)->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        if(p < (yyvsp[0].node)->argCount){
            yyerror("Number of elements in initializer is greater than array size for '" + name + "'.");
        }

        if(lastClassType == "")
        {
            bool ok = declareSymbol(n->place,n->type,n->kind,n->syn);
            if (!ok) {
                yyerror("Duplicate declaration of '" + name + "' in same scope.");
            }
        }
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += p * typeSize[n->type.substr(0, n->type.size() - n->argCount)];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared array: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        for(int i = 0; i < n->argCount; i++)
        {
            dbg("Dimension " + to_string(i+1) + ": " + n->syn[i]);
        }
        dbg("");
        (yyval.node) = n;
    }
#line 3693 "src/parser.tab.c"
    break;

  case 104: /* initializer: LCURLY initializer_list RCURLY  */
#line 1880 "src/parser.y"
    { 
        dbg("initializer -> { initializer_list }");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3702 "src/parser.tab.c"
    break;

  case 105: /* initializer_list: assignment_expression  */
#line 1889 "src/parser.y"
    { 
        dbg("initializer_list -> assignment_expression");
        Node * n = (yyvsp[0].node);
        n->argCount = 1;
        (yyval.node) = n;
    }
#line 3713 "src/parser.tab.c"
    break;

  case 106: /* initializer_list: initializer_list COMMA assignment_expression  */
#line 1896 "src/parser.y"
    {
        dbg("initializer_list -> initializer_list , assignment_expression");
        Node* n = (yyvsp[-2].node); 

        if(n->type != (yyvsp[0].node)->type)
        {
            yyerror("Type mismatch in initializer list.");
        }

        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        n->argCount = n->argCount + 1;
        (yyval.node) = n;
    }
#line 3731 "src/parser.tab.c"
    break;

  case 107: /* square_list: square_list LSQUARE constant_expression RSQUARE  */
#line 1914 "src/parser.y"
    {
        dbg("square_list -> square_list [ constant_expression ]");
        Node* n = (yyvsp[-3].node);
        n->argCount = n->argCount + 1;
        n->code.insert(n->code.end(),(yyvsp[-1].node)->code.begin(),(yyvsp[-1].node)->code.end());
        n->syn.push_back(to_string((yyvsp[-1].node)->argCount));

        if((yyvsp[-1].node)->type!="int"){
            yyerror("Array size must be of type int.");
        }

        (yyval.node) = n;
    }
#line 3749 "src/parser.tab.c"
    break;

  case 108: /* square_list: LSQUARE constant_expression RSQUARE  */
#line 1928 "src/parser.y"
    {
        dbg("square_opt -> [ constant_expression ]");
        Node* n = new Node();
        n->argCount = 1;
        n->code = (yyvsp[-1].node)->code;
        n->syn.push_back(to_string((yyvsp[-1].node)->argCount));

        if((yyvsp[-1].node)->type!="int"){
            yyerror("Array size must be of type int.");
        }
        (yyval.node) = n;
    }
#line 3766 "src/parser.tab.c"
    break;

  case 109: /* static_opt: STATIC  */
#line 1945 "src/parser.y"
                 { 
        dbg("static_opt -> STATIC");
        (yyval.str) = strdup("static"); }
#line 3774 "src/parser.tab.c"
    break;

  case 110: /* static_opt: %empty  */
#line 1948 "src/parser.y"
       { 
        dbg("static_opt -> <empty>");
        (yyval.str) = strdup(""); }
#line 3782 "src/parser.tab.c"
    break;

  case 111: /* type_specifier: VOID  */
#line 1955 "src/parser.y"
                 { 
        dbg("type_specifier -> VOID");
        (yyval.str) = strdup("void"); lastDeclType = "void"; }
#line 3790 "src/parser.tab.c"
    break;

  case 112: /* type_specifier: CHAR  */
#line 1958 "src/parser.y"
                 { 
        dbg("type_specifier -> CHAR");
        (yyval.str) = strdup("char"); lastDeclType = "char"; }
#line 3798 "src/parser.tab.c"
    break;

  case 113: /* type_specifier: INT  */
#line 1961 "src/parser.y"
                 { 
        dbg("type_specifier -> INT");
        (yyval.str) = strdup("int"); lastDeclType = "int"; }
#line 3806 "src/parser.tab.c"
    break;

  case 114: /* type_specifier: LONG  */
#line 1964 "src/parser.y"
                 { 
        dbg("type_specifier -> LONG");
        (yyval.str) = strdup("long"); lastDeclType = "long"; }
#line 3814 "src/parser.tab.c"
    break;

  case 115: /* type_specifier: DOUBLE  */
#line 1967 "src/parser.y"
                 { 
        dbg("type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); lastDeclType = "double"; }
#line 3822 "src/parser.tab.c"
    break;

  case 116: /* type_specifier: BOOL  */
#line 1970 "src/parser.y"
                 { 
        dbg("type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); lastDeclType = "bool"; }
#line 3830 "src/parser.tab.c"
    break;

  case 117: /* type_specifier: TYPE_NAME  */
#line 1976 "src/parser.y"
                    { 
        dbg("type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str); lastDeclType = string((yyvsp[0].str)); }
#line 3838 "src/parser.tab.c"
    break;

  case 118: /* $@1: %empty  */
#line 1984 "src/parser.y"
    { 
        lastClassType = string((yyvsp[-1].str)); 
        if(typeSize.find(lastClassType) != typeSize.end()){
            yyerror("Redefinition of class/struct '" + lastClassType + "'.");
        }
        typeSize[lastClassType] = 0;
        classOffset = 0;
        pushScope();
    }
#line 3852 "src/parser.tab.c"
    break;

  case 119: /* struct_or_class_specifier: struct_or_class IDENTIFIER LCURLY $@1 struct_or_class_member_list RCURLY  */
#line 1993 "src/parser.y"
    { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        popScope();
        (yyval.node) = (yyvsp[-1].node); 
        lastClassType = "";
    }
#line 3863 "src/parser.tab.c"
    break;

  case 120: /* struct_or_class: STRUCT  */
#line 2004 "src/parser.y"
    { 
        dbg("struct_or_class -> STRUCT");
        (yyval.node) = new Node(); 
        lastUsage = "public";
    }
#line 3873 "src/parser.tab.c"
    break;

  case 121: /* struct_or_class: CLASS  */
#line 2010 "src/parser.y"
    { 
        dbg("struct_or_class -> CLASS");
        (yyval.node) = new Node(); 
        lastUsage = "private";
    }
#line 3883 "src/parser.tab.c"
    break;

  case 122: /* struct_or_class_member_list: %empty  */
#line 2020 "src/parser.y"
    { 
        dbg("struct_or_class_member_list -> <empty>");
        (yyval.node) = new Node(); 
    }
#line 3892 "src/parser.tab.c"
    break;

  case 123: /* struct_or_class_member_list: struct_or_class_member_list struct_or_class_member  */
#line 2025 "src/parser.y"
    { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        Node* n = (yyvsp[-1].node); 
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; 
    }
#line 3903 "src/parser.tab.c"
    break;

  case 124: /* struct_or_class_member: access_specifier_label  */
#line 2035 "src/parser.y"
    { 
        dbg("struct_or_class_member -> access_specifier_label");
        lastUsage = string((yyvsp[0].node)->place);
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3913 "src/parser.tab.c"
    break;

  case 125: /* struct_or_class_member: member_declaration  */
#line 2041 "src/parser.y"
    { 
        dbg("struct_or_class_member -> member_declaration");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3922 "src/parser.tab.c"
    break;

  case 126: /* access_specifier_label: PUBLIC COLON  */
#line 2049 "src/parser.y"
    { 
        dbg("access_specifier_label -> PUBLIC :");
        Node* n=new Node(); 
        n->place = "public";
        (yyval.node) = n; 
    }
#line 3933 "src/parser.tab.c"
    break;

  case 127: /* access_specifier_label: PRIVATE COLON  */
#line 2056 "src/parser.y"
    { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); 
        n->place = "private";
        (yyval.node) = n; 
    }
#line 3944 "src/parser.tab.c"
    break;

  case 128: /* access_specifier_label: PROTECTED COLON  */
#line 2063 "src/parser.y"
    { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); 
        n->place = "protected";
        (yyval.node) = n; 
    }
#line 3955 "src/parser.tab.c"
    break;

  case 129: /* $@2: %empty  */
#line 2072 "src/parser.y"
                                {lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));}
#line 3961 "src/parser.tab.c"
    break;

  case 130: /* member_declaration: const_opt return_type $@2 struct_declarator_list SEMICOLON  */
#line 2073 "src/parser.y"
    { 
        dbg("member_declaration -> const_opt return_type struct_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node); 
    }
#line 3970 "src/parser.tab.c"
    break;

  case 131: /* member_declaration: function_header compound_statement  */
#line 2078 "src/parser.y"
    { 
        dbg("member_declaration -> function_header compound_statement");
        Node* n = (yyvsp[-1].node);
        n->code.push_back(lastClassType + "." + n->place + ":");
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        (yyval.node) = n;
    }
#line 3982 "src/parser.tab.c"
    break;

  case 132: /* struct_declarator_list: struct_declarator  */
#line 2093 "src/parser.y"
    { 
        dbg("struct_declarator_list -> struct_declarator");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3991 "src/parser.tab.c"
    break;

  case 133: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 2098 "src/parser.y"
    { 
        dbg("struct_declarator_list -> struct_declarator_list , struct_declarator");
        Node* n = (yyvsp[-2].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; 
    }
#line 4002 "src/parser.tab.c"
    break;

  case 134: /* struct_declarator: init_declarator  */
#line 2108 "src/parser.y"
    { 
        dbg("struct_declarator -> init_declarator");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4011 "src/parser.tab.c"
    break;

  case 135: /* const_opt: CONST  */
#line 2116 "src/parser.y"
                { 
        dbg("const_opt -> CONST");
        (yyval.str) = strdup("const"); }
#line 4019 "src/parser.tab.c"
    break;

  case 136: /* const_opt: %empty  */
#line 2119 "src/parser.y"
       {
        dbg("const_opt -> <empty>");
        (yyval.str) = strdup(""); }
#line 4027 "src/parser.tab.c"
    break;

  case 137: /* parameter_list: parameter_declaration  */
#line 2126 "src/parser.y"
                                { 
            dbg("parameter_list -> parameter_declaration");
            (yyval.node) = (yyvsp[0].node); 
        }
#line 4036 "src/parser.tab.c"
    break;

  case 138: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 2131 "src/parser.y"
        {
            dbg("parameter_list -> parameter_list , parameter_declaration");
            Node* n = (yyvsp[-2].node);
            n->syn.insert(n->syn.end(), (yyvsp[0].node)->syn.begin(), (yyvsp[0].node)->syn.end()); 
            (yyval.node) = n;
        }
#line 4047 "src/parser.tab.c"
    break;

  case 139: /* parameter_declaration: return_type IDENTIFIER  */
#line 2142 "src/parser.y"
        {
            dbg("parameter_declaration -> return_type IDENTIFIER");
            Node* n = new Node();
            n->syn.push_back(string((yyvsp[-1].str))); 
            n->syn.push_back(string((yyvsp[0].str)));
            (yyval.node) = n;
        }
#line 4059 "src/parser.tab.c"
    break;

  case 140: /* statement: labeled_statement  */
#line 2153 "src/parser.y"
                            { 
        dbg("statement -> labeled_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4067 "src/parser.tab.c"
    break;

  case 141: /* statement: compound_statement  */
#line 2156 "src/parser.y"
                             { 
        dbg("statement -> compound_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4075 "src/parser.tab.c"
    break;

  case 142: /* statement: expression_statement  */
#line 2159 "src/parser.y"
                               { 
        dbg("statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4083 "src/parser.tab.c"
    break;

  case 143: /* statement: selection_statement  */
#line 2162 "src/parser.y"
                              { 
        dbg("statement -> selection_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4091 "src/parser.tab.c"
    break;

  case 144: /* statement: iteration_statement  */
#line 2165 "src/parser.y"
                              { 
        dbg("statement -> iteration_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4099 "src/parser.tab.c"
    break;

  case 145: /* statement: jump_statement  */
#line 2168 "src/parser.y"
                         { 
        dbg("statement -> jump_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4107 "src/parser.tab.c"
    break;

  case 146: /* statement: io_statement  */
#line 2171 "src/parser.y"
                       { 
        dbg("statement -> io_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4115 "src/parser.tab.c"
    break;

  case 147: /* io_statement: cout_expression SEMICOLON  */
#line 2178 "src/parser.y"
                                { 
        dbg("io_statement -> cout_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4123 "src/parser.tab.c"
    break;

  case 148: /* io_statement: cin_expression SEMICOLON  */
#line 2181 "src/parser.y"
                                { 
        dbg("io_statement -> cin_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4131 "src/parser.tab.c"
    break;

  case 149: /* cout_expression: COUT insertion_list  */
#line 2188 "src/parser.y"
                          { 
        dbg("cout_expression -> COUT insertion_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4139 "src/parser.tab.c"
    break;

  case 150: /* insertion_list: LEFT_SHIFT assignment_expression  */
#line 2195 "src/parser.y"
                                       {
          dbg("insertion_list -> LEFT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node);
          Node* n = new Node();
          n->code = e->code;
          n->code.push_back("print " + e->place); 
          (yyval.node) = n;
      }
#line 4152 "src/parser.tab.c"
    break;

  case 151: /* insertion_list: LEFT_SHIFT ENDL  */
#line 2203 "src/parser.y"
                          {
            dbg("insertion_list -> LEFT_SHIFT ENDL");
          Node* n = new Node();
          n->code.push_back("print newline"); 
          (yyval.node) = n;
      }
#line 4163 "src/parser.tab.c"
    break;

  case 152: /* insertion_list: insertion_list LEFT_SHIFT ENDL  */
#line 2209 "src/parser.y"
                                         {
            dbg("insertion_list -> insertion_list LEFT_SHIFT ENDL");
          Node* n = (yyvsp[-2].node); 
          n->code.push_back("print newline"); 
          (yyval.node) = n;
      }
#line 4174 "src/parser.tab.c"
    break;

  case 153: /* insertion_list: insertion_list LEFT_SHIFT assignment_expression  */
#line 2215 "src/parser.y"
                                                          {
            dbg("insertion_list -> insertion_list LEFT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("print " + e->place); (yyval.node) = n;
      }
#line 4185 "src/parser.tab.c"
    break;

  case 154: /* cin_expression: CIN extraction_list  */
#line 2225 "src/parser.y"
                          { 
        dbg("cin_expression -> CIN extraction_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4193 "src/parser.tab.c"
    break;

  case 155: /* extraction_list: RIGHT_SHIFT assignment_expression  */
#line 2232 "src/parser.y"
                                        {
            dbg("extraction_list -> RIGHT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node); 
          Node* n = new Node();
          n->code = e->code; 
          n->code.push_back("read " + e->place); 
          (yyval.node) = n;
      }
#line 4206 "src/parser.tab.c"
    break;

  case 156: /* extraction_list: extraction_list RIGHT_SHIFT assignment_expression  */
#line 2240 "src/parser.y"
                                                        {
            dbg("extraction_list -> extraction_list RIGHT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); 
          Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("read " + e->place); 
          (yyval.node) = n;
      }
#line 4219 "src/parser.tab.c"
    break;

  case 157: /* labeled_statement: IDENTIFIER COLON  */
#line 2252 "src/parser.y"
                           {
            dbg("labeled_statement -> IDENTIFIER :");
            if(!declareSymbol(string((yyvsp[-1].str)),string("label"))){
                yyerror("Duplicate '" + string((yyvsp[-1].str)) + "' in same function.");
            }
            Node* s = new Node();
            string label = string((yyvsp[-1].str));
            s->code.push_back(label + ":");
          (yyval.node) = s;
        }
#line 4234 "src/parser.tab.c"
    break;

  case 158: /* compound_statement: LCURLY RCURLY  */
#line 2266 "src/parser.y"
                        {
            dbg("compound_statement -> { }");
          Node* n = new Node();
          (yyval.node) = n;
      }
#line 4244 "src/parser.tab.c"
    break;

  case 159: /* $@3: %empty  */
#line 2271 "src/parser.y"
                 { pushScope();}
#line 4250 "src/parser.tab.c"
    break;

  case 160: /* compound_statement: LCURLY $@3 statement_list RCURLY  */
#line 2271 "src/parser.y"
                                                       {
            dbg("compound_statement -> { statement_list }");
          Node* n = (yyvsp[-1].node);
          popScope();
          (yyval.node) = n;
      }
#line 4261 "src/parser.tab.c"
    break;

  case 161: /* statement_list: block_item  */
#line 2281 "src/parser.y"
                     { 
        dbg("statement_list -> block_item");
        (yyval.node) = (yyvsp[0].node); }
#line 4269 "src/parser.tab.c"
    break;

  case 162: /* statement_list: statement_list block_item  */
#line 2284 "src/parser.y"
                                    {
            dbg("statement_list -> statement_list block_item");
          Node* n = (yyvsp[-1].node);
          if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 4280 "src/parser.tab.c"
    break;

  case 163: /* block_item: statement  */
#line 2294 "src/parser.y"
                { 
        dbg("block_item -> statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4288 "src/parser.tab.c"
    break;

  case 164: /* block_item: declaration  */
#line 2297 "src/parser.y"
                  { 
        dbg("block_item -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4296 "src/parser.tab.c"
    break;

  case 165: /* block_item: error SEMICOLON  */
#line 2300 "src/parser.y"
                      { yyerrok;}
#line 4302 "src/parser.tab.c"
    break;

  case 166: /* expression_statement: SEMICOLON  */
#line 2304 "src/parser.y"
                    { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4310 "src/parser.tab.c"
    break;

  case 167: /* expression_statement: expression SEMICOLON  */
#line 2307 "src/parser.y"
                               { 
        dbg("expression_statement -> expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4318 "src/parser.tab.c"
    break;

  case 168: /* selection_statement: IF LROUND expression RROUND statement  */
#line 2313 "src/parser.y"
                                                                      {
          dbg("selection_statement -> if ( expression ) statement");
          string Ltrue = newLabel();
          string Lend  = newLabel();
          Node* e = (yyvsp[-2].node);
          Node* s1 = (yyvsp[0].node);
          Node* n = new Node();
          n->code = e->code;
          n->code.push_back("if " + e->place + " goto " + Ltrue);
          n->code.push_back("goto " + Lend);
          n->code.push_back(Ltrue + ":");
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4338 "src/parser.tab.c"
    break;

  case 169: /* selection_statement: IF LROUND expression RROUND statement ELSE statement  */
#line 2328 "src/parser.y"
                                                               {
            dbg("selection_statement -> if ( expression ) statement else statement");

          string Ltrue = newLabel();
          string Lfalse = newLabel();
          string Lend  = newLabel();

          Node* e = (yyvsp[-4].node);
          Node* s1 = (yyvsp[-2].node);
          Node* s2 = (yyvsp[0].node);

          Node* n = new Node();
          n->code = e->code;
          n->code.push_back("if " + e->place + " goto " + Ltrue);
          n->code.push_back("goto " + Lfalse);

          n->code.push_back(Ltrue + ":");
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          n->code.push_back("goto " + Lend);
    
          n->code.push_back(Lfalse + ":");
          n->code.insert(n->code.end(), s2->code.begin(), s2->code.end());
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4368 "src/parser.tab.c"
    break;

  case 170: /* iteration_statement: WHILE LROUND expression RROUND statement  */
#line 2359 "src/parser.y"
                                                   {
          dbg("iteration_statement -> WHILE ( expression ) statement");
          Node* cond = (yyvsp[-2].node); Node* body = (yyvsp[0].node);
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back(Lbegin + ":");
          n->code.push_back("ifFalse " + cond->place + " goto " + Lend);
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.push_back("goto " + Lbegin);
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4386 "src/parser.tab.c"
    break;

  case 171: /* iteration_statement: UNTIL LROUND expression RROUND statement  */
#line 2372 "src/parser.y"
                                                   {
            dbg("iteration_statement -> UNTIL ( expression ) statement");
          Node* cond = (yyvsp[-2].node); Node* body = (yyvsp[0].node);
          Node* n = new Node();
          string Lbegin = newLabel();
          n->code.push_back(Lbegin + ":");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back("ifTrue " + cond->place + " goto " + Lbegin);
          (yyval.node) = n;
      }
#line 4402 "src/parser.tab.c"
    break;

  case 172: /* iteration_statement: DO statement WHILE LROUND expression RROUND SEMICOLON  */
#line 2383 "src/parser.y"
                                                                {
            dbg("iteration_statement -> DO statement WHILE ( expression ) ;");
          Node* body = (yyvsp[-5].node); Node* cond = (yyvsp[-2].node);
          Node* n = new Node();
          string Lbegin = newLabel();
          n->code.push_back(Lbegin + ":");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back("ifTrue " + cond->place + " goto " + Lbegin);
          (yyval.node) = n;
      }
#line 4418 "src/parser.tab.c"
    break;

  case 173: /* iteration_statement: FOR LROUND for_init_statement expression_statement RROUND statement  */
#line 2394 "src/parser.y"
                                                                              {
            dbg("iteration_statement -> FOR ( for_init_statement expression_statement ) statement");
          Node* init = (yyvsp[-3].node); Node* cond = (yyvsp[-2].node); Node* body = (yyvsp[0].node);
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
          n->code.push_back(Lbegin + ":");
          if (cond) {
              n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
              n->code.push_back("ifFalse " + cond->place + " goto " + Lend);
          }
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.push_back("goto " + Lbegin);
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4439 "src/parser.tab.c"
    break;

  case 174: /* iteration_statement: FOR LROUND for_init_statement expression_statement expression RROUND statement  */
#line 2410 "src/parser.y"
                                                                                         {
            dbg("iteration_statement -> FOR ( for_init_statement expression_statement expression ) statement");
          Node* init = (yyvsp[-4].node); Node* cond = (yyvsp[-3].node); Node* iter = (yyvsp[-2].node); Node* body = (yyvsp[0].node);
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
          n->code.push_back(Lbegin + ":");
          if (cond) {
              n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
              n->code.push_back("ifFalse " + cond->place + " goto " + Lend);
          }
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          if (iter) n->code.insert(n->code.end(), iter->code.begin(), iter->code.end());
          n->code.push_back("goto " + Lbegin);
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4461 "src/parser.tab.c"
    break;

  case 175: /* for_init_statement: expression_statement  */
#line 2430 "src/parser.y"
                               { 
        dbg("for_init_statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4469 "src/parser.tab.c"
    break;

  case 176: /* for_init_statement: declaration  */
#line 2433 "src/parser.y"
                      { 
        dbg("for_init_statement -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4477 "src/parser.tab.c"
    break;

  case 177: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 2440 "src/parser.y"
                                    {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string((yyvsp[-1].str)));
          (yyval.node) = n;
      }
#line 4488 "src/parser.tab.c"
    break;

  case 178: /* jump_statement: CONTINUE SEMICOLON  */
#line 2446 "src/parser.y"
                             {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); 
          n->code.push_back("continue;"); 
          (yyval.node) = n;
      }
#line 4499 "src/parser.tab.c"
    break;

  case 179: /* jump_statement: BREAK SEMICOLON  */
#line 2452 "src/parser.y"
                          {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); 
          n->code.push_back("break;"); 
          (yyval.node) = n;
      }
#line 4510 "src/parser.tab.c"
    break;

  case 180: /* jump_statement: RETURN SEMICOLON  */
#line 2458 "src/parser.y"
                           {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); 
          n->code.push_back("return;"); 
          (yyval.node) = n;
      }
#line 4521 "src/parser.tab.c"
    break;

  case 181: /* jump_statement: RETURN expression SEMICOLON  */
#line 2464 "src/parser.y"
                                      {
            dbg("jump_statement -> RETURN expression ;");
          Node* expr = (yyvsp[-1].node);
          Node* n = new Node();
          n->code = expr->code;
          n->code.push_back("return " + expr->place);
          (yyval.node) = n;
      }
#line 4534 "src/parser.tab.c"
    break;

  case 182: /* translation_unit: external_declaration  */
#line 2476 "src/parser.y"
                               { 
        dbg("translation_unit -> external_declaration");
        finalRoot = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 4542 "src/parser.tab.c"
    break;

  case 183: /* translation_unit: translation_unit external_declaration  */
#line 2479 "src/parser.y"
                                                {
            dbg("translation_unit -> translation_unit external_declaration");
          Node* a = (yyvsp[-1].node); Node* b = (yyvsp[0].node);
          if (a) { 
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; (yyval.node) = a; }
          else { finalRoot = b; (yyval.node) = b; }
      }
#line 4555 "src/parser.tab.c"
    break;

  case 184: /* external_declaration: function_definition  */
#line 2491 "src/parser.y"
                              { 
        dbg("external_declaration -> function_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 4563 "src/parser.tab.c"
    break;

  case 185: /* external_declaration: struct_or_class_specifier SEMICOLON  */
#line 2494 "src/parser.y"
                                              { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4571 "src/parser.tab.c"
    break;

  case 186: /* external_declaration: declaration  */
#line 2497 "src/parser.y"
                      {
        dbg("external_declaration -> declaration");
         (yyval.node) = (yyvsp[0].node); }
#line 4579 "src/parser.tab.c"
    break;

  case 187: /* external_declaration: TYPEDEF return_type IDENTIFIER SEMICOLON  */
#line 2500 "src/parser.y"
                                               {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string((yyvsp[-1].str))] = typeSize[string((yyvsp[-2].str))];
        (yyval.node) = new Node();
        }
#line 4589 "src/parser.tab.c"
    break;

  case 188: /* function_header: return_type IDENTIFIER LROUND RROUND  */
#line 2510 "src/parser.y"
        {
            dbg("function_header -> return_type IDENTIFIER ( )");
            string fname = string((yyvsp[-2].str));

            if(funcTable.find(fname)!=funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string((yyvsp[-3].str)) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;

            funcTable[fname].returnType = string((yyvsp[-3].str));
            funcTable[fname].paramCount = 0;
            // dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");
            // dbg("Function '" + fname + "' with " + to_string(funcTable[fname].paramCount) + " parameters declared.");
            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            currentFunction = fname;
            localTemp = 0; localLabel = 0;
            Node* n = new Node();
            n->code.push_back(fname + ":");

            pushScope(); 
            (yyval.node) = n;
        }
#line 4618 "src/parser.tab.c"
    break;

  case 189: /* function_header: return_type IDENTIFIER LROUND parameter_list RROUND  */
#line 2536 "src/parser.y"
        {
            dbg("function_definition -> return_type IDENTIFIER ( parameter_list ) compound_statement");
            string fname = string((yyvsp[-3].str));

            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            for (int i=0;i<(yyvsp[-1].node)->syn.size();i+=2)
            {
                fname += "_" + (yyvsp[-1].node)->syn[i];
            }


            if(funcTable.find(fname) != funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string((yyvsp[-4].str)) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;
                       
            funcTable[fname].returnType = string((yyvsp[-4].str)); 
            funcTable[fname].paramCount = (yyvsp[-1].node)->syn.size()/2;
            dbg("");
            dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");

            for (int i=0;i<(yyvsp[-1].node)->syn.size();i+=2){
                funcTable[fname].paramTypes.push_back((yyvsp[-1].node)->syn[i]);
                dbg("Parameter: " + (yyvsp[-1].node)->syn[i+1] + " of type " + (yyvsp[-1].node)->syn[i]);
            }
            dbg("");
            
            currentFunction = fname;
            localTemp = 0; localLabel = 0;
            Node* n = new Node();            
            n->code.push_back(fname + ":");
            pushScope(); 

            for(int i=1;i<(yyvsp[-1].node)->syn.size();i+=2){
                string pname = (yyvsp[-1].node)->syn[i];
                string ptype = (yyvsp[-1].node)->syn[i-1];
                bool ok = declareSymbol(pname,ptype);
                if(!ok) yyerror("Duplicate parameter name '" + pname + "' in function '" + fname + "'.");
            }
            (yyval.node) = n;
        }
#line 4666 "src/parser.tab.c"
    break;

  case 190: /* function_definition: function_header compound_statement  */
#line 2583 "src/parser.y"
                                        {
            dbg("function_definition -> function_header compound_statement");
            Node* n = (yyvsp[-1].node);
            if((yyvsp[0].node)) n->code.insert(n->code.end(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end()); 
            popScope(); 
            finalRoot = n;
            currentFunction = "global";
            (yyval.node) = n;
        }
#line 4680 "src/parser.tab.c"
    break;

  case 191: /* function_definition: error RCURLY  */
#line 2592 "src/parser.y"
                   { yyerrok;}
#line 4686 "src/parser.tab.c"
    break;

  case 192: /* return_type: type_specifier pointer_opt  */
#line 2598 "src/parser.y"
    { 
        dbg("return_type -> type_specifier pointer_opt");
        (yyval.str) = strdup( (string((yyvsp[-1].str)) + string((yyvsp[0].str))).c_str() );
    }
#line 4695 "src/parser.tab.c"
    break;


#line 4699 "src/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2661 "src/parser.y"



#include <cstdio>
#include "parser.tab.h"
extern int yydebug;
void yyerror(const char *s);

int main(int argc, char** argv){
    yydebug = 0;
    pushScope();
    if(yyparse()) cerr << "Parsing failed.\n";
    else cerr << "Parsing completed successfully.\n"; 

    if(!errors.empty()){
        cout<<"---- Errors found ----\n";
        for(auto &e:errors) cout<<e<<"\n";
        return 1;
    }

    if(finalRoot){
        for(int i=0;i<finalRoot->code.size();i++) {
            cout<<"["<<(i+1)<<"] "<<finalRoot->code[i]<<"\n";
        }
    }

    return 0;
}

