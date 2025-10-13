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

    ofstream dbgfile("debug.txt");
    void dbg(const string &msg) {
        dbgfile << "Debug: " << msg << endl;
    }


#line 364 "src/parser.tab.c"

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
  YYSYMBOL_STRING = 71,                    /* STRING  */
  YYSYMBOL_LONG = 72,                      /* LONG  */
  YYSYMBOL_TRUE = 73,                      /* TRUE  */
  YYSYMBOL_FALSE = 74,                     /* FALSE  */
  YYSYMBOL_NULLPTR = 75,                   /* NULLPTR  */
  YYSYMBOL_AUTO = 76,                      /* AUTO  */
  YYSYMBOL_STATIC = 77,                    /* STATIC  */
  YYSYMBOL_CONST = 78,                     /* CONST  */
  YYSYMBOL_CLASS = 79,                     /* CLASS  */
  YYSYMBOL_STRUCT = 80,                    /* STRUCT  */
  YYSYMBOL_PUBLIC = 81,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 82,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 83,                 /* PROTECTED  */
  YYSYMBOL_DELETE = 84,                    /* DELETE  */
  YYSYMBOL_NEW = 85,                       /* NEW  */
  YYSYMBOL_CIN = 86,                       /* CIN  */
  YYSYMBOL_COUT = 87,                      /* COUT  */
  YYSYMBOL_ENDL = 88,                      /* ENDL  */
  YYSYMBOL_IDENTIFIER = 89,                /* IDENTIFIER  */
  YYSYMBOL_INVALID_IDENTIFIER = 90,        /* INVALID_IDENTIFIER  */
  YYSYMBOL_DECIMAL_LITERAL = 91,           /* DECIMAL_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 92,            /* DOUBLE_LITERAL  */
  YYSYMBOL_EXPONENT_LITERAL = 93,          /* EXPONENT_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 94,         /* CHARACTER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 95,            /* STRING_LITERAL  */
  YYSYMBOL_LOWER_THAN_ELSE = 96,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 97,                  /* $accept  */
  YYSYMBOL_primary_expression = 98,        /* primary_expression  */
  YYSYMBOL_constant = 99,                  /* constant  */
  YYSYMBOL_postfix_expression = 100,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 101, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 102,         /* unary_expression  */
  YYSYMBOL_unary_operator = 103,           /* unary_operator  */
  YYSYMBOL_new_expression = 104,           /* new_expression  */
  YYSYMBOL_new_square = 105,               /* new_square  */
  YYSYMBOL_delete_expression = 106,        /* delete_expression  */
  YYSYMBOL_cast_expression = 107,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 108, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 109,      /* additive_expression  */
  YYSYMBOL_shift_expression = 110,         /* shift_expression  */
  YYSYMBOL_relational_expression = 111,    /* relational_expression  */
  YYSYMBOL_equality_expression = 112,      /* equality_expression  */
  YYSYMBOL_and_expression = 113,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 114,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 115,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 116,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 117,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 118,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 119,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 120,      /* assignment_operator  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_constant_expression = 122,      /* constant_expression  */
  YYSYMBOL_declaration = 123,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 124,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 125,     /* init_declarator_list  */
  YYSYMBOL_pointer_opt = 126,              /* pointer_opt  */
  YYSYMBOL_pointer_list = 127,             /* pointer_list  */
  YYSYMBOL_init_declarator = 128,          /* init_declarator  */
  YYSYMBOL_initializer = 129,              /* initializer  */
  YYSYMBOL_initializer_list = 130,         /* initializer_list  */
  YYSYMBOL_square_list = 131,              /* square_list  */
  YYSYMBOL_static_opt = 132,               /* static_opt  */
  YYSYMBOL_type_specifier = 133,           /* type_specifier  */
  YYSYMBOL_struct_or_class_specifier = 134, /* struct_or_class_specifier  */
  YYSYMBOL_135_1 = 135,                    /* $@1  */
  YYSYMBOL_struct_or_class = 136,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 137, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 138,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 139,   /* access_specifier_label  */
  YYSYMBOL_member_declaration = 140,       /* member_declaration  */
  YYSYMBOL_141_2 = 141,                    /* $@2  */
  YYSYMBOL_struct_declarator_list = 142,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 143,        /* struct_declarator  */
  YYSYMBOL_const_opt = 144,                /* const_opt  */
  YYSYMBOL_parameter_list = 145,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 146,    /* parameter_declaration  */
  YYSYMBOL_statement = 147,                /* statement  */
  YYSYMBOL_io_statement = 148,             /* io_statement  */
  YYSYMBOL_cout_expression = 149,          /* cout_expression  */
  YYSYMBOL_insertion_list = 150,           /* insertion_list  */
  YYSYMBOL_cin_expression = 151,           /* cin_expression  */
  YYSYMBOL_extraction_list = 152,          /* extraction_list  */
  YYSYMBOL_labeled_statement = 153,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 154,       /* compound_statement  */
  YYSYMBOL_155_3 = 155,                    /* $@3  */
  YYSYMBOL_statement_list = 156,           /* statement_list  */
  YYSYMBOL_block_item = 157,               /* block_item  */
  YYSYMBOL_expression_statement = 158,     /* expression_statement  */
  YYSYMBOL_selection_statement = 159,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 160,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 161,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 162,           /* jump_statement  */
  YYSYMBOL_translation_unit = 163,         /* translation_unit  */
  YYSYMBOL_external_declaration = 164,     /* external_declaration  */
  YYSYMBOL_function_header = 165,          /* function_header  */
  YYSYMBOL_function_definition = 166,      /* function_definition  */
  YYSYMBOL_return_type = 167               /* return_type  */
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
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1153

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  329

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   351


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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   380,   380,   406,   411,   423,   433,   442,   448,   454,
     460,   465,   470,   478,   483,   535,   561,   613,   641,   682,
     701,   723,   741,   762,   765,   780,   795,   830,   841,   851,
     854,   861,   864,   867,   870,   873,   876,   883,   896,   910,
     919,   934,   941,   952,   955,   972,   975,   988,  1002,  1020,
    1023,  1037,  1055,  1058,  1072,  1090,  1093,  1105,  1117,  1129,
    1145,  1148,  1161,  1178,  1181,  1198,  1201,  1218,  1221,  1238,
    1241,  1258,  1261,  1277,  1282,  1304,  1307,  1335,  1338,  1341,
    1344,  1347,  1350,  1353,  1356,  1359,  1362,  1365,  1372,  1377,
    1390,  1399,  1408,  1417,  1422,  1433,  1439,  1447,  1452,  1461,
    1505,  1569,  1617,  1669,  1723,  1863,  1872,  1879,  1897,  1911,
    1929,  1932,  1939,  1942,  1945,  1948,  1951,  1954,  1957,  1960,
    1968,  1967,  1987,  1993,  2004,  2008,  2018,  2024,  2032,  2039,
    2046,  2056,  2056,  2061,  2076,  2081,  2091,  2100,  2103,  2110,
    2114,  2125,  2137,  2140,  2143,  2146,  2149,  2152,  2155,  2162,
    2165,  2172,  2179,  2187,  2193,  2199,  2209,  2216,  2224,  2236,
    2250,  2255,  2255,  2265,  2268,  2278,  2281,  2284,  2288,  2291,
    2297,  2312,  2343,  2356,  2367,  2378,  2394,  2414,  2417,  2424,
    2430,  2436,  2442,  2448,  2460,  2463,  2475,  2478,  2481,  2484,
    2493,  2519,  2567,  2576,  2581
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
  "STRING", "LONG", "TRUE", "FALSE", "NULLPTR", "AUTO", "STATIC", "CONST",
  "CLASS", "STRUCT", "PUBLIC", "PRIVATE", "PROTECTED", "DELETE", "NEW",
  "CIN", "COUT", "ENDL", "IDENTIFIER", "INVALID_IDENTIFIER",
  "DECIMAL_LITERAL", "DOUBLE_LITERAL", "EXPONENT_LITERAL",
  "CHARACTER_LITERAL", "STRING_LITERAL", "LOWER_THAN_ELSE", "$accept",
  "primary_expression", "constant", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "new_expression", "new_square", "delete_expression", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
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

#define YYPACT_NINF (-186)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-112)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     888,    12,    60,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,    -1,   -51,    66,    -6,     0,
     487,  -186,    59,  -186,    17,  -186,    28,  -186,    13,    25,
       9,  -186,  -186,    60,  -186,   113,  -186,   100,  -186,  -186,
     109,  -186,   120,   116,  1007,  1007,    14,  -186,    -1,  -186,
     152,  -186,  -186,  -186,   342,    44,  -186,  -186,  -186,  -186,
    1058,  1058,  -186,  -186,   433,  -186,   128,  -186,  -186,  -186,
     664,    60,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
       7,   245,  1007,  -186,  -186,  -186,   115,    37,   122,   117,
     135,   168,   170,   172,   169,   -15,  -186,  -186,  -186,  -186,
     151,   158,  1007,  -186,  1007,  -186,   155,  -186,   162,   163,
     594,   164,   119,   159,   160,   715,   171,   185,   188,   166,
    -186,    45,  -186,  -186,  -186,   173,   174,  -186,  -186,   247,
    -186,  -186,  -186,  -186,  -186,  -186,   -17,  -186,   126,  1007,
    -186,  -186,   -14,   176,   524,   178,  -186,   177,  -186,  -186,
     134,   755,  1007,   136,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  1007,  -186,  1007,  1007,  1007,
    1007,  1007,  1007,  1007,  1007,  1007,  1007,  1007,  1007,  1007,
    1007,  1007,  1007,  1007,  1007,  1007,  -186,  1007,  -186,   183,
    -186,  1043,  -186,  1007,  1007,   179,     2,   186,  -186,  -186,
    -186,    62,  1007,  1007,   204,   806,   207,  -186,  -186,  1007,
    -186,  -186,  -186,  -186,  -186,    60,  -186,  -186,  1007,   193,
     194,  1007,  1007,   192,  -186,  -186,   -11,  -186,   -26,  -186,
    -186,  -186,  -186,  -186,   115,   115,    37,    37,   122,   122,
     122,   122,   117,   117,   135,   168,   170,   172,   169,   107,
    -186,    57,  -186,  -186,   191,   197,   198,  -186,  -186,  -186,
      60,    59,    -9,    -5,   199,  -186,  -186,   857,  -186,  -186,
      11,  -186,  1007,  -186,  -186,   897,  -186,  -186,  -186,  -186,
    -186,  -186,    -7,  1007,  -186,  1007,  -186,  1007,  -186,  1007,
    -186,  -186,  -186,  -186,  -186,   594,   594,  1007,   967,   594,
    -186,  -186,  -186,  -186,    36,  -186,  -186,  -186,    -1,   187,
    -186,    19,   594,    31,  -186,  -186,  -186,    73,  -186,   594,
     202,  -186,   594,  -186,    -1,  -186,  -186,  -186,  -186
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   119,   112,   114,   116,   113,   117,   118,
     115,   110,   123,   122,   188,     0,   138,    96,     0,     0,
       0,   184,     0,   186,     0,   193,     0,    98,    99,     0,
       0,    93,   137,     0,   194,    95,   187,     0,     1,   185,
     161,   192,     0,     0,     0,     0,   100,    91,     0,    97,
     101,    92,   120,   160,     0,     0,   189,    33,    34,    32,
       0,     0,    31,    36,     0,    35,     0,    11,    12,    10,
       0,     0,     2,     5,     9,     8,     6,     7,    13,     3,
      23,    43,     0,    30,    29,    45,    49,    52,    55,    60,
      63,    65,    67,    69,    71,    73,    75,   102,    43,    90,
       0,     0,     0,    94,     0,   124,     0,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
      88,     0,   166,   165,   148,     0,     0,   142,   143,     0,
     163,   144,   145,   146,   147,   190,     0,   139,     0,     0,
      24,    25,     0,     0,     0,     0,    42,    38,    19,    20,
       0,     0,     0,     0,    77,    81,    82,    78,    79,    80,
      85,    87,    86,    83,    84,     0,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   109,     0,   104,     0,
     103,     0,   167,     0,     0,     0,   111,     0,   180,   181,
     182,     0,     0,     0,   156,     0,   151,   159,   169,     0,
     149,   150,   162,   164,   191,     0,   141,     4,     0,     0,
       0,     0,     0,    37,    18,    15,     0,    21,     0,    17,
      76,    46,    47,    48,    50,    51,    53,    54,    57,    56,
      58,    59,    61,    62,    64,    66,    68,    70,    72,     0,
     106,     0,   108,   121,     0,     0,     0,   125,   126,   127,
       0,     0,     0,     0,     0,   178,   177,     0,   179,   183,
       0,   157,     0,   153,   152,     0,    89,   140,    44,    27,
      28,    41,     0,     0,    16,     0,    14,     0,   105,     0,
     128,   129,   130,   131,   133,     0,     0,     0,     0,     0,
     158,   154,   155,    39,     0,    22,    74,   107,     0,   170,
     172,     0,     0,     0,   173,    40,   136,     0,   134,     0,
       0,   175,     0,   132,     0,   171,   174,   176,   135
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,  -186,  -186,  -186,  -186,     3,  -186,  -186,  -186,  -186,
     -66,   -13,    -8,   -37,   -10,    69,    58,    68,    74,    67,
    -186,   -42,   -43,  -186,     4,   161,   -48,  -186,  -186,  -186,
     244,    -3,  -186,  -186,  -186,  -186,   229,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,   -60,    75,  -186,    50,
    -105,  -186,  -186,  -186,  -186,  -186,  -186,   -20,  -186,  -186,
     139,  -185,  -186,  -186,  -186,  -186,  -186,   249,    79,  -186,
      -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    78,    79,    80,   226,    81,    82,    83,   223,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,   120,   165,   121,   100,    14,    15,    29,    34,
      30,   316,   188,   251,    46,    16,    17,    18,   105,    19,
     191,   257,   258,   259,   308,   317,   318,    33,   136,   137,
     123,   124,   125,   206,   126,   204,   127,   128,    54,   129,
     130,   131,   132,   133,   267,   134,    20,    21,    22,    23,
      24
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,    97,    41,    99,   146,   195,   122,    27,    57,    58,
      59,   266,    31,   184,    60,    61,   166,    49,   286,   148,
     149,   209,    62,   214,    44,   101,   217,    32,    63,   284,
     215,   295,   150,   209,   185,   296,   285,   303,   209,    36,
     209,    64,   209,   170,   171,   103,   151,   107,    98,     3,
     152,   299,    65,   138,    25,   153,    45,   102,   209,   320,
      99,   190,   143,   140,   141,     3,   209,    66,   142,   147,
      47,   322,    48,    98,    27,    67,    68,    69,   209,    11,
     315,   122,   298,   209,   135,    98,    70,    71,    28,    37,
     208,    72,   209,    73,    74,    75,    76,    77,    50,   288,
      40,   231,   232,   233,   289,    98,    42,   269,   227,   209,
       4,     5,     6,     7,     8,     9,    10,    43,   323,   201,
     324,    49,   230,   167,   168,   169,     4,     5,     6,     7,
       8,     9,    10,   174,   175,   176,   177,   238,   239,   240,
     241,    52,   220,   142,   250,   172,   173,   219,   265,   178,
     179,    53,   278,   287,   209,   281,   228,   234,   235,    55,
     271,    56,   274,   104,   236,   237,   276,   144,   242,   243,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,   180,   249,
     309,   310,   181,   182,   314,   186,   183,   262,   263,   187,
     192,   193,   194,   196,   198,   199,   270,   321,   197,   203,
     202,   205,   207,   138,   325,   216,   218,   327,   210,   211,
     222,    98,   221,   224,    98,   229,   282,   252,   272,   300,
     275,   268,   302,   279,   280,   283,   264,   290,   297,   245,
     319,   294,   305,   291,   292,   306,   307,   326,   106,   244,
     246,   248,  -111,    57,    58,    59,   154,   247,   293,    60,
      61,    35,    51,   189,   328,   277,   260,    62,   213,    39,
     261,     0,     0,    63,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,     0,     0,    64,   304,    40,   212,
      98,     0,   107,     0,     0,     0,     0,    65,     0,   108,
       0,   311,   313,     0,   109,   110,   111,   112,   113,   114,
     115,   116,    66,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
      67,    68,    69,     0,    11,  -111,     0,     0,     0,     0,
       0,    70,    71,   117,   118,     0,   119,     0,    73,    74,
      75,    76,    77,   106,     0,     0,     0,  -111,    57,    58,
      59,     0,     0,     0,    60,    61,     0,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,    40,     0,     0,     0,   107,     0,     0,
       0,     0,    65,     0,   108,     0,     0,     0,     0,   109,
     110,   111,   112,   113,   114,   115,   116,    66,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,    67,    68,    69,     0,    11,
    -111,     0,     0,     0,     0,     0,    70,    71,   117,   118,
       0,   119,     0,    73,    74,    75,    76,    77,     3,    57,
      58,    59,     0,     0,     0,    60,    61,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,     0,     0,     0,    38,     1,     0,
       0,     2,     3,     0,     0,     0,     0,     0,    66,     4,
       5,     6,     7,     8,     9,    10,    67,    68,    69,     0,
       0,     0,     0,     0,     0,     0,     0,    70,    71,     0,
       0,     0,    72,     0,    73,    74,    75,    76,    77,     3,
      57,    58,    59,     0,     0,     0,    60,    61,     0,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,     0,
      63,     0,     0,     4,     5,     6,     7,     8,     9,    10,
       0,     0,     0,   139,    11,  -111,    12,    13,     0,     0,
       0,     0,     0,     0,    65,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    66,
       4,     5,     6,     7,     8,     9,    10,    67,    68,    69,
      57,    58,    59,     0,     0,     0,    60,    61,    70,    71,
       0,     0,     0,    72,    62,    73,    74,    75,    76,    77,
      63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,    40,     0,     0,     0,   107,
       0,     0,     0,     0,    65,     0,   108,     0,     0,     0,
       0,   109,   110,   111,   112,   113,   114,   115,   116,    66,
       0,     0,     0,     0,     0,     0,     0,    67,    68,    69,
      57,    58,    59,     0,     0,     0,    60,    61,    70,    71,
     117,   118,     0,   119,    62,    73,    74,    75,    76,    77,
      63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,   145,     0,     0,
       0,     0,     0,     0,    65,     0,     0,     0,     0,     0,
       0,    57,    58,    59,     0,     0,     0,    60,    61,    66,
       0,     0,     0,     0,     0,    62,     0,    67,    68,    69,
       0,    63,     0,     0,     0,     0,     0,     0,    70,    71,
       0,     0,     0,    72,    64,    73,    74,    75,    76,    77,
     200,    57,    58,    59,     0,    65,     0,    60,    61,     0,
       0,     0,     0,     0,     0,    62,     0,     0,     0,     0,
      66,    63,     0,     0,     0,     0,     0,     0,    67,    68,
      69,     0,     0,     0,    64,   225,     0,     0,     0,    70,
      71,     0,     0,     0,    72,    65,    73,    74,    75,    76,
      77,     0,    57,    58,    59,     0,     0,     0,    60,    61,
      66,     0,     0,     0,     0,     0,    62,     0,    67,    68,
      69,     0,    63,     0,     0,     0,     0,     0,     0,    70,
      71,     0,     0,     0,    72,    64,    73,    74,    75,    76,
      77,     0,     0,     0,     0,     0,    65,     0,     0,     0,
       0,     0,     0,    57,    58,    59,     0,     0,     0,    60,
      61,    66,     0,     0,     0,     0,     0,    62,     0,    67,
      68,    69,     0,    63,     0,     0,     0,     0,     0,     1,
      70,    71,     2,     3,   273,    72,    64,    73,    74,    75,
      76,    77,   107,    57,    58,    59,     0,    65,     0,    60,
      61,     0,     0,     0,     0,     0,     0,    62,     0,     0,
       0,     0,    66,    63,     0,     0,     0,     0,     0,     0,
      67,    68,    69,     0,     0,     0,    64,     0,     0,     0,
       0,    70,    71,     0,     0,     0,    72,    65,    73,    74,
      75,    76,    77,     0,     4,     5,     6,     7,     8,     9,
      10,     0,    66,     0,     0,    11,  -111,    12,    13,     0,
      67,    68,    69,    57,    58,    59,     0,     0,     0,    60,
      61,    70,    71,     0,     0,   301,    72,    62,    73,    74,
      75,    76,    77,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,   312,     0,     0,
       0,     0,     0,    57,    58,    59,     0,    65,     0,    60,
      61,     0,     0,     0,     0,     0,     0,    62,     0,     0,
       0,     0,    66,    63,     0,     0,     0,     0,     0,     0,
      67,    68,    69,     0,     0,     0,    64,     0,     3,     0,
       0,    70,    71,     0,     0,     0,    72,    65,    73,    74,
      75,    76,    77,     0,    57,    58,    59,     0,     0,     0,
      60,    61,    66,     0,     0,     0,     0,     0,    62,     0,
      67,    68,    69,     0,    63,   253,     0,     0,     0,     0,
       0,    70,    71,     0,     0,     0,    72,   139,    73,    74,
      75,    76,    77,     0,     0,     0,     0,     0,    65,     4,
       5,     6,     7,     8,     9,    10,     0,     0,     0,     0,
       0,    32,     0,    66,   254,   255,   256,     0,     0,     0,
       0,    67,    68,    69,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    71,     0,     0,     0,    72,     0,    73,
      74,    75,    76,    77
};

static const yytype_int16 yycheck[] =
{
       2,    44,    22,    45,    70,   110,    54,     8,     6,     7,
       8,   196,    15,    28,    12,    13,    82,     8,    44,    12,
      13,    47,    20,    40,    11,    11,    40,    78,    26,    40,
      47,    40,    25,    47,    49,    40,    47,    44,    47,    45,
      47,    39,    47,     6,     7,    48,    39,    45,    45,     5,
      43,    40,    50,    55,    42,    48,    43,    43,    47,    40,
     102,   104,    64,    60,    61,     5,    47,    65,    64,    71,
      45,    40,    47,    70,     8,    73,    74,    75,    47,    77,
      44,   129,   267,    47,    40,    82,    84,    85,    89,    89,
      45,    89,    47,    91,    92,    93,    94,    95,    89,    42,
      41,   167,   168,   169,    47,   102,    89,    45,   151,    47,
      66,    67,    68,    69,    70,    71,    72,    89,    45,   115,
      47,     8,   165,     8,     9,    10,    66,    67,    68,    69,
      70,    71,    72,    16,    17,    18,    19,   174,   175,   176,
     177,    41,   144,   139,   187,    23,    24,   144,   196,    14,
      15,    42,   218,    46,    47,   221,   152,   170,   171,    39,
     203,    45,   205,    11,   172,   173,   209,    39,   178,   179,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,    20,   185,
     295,   296,    22,    21,   299,    44,    27,   193,   194,    41,
      45,    39,    39,    39,    45,    45,   202,   312,    89,    24,
      39,    23,    46,   215,   319,    89,    40,   322,    45,    45,
      43,   218,    44,    89,   221,    89,   222,    44,    24,   272,
      23,    45,   275,    40,    40,    43,    57,    46,    39,   181,
      53,   261,   285,    46,    46,   287,   289,    45,     1,   180,
     182,   184,     5,     6,     7,     8,    11,   183,   260,    12,
      13,    17,    33,   102,   324,   215,   191,    20,   129,    20,
     191,    -1,    -1,    26,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    39,   283,    41,    42,
     287,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    52,
      -1,   297,   298,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    -1,    77,    78,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,    -1,    89,    -1,    91,    92,
      93,    94,    95,     1,    -1,    -1,    -1,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    52,    -1,    -1,    -1,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    77,
      78,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      -1,    89,    -1,    91,    92,    93,    94,    95,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,     0,     1,    -1,
      -1,     4,     5,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    89,    -1,    91,    92,    93,    94,    95,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      -1,    -1,    -1,    39,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      -1,    -1,    -1,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    41,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    50,    -1,    52,    -1,    -1,    -1,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      86,    87,    -1,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    -1,    -1,    -1,    12,    13,    65,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    73,    74,    75,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    89,    39,    91,    92,    93,    94,    95,
      45,     6,     7,     8,    -1,    50,    -1,    12,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      65,    26,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    89,    50,    91,    92,    93,    94,
      95,    -1,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      65,    -1,    -1,    -1,    -1,    -1,    20,    -1,    73,    74,
      75,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    89,    39,    91,    92,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    65,    -1,    -1,    -1,    -1,    -1,    20,    -1,    73,
      74,    75,    -1,    26,    -1,    -1,    -1,    -1,    -1,     1,
      84,    85,     4,     5,    88,    89,    39,    91,    92,    93,
      94,    95,    45,     6,     7,     8,    -1,    50,    -1,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    65,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    89,    50,    91,    92,
      93,    94,    95,    -1,    66,    67,    68,    69,    70,    71,
      72,    -1,    65,    -1,    -1,    77,    78,    79,    80,    -1,
      73,    74,    75,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    84,    85,    -1,    -1,    88,    89,    20,    91,    92,
      93,    94,    95,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    -1,    50,    -1,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    65,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    -1,    -1,    -1,    39,    -1,     5,    -1,
      -1,    84,    85,    -1,    -1,    -1,    89,    50,    91,    92,
      93,    94,    95,    -1,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    65,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      73,    74,    75,    -1,    26,    42,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    89,    39,    91,    92,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    50,    66,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    65,    81,    82,    83,    -1,    -1,    -1,
      -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    89,    -1,    91,
      92,    93,    94,    95
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     5,    66,    67,    68,    69,    70,    71,
      72,    77,    79,    80,   123,   124,   132,   133,   134,   136,
     163,   164,   165,   166,   167,    42,   167,     8,    89,   125,
     127,   128,    78,   144,   126,   127,    45,    89,     0,   164,
      41,   154,    89,    89,    11,    43,   131,    45,    47,     8,
      89,   133,    41,    42,   155,    39,    45,     6,     7,     8,
      12,    13,    20,    26,    39,    50,    65,    73,    74,    75,
      84,    85,    89,    91,    92,    93,    94,    95,    98,    99,
     100,   102,   103,   104,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   102,   118,
     122,    11,    43,   128,    11,   135,     1,    45,    52,    57,
      58,    59,    60,    61,    62,    63,    64,    86,    87,    89,
     119,   121,   123,   147,   148,   149,   151,   153,   154,   156,
     157,   158,   159,   160,   162,    40,   145,   146,   167,    39,
     102,   102,   121,   167,    39,    43,   107,   167,    12,    13,
      25,    39,    43,    48,    11,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,   120,   107,     8,     9,    10,
       6,     7,    23,    24,    16,    17,    18,    19,    14,    15,
      20,    22,    21,    27,    28,    49,    44,    41,   129,   122,
     119,   137,    45,    39,    39,   147,    39,    89,    45,    45,
      45,   121,    39,    24,   152,    23,   150,    46,    45,    47,
      45,    45,    42,   157,    40,    47,    89,    40,    40,   102,
     167,    44,    43,   105,    89,    40,   101,   119,   121,    89,
     119,   107,   107,   107,   108,   108,   109,   109,   110,   110,
     110,   110,   111,   111,   112,   113,   114,   115,   116,   121,
     119,   130,    44,    42,    81,    82,    83,   138,   139,   140,
     144,   165,   121,   121,    57,   123,   158,   161,    45,    45,
     121,   119,    24,    88,   119,    23,   119,   146,   107,    40,
      40,   107,   121,    43,    40,    47,    44,    46,    42,    47,
      46,    46,    46,   167,   154,    40,    40,    39,   158,    40,
     119,    88,   119,    44,   121,   119,   118,   119,   141,   147,
     147,   121,    40,   121,   147,    44,   128,   142,   143,    53,
      40,   147,    40,    45,    47,   147,    45,   147,   143
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    98,    98,    99,    99,    99,    99,    99,
      99,    99,    99,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   103,   103,   103,   103,   103,   103,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   108,   108,   108,   109,
     109,   109,   110,   110,   110,   111,   111,   111,   111,   111,
     112,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   121,   121,
     122,   123,   124,   125,   125,   126,   126,   127,   127,   128,
     128,   128,   128,   128,   128,   129,   130,   130,   131,   131,
     132,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     135,   134,   136,   136,   137,   137,   138,   138,   139,   139,
     139,   141,   140,   140,   142,   142,   143,   144,   144,   145,
     145,   146,   147,   147,   147,   147,   147,   147,   147,   148,
     148,   149,   150,   150,   150,   150,   151,   152,   152,   153,
     154,   155,   154,   156,   156,   157,   157,   157,   158,   158,
     159,   159,   160,   160,   160,   160,   160,   161,   161,   162,
     162,   162,   162,   162,   163,   163,   164,   164,   164,   164,
     165,   165,   166,   166,   167
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     3,     3,     2,
       2,     1,     3,     1,     2,     2,     2,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     3,
       4,     4,     2,     1,     4,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     5,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     3,     1,     3,     1,     0,     2,     1,     1,
       2,     2,     3,     4,     4,     3,     1,     3,     4,     3,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     1,     1,     0,     2,     1,     1,     2,     2,
       2,     0,     5,     2,     1,     3,     1,     1,     0,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     3,     3,     2,     2,     3,     2,
       2,     0,     4,     1,     2,     1,     1,     2,     1,     2,
       5,     7,     5,     5,     7,     6,     7,     1,     1,     3,
       2,     2,     2,     3,     1,     2,     1,     2,     1,     4,
       4,     5,     2,     2,     2
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
#line 381 "src/parser.y"
    {
        dbg("primary_expression -> IDENTIFIER");
        Node* n = new Node();
        string name = string((yyvsp[0].str));
        n->place = name;
        Symbol* sym = lookupSymbol(name);
        if (!sym) {
            yyerror("Use of undeclared identifier '" + name + "'.");
        } else {
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
#line 1973 "src/parser.tab.c"
    break;

  case 3: /* primary_expression: constant  */
#line 407 "src/parser.y"
    { 
        dbg("primary_expression -> constant");
        (yyval.node) = (yyvsp[0].node);
    }
#line 1982 "src/parser.tab.c"
    break;

  case 4: /* primary_expression: LROUND expression RROUND  */
#line 412 "src/parser.y"
    {
        dbg("primary_expression -> ( expression )");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1991 "src/parser.tab.c"
    break;

  case 5: /* constant: DECIMAL_LITERAL  */
#line 424 "src/parser.y"
    {
        dbg("constant -> DECIMAL_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "int", "const");
        n->argCount = stoi(string((yyvsp[0].str)));
        dbg("");
        dbg("Integer constant value: " + to_string(n->argCount));
        dbg("");
        (yyval.node) = n;
    }
#line 2005 "src/parser.tab.c"
    break;

  case 6: /* constant: CHARACTER_LITERAL  */
#line 434 "src/parser.y"
    {
        dbg("constant -> CHARACTER_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "char", "const");
        dbg("");
        dbg("Character constant value: " + string(1, (yyvsp[0].str)[1]));
        dbg("");
        (yyval.node) = n;
    }
#line 2018 "src/parser.tab.c"
    break;

  case 7: /* constant: STRING_LITERAL  */
#line 443 "src/parser.y"
    {
        dbg("constant -> STRING_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "string", "const");
        (yyval.node) = n;
    }
#line 2028 "src/parser.tab.c"
    break;

  case 8: /* constant: EXPONENT_LITERAL  */
#line 449 "src/parser.y"
    {
        dbg("constant -> EXPONENT_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "double", "const");
        (yyval.node) = n;
    }
#line 2038 "src/parser.tab.c"
    break;

  case 9: /* constant: DOUBLE_LITERAL  */
#line 455 "src/parser.y"
    {
        dbg("constant -> DOUBLE_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "double", "const");
        (yyval.node) = n;
    }
#line 2048 "src/parser.tab.c"
    break;

  case 10: /* constant: NULLPTR  */
#line 460 "src/parser.y"
                            {
            dbg("constant -> NULLPTR");
          Node* n = new Node("0", "nullptr", "const");
          (yyval.node) = n;
      }
#line 2058 "src/parser.tab.c"
    break;

  case 11: /* constant: TRUE  */
#line 465 "src/parser.y"
                            {
            dbg("constant -> TRUE");
          Node* n = new Node("1", "bool", "const");
          (yyval.node) = n;
      }
#line 2068 "src/parser.tab.c"
    break;

  case 12: /* constant: FALSE  */
#line 470 "src/parser.y"
                            {
            dbg("constant -> FALSE");
          Node* n = new Node("0", "bool", "const");
          (yyval.node) = n;
      }
#line 2078 "src/parser.tab.c"
    break;

  case 13: /* postfix_expression: primary_expression  */
#line 479 "src/parser.y"
    { 
        dbg("postfix_expression -> primary_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 2087 "src/parser.tab.c"
    break;

  case 14: /* postfix_expression: postfix_expression LSQUARE expression RSQUARE  */
#line 484 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression [ expression ]");
        Node* base = (yyvsp[-3].node); 
        Node* idx = (yyvsp[-1].node);
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
        Node* n = new Node();
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
        (yyval.node) = n;
    }
#line 2143 "src/parser.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression LROUND RROUND  */
#line 536 "src/parser.y"
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
#line 2173 "src/parser.tab.c"
    break;

  case 16: /* postfix_expression: postfix_expression LROUND argument_expression_list RROUND  */
#line 562 "src/parser.y"
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
#line 2229 "src/parser.tab.c"
    break;

  case 17: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 613 "src/parser.y"
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
#line 2262 "src/parser.tab.c"
    break;

  case 18: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 641 "src/parser.y"
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
#line 2308 "src/parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression INCREMENT  */
#line 682 "src/parser.y"
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
#line 2332 "src/parser.tab.c"
    break;

  case 20: /* postfix_expression: postfix_expression DECREMENT  */
#line 701 "src/parser.y"
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
#line 2355 "src/parser.tab.c"
    break;

  case 21: /* argument_expression_list: assignment_expression  */
#line 724 "src/parser.y"
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
#line 2377 "src/parser.tab.c"
    break;

  case 22: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 742 "src/parser.y"
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
#line 2398 "src/parser.tab.c"
    break;

  case 23: /* unary_expression: postfix_expression  */
#line 762 "src/parser.y"
                             { 
        dbg("unary_expression -> postfix_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2406 "src/parser.tab.c"
    break;

  case 24: /* unary_expression: INCREMENT unary_expression  */
#line 765 "src/parser.y"
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
#line 2426 "src/parser.tab.c"
    break;

  case 25: /* unary_expression: DECREMENT unary_expression  */
#line 780 "src/parser.y"
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
#line 2446 "src/parser.tab.c"
    break;

  case 26: /* unary_expression: unary_operator cast_expression  */
#line 795 "src/parser.y"
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
#line 2486 "src/parser.tab.c"
    break;

  case 27: /* unary_expression: SIZEOF LROUND unary_expression RROUND  */
#line 830 "src/parser.y"
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
#line 2502 "src/parser.tab.c"
    break;

  case 28: /* unary_expression: SIZEOF LROUND return_type RROUND  */
#line 841 "src/parser.y"
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
#line 2517 "src/parser.tab.c"
    break;

  case 29: /* unary_expression: delete_expression  */
#line 851 "src/parser.y"
                            { 
        dbg("unary_expression -> delete_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2525 "src/parser.tab.c"
    break;

  case 30: /* unary_expression: new_expression  */
#line 854 "src/parser.y"
                         { 
        dbg("unary_expression -> new_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2533 "src/parser.tab.c"
    break;

  case 31: /* unary_operator: BITWISE_AND  */
#line 861 "src/parser.y"
                      { 
        dbg("unary_operator -> &");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2541 "src/parser.tab.c"
    break;

  case 32: /* unary_operator: STAR  */
#line 864 "src/parser.y"
               { 
        dbg("unary_operator -> *");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2549 "src/parser.tab.c"
    break;

  case 33: /* unary_operator: PLUS  */
#line 867 "src/parser.y"
               { 
        dbg("unary_operator -> +");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2557 "src/parser.tab.c"
    break;

  case 34: /* unary_operator: MINUS  */
#line 870 "src/parser.y"
                { 
        dbg("unary_operator -> -");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2565 "src/parser.tab.c"
    break;

  case 35: /* unary_operator: TILDE  */
#line 873 "src/parser.y"
                { 
        dbg("unary_operator -> ~");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2573 "src/parser.tab.c"
    break;

  case 36: /* unary_operator: LOGICAL_NOT  */
#line 876 "src/parser.y"
                      { 
        dbg("unary_operator -> !");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2581 "src/parser.tab.c"
    break;

  case 37: /* new_expression: NEW return_type new_square  */
#line 883 "src/parser.y"
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
#line 2599 "src/parser.tab.c"
    break;

  case 38: /* new_expression: NEW return_type  */
#line 896 "src/parser.y"
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
#line 2614 "src/parser.tab.c"
    break;

  case 39: /* new_square: LSQUARE expression RSQUARE  */
#line 910 "src/parser.y"
                                     { 
            dbg("new_square -> [ expression ]");
            Node* n = new Node();
            n->code = (yyvsp[-1].node)->code;
            n->place = (yyvsp[-1].node)->place;
            n->type = "*";
            n->argCount = 1;
            (yyval.node) = n; 
        }
#line 2628 "src/parser.tab.c"
    break;

  case 40: /* new_square: new_square LSQUARE expression RSQUARE  */
#line 919 "src/parser.y"
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
#line 2644 "src/parser.tab.c"
    break;

  case 41: /* delete_expression: DELETE LSQUARE RSQUARE cast_expression  */
#line 934 "src/parser.y"
                                                 {
          dbg("delete_expression -> DELETE [ ] cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("call free, " + (yyvsp[0].node)->place);
          (yyval.node) = n;
      }
#line 2656 "src/parser.tab.c"
    break;

  case 42: /* delete_expression: DELETE cast_expression  */
#line 941 "src/parser.y"
                                 {
            dbg("delete_expression -> DELETE cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("call free, " + (yyvsp[0].node)->place);
          (yyval.node) = n;
      }
#line 2668 "src/parser.tab.c"
    break;

  case 43: /* cast_expression: unary_expression  */
#line 952 "src/parser.y"
                           { 
        dbg("cast_expression -> unary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2676 "src/parser.tab.c"
    break;

  case 44: /* cast_expression: LROUND return_type RROUND cast_expression  */
#line 955 "src/parser.y"
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
#line 2694 "src/parser.tab.c"
    break;

  case 45: /* multiplicative_expression: cast_expression  */
#line 972 "src/parser.y"
                          { 
        dbg("multiplicative_expression -> cast_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2702 "src/parser.tab.c"
    break;

  case 46: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 975 "src/parser.y"
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
#line 2720 "src/parser.tab.c"
    break;

  case 47: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 988 "src/parser.y"
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
#line 2739 "src/parser.tab.c"
    break;

  case 48: /* multiplicative_expression: multiplicative_expression MODULUS cast_expression  */
#line 1002 "src/parser.y"
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
#line 2758 "src/parser.tab.c"
    break;

  case 49: /* additive_expression: multiplicative_expression  */
#line 1020 "src/parser.y"
                                    { 
        dbg("additive_expression -> multiplicative_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2766 "src/parser.tab.c"
    break;

  case 50: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 1023 "src/parser.y"
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
#line 2785 "src/parser.tab.c"
    break;

  case 51: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 1037 "src/parser.y"
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
#line 2804 "src/parser.tab.c"
    break;

  case 52: /* shift_expression: additive_expression  */
#line 1055 "src/parser.y"
                              { 
        dbg("shift_expression -> additive_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2812 "src/parser.tab.c"
    break;

  case 53: /* shift_expression: shift_expression LEFT_SHIFT additive_expression  */
#line 1058 "src/parser.y"
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
#line 2831 "src/parser.tab.c"
    break;

  case 54: /* shift_expression: shift_expression RIGHT_SHIFT additive_expression  */
#line 1072 "src/parser.y"
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
#line 2850 "src/parser.tab.c"
    break;

  case 55: /* relational_expression: shift_expression  */
#line 1090 "src/parser.y"
                           { 
        dbg("relational_expression -> shift_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2858 "src/parser.tab.c"
    break;

  case 56: /* relational_expression: relational_expression GREATER_THAN shift_expression  */
#line 1093 "src/parser.y"
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
#line 2875 "src/parser.tab.c"
    break;

  case 57: /* relational_expression: relational_expression LESS_THAN shift_expression  */
#line 1105 "src/parser.y"
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
#line 2892 "src/parser.tab.c"
    break;

  case 58: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 1117 "src/parser.y"
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
#line 2909 "src/parser.tab.c"
    break;

  case 59: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 1129 "src/parser.y"
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
#line 2926 "src/parser.tab.c"
    break;

  case 60: /* equality_expression: relational_expression  */
#line 1145 "src/parser.y"
                                { 
        dbg("equality_expression -> relational_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2934 "src/parser.tab.c"
    break;

  case 61: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 1148 "src/parser.y"
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
#line 2952 "src/parser.tab.c"
    break;

  case 62: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 1161 "src/parser.y"
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
#line 2970 "src/parser.tab.c"
    break;

  case 63: /* and_expression: equality_expression  */
#line 1178 "src/parser.y"
                              { 
        dbg("and_expression -> equality_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2978 "src/parser.tab.c"
    break;

  case 64: /* and_expression: and_expression BITWISE_AND equality_expression  */
#line 1181 "src/parser.y"
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
#line 2996 "src/parser.tab.c"
    break;

  case 65: /* exclusive_or_expression: and_expression  */
#line 1198 "src/parser.y"
                         { 
        dbg("exclusive_or_expression -> and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3004 "src/parser.tab.c"
    break;

  case 66: /* exclusive_or_expression: exclusive_or_expression BITWISE_XOR and_expression  */
#line 1201 "src/parser.y"
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
#line 3022 "src/parser.tab.c"
    break;

  case 67: /* inclusive_or_expression: exclusive_or_expression  */
#line 1218 "src/parser.y"
                                  { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3030 "src/parser.tab.c"
    break;

  case 68: /* inclusive_or_expression: inclusive_or_expression BITWISE_OR exclusive_or_expression  */
#line 1221 "src/parser.y"
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
#line 3048 "src/parser.tab.c"
    break;

  case 69: /* logical_and_expression: inclusive_or_expression  */
#line 1238 "src/parser.y"
                                  { 
        dbg("logical_and_expression -> inclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3056 "src/parser.tab.c"
    break;

  case 70: /* logical_and_expression: logical_and_expression LOGICAL_AND inclusive_or_expression  */
#line 1241 "src/parser.y"
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
#line 3074 "src/parser.tab.c"
    break;

  case 71: /* logical_or_expression: logical_and_expression  */
#line 1258 "src/parser.y"
                                 { 
        dbg("logical_or_expression -> logical_and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3082 "src/parser.tab.c"
    break;

  case 72: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 1261 "src/parser.y"
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
#line 3100 "src/parser.tab.c"
    break;

  case 73: /* conditional_expression: logical_or_expression  */
#line 1278 "src/parser.y"
    { 
        dbg("conditional_expression -> logical_or_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3109 "src/parser.tab.c"
    break;

  case 74: /* conditional_expression: logical_or_expression QUESTION_MARK expression COLON conditional_expression  */
#line 1282 "src/parser.y"
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
#line 3132 "src/parser.tab.c"
    break;

  case 75: /* assignment_expression: conditional_expression  */
#line 1304 "src/parser.y"
                                 { 
        dbg("assignment_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3140 "src/parser.tab.c"
    break;

  case 76: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 1307 "src/parser.y"
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
#line 3168 "src/parser.tab.c"
    break;

  case 77: /* assignment_operator: ASSIGN  */
#line 1335 "src/parser.y"
                 { 
        dbg("assignment_operator -> =");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3176 "src/parser.tab.c"
    break;

  case 78: /* assignment_operator: STAR_EQUAL  */
#line 1338 "src/parser.y"
                     { 
        dbg("assignment_operator -> *=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3184 "src/parser.tab.c"
    break;

  case 79: /* assignment_operator: DIV_EQUAL  */
#line 1341 "src/parser.y"
                    { 
        dbg("assignment_operator -> /=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3192 "src/parser.tab.c"
    break;

  case 80: /* assignment_operator: MOD_EQUAL  */
#line 1344 "src/parser.y"
                    { 
        dbg("assignment_operator -> %=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3200 "src/parser.tab.c"
    break;

  case 81: /* assignment_operator: PLUS_EQUAL  */
#line 1347 "src/parser.y"
                     { 
        dbg("assignment_operator -> +=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3208 "src/parser.tab.c"
    break;

  case 82: /* assignment_operator: MINUS_EQUAL  */
#line 1350 "src/parser.y"
                      { 
        dbg("assignment_operator -> -=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3216 "src/parser.tab.c"
    break;

  case 83: /* assignment_operator: LEFT_SHIFT_EQ  */
#line 1353 "src/parser.y"
                        { 
        dbg("assignment_operator -> <<=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3224 "src/parser.tab.c"
    break;

  case 84: /* assignment_operator: RIGHT_SHIFT_EQ  */
#line 1356 "src/parser.y"
                         { 
        dbg("assignment_operator -> >>=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3232 "src/parser.tab.c"
    break;

  case 85: /* assignment_operator: AND_EQUAL  */
#line 1359 "src/parser.y"
                    { 
        dbg("assignment_operator -> &=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3240 "src/parser.tab.c"
    break;

  case 86: /* assignment_operator: XOR_EQUAL  */
#line 1362 "src/parser.y"
                    { 
        dbg("assignment_operator -> ^=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3248 "src/parser.tab.c"
    break;

  case 87: /* assignment_operator: OR_EQUAL  */
#line 1365 "src/parser.y"
                   { 
        dbg("assignment_operator -> |=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3256 "src/parser.tab.c"
    break;

  case 88: /* expression: assignment_expression  */
#line 1373 "src/parser.y"
    { 
        dbg("expression -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3265 "src/parser.tab.c"
    break;

  case 89: /* expression: expression COMMA assignment_expression  */
#line 1378 "src/parser.y"
        {
            dbg("expression -> expression , assignment_expression");
            Node* n = new Node();
            n->code = (yyvsp[-2].node)->code;
            n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
            n->place = (yyvsp[0].node)->place;
            (yyval.node) = n;
        }
#line 3278 "src/parser.tab.c"
    break;

  case 90: /* constant_expression: conditional_expression  */
#line 1391 "src/parser.y"
    { 
        dbg("constant_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3287 "src/parser.tab.c"
    break;

  case 91: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 1400 "src/parser.y"
    {
        dbg("declaration -> declaration_specifiers init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3296 "src/parser.tab.c"
    break;

  case 92: /* declaration_specifiers: static_opt const_opt type_specifier  */
#line 1408 "src/parser.y"
                                          {
        dbg("declaration_specifiers -> static_opt const_opt type_specifier");
        lastDeclType = string((yyvsp[-2].str))+string((yyvsp[-1].str))+string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
	}
#line 3306 "src/parser.tab.c"
    break;

  case 93: /* init_declarator_list: init_declarator  */
#line 1418 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3315 "src/parser.tab.c"
    break;

  case 94: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1423 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator_list , init_declarator");
        Node* n = (yyvsp[-2].node);
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        (yyval.node) = n;
    }
#line 3326 "src/parser.tab.c"
    break;

  case 95: /* pointer_opt: pointer_list  */
#line 1434 "src/parser.y"
    {
        dbg("pointer_opt -> pointer_list");
        (yyval.str) = (yyvsp[0].str);
    }
#line 3335 "src/parser.tab.c"
    break;

  case 96: /* pointer_opt: %empty  */
#line 1439 "src/parser.y"
    {
        dbg("pointer_opt -> <empty>");
        (yyval.str) = strdup("");
    }
#line 3344 "src/parser.tab.c"
    break;

  case 97: /* pointer_list: pointer_list STAR  */
#line 1448 "src/parser.y"
    {
        dbg("pointer_list -> pointer_list *");
        (yyval.str) = strdup((string("*")+string((yyvsp[-1].str))).c_str());
    }
#line 3353 "src/parser.tab.c"
    break;

  case 98: /* pointer_list: STAR  */
#line 1453 "src/parser.y"
    {
        dbg("pointer_list -> *");
        (yyval.str) = strdup("*");
    }
#line 3362 "src/parser.tab.c"
    break;

  case 99: /* init_declarator: IDENTIFIER  */
#line 1462 "src/parser.y"
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
#line 3410 "src/parser.tab.c"
    break;

  case 100: /* init_declarator: IDENTIFIER square_list  */
#line 1506 "src/parser.y"
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
#line 3478 "src/parser.tab.c"
    break;

  case 101: /* init_declarator: pointer_list IDENTIFIER  */
#line 1570 "src/parser.y"
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
#line 3529 "src/parser.tab.c"
    break;

  case 102: /* init_declarator: IDENTIFIER ASSIGN assignment_expression  */
#line 1618 "src/parser.y"
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
#line 3584 "src/parser.tab.c"
    break;

  case 103: /* init_declarator: pointer_list IDENTIFIER ASSIGN assignment_expression  */
#line 1670 "src/parser.y"
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
#line 3641 "src/parser.tab.c"
    break;

  case 104: /* init_declarator: IDENTIFIER square_list ASSIGN initializer  */
#line 1724 "src/parser.y"
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
#line 3712 "src/parser.tab.c"
    break;

  case 105: /* initializer: LCURLY initializer_list RCURLY  */
#line 1864 "src/parser.y"
    { 
        dbg("initializer -> { initializer_list }");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3721 "src/parser.tab.c"
    break;

  case 106: /* initializer_list: assignment_expression  */
#line 1873 "src/parser.y"
    { 
        dbg("initializer_list -> assignment_expression");
        Node * n = (yyvsp[0].node);
        n->argCount = 1;
        (yyval.node) = n;
    }
#line 3732 "src/parser.tab.c"
    break;

  case 107: /* initializer_list: initializer_list COMMA assignment_expression  */
#line 1880 "src/parser.y"
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
#line 3750 "src/parser.tab.c"
    break;

  case 108: /* square_list: square_list LSQUARE constant_expression RSQUARE  */
#line 1898 "src/parser.y"
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
#line 3768 "src/parser.tab.c"
    break;

  case 109: /* square_list: LSQUARE constant_expression RSQUARE  */
#line 1912 "src/parser.y"
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
#line 3785 "src/parser.tab.c"
    break;

  case 110: /* static_opt: STATIC  */
#line 1929 "src/parser.y"
                 { 
        dbg("static_opt -> STATIC");
        (yyval.str) = strdup("static"); }
#line 3793 "src/parser.tab.c"
    break;

  case 111: /* static_opt: %empty  */
#line 1932 "src/parser.y"
       { 
        dbg("static_opt -> <empty>");
        (yyval.str) = strdup(""); }
#line 3801 "src/parser.tab.c"
    break;

  case 112: /* type_specifier: VOID  */
#line 1939 "src/parser.y"
                 { 
        dbg("type_specifier -> VOID");
        (yyval.str) = strdup("void"); lastDeclType = "void"; }
#line 3809 "src/parser.tab.c"
    break;

  case 113: /* type_specifier: CHAR  */
#line 1942 "src/parser.y"
                 { 
        dbg("type_specifier -> CHAR");
        (yyval.str) = strdup("char"); lastDeclType = "char"; }
#line 3817 "src/parser.tab.c"
    break;

  case 114: /* type_specifier: INT  */
#line 1945 "src/parser.y"
                 { 
        dbg("type_specifier -> INT");
        (yyval.str) = strdup("int"); lastDeclType = "int"; }
#line 3825 "src/parser.tab.c"
    break;

  case 115: /* type_specifier: LONG  */
#line 1948 "src/parser.y"
                 { 
        dbg("type_specifier -> LONG");
        (yyval.str) = strdup("long"); lastDeclType = "long"; }
#line 3833 "src/parser.tab.c"
    break;

  case 116: /* type_specifier: DOUBLE  */
#line 1951 "src/parser.y"
                 { 
        dbg("type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); lastDeclType = "double"; }
#line 3841 "src/parser.tab.c"
    break;

  case 117: /* type_specifier: BOOL  */
#line 1954 "src/parser.y"
                 { 
        dbg("type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); lastDeclType = "bool"; }
#line 3849 "src/parser.tab.c"
    break;

  case 118: /* type_specifier: STRING  */
#line 1957 "src/parser.y"
                 { 
        dbg("type_specifier -> STRING");
        (yyval.str) = strdup("string"); lastDeclType = "string"; }
#line 3857 "src/parser.tab.c"
    break;

  case 119: /* type_specifier: TYPE_NAME  */
#line 1960 "src/parser.y"
                    { 
        dbg("type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str); lastDeclType = string((yyvsp[0].str)); }
#line 3865 "src/parser.tab.c"
    break;

  case 120: /* $@1: %empty  */
#line 1968 "src/parser.y"
    { 
        lastClassType = string((yyvsp[-1].str)); 
        if(typeSize.find(lastClassType) != typeSize.end()){
            yyerror("Redefinition of class/struct '" + lastClassType + "'.");
        }
        typeSize[lastClassType] = 0;
        classOffset = 0;
        pushScope();
    }
#line 3879 "src/parser.tab.c"
    break;

  case 121: /* struct_or_class_specifier: struct_or_class IDENTIFIER LCURLY $@1 struct_or_class_member_list RCURLY  */
#line 1977 "src/parser.y"
    { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        popScope();
        (yyval.node) = (yyvsp[-1].node); 
        lastClassType = "";
    }
#line 3890 "src/parser.tab.c"
    break;

  case 122: /* struct_or_class: STRUCT  */
#line 1988 "src/parser.y"
    { 
        dbg("struct_or_class -> STRUCT");
        (yyval.node) = new Node(); 
        lastUsage = "public";
    }
#line 3900 "src/parser.tab.c"
    break;

  case 123: /* struct_or_class: CLASS  */
#line 1994 "src/parser.y"
    { 
        dbg("struct_or_class -> CLASS");
        (yyval.node) = new Node(); 
        lastUsage = "private";
    }
#line 3910 "src/parser.tab.c"
    break;

  case 124: /* struct_or_class_member_list: %empty  */
#line 2004 "src/parser.y"
    { 
        dbg("struct_or_class_member_list -> <empty>");
        (yyval.node) = new Node(); 
    }
#line 3919 "src/parser.tab.c"
    break;

  case 125: /* struct_or_class_member_list: struct_or_class_member_list struct_or_class_member  */
#line 2009 "src/parser.y"
    { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        Node* n = (yyvsp[-1].node); 
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; 
    }
#line 3930 "src/parser.tab.c"
    break;

  case 126: /* struct_or_class_member: access_specifier_label  */
#line 2019 "src/parser.y"
    { 
        dbg("struct_or_class_member -> access_specifier_label");
        lastUsage = string((yyvsp[0].node)->place);
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3940 "src/parser.tab.c"
    break;

  case 127: /* struct_or_class_member: member_declaration  */
#line 2025 "src/parser.y"
    { 
        dbg("struct_or_class_member -> member_declaration");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3949 "src/parser.tab.c"
    break;

  case 128: /* access_specifier_label: PUBLIC COLON  */
#line 2033 "src/parser.y"
    { 
        dbg("access_specifier_label -> PUBLIC :");
        Node* n=new Node(); 
        n->place = "public";
        (yyval.node) = n; 
    }
#line 3960 "src/parser.tab.c"
    break;

  case 129: /* access_specifier_label: PRIVATE COLON  */
#line 2040 "src/parser.y"
    { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); 
        n->place = "private";
        (yyval.node) = n; 
    }
#line 3971 "src/parser.tab.c"
    break;

  case 130: /* access_specifier_label: PROTECTED COLON  */
#line 2047 "src/parser.y"
    { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); 
        n->place = "protected";
        (yyval.node) = n; 
    }
#line 3982 "src/parser.tab.c"
    break;

  case 131: /* $@2: %empty  */
#line 2056 "src/parser.y"
                                {lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));}
#line 3988 "src/parser.tab.c"
    break;

  case 132: /* member_declaration: const_opt return_type $@2 struct_declarator_list SEMICOLON  */
#line 2057 "src/parser.y"
    { 
        dbg("member_declaration -> const_opt return_type struct_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node); 
    }
#line 3997 "src/parser.tab.c"
    break;

  case 133: /* member_declaration: function_header compound_statement  */
#line 2062 "src/parser.y"
    { 
        dbg("member_declaration -> function_header compound_statement");
        Node* n = (yyvsp[-1].node);
        n->code.push_back(lastClassType + "." + n->place + ":");
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        (yyval.node) = n;
    }
#line 4009 "src/parser.tab.c"
    break;

  case 134: /* struct_declarator_list: struct_declarator  */
#line 2077 "src/parser.y"
    { 
        dbg("struct_declarator_list -> struct_declarator");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4018 "src/parser.tab.c"
    break;

  case 135: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 2082 "src/parser.y"
    { 
        dbg("struct_declarator_list -> struct_declarator_list , struct_declarator");
        Node* n = (yyvsp[-2].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; 
    }
#line 4029 "src/parser.tab.c"
    break;

  case 136: /* struct_declarator: init_declarator  */
#line 2092 "src/parser.y"
    { 
        dbg("struct_declarator -> init_declarator");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4038 "src/parser.tab.c"
    break;

  case 137: /* const_opt: CONST  */
#line 2100 "src/parser.y"
                { 
        dbg("const_opt -> CONST");
        (yyval.str) = strdup("const"); }
#line 4046 "src/parser.tab.c"
    break;

  case 138: /* const_opt: %empty  */
#line 2103 "src/parser.y"
       {
        dbg("const_opt -> <empty>");
        (yyval.str) = strdup(""); }
#line 4054 "src/parser.tab.c"
    break;

  case 139: /* parameter_list: parameter_declaration  */
#line 2110 "src/parser.y"
                                { 
            dbg("parameter_list -> parameter_declaration");
            (yyval.node) = (yyvsp[0].node); 
        }
#line 4063 "src/parser.tab.c"
    break;

  case 140: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 2115 "src/parser.y"
        {
            dbg("parameter_list -> parameter_list , parameter_declaration");
            Node* n = (yyvsp[-2].node);
            n->syn.insert(n->syn.end(), (yyvsp[0].node)->syn.begin(), (yyvsp[0].node)->syn.end()); 
            (yyval.node) = n;
        }
#line 4074 "src/parser.tab.c"
    break;

  case 141: /* parameter_declaration: return_type IDENTIFIER  */
#line 2126 "src/parser.y"
        {
            dbg("parameter_declaration -> return_type IDENTIFIER");
            Node* n = new Node();
            n->syn.push_back(string((yyvsp[-1].str))); 
            n->syn.push_back(string((yyvsp[0].str)));
            (yyval.node) = n;
        }
#line 4086 "src/parser.tab.c"
    break;

  case 142: /* statement: labeled_statement  */
#line 2137 "src/parser.y"
                            { 
        dbg("statement -> labeled_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4094 "src/parser.tab.c"
    break;

  case 143: /* statement: compound_statement  */
#line 2140 "src/parser.y"
                             { 
        dbg("statement -> compound_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4102 "src/parser.tab.c"
    break;

  case 144: /* statement: expression_statement  */
#line 2143 "src/parser.y"
                               { 
        dbg("statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4110 "src/parser.tab.c"
    break;

  case 145: /* statement: selection_statement  */
#line 2146 "src/parser.y"
                              { 
        dbg("statement -> selection_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4118 "src/parser.tab.c"
    break;

  case 146: /* statement: iteration_statement  */
#line 2149 "src/parser.y"
                              { 
        dbg("statement -> iteration_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4126 "src/parser.tab.c"
    break;

  case 147: /* statement: jump_statement  */
#line 2152 "src/parser.y"
                         { 
        dbg("statement -> jump_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4134 "src/parser.tab.c"
    break;

  case 148: /* statement: io_statement  */
#line 2155 "src/parser.y"
                       { 
        dbg("statement -> io_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4142 "src/parser.tab.c"
    break;

  case 149: /* io_statement: cout_expression SEMICOLON  */
#line 2162 "src/parser.y"
                                { 
        dbg("io_statement -> cout_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4150 "src/parser.tab.c"
    break;

  case 150: /* io_statement: cin_expression SEMICOLON  */
#line 2165 "src/parser.y"
                                { 
        dbg("io_statement -> cin_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4158 "src/parser.tab.c"
    break;

  case 151: /* cout_expression: COUT insertion_list  */
#line 2172 "src/parser.y"
                          { 
        dbg("cout_expression -> COUT insertion_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4166 "src/parser.tab.c"
    break;

  case 152: /* insertion_list: LEFT_SHIFT assignment_expression  */
#line 2179 "src/parser.y"
                                       {
          dbg("insertion_list -> LEFT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node);
          Node* n = new Node();
          n->code = e->code;
          n->code.push_back("print " + e->place); 
          (yyval.node) = n;
      }
#line 4179 "src/parser.tab.c"
    break;

  case 153: /* insertion_list: LEFT_SHIFT ENDL  */
#line 2187 "src/parser.y"
                          {
            dbg("insertion_list -> LEFT_SHIFT ENDL");
          Node* n = new Node();
          n->code.push_back("print newline"); 
          (yyval.node) = n;
      }
#line 4190 "src/parser.tab.c"
    break;

  case 154: /* insertion_list: insertion_list LEFT_SHIFT ENDL  */
#line 2193 "src/parser.y"
                                         {
            dbg("insertion_list -> insertion_list LEFT_SHIFT ENDL");
          Node* n = (yyvsp[-2].node); 
          n->code.push_back("print newline"); 
          (yyval.node) = n;
      }
#line 4201 "src/parser.tab.c"
    break;

  case 155: /* insertion_list: insertion_list LEFT_SHIFT assignment_expression  */
#line 2199 "src/parser.y"
                                                          {
            dbg("insertion_list -> insertion_list LEFT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("print " + e->place); (yyval.node) = n;
      }
#line 4212 "src/parser.tab.c"
    break;

  case 156: /* cin_expression: CIN extraction_list  */
#line 2209 "src/parser.y"
                          { 
        dbg("cin_expression -> CIN extraction_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4220 "src/parser.tab.c"
    break;

  case 157: /* extraction_list: RIGHT_SHIFT assignment_expression  */
#line 2216 "src/parser.y"
                                        {
            dbg("extraction_list -> RIGHT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node); 
          Node* n = new Node();
          n->code = e->code; 
          n->code.push_back("read " + e->place); 
          (yyval.node) = n;
      }
#line 4233 "src/parser.tab.c"
    break;

  case 158: /* extraction_list: extraction_list RIGHT_SHIFT assignment_expression  */
#line 2224 "src/parser.y"
                                                        {
            dbg("extraction_list -> extraction_list RIGHT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); 
          Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("read " + e->place); 
          (yyval.node) = n;
      }
#line 4246 "src/parser.tab.c"
    break;

  case 159: /* labeled_statement: IDENTIFIER COLON  */
#line 2236 "src/parser.y"
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
#line 4261 "src/parser.tab.c"
    break;

  case 160: /* compound_statement: LCURLY RCURLY  */
#line 2250 "src/parser.y"
                        {
            dbg("compound_statement -> { }");
          Node* n = new Node();
          (yyval.node) = n;
      }
#line 4271 "src/parser.tab.c"
    break;

  case 161: /* $@3: %empty  */
#line 2255 "src/parser.y"
                 { pushScope();}
#line 4277 "src/parser.tab.c"
    break;

  case 162: /* compound_statement: LCURLY $@3 statement_list RCURLY  */
#line 2255 "src/parser.y"
                                                       {
            dbg("compound_statement -> { statement_list }");
          Node* n = (yyvsp[-1].node);
          popScope();
          (yyval.node) = n;
      }
#line 4288 "src/parser.tab.c"
    break;

  case 163: /* statement_list: block_item  */
#line 2265 "src/parser.y"
                     { 
        dbg("statement_list -> block_item");
        (yyval.node) = (yyvsp[0].node); }
#line 4296 "src/parser.tab.c"
    break;

  case 164: /* statement_list: statement_list block_item  */
#line 2268 "src/parser.y"
                                    {
            dbg("statement_list -> statement_list block_item");
          Node* n = (yyvsp[-1].node);
          if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 4307 "src/parser.tab.c"
    break;

  case 165: /* block_item: statement  */
#line 2278 "src/parser.y"
                { 
        dbg("block_item -> statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4315 "src/parser.tab.c"
    break;

  case 166: /* block_item: declaration  */
#line 2281 "src/parser.y"
                  { 
        dbg("block_item -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4323 "src/parser.tab.c"
    break;

  case 167: /* block_item: error SEMICOLON  */
#line 2284 "src/parser.y"
                      { yyerrok;}
#line 4329 "src/parser.tab.c"
    break;

  case 168: /* expression_statement: SEMICOLON  */
#line 2288 "src/parser.y"
                    { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4337 "src/parser.tab.c"
    break;

  case 169: /* expression_statement: expression SEMICOLON  */
#line 2291 "src/parser.y"
                               { 
        dbg("expression_statement -> expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4345 "src/parser.tab.c"
    break;

  case 170: /* selection_statement: IF LROUND expression RROUND statement  */
#line 2297 "src/parser.y"
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
#line 4365 "src/parser.tab.c"
    break;

  case 171: /* selection_statement: IF LROUND expression RROUND statement ELSE statement  */
#line 2312 "src/parser.y"
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
#line 4395 "src/parser.tab.c"
    break;

  case 172: /* iteration_statement: WHILE LROUND expression RROUND statement  */
#line 2343 "src/parser.y"
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
#line 4413 "src/parser.tab.c"
    break;

  case 173: /* iteration_statement: UNTIL LROUND expression RROUND statement  */
#line 2356 "src/parser.y"
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
#line 4429 "src/parser.tab.c"
    break;

  case 174: /* iteration_statement: DO statement WHILE LROUND expression RROUND SEMICOLON  */
#line 2367 "src/parser.y"
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
#line 4445 "src/parser.tab.c"
    break;

  case 175: /* iteration_statement: FOR LROUND for_init_statement expression_statement RROUND statement  */
#line 2378 "src/parser.y"
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
#line 4466 "src/parser.tab.c"
    break;

  case 176: /* iteration_statement: FOR LROUND for_init_statement expression_statement expression RROUND statement  */
#line 2394 "src/parser.y"
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
#line 4488 "src/parser.tab.c"
    break;

  case 177: /* for_init_statement: expression_statement  */
#line 2414 "src/parser.y"
                               { 
        dbg("for_init_statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4496 "src/parser.tab.c"
    break;

  case 178: /* for_init_statement: declaration  */
#line 2417 "src/parser.y"
                      { 
        dbg("for_init_statement -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4504 "src/parser.tab.c"
    break;

  case 179: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 2424 "src/parser.y"
                                    {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string((yyvsp[-1].str)));
          (yyval.node) = n;
      }
#line 4515 "src/parser.tab.c"
    break;

  case 180: /* jump_statement: CONTINUE SEMICOLON  */
#line 2430 "src/parser.y"
                             {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); 
          n->code.push_back("continue;"); 
          (yyval.node) = n;
      }
#line 4526 "src/parser.tab.c"
    break;

  case 181: /* jump_statement: BREAK SEMICOLON  */
#line 2436 "src/parser.y"
                          {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); 
          n->code.push_back("break;"); 
          (yyval.node) = n;
      }
#line 4537 "src/parser.tab.c"
    break;

  case 182: /* jump_statement: RETURN SEMICOLON  */
#line 2442 "src/parser.y"
                           {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); 
          n->code.push_back("return;"); 
          (yyval.node) = n;
      }
#line 4548 "src/parser.tab.c"
    break;

  case 183: /* jump_statement: RETURN expression SEMICOLON  */
#line 2448 "src/parser.y"
                                      {
            dbg("jump_statement -> RETURN expression ;");
          Node* expr = (yyvsp[-1].node);
          Node* n = new Node();
          n->code = expr->code;
          n->code.push_back("return " + expr->place);
          (yyval.node) = n;
      }
#line 4561 "src/parser.tab.c"
    break;

  case 184: /* translation_unit: external_declaration  */
#line 2460 "src/parser.y"
                               { 
        dbg("translation_unit -> external_declaration");
        finalRoot = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 4569 "src/parser.tab.c"
    break;

  case 185: /* translation_unit: translation_unit external_declaration  */
#line 2463 "src/parser.y"
                                                {
            dbg("translation_unit -> translation_unit external_declaration");
          Node* a = (yyvsp[-1].node); Node* b = (yyvsp[0].node);
          if (a) { 
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; (yyval.node) = a; }
          else { finalRoot = b; (yyval.node) = b; }
      }
#line 4582 "src/parser.tab.c"
    break;

  case 186: /* external_declaration: function_definition  */
#line 2475 "src/parser.y"
                              { 
        dbg("external_declaration -> function_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 4590 "src/parser.tab.c"
    break;

  case 187: /* external_declaration: struct_or_class_specifier SEMICOLON  */
#line 2478 "src/parser.y"
                                              { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4598 "src/parser.tab.c"
    break;

  case 188: /* external_declaration: declaration  */
#line 2481 "src/parser.y"
                      {
        dbg("external_declaration -> declaration");
         (yyval.node) = (yyvsp[0].node); }
#line 4606 "src/parser.tab.c"
    break;

  case 189: /* external_declaration: TYPEDEF return_type IDENTIFIER SEMICOLON  */
#line 2484 "src/parser.y"
                                               {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string((yyvsp[-1].str))] = typeSize[string((yyvsp[-2].str))];
        (yyval.node) = new Node();
        }
#line 4616 "src/parser.tab.c"
    break;

  case 190: /* function_header: return_type IDENTIFIER LROUND RROUND  */
#line 2494 "src/parser.y"
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
#line 4645 "src/parser.tab.c"
    break;

  case 191: /* function_header: return_type IDENTIFIER LROUND parameter_list RROUND  */
#line 2520 "src/parser.y"
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
#line 4693 "src/parser.tab.c"
    break;

  case 192: /* function_definition: function_header compound_statement  */
#line 2567 "src/parser.y"
                                        {
            dbg("function_definition -> function_header compound_statement");
            Node* n = (yyvsp[-1].node);
            if((yyvsp[0].node)) n->code.insert(n->code.end(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end()); 
            popScope(); 
            finalRoot = n;
            currentFunction = "global";
            (yyval.node) = n;
        }
#line 4707 "src/parser.tab.c"
    break;

  case 193: /* function_definition: error RCURLY  */
#line 2576 "src/parser.y"
                   { yyerrok;}
#line 4713 "src/parser.tab.c"
    break;

  case 194: /* return_type: type_specifier pointer_opt  */
#line 2582 "src/parser.y"
    { 
        dbg("return_type -> type_specifier pointer_opt");
        (yyval.str) = strdup( (string((yyvsp[-1].str)) + string((yyvsp[0].str))).c_str() );
    }
#line 4722 "src/parser.tab.c"
    break;


#line 4726 "src/parser.tab.c"

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

#line 2645 "src/parser.y"



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

