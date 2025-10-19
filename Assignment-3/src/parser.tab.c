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
        string printName;
        int argCount = 0;
        Node() : place(""), type("") , kind("") {}
        Node(string p, string t, string k) : place(p), type(t), kind(k) {}
    };

    struct Symbol {
        string printName;
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
        string original;
        string kind;
        string returnType;
        bool hasReturn = false;
        vector<string> paramTypes;
        int paramCount = 0;
        funcInfo() : returnType("void"), hasReturn(false) {}
    };

    struct memberInfo {
        int offset = 0;
        string place;
        string type;
        string kind;
        funcInfo method;
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
    static string lastUsage = "";
    static string lastFnType = "int";
    static string currentScope = "";

    vector<string> globalCode;

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

    memberInfo* lookupClassMember(const string& c,const string& m){
        auto it = classTable.find(c);
        if(it!=classTable.end()){
            auto y = it->second.find(m);
            if(y!=it->second.end()){
                return &(y->second);
            }
            return nullptr;
        }
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

    vector<int> makeList(int index) {
        vector<int> list;
        list.push_back(index);
        return list;
    }

    void backpatch(vector<string>& code, vector<int> list, string label) {
        for(int i : list) {
            // Replace the placeholder with the actual label
            size_t pos = code[i].find("__");
            if(pos != string::npos) {
                code[i].replace(pos, 2, label);
            }
        }
    }

    vector<int> merge(vector<int> list1, vector<int> list2) {
        vector<int> result = list1;
        result.insert(result.end(), list2.begin(), list2.end());
        return result;
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


#line 407 "src/parser.tab.c"

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
  YYSYMBOL_STRING_LITERAL = 83,            /* STRING_LITERAL  */
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
  YYSYMBOL_LOWER_THAN_ELSE = 95,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 96,                  /* $accept  */
  YYSYMBOL_primary_expression = 97,        /* primary_expression  */
  YYSYMBOL_constant = 98,                  /* constant  */
  YYSYMBOL_postfix_expression = 99,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 100, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 101,         /* unary_expression  */
  YYSYMBOL_unary_operator = 102,           /* unary_operator  */
  YYSYMBOL_cast_expression = 103,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 104, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 105,      /* additive_expression  */
  YYSYMBOL_shift_expression = 106,         /* shift_expression  */
  YYSYMBOL_relational_expression = 107,    /* relational_expression  */
  YYSYMBOL_equality_expression = 108,      /* equality_expression  */
  YYSYMBOL_and_expression = 109,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 110,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 111,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 112,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 113,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 114,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 115,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 116,      /* assignment_operator  */
  YYSYMBOL_expression = 117,               /* expression  */
  YYSYMBOL_constant_expression = 118,      /* constant_expression  */
  YYSYMBOL_declaration = 119,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 120,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 121,     /* init_declarator_list  */
  YYSYMBOL_pointer_opt = 122,              /* pointer_opt  */
  YYSYMBOL_pointer_list = 123,             /* pointer_list  */
  YYSYMBOL_init_declarator = 124,          /* init_declarator  */
  YYSYMBOL_initializer = 125,              /* initializer  */
  YYSYMBOL_initializer_list = 126,         /* initializer_list  */
  YYSYMBOL_square_list = 127,              /* square_list  */
  YYSYMBOL_type_specifier = 128,           /* type_specifier  */
  YYSYMBOL_translation_unit = 129,         /* translation_unit  */
  YYSYMBOL_struct_or_class_specifier = 130, /* struct_or_class_specifier  */
  YYSYMBOL_131_1 = 131,                    /* $@1  */
  YYSYMBOL_struct_or_class = 132,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 133, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 134,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 135,   /* access_specifier_label  */
  YYSYMBOL_parameter_list = 136,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 137,    /* parameter_declaration  */
  YYSYMBOL_statement = 138,                /* statement  */
  YYSYMBOL_labeled_statement = 139,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 140,       /* compound_statement  */
  YYSYMBOL_141_5 = 141,                    /* $@5  */
  YYSYMBOL_statement_list = 142,           /* statement_list  */
  YYSYMBOL_block_item = 143,               /* block_item  */
  YYSYMBOL_expression_statement = 144,     /* expression_statement  */
  YYSYMBOL_selection_statement = 145,      /* selection_statement  */
  YYSYMBOL_switch_head = 146,              /* switch_head  */
  YYSYMBOL_case_list = 147,                /* case_list  */
  YYSYMBOL_case_item = 148,                /* case_item  */
  YYSYMBOL_iteration_statement = 149,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 150,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 151,           /* jump_statement  */
  YYSYMBOL_external_declaration = 152,     /* external_declaration  */
  YYSYMBOL_153_6 = 153,                    /* $@6  */
  YYSYMBOL_154_7 = 154,                    /* $@7  */
  YYSYMBOL_declare = 155,                  /* declare  */
  YYSYMBOL_156_8 = 156,                    /* $@8  */
  YYSYMBOL_157_9 = 157,                    /* $@9  */
  YYSYMBOL_158_10 = 158,                   /* $@10  */
  YYSYMBOL_external = 159,                 /* external  */
  YYSYMBOL_160_11 = 160,                   /* $@11  */
  YYSYMBOL_161_12 = 161,                   /* $@12  */
  YYSYMBOL_return_type = 162               /* return_type  */
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
#define YYFINAL  27
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1010

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  317

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   350


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
      95
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   423,   423,   462,   467,   472,   481,   491,   500,   506,
     512,   518,   524,   533,   538,   596,   635,   695,   753,   794,
     813,   835,   853,   874,   877,   892,   907,   944,   955,   975,
     978,   981,   984,   987,   990,  1066,  1069,  1087,  1090,  1104,
    1119,  1137,  1140,  1154,  1172,  1175,  1189,  1207,  1210,  1222,
    1234,  1246,  1262,  1265,  1278,  1295,  1298,  1315,  1318,  1335,
    1338,  1355,  1358,  1375,  1378,  1395,  1400,  1442,  1445,  1475,
    1478,  1481,  1484,  1487,  1490,  1493,  1496,  1499,  1502,  1505,
    1512,  1517,  1530,  1539,  1554,  1559,  1564,  1569,  1578,  1583,
    1594,  1600,  1608,  1613,  1622,  1709,  1814,  1901,  1988,  2078,
    2259,  2268,  2279,  2301,  2315,  2343,  2346,  2349,  2352,  2355,
    2358,  2364,  2381,  2384,  2398,  2397,  2420,  2426,  2437,  2442,
    2453,  2460,  2470,  2478,  2485,  2634,  2638,  2649,  2661,  2664,
    2667,  2670,  2673,  2676,  2761,  2775,  2781,  2780,  2795,  2798,
    2808,  2811,  2817,  2820,  2826,  2845,  2875,  2902,  2913,  2918,
    2929,  2949,  2972,  2994,  3016,  3032,  3061,  3094,  3097,  3105,
    3111,  3117,  3123,  3131,  3173,  3172,  3184,  3183,  3197,  3202,
    3207,  3216,  3215,  3226,  3225,  3236,  3235,  3249,  3248,  3319,
    3318,  3429,  3526
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
  "STRUCT", "PUBLIC", "PRIVATE", "PROTECTED", "STRING_LITERAL", "DELETE",
  "NEW", "CIN", "COUT", "ENDL", "IDENTIFIER", "INVALID_IDENTIFIER",
  "DECIMAL_LITERAL", "DOUBLE_LITERAL", "EXPONENT_LITERAL",
  "CHARACTER_LITERAL", "LOWER_THAN_ELSE", "$accept", "primary_expression",
  "constant", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "pointer_opt",
  "pointer_list", "init_declarator", "initializer", "initializer_list",
  "square_list", "type_specifier", "translation_unit",
  "struct_or_class_specifier", "$@1", "struct_or_class",
  "struct_or_class_member_list", "struct_or_class_member",
  "access_specifier_label", "parameter_list", "parameter_declaration",
  "statement", "labeled_statement", "compound_statement", "$@5",
  "statement_list", "block_item", "expression_statement",
  "selection_statement", "switch_head", "case_list", "case_item",
  "iteration_statement", "for_init_statement", "jump_statement",
  "external_declaration", "$@6", "$@7", "declare", "$@8", "$@9", "$@10",
  "external", "$@11", "$@12", "return_type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-240)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     539,   299,  -240,  -240,  -240,  -240,  -240,  -240,  -240,   167,
     299,  -240,  -240,    36,   107,    -6,   -37,  -240,  -240,    36,
     -35,   299,  -240,  -240,  -240,   100,    -3,  -240,  -240,  -240,
      75,  -240,   100,    81,  -240,    -2,    -2,  -240,    -3,     7,
      30,    17,  -240,  -240,  -240,  -240,    -2,     8,    70,    86,
    -240,   860,   286,   860,    16,  -240,    -2,   119,  -240,    99,
    -240,  -240,  -240,  -240,  -240,   916,   916,  -240,  -240,   464,
    -240,   104,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,    -5,   426,   860,  -240,   153,    78,    96,
     141,   124,   115,   132,   166,   171,     4,  -240,  -240,  -240,
     -16,  -240,   117,  -240,  -240,   150,   163,   860,  -240,   860,
     521,  -240,   860,  -240,  -240,  -240,   -11,   172,   554,  -240,
    -240,   122,   116,   860,   129,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,   860,  -240,   860,   860,
     860,   860,   860,   860,   860,   860,   860,   860,   860,   860,
     860,   860,   860,   860,   860,   860,   860,   178,  -240,   299,
    -240,  -240,   860,  -240,   169,  -240,  -240,   174,   176,   180,
    -240,  -240,  -240,  -240,   860,   860,   187,   188,  -240,  -240,
     -10,  -240,    32,  -240,  -240,  -240,  -240,  -240,   153,   153,
      78,    78,    96,    96,    96,    96,   141,   141,   124,   115,
     132,   166,   171,   105,   190,  -240,   178,  -240,  -240,    31,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,   860,
    -240,   860,  -240,   338,  -240,  -240,   860,  -240,  -240,  -240,
     191,   200,   203,   643,   204,   140,   202,   212,   732,   206,
     209,   299,   213,   102,  -240,    -2,  -240,  -240,  -240,  -240,
     248,  -240,  -240,  -240,   208,  -240,  -240,  -240,   860,   860,
     860,   201,   428,   218,  -240,  -240,  -240,   123,   860,   299,
    -240,  -240,  -240,  -240,   135,  -240,  -240,  -240,    -7,     2,
      18,   225,  -240,  -240,   768,  -240,  -240,    20,  -240,  -240,
       6,   643,  -240,   643,   860,   824,   643,  -240,   860,   643,
    -240,   214,  -240,    23,   643,    24,  -240,   643,  -240,   643,
     220,  -240,   643,  -240,  -240,  -240,  -240
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   111,   105,   107,   109,   106,   110,   108,     0,
       0,   117,   116,   164,     0,     0,     0,   112,   170,    91,
       0,     0,   175,   171,    93,   166,     0,     1,   113,   168,
       0,   182,    90,     0,   173,     0,     0,    92,     0,    94,
       0,     0,    88,   165,   114,   169,     0,    94,     0,     0,
     167,     0,     0,     0,    95,   181,     0,    96,   118,     0,
     176,   172,    31,    32,    30,     0,     0,    29,    34,     0,
      33,     0,    11,    12,    10,     5,     2,     6,     9,     8,
       7,    13,     3,    23,    35,     0,    37,    41,    44,    47,
      52,    55,    57,    59,    61,    63,    65,    67,    97,   177,
       0,   125,     0,    35,    82,     0,     0,     0,    89,     0,
       0,   174,     0,    24,    25,    80,     0,     0,     0,    19,
      20,     0,     0,     0,     0,    69,    73,    74,    70,    71,
      72,    77,    79,    78,    75,    76,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,     0,
     127,   104,     0,    99,     0,    98,   115,     0,     0,     0,
     119,   120,   121,     4,     0,     0,     0,     0,    18,    15,
       0,    21,     0,    17,    68,    38,    39,    40,    42,    43,
      45,    46,    49,    48,    50,    51,    53,    54,    56,    58,
      60,    62,    64,     0,   136,   178,     0,   126,   101,     0,
     103,   122,   123,   124,    81,    36,    27,    28,    16,     0,
      14,     0,   135,     0,   180,   100,     0,    22,    66,   142,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     0,   141,     0,    84,   140,   128,   129,
       0,   138,   130,   131,     0,   132,   133,   102,     0,     0,
       0,     0,     0,     0,   160,   161,   162,     0,     0,     0,
      85,    86,   134,   143,     0,   137,   139,   148,     0,     0,
       0,     0,   158,   157,     0,   159,   163,     0,    87,    83,
       0,     0,   147,     0,     0,     0,     0,   146,     0,     0,
     149,   144,   152,     0,     0,     0,   153,     0,   151,     0,
       0,   155,     0,   150,   145,   154,   156
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -240,  -240,  -240,  -240,  -240,   -50,  -240,   -57,    50,    21,
      55,    47,   120,   114,   128,   118,   127,  -240,   -52,     5,
    -240,   -43,  -105,    11,  -240,   -24,  -240,    28,   227,  -240,
    -240,  -240,     0,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,   111,  -159,  -240,  -140,  -240,  -240,    34,  -239,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,    -1,  -240,  -240,  -240,
    -240,  -240,  -240,   247,  -240,  -240,     3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    81,    82,    83,   180,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,   115,
     136,   243,   105,   244,   245,    40,    31,    41,    42,   163,
     209,    54,    19,    14,    15,    58,    16,   110,   170,   171,
     100,   101,   247,   248,   249,   223,   250,   251,   252,   253,
     254,   290,   300,   255,   284,   256,    17,    26,    38,    18,
      36,    46,    35,    43,   157,   206,   102
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,   104,   164,   103,    20,    24,    24,   119,   120,    22,
      23,    48,    49,    28,    13,   113,   114,   205,    51,    51,
     121,    34,    59,   283,   158,    37,   116,   106,   137,   173,
     218,   159,   155,   291,   122,   103,   174,   219,   123,    29,
     174,    25,   292,   124,    24,   295,    52,    32,   297,   174,
      53,    53,    30,   156,    33,   104,    98,   103,   293,   107,
     296,   298,   299,   310,   312,   174,   224,   174,   176,   116,
     174,   174,   117,   225,   261,    55,   220,    56,   226,   174,
     182,   185,   186,   187,   141,   142,    39,    47,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,    57,    27,    37,   172,
      13,     1,     2,   203,   165,    60,    44,    56,   215,   143,
     144,   177,    62,    63,    64,   103,    45,   181,    65,    66,
     109,    61,   301,    56,   302,   151,    67,   306,   149,   150,
     308,   184,    68,   118,   111,   311,    56,   273,   313,   174,
     314,   221,   174,   316,   152,    69,   179,   145,   146,   147,
     148,   138,   139,   140,   190,   191,    70,   208,   286,   228,
     174,   103,     2,     3,     4,     5,     6,     7,     8,   214,
     289,    71,    56,     9,    10,    11,    12,   153,    72,    73,
      74,   188,   189,   307,   161,   267,   196,   197,   154,    75,
     192,   193,   194,   195,   162,    76,   160,    77,    78,    79,
      80,   178,   175,   210,     2,   278,   279,   280,   183,   204,
     211,   274,   212,   246,   227,   287,   213,   216,   217,   263,
     258,   257,   222,     3,     4,     5,     6,     7,     8,   259,
     270,   271,   260,   262,    21,   268,   104,   264,   103,   277,
     246,   303,   305,     2,    62,    63,    64,   265,   281,   272,
      65,    66,   246,   285,   294,   315,   199,   309,    67,   288,
     207,   198,   201,   282,    68,     3,     4,     5,     6,     7,
       8,   200,   202,   108,   276,    50,   269,    69,     0,   204,
     275,     2,     0,   229,     0,     0,     0,     0,    70,     0,
     230,     0,   231,     0,     2,   232,   233,   234,   235,   236,
     237,   238,   239,    71,     3,     4,     5,     6,     7,     8,
      72,    73,    74,     0,   240,   241,    99,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,   242,     0,    77,
      78,    79,    80,     2,    62,    63,    64,     0,     0,     0,
      65,    66,     3,     4,     5,     6,     7,     8,    67,     0,
       0,     0,     0,     0,    68,     3,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     0,     0,    69,     0,   204,
       0,     0,     0,   229,     0,     0,     0,     0,    70,     0,
     230,     0,   231,     0,     0,   232,   233,   234,   235,   236,
     237,   238,   239,    71,     3,     4,     5,     6,     7,     8,
      72,    73,    74,     0,   240,   241,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,   242,     0,    77,
      78,    79,    80,     2,    62,    63,    64,   125,     0,     0,
      65,    66,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,    68,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,     0,     0,    69,     0,     2,
      62,    63,    64,   229,     0,     0,    65,    66,    70,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,     0,
      68,     0,     0,    71,     3,     4,     5,     6,     7,     8,
      72,    73,    74,    69,   240,   241,     0,     0,     0,     0,
       0,    75,     0,     0,    70,     0,     0,    76,     0,    77,
      78,    79,    80,     0,     0,     1,     2,     0,     0,    71,
       3,     4,     5,     6,     7,     8,    72,    73,    74,     0,
       0,     0,     0,     1,     2,     0,     0,    75,     0,     0,
       0,     0,     0,    76,     0,    77,    78,    79,    80,     2,
      62,    63,    64,   166,     0,     0,    65,    66,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,     3,     4,     5,
       6,     7,     8,   112,     0,     0,     0,     9,    10,    11,
      12,   167,   168,   169,    70,     3,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     9,    10,    11,    12,    71,
       3,     4,     5,     6,     7,     8,    72,    73,    74,     0,
       0,     0,     0,     0,     0,     0,     0,    75,     0,     0,
       0,     0,     0,    76,     0,    77,    78,    79,    80,    62,
      63,    64,     0,     0,     0,    65,    66,     0,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,    68,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    69,     0,   204,     0,     0,     0,   229,     0,
       0,     0,     0,    70,     0,   230,     0,   231,     0,     0,
     232,   233,   234,   235,   236,   237,   238,   239,    71,     0,
       0,     0,     0,     0,     0,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,    75,     0,     0,     0,
       0,     0,   242,     0,    77,    78,    79,    80,    62,    63,
      64,     0,     0,     0,    65,    66,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,     0,    68,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,     0,    62,    63,    64,   266,     0,     0,
      65,    66,    70,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,    68,     0,     0,    71,     0,     0,
       0,     0,     0,     0,    72,    73,    74,    69,     0,     0,
       0,     0,     0,   229,     0,    75,     0,     0,    70,     0,
       0,    76,     0,    77,    78,    79,    80,     0,     0,     0,
      62,    63,    64,    71,     0,     0,    65,    66,     0,     0,
      72,    73,    74,     0,    67,     0,     0,     0,     0,     0,
      68,    75,     0,     0,     0,     0,     0,    76,     0,    77,
      78,    79,    80,    69,   304,     0,    62,    63,    64,     0,
       0,     0,    65,    66,    70,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,     0,    68,     0,     0,    71,
       0,     0,     0,     0,     0,     0,    72,    73,    74,    69,
       0,     0,     0,     0,     0,     0,     0,    75,     0,     0,
      70,     0,     0,    76,     0,    77,    78,    79,    80,     0,
       0,     0,    62,    63,    64,    71,     0,     0,    65,    66,
       0,     0,    72,    73,    74,     0,    67,     0,     0,     0,
       0,     0,    68,    75,     0,     0,     0,     0,     0,    76,
       0,    77,    78,    79,    80,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,     0,     0,     0,     0,     0,     0,    72,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,    75,
       0,     0,     0,     0,     0,    76,     0,    77,    78,    79,
      80
};

static const yytype_int16 yycheck[] =
{
       0,    53,   107,    53,     1,     8,     8,    12,    13,     9,
      10,    35,    36,    14,    14,    65,    66,   157,    11,    11,
      25,    21,    46,   262,    40,     8,    69,    11,    85,    40,
      40,    47,    28,    40,    39,    85,    47,    47,    43,    45,
      47,    13,    40,    48,     8,   284,    39,    19,    42,    47,
      43,    43,    89,    49,    89,   107,    51,   107,    40,    43,
      40,    55,    56,    40,    40,    47,   206,    47,   118,   112,
      47,    47,    69,    42,   233,    45,    44,    47,    47,    47,
     123,   138,   139,   140,     6,     7,    89,    89,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,    89,     0,     8,   110,
     110,     4,     5,   156,   109,    45,    41,    47,   175,    23,
      24,   118,     6,     7,     8,   175,    45,   122,    12,    13,
      11,    45,   291,    47,   293,    20,    20,   296,    14,    15,
     299,   136,    26,    39,    45,   304,    47,    45,   307,    47,
     309,    46,    47,   312,    22,    39,    40,    16,    17,    18,
      19,     8,     9,    10,   143,   144,    50,   162,    45,   221,
      47,   221,     5,    66,    67,    68,    69,    70,    71,   174,
      45,    65,    47,    76,    77,    78,    79,    21,    72,    73,
      74,   141,   142,   298,    44,   238,   149,   150,    27,    83,
     145,   146,   147,   148,    41,    89,    89,    91,    92,    93,
      94,    89,    40,    44,     5,   258,   259,   260,    89,    41,
      46,   245,    46,   223,   219,   268,    46,    40,    40,    89,
      39,   226,    42,    66,    67,    68,    69,    70,    71,    39,
     240,   241,    39,    39,    77,    39,   298,    45,   298,    41,
     250,   294,   295,     5,     6,     7,     8,    45,    57,    46,
      12,    13,   262,    45,    39,    45,   152,    53,    20,   269,
     159,   151,   154,   262,    26,    66,    67,    68,    69,    70,
      71,   153,   155,    56,   250,    38,    77,    39,    -1,    41,
      42,     5,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    54,    -1,     5,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    76,    77,    40,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    89,    -1,    91,
      92,    93,    94,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    66,    67,    68,    69,    70,    71,    20,    -1,
      -1,    -1,    -1,    -1,    26,    66,    67,    68,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    54,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    76,    77,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    89,    -1,    91,
      92,    93,    94,     5,     6,     7,     8,    11,    -1,    -1,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    26,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    39,    -1,     5,
       6,     7,     8,    45,    -1,    -1,    12,    13,    50,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    39,    76,    77,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    50,    -1,    -1,    89,    -1,    91,
      92,    93,    94,    -1,    -1,     4,     5,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,     4,     5,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    91,    92,    93,    94,     5,
       6,     7,     8,    42,    -1,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,    39,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    50,    66,    67,    68,    69,    70,
      71,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    91,    92,    93,    94,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    41,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    50,    -1,    52,    -1,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    91,    92,    93,    94,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,     6,     7,     8,    45,    -1,    -1,
      12,    13,    50,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    83,    -1,    -1,    50,    -1,
      -1,    89,    -1,    91,    92,    93,    94,    -1,    -1,    -1,
       6,     7,     8,    65,    -1,    -1,    12,    13,    -1,    -1,
      72,    73,    74,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    83,    -1,    -1,    -1,    -1,    -1,    89,    -1,    91,
      92,    93,    94,    39,    40,    -1,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    50,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,
      50,    -1,    -1,    89,    -1,    91,    92,    93,    94,    -1,
      -1,    -1,     6,     7,     8,    65,    -1,    -1,    12,    13,
      -1,    -1,    72,    73,    74,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    26,    83,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    91,    92,    93,    94,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    91,    92,    93,
      94
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    66,    67,    68,    69,    70,    71,    76,
      77,    78,    79,   128,   129,   130,   132,   152,   155,   128,
     162,    77,   128,   128,     8,   123,   153,     0,   152,    45,
      89,   122,   123,    89,   128,   158,   156,     8,   154,    89,
     121,   123,   124,   159,    41,    45,   157,    89,   121,   121,
     159,    11,    39,    43,   127,    45,    47,    89,   131,   121,
      45,    45,     6,     7,     8,    12,    13,    20,    26,    39,
      50,    65,    72,    73,    74,    83,    89,    91,    92,    93,
      94,    97,    98,    99,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    40,
     136,   137,   162,   101,   114,   118,    11,    43,   124,    11,
     133,    45,    39,   101,   101,   115,   117,   162,    39,    12,
      13,    25,    39,    43,    48,    11,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   116,   103,     8,     9,
      10,     6,     7,    23,    24,    16,    17,    18,    19,    14,
      15,    20,    22,    21,    27,    28,    49,   160,    40,    47,
      89,    44,    41,   125,   118,   115,    42,    80,    81,    82,
     134,   135,   152,    40,    47,    40,   101,   162,    89,    40,
     100,   115,   117,    89,   115,   103,   103,   103,   104,   104,
     105,   105,   106,   106,   106,   106,   107,   107,   108,   109,
     110,   111,   112,   117,    41,   140,   161,   137,   115,   126,
      44,    46,    46,    46,   115,   103,    40,    40,    40,    47,
      44,    46,    42,   141,   140,    42,    47,   115,   114,    45,
      52,    54,    57,    58,    59,    60,    61,    62,    63,    64,
      76,    77,    89,   117,   119,   120,   128,   138,   139,   140,
     142,   143,   144,   145,   146,   149,   151,   115,    39,    39,
      39,   138,    39,    89,    45,    45,    45,   117,    39,    77,
     128,   128,    46,    45,   121,    42,   143,    41,   117,   117,
     117,    57,   119,   144,   150,    45,    45,   117,   128,    45,
     147,    40,    40,    40,    39,   144,    40,    42,    55,    56,
     148,   138,   138,   117,    40,   117,   138,   118,   138,    53,
      40,   138,    40,   138,   138,    45,   138
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    96,    97,    97,    97,    97,    98,    98,    98,    98,
      98,    98,    98,    99,    99,    99,    99,    99,    99,    99,
      99,   100,   100,   101,   101,   101,   101,   101,   101,   102,
     102,   102,   102,   102,   102,   103,   103,   104,   104,   104,
     104,   105,   105,   105,   106,   106,   106,   107,   107,   107,
     107,   107,   108,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   118,   119,   120,   120,   120,   120,   121,   121,
     122,   122,   123,   123,   124,   124,   124,   124,   124,   124,
     125,   126,   126,   127,   127,   128,   128,   128,   128,   128,
     128,   128,   129,   129,   131,   130,   132,   132,   133,   133,
     134,   134,   135,   135,   135,   136,   136,   137,   138,   138,
     138,   138,   138,   138,   139,   140,   141,   140,   142,   142,
     143,   143,   144,   144,   145,   145,   145,   146,   147,   147,
     148,   148,   149,   149,   149,   149,   149,   150,   150,   151,
     151,   151,   151,   151,   153,   152,   154,   152,   152,   152,
     152,   156,   155,   157,   155,   158,   155,   160,   159,   161,
     159,   159,   162
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     3,     3,     2,
       2,     1,     3,     1,     2,     2,     2,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     2,     2,     3,     1,     3,
       1,     0,     2,     1,     1,     2,     2,     3,     4,     4,
       3,     1,     3,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     6,     1,     1,     0,     2,
       1,     1,     2,     2,     2,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     2,     2,     0,     4,     1,     2,
       1,     1,     1,     2,     5,     7,     4,     4,     0,     2,
       3,     2,     5,     5,     7,     6,     7,     1,     1,     3,
       2,     2,     2,     3,     0,     3,     0,     4,     2,     4,
       1,     0,     5,     0,     6,     0,     5,     0,     5,     0,
       6,     2,     2
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
#line 424 "src/parser.y"
    {
        dbg("primary_expression -> IDENTIFIER");
        Node* n = new Node();
        string name = string((yyvsp[0].str));
        Symbol* sym = lookupSymbol(name);
        dbg("");
        dbg("Looking up symbol: " + name);
        dbg("");
        if (!sym) {
            if(name=="printf" || name=="scanf" || name=="malloc" || name=="free"){
                n->place = name;
                n->printName = name;
            }
            else{
                dbg("Symbol not found: " + name);
                yyerror("Use of undeclared identifier '" + name + "'.");
            }
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
            n->place = sym->name;
            n->printName = sym->printName;
        }
        dbg("n->place is " + n->place + ", n->name is " + name);
        (yyval.node) = n;
    }
#line 1985 "src/parser.tab.c"
    break;

  case 3: /* primary_expression: constant  */
#line 463 "src/parser.y"
    { 
        dbg("primary_expression -> constant");
        (yyval.node) = (yyvsp[0].node);
    }
#line 1994 "src/parser.tab.c"
    break;

  case 4: /* primary_expression: LROUND expression RROUND  */
#line 468 "src/parser.y"
    {
        dbg("primary_expression -> ( expression )");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2003 "src/parser.tab.c"
    break;

  case 5: /* primary_expression: STRING_LITERAL  */
#line 473 "src/parser.y"
    {
        dbg("constant -> STRING_LITERAL");
        (yyval.node) = new Node(string((yyvsp[0].str)), "string", "const");
    }
#line 2012 "src/parser.tab.c"
    break;

  case 6: /* constant: DECIMAL_LITERAL  */
#line 482 "src/parser.y"
    {
        dbg("constant -> DECIMAL_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "int", "const");
        n->argCount = stoi(string((yyvsp[0].str)));
        dbg("");
        dbg("Integer constant value: " + to_string(n->argCount));
        dbg("");
        (yyval.node) = n;
    }
#line 2026 "src/parser.tab.c"
    break;

  case 7: /* constant: CHARACTER_LITERAL  */
#line 492 "src/parser.y"
    {
        dbg("constant -> CHARACTER_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "char", "const");
        dbg("");
        dbg("Character constant value: " + string(1, (yyvsp[0].str)[1]));
        dbg("");
        (yyval.node) = n;
    }
#line 2039 "src/parser.tab.c"
    break;

  case 8: /* constant: EXPONENT_LITERAL  */
#line 501 "src/parser.y"
    {
        dbg("constant -> EXPONENT_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "double", "const");
        (yyval.node) = n;
    }
#line 2049 "src/parser.tab.c"
    break;

  case 9: /* constant: DOUBLE_LITERAL  */
#line 507 "src/parser.y"
    {
        dbg("constant -> DOUBLE_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "double", "const");
        (yyval.node) = n;
    }
#line 2059 "src/parser.tab.c"
    break;

  case 10: /* constant: NULLPTR  */
#line 513 "src/parser.y"
    {
        dbg("constant -> NULLPTR");
        Node* n = new Node("0", "nullptr", "const");
        (yyval.node) = n;
    }
#line 2069 "src/parser.tab.c"
    break;

  case 11: /* constant: TRUE  */
#line 519 "src/parser.y"
    {
        dbg("constant -> TRUE");
        Node* n = new Node("1", "bool", "const");
        (yyval.node) = n;
    }
#line 2079 "src/parser.tab.c"
    break;

  case 12: /* constant: FALSE  */
#line 525 "src/parser.y"
    {
        dbg("constant -> FALSE");
        Node* n = new Node("0", "bool", "const");
        (yyval.node) = n;
    }
#line 2089 "src/parser.tab.c"
    break;

  case 13: /* postfix_expression: primary_expression  */
#line 534 "src/parser.y"
    { 
        dbg("postfix_expression -> primary_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 2098 "src/parser.tab.c"
    break;

  case 14: /* postfix_expression: postfix_expression LSQUARE expression RSQUARE  */
#line 539 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression [ expression ]");
        Node* base = (yyvsp[-3].node); 
        Node* idx = (yyvsp[-1].node);
        Node* n = new Node();

        if(!base || !idx) {
            yyerror("Invalid array subscript operation.");
        }
        else
        {
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
#line 2160 "src/parser.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression LROUND RROUND  */
#line 597 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression ( )");
        Node* fun = (yyvsp[-2].node);
        dbg(fun->place);

        string funcName = fun->place;
        dbg("Function name before processing: " + funcName);
        int idx=0;
        for(int i=0;i<funcName.size();i++){
            if(funcName[i]=='$') idx = i;
        }
        funcName.erase(0,idx);
        dbg("Function name after processing: " + funcName);
        funcInfo* s = lookupFunction(funcName);
        check_func_access(s);
        Node* n = new Node();
        if(!s){
            yyerror("Call to non-function '" + funcName + "'.");
        }
        if(s)
        {
            if(s->paramCount != 0){
                yyerror("Call to function '" + funcName + "' with incorrect number of arguments.");
            }

            n->code = fun->code;
            n->type = s->returnType;

            if(fun->type=="void"){
                n->code.push_back("call " + funcName + ", 0;");
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = call " + funcName + ", 0;");
            }
        }
        (yyval.node) = n;
    }
#line 2203 "src/parser.tab.c"
    break;

  case 16: /* postfix_expression: postfix_expression LROUND argument_expression_list RROUND  */
#line 636 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression ( argument_expression_list )");
        Node* fun = (yyvsp[-3].node);
        dbg("133");
        dbg(fun->place);
        string name = fun->place;
        string original = fun->place;
        Node* args = (yyvsp[-1].node);
        int idx=0;
        for(int i=0;i<name.size();i++){
            if(name[i]=='$') idx = i;
        }
        name.erase(0,idx);

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
            dbg("121212121");
            yyerror("Function '" + original + "' with given argument types not found.");
        }
        if(s)
        {
            if (s->paramCount != args->argCount) {
                yyerror("Call to function '" + original + "' with incorrect number of arguments.");
            }
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
#line 2267 "src/parser.tab.c"
    break;

  case 17: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 695 "src/parser.y"
                                            {
        dbg("postfix_expression -> postfix_expression . IDENTIFIER");
        Node* obj = (yyvsp[-2].node);
        string currentType = obj->type;
        dbg("currentType is " + currentType);
        if(obj->type!="struct" && obj->type!="class" && classTable.find(currentType) == classTable.end()){
            yyerror("Dot operator can not be applied here.");
        }

        int idx=0;
        for(int i=0;i<obj->place.size();i++){
            if(obj->place[i]=='$') idx = i;
        }
        obj->place.erase(0,idx+1);
        string nm = obj->place + "." + string((yyvsp[0].str));


        dbg("");
        dbg(nm);
        dbg("");
        Symbol* s = lookupSymbol(nm);
        funcInfo* f = lookupFunction(nm);
        memberInfo* m = lookupClassMember(currentType,string((yyvsp[0].str)));

        if(!s)
            dbg("YES");

        Node* n = new Node();
        if(s) 
        {
            if(s->isFunction)
            {
                dbg("function");
                n->place = nm;
            }
            else
            {
                check_access(s);
                n->place = s->name;
                n->type = s->type;
                n->kind = s->kind;
            }
        }

        else if(m){
            n->type = m->type;
            n->kind = m->kind;
            n->place = nm;
        }
        else{
            yyerror("No member or function named '" + nm+"'.");
        }

        n->code = obj->code;
        dbg("1");
        // n->code.push_back(n->place + " = " + nm);
        (yyval.node) = n;
    }
#line 2330 "src/parser.tab.c"
    break;

  case 18: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 753 "src/parser.y"
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
            // n->code.push_back(n->place + " = " + tmp + "." + string($3));
            (yyval.node) = n;
      }
#line 2376 "src/parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression INCREMENT  */
#line 794 "src/parser.y"
                                       {
          dbg("postfix_expression -> postfix_expression ++");
          Node* v = (yyvsp[-1].node);
          if(!check_unary_comp(v->type,"++")){
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
#line 2400 "src/parser.tab.c"
    break;

  case 20: /* postfix_expression: postfix_expression DECREMENT  */
#line 813 "src/parser.y"
                                       { 
            dbg("postfix_expression -> postfix_expression --");
          Node* v = (yyvsp[-1].node);
          if(!check_unary_comp(v->type,"--")){
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
#line 2423 "src/parser.tab.c"
    break;

  case 21: /* argument_expression_list: assignment_expression  */
#line 836 "src/parser.y"
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
#line 2445 "src/parser.tab.c"
    break;

  case 22: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 854 "src/parser.y"
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
#line 2466 "src/parser.tab.c"
    break;

  case 23: /* unary_expression: postfix_expression  */
#line 874 "src/parser.y"
                             { 
        dbg("unary_expression -> postfix_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2474 "src/parser.tab.c"
    break;

  case 24: /* unary_expression: INCREMENT unary_expression  */
#line 877 "src/parser.y"
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
#line 2494 "src/parser.tab.c"
    break;

  case 25: /* unary_expression: DECREMENT unary_expression  */
#line 892 "src/parser.y"
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
#line 2514 "src/parser.tab.c"
    break;

  case 26: /* unary_expression: unary_operator cast_expression  */
#line 907 "src/parser.y"
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
            n = (yyvsp[0].node);
            //   n->place = newTemp();
            //   n->code.push_back(n->place + " = *" + rhs->place);
              n->type = rhs->type.substr(0, rhs->type.size() - 1);
              n->place = "*" + rhs->place;
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
#line 2556 "src/parser.tab.c"
    break;

  case 27: /* unary_expression: SIZEOF LROUND unary_expression RROUND  */
#line 944 "src/parser.y"
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
#line 2572 "src/parser.tab.c"
    break;

  case 28: /* unary_expression: SIZEOF LROUND return_type RROUND  */
#line 955 "src/parser.y"
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
#line 2587 "src/parser.tab.c"
    break;

  case 29: /* unary_operator: BITWISE_AND  */
#line 975 "src/parser.y"
                      { 
        dbg("unary_operator -> &");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2595 "src/parser.tab.c"
    break;

  case 30: /* unary_operator: STAR  */
#line 978 "src/parser.y"
               { 
        dbg("unary_operator -> *");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2603 "src/parser.tab.c"
    break;

  case 31: /* unary_operator: PLUS  */
#line 981 "src/parser.y"
               { 
        dbg("unary_operator -> +");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2611 "src/parser.tab.c"
    break;

  case 32: /* unary_operator: MINUS  */
#line 984 "src/parser.y"
                { 
        dbg("unary_operator -> -");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2619 "src/parser.tab.c"
    break;

  case 33: /* unary_operator: TILDE  */
#line 987 "src/parser.y"
                { 
        dbg("unary_operator -> ~");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2627 "src/parser.tab.c"
    break;

  case 34: /* unary_operator: LOGICAL_NOT  */
#line 990 "src/parser.y"
                      { 
        dbg("unary_operator -> !");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2635 "src/parser.tab.c"
    break;

  case 35: /* cast_expression: unary_expression  */
#line 1066 "src/parser.y"
                           { 
        dbg("cast_expression -> unary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2643 "src/parser.tab.c"
    break;

  case 36: /* cast_expression: LROUND return_type RROUND cast_expression  */
#line 1070 "src/parser.y"
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
#line 2661 "src/parser.tab.c"
    break;

  case 37: /* multiplicative_expression: cast_expression  */
#line 1087 "src/parser.y"
                          { 
        dbg("multiplicative_expression -> cast_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2669 "src/parser.tab.c"
    break;

  case 38: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 1091 "src/parser.y"
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
#line 2687 "src/parser.tab.c"
    break;

  case 39: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 1105 "src/parser.y"
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
#line 2706 "src/parser.tab.c"
    break;

  case 40: /* multiplicative_expression: multiplicative_expression MODULUS cast_expression  */
#line 1119 "src/parser.y"
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
#line 2725 "src/parser.tab.c"
    break;

  case 41: /* additive_expression: multiplicative_expression  */
#line 1137 "src/parser.y"
                                    { 
        dbg("additive_expression -> multiplicative_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2733 "src/parser.tab.c"
    break;

  case 42: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 1140 "src/parser.y"
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
#line 2752 "src/parser.tab.c"
    break;

  case 43: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 1154 "src/parser.y"
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
#line 2771 "src/parser.tab.c"
    break;

  case 44: /* shift_expression: additive_expression  */
#line 1172 "src/parser.y"
                              { 
        dbg("shift_expression -> additive_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2779 "src/parser.tab.c"
    break;

  case 45: /* shift_expression: shift_expression LEFT_SHIFT additive_expression  */
#line 1175 "src/parser.y"
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
#line 2798 "src/parser.tab.c"
    break;

  case 46: /* shift_expression: shift_expression RIGHT_SHIFT additive_expression  */
#line 1189 "src/parser.y"
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
#line 2817 "src/parser.tab.c"
    break;

  case 47: /* relational_expression: shift_expression  */
#line 1207 "src/parser.y"
                           { 
        dbg("relational_expression -> shift_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2825 "src/parser.tab.c"
    break;

  case 48: /* relational_expression: relational_expression GREATER_THAN shift_expression  */
#line 1210 "src/parser.y"
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
#line 2842 "src/parser.tab.c"
    break;

  case 49: /* relational_expression: relational_expression LESS_THAN shift_expression  */
#line 1222 "src/parser.y"
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
#line 2859 "src/parser.tab.c"
    break;

  case 50: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 1234 "src/parser.y"
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
#line 2876 "src/parser.tab.c"
    break;

  case 51: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 1246 "src/parser.y"
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
#line 2893 "src/parser.tab.c"
    break;

  case 52: /* equality_expression: relational_expression  */
#line 1262 "src/parser.y"
                                { 
        dbg("equality_expression -> relational_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2901 "src/parser.tab.c"
    break;

  case 53: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 1265 "src/parser.y"
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
#line 2919 "src/parser.tab.c"
    break;

  case 54: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 1278 "src/parser.y"
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
#line 2937 "src/parser.tab.c"
    break;

  case 55: /* and_expression: equality_expression  */
#line 1295 "src/parser.y"
                              { 
        dbg("and_expression -> equality_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2945 "src/parser.tab.c"
    break;

  case 56: /* and_expression: and_expression BITWISE_AND equality_expression  */
#line 1298 "src/parser.y"
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
#line 2963 "src/parser.tab.c"
    break;

  case 57: /* exclusive_or_expression: and_expression  */
#line 1315 "src/parser.y"
                         { 
        dbg("exclusive_or_expression -> and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2971 "src/parser.tab.c"
    break;

  case 58: /* exclusive_or_expression: exclusive_or_expression BITWISE_XOR and_expression  */
#line 1318 "src/parser.y"
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
#line 2989 "src/parser.tab.c"
    break;

  case 59: /* inclusive_or_expression: exclusive_or_expression  */
#line 1335 "src/parser.y"
                                  { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2997 "src/parser.tab.c"
    break;

  case 60: /* inclusive_or_expression: inclusive_or_expression BITWISE_OR exclusive_or_expression  */
#line 1338 "src/parser.y"
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
#line 3015 "src/parser.tab.c"
    break;

  case 61: /* logical_and_expression: inclusive_or_expression  */
#line 1355 "src/parser.y"
                                  { 
        dbg("logical_and_expression -> inclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3023 "src/parser.tab.c"
    break;

  case 62: /* logical_and_expression: logical_and_expression LOGICAL_AND inclusive_or_expression  */
#line 1358 "src/parser.y"
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
#line 3041 "src/parser.tab.c"
    break;

  case 63: /* logical_or_expression: logical_and_expression  */
#line 1375 "src/parser.y"
                                 { 
        dbg("logical_or_expression -> logical_and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3049 "src/parser.tab.c"
    break;

  case 64: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 1378 "src/parser.y"
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
#line 3067 "src/parser.tab.c"
    break;

  case 65: /* conditional_expression: logical_or_expression  */
#line 1396 "src/parser.y"
    { 
        dbg("conditional_expression -> logical_or_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3076 "src/parser.tab.c"
    break;

  case 66: /* conditional_expression: logical_or_expression QUESTION_MARK expression COLON conditional_expression  */
#line 1400 "src/parser.y"
                                                                                  {
        dbg("conditional_expression -> logical_or_expression ? expression : conditional_expression");
        Node* cond = (yyvsp[-4].node); 
        Node* e1 = (yyvsp[-2].node); 
        Node* e2 = (yyvsp[0].node);
        Node* n = new Node();

        if(e1->type != e2->type){
            yyerror("Type incompatibility in conditional expression.");
        }
        
        n->code = cond->code;
        n->place = newTemp();
        
        int condJumpIndex = n->code.size();
        n->code.push_back("if " + cond->place + "==false goto __");
        vector<int> falseList = makeList(condJumpIndex);
        
        n->code.insert(n->code.end(), e1->code.begin(), e1->code.end());
        n->code.push_back(n->place + " = " + e1->place);
        
        int endJumpIndex = n->code.size();
        n->code.push_back("goto __");
        vector<int> nextList = makeList(endJumpIndex);
        
        string Lfalse = newLabel();
        n->code.push_back(Lfalse + ":");
        backpatch(n->code, falseList, Lfalse);
        
        n->code.insert(n->code.end(), e2->code.begin(), e2->code.end());
        n->code.push_back(n->place + " = " + e2->place);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, nextList, Lend);
        n->type = e1->type;
        (yyval.node) = n;
    }
#line 3119 "src/parser.tab.c"
    break;

  case 67: /* assignment_expression: conditional_expression  */
#line 1442 "src/parser.y"
                                 { 
        dbg("assignment_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3127 "src/parser.tab.c"
    break;

  case 68: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 1445 "src/parser.y"
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
          n->place = left->place;
          n->type = left->type;
          (yyval.node) = n;
      }
#line 3157 "src/parser.tab.c"
    break;

  case 69: /* assignment_operator: ASSIGN  */
#line 1475 "src/parser.y"
                 { 
        dbg("assignment_operator -> =");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3165 "src/parser.tab.c"
    break;

  case 70: /* assignment_operator: STAR_EQUAL  */
#line 1478 "src/parser.y"
                     { 
        dbg("assignment_operator -> *=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3173 "src/parser.tab.c"
    break;

  case 71: /* assignment_operator: DIV_EQUAL  */
#line 1481 "src/parser.y"
                    { 
        dbg("assignment_operator -> /=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3181 "src/parser.tab.c"
    break;

  case 72: /* assignment_operator: MOD_EQUAL  */
#line 1484 "src/parser.y"
                    { 
        dbg("assignment_operator -> %=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3189 "src/parser.tab.c"
    break;

  case 73: /* assignment_operator: PLUS_EQUAL  */
#line 1487 "src/parser.y"
                     { 
        dbg("assignment_operator -> +=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3197 "src/parser.tab.c"
    break;

  case 74: /* assignment_operator: MINUS_EQUAL  */
#line 1490 "src/parser.y"
                      { 
        dbg("assignment_operator -> -=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3205 "src/parser.tab.c"
    break;

  case 75: /* assignment_operator: LEFT_SHIFT_EQ  */
#line 1493 "src/parser.y"
                        { 
        dbg("assignment_operator -> <<=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3213 "src/parser.tab.c"
    break;

  case 76: /* assignment_operator: RIGHT_SHIFT_EQ  */
#line 1496 "src/parser.y"
                         { 
        dbg("assignment_operator -> >>=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3221 "src/parser.tab.c"
    break;

  case 77: /* assignment_operator: AND_EQUAL  */
#line 1499 "src/parser.y"
                    { 
        dbg("assignment_operator -> &=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3229 "src/parser.tab.c"
    break;

  case 78: /* assignment_operator: XOR_EQUAL  */
#line 1502 "src/parser.y"
                    { 
        dbg("assignment_operator -> ^=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3237 "src/parser.tab.c"
    break;

  case 79: /* assignment_operator: OR_EQUAL  */
#line 1505 "src/parser.y"
                   { 
        dbg("assignment_operator -> |=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3245 "src/parser.tab.c"
    break;

  case 80: /* expression: assignment_expression  */
#line 1513 "src/parser.y"
    { 
        dbg("expression -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3254 "src/parser.tab.c"
    break;

  case 81: /* expression: expression COMMA assignment_expression  */
#line 1518 "src/parser.y"
        {
            dbg("expression -> expression , assignment_expression");
            Node* n = new Node();
            n->code = (yyvsp[-2].node)->code;
            n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
            n->place = (yyvsp[0].node)->place;
            (yyval.node) = n;
        }
#line 3267 "src/parser.tab.c"
    break;

  case 82: /* constant_expression: conditional_expression  */
#line 1531 "src/parser.y"
    { 
        dbg("constant_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3276 "src/parser.tab.c"
    break;

  case 83: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 1540 "src/parser.y"
    {
        dbg("declaration -> declaration_specifiers init_declarator_list ;");
        if(lastDeclType.find("static")!=string::npos){ 
            globalCode.insert(globalCode.end(), (yyvsp[-1].node)->code.begin(), (yyvsp[-1].node)->code.end());
            (yyval.node) = new Node();
        }
        else{
            (yyval.node) = (yyvsp[-1].node);
        }
    }
#line 3291 "src/parser.tab.c"
    break;

  case 84: /* declaration_specifiers: type_specifier  */
#line 1554 "src/parser.y"
                     {
        dbg("declaration_specifiers -> type_specifier");
        lastDeclType = string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
	}
#line 3301 "src/parser.tab.c"
    break;

  case 85: /* declaration_specifiers: STATIC type_specifier  */
#line 1559 "src/parser.y"
                            {
        dbg("declaration_specifiers -> static type_specifier");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
    }
#line 3311 "src/parser.tab.c"
    break;

  case 86: /* declaration_specifiers: CONST type_specifier  */
#line 1564 "src/parser.y"
                           {
        dbg("declaration_specifiers -> const type_specifier");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
	}
#line 3321 "src/parser.tab.c"
    break;

  case 87: /* declaration_specifiers: STATIC CONST type_specifier  */
#line 1569 "src/parser.y"
                                  {
        dbg("declaration_specifiers -> static const type_specifier");
        lastDeclType = string((yyvsp[-2].str))+string((yyvsp[-1].str))+string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
    }
#line 3331 "src/parser.tab.c"
    break;

  case 88: /* init_declarator_list: init_declarator  */
#line 1579 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3340 "src/parser.tab.c"
    break;

  case 89: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1584 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator_list , init_declarator");
        Node* n = (yyvsp[-2].node);
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        (yyval.node) = n;
    }
#line 3351 "src/parser.tab.c"
    break;

  case 90: /* pointer_opt: pointer_list  */
#line 1595 "src/parser.y"
    {
        dbg("pointer_opt -> pointer_list");
        (yyval.str) = (yyvsp[0].str);
    }
#line 3360 "src/parser.tab.c"
    break;

  case 91: /* pointer_opt: %empty  */
#line 1600 "src/parser.y"
    {
        dbg("pointer_opt -> <empty>");
        (yyval.str) = strdup("");
    }
#line 3369 "src/parser.tab.c"
    break;

  case 92: /* pointer_list: pointer_list STAR  */
#line 1609 "src/parser.y"
    {
        dbg("pointer_list -> pointer_list *");
        (yyval.str) = strdup((string("*")+string((yyvsp[-1].str))).c_str());
    }
#line 3378 "src/parser.tab.c"
    break;

  case 93: /* pointer_list: STAR  */
#line 1614 "src/parser.y"
    {
        dbg("pointer_list -> *");
        (yyval.str) = strdup("*");
    }
#line 3387 "src/parser.tab.c"
    break;

  case 94: /* init_declarator: IDENTIFIER  */
#line 1623 "src/parser.y"
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
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        
        n->argCount = 0;
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }

        Symbol* sym = lookupSymbol(n->place);
        string w = lastClassType+currentFunction+currentScope+n->place;
        sym->printName = w;
        
        if(lastClassType != "" && currentFunction == "global")
        {
            dbg("12" + n->place);
            dbg(currentFunction);
            dbg("13");
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
        dbg("Declared variable is: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");

        if(n->type.find("void")!=string::npos){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3478 "src/parser.tab.c"
    break;

  case 95: /* init_declarator: IDENTIFIER square_list  */
#line 1710 "src/parser.y"
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
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        for(int i = 0; i < (yyvsp[0].node)->argCount; i++)
        {
            n->type += "*";
        }

        bool ok = declareSymbol(n->place, n->type, n->kind, n->syn);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }
        
        Symbol* sym = lookupSymbol(n->place);
        string w = lastClassType+currentFunction+currentScope+n->place;
        sym->printName = w;
        

        if(lastClassType != "" && currentFunction == "global")
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

        if(n->type.find("void")!=string::npos){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3587 "src/parser.tab.c"
    break;

  case 96: /* init_declarator: pointer_list IDENTIFIER  */
#line 1815 "src/parser.y"
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
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }

        Symbol* sym = lookupSymbol(n->place);
        string w = lastClassType+currentFunction+currentScope+n->place;
        sym->printName = w;
       
        if(lastClassType != "" && currentFunction == "global")
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

        if(n->type.find("void")!=string::npos){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3677 "src/parser.tab.c"
    break;

  case 97: /* init_declarator: IDENTIFIER ASSIGN assignment_expression  */
#line 1902 "src/parser.y"
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
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }

        if(n->type != (yyvsp[0].node)->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
        Symbol* sym = lookupSymbol(n->place);
        string w = lastClassType+currentFunction+currentScope+n->place;
        sym->printName = w;
        n->code.push_back(w + " = " + (yyvsp[0].node)->place);
        
        if(lastClassType != "" && currentFunction == "global")
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

        if(n->type.find("void")!=string::npos){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3767 "src/parser.tab.c"
    break;

  case 98: /* init_declarator: pointer_list IDENTIFIER ASSIGN assignment_expression  */
#line 1989 "src/parser.y"
    {
        dbg("init_declarator -> pointer_list IDENTIFIER = assignment_expression ");
        Node* n = new Node();
        string name = string((yyvsp[-2].str));
        n->place = name;
        string stars = string((yyvsp[-3].str));
        
        n->type = lastDeclType + stars;
        n->code = (yyvsp[0].node)->code;
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

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }

        Symbol* sym = lookupSymbol(n->place);
        string w = lastClassType+currentFunction+currentScope+n->place;
        sym->printName = w;
        n->code.push_back(w + " = " + (yyvsp[0].node)->place);
       
        if(lastClassType != "" && currentFunction == "global")
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

        if(n->type.find("void")!=string::npos){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3860 "src/parser.tab.c"
    break;

  case 99: /* init_declarator: IDENTIFIER square_list ASSIGN initializer  */
#line 2079 "src/parser.y"
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
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
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

        bool ok = declareSymbol(n->place,n->type,n->kind,n->syn);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }

        Symbol* sym = lookupSymbol(n->place);
        string w = lastClassType+currentFunction+currentScope+n->place;
        sym->printName = w;

        string tmp = newTemp();
        n->code.push_back(tmp + " = &" + n->place);
        for(int i = 0; i < (yyvsp[0].node)->argCount; i++)
        {
            n->code.push_back("*(" + tmp + " + " + to_string(i*typeSize[(yyvsp[0].node)->type]) + ") = " + (yyvsp[0].node)->syn[i]);
        }

       
        if(lastClassType != "" && currentFunction == "global")
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
        if(n->type.find("void")!=string::npos){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3974 "src/parser.tab.c"
    break;

  case 100: /* initializer: LCURLY initializer_list RCURLY  */
#line 2260 "src/parser.y"
    { 
        dbg("initializer -> { initializer_list }");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3983 "src/parser.tab.c"
    break;

  case 101: /* initializer_list: assignment_expression  */
#line 2269 "src/parser.y"
    { 
        dbg("initializer_list -> assignment_expression");
        Node * n = (yyvsp[0].node);
        n->argCount = 1;
        if(n->place == ""){
            yyerror("Initializer type incorrect.");
        }
        n->syn.push_back(n->place);
        (yyval.node) = n;
    }
#line 3998 "src/parser.tab.c"
    break;

  case 102: /* initializer_list: initializer_list COMMA assignment_expression  */
#line 2280 "src/parser.y"
    {
        dbg("initializer_list -> initializer_list , assignment_expression");
        Node* n = (yyvsp[-2].node); 

        if(n->type != (yyvsp[0].node)->type)
        {
            yyerror("Type mismatch in initializer list.");
        }

        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        if((yyvsp[0].node)->place == ""){
            yyerror("Initializer type incorrect.");
        }
        n->syn.push_back((yyvsp[0].node)->place);
        n->argCount = n->argCount + 1;
        (yyval.node) = n;
    }
#line 4020 "src/parser.tab.c"
    break;

  case 103: /* square_list: square_list LSQUARE constant_expression RSQUARE  */
#line 2302 "src/parser.y"
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
#line 4038 "src/parser.tab.c"
    break;

  case 104: /* square_list: LSQUARE constant_expression RSQUARE  */
#line 2316 "src/parser.y"
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
#line 4055 "src/parser.tab.c"
    break;

  case 105: /* type_specifier: VOID  */
#line 2343 "src/parser.y"
                 { 
        dbg("type_specifier -> VOID");
        (yyval.str) = strdup("void"); lastDeclType = "void"; }
#line 4063 "src/parser.tab.c"
    break;

  case 106: /* type_specifier: CHAR  */
#line 2346 "src/parser.y"
                 { 
        dbg("type_specifier -> CHAR");
        (yyval.str) = strdup("char"); lastDeclType = "char"; }
#line 4071 "src/parser.tab.c"
    break;

  case 107: /* type_specifier: INT  */
#line 2349 "src/parser.y"
                 { 
        dbg("type_specifier -> INT");
        (yyval.str) = strdup("int"); lastDeclType = "int"; }
#line 4079 "src/parser.tab.c"
    break;

  case 108: /* type_specifier: LONG  */
#line 2352 "src/parser.y"
                 { 
        dbg("type_specifier -> LONG");
        (yyval.str) = strdup("long"); lastDeclType = "long"; }
#line 4087 "src/parser.tab.c"
    break;

  case 109: /* type_specifier: DOUBLE  */
#line 2355 "src/parser.y"
                 { 
        dbg("type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); lastDeclType = "double"; }
#line 4095 "src/parser.tab.c"
    break;

  case 110: /* type_specifier: BOOL  */
#line 2358 "src/parser.y"
                 { 
        dbg("type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); lastDeclType = "bool"; }
#line 4103 "src/parser.tab.c"
    break;

  case 111: /* type_specifier: TYPE_NAME  */
#line 2365 "src/parser.y"
    { 
        dbg("type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str); 
        lastDeclType = string((yyvsp[0].str)); 
        if(typeSize.find(lastDeclType) == typeSize.end()){
            yyerror("Unknown type '" + lastDeclType + "'.");    
        }
        else
        {
            dbg("User defined type found: " + lastDeclType);
        }
    }
#line 4120 "src/parser.tab.c"
    break;

  case 112: /* translation_unit: external_declaration  */
#line 2381 "src/parser.y"
                               { 
        dbg("translation_unit -> external_declaration");
        finalRoot = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 4128 "src/parser.tab.c"
    break;

  case 113: /* translation_unit: translation_unit external_declaration  */
#line 2384 "src/parser.y"
                                                {
            dbg("translation_unit -> translation_unit external_declaration");
          Node* a = (yyvsp[-1].node); Node* b = (yyvsp[0].node);
          if (a) {
            a->code.push_back("");
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; (yyval.node) = a; }
          else { finalRoot = b; (yyval.node) = b; }
      }
#line 4142 "src/parser.tab.c"
    break;

  case 114: /* $@1: %empty  */
#line 2398 "src/parser.y"
    { 
        lastClassType = string((yyvsp[-1].str)); 
        if(typeSize.find(lastClassType) != typeSize.end()){
            yyerror("Redefinition of class/struct '" + lastClassType + "'.");
        }
        typeSize[lastClassType] = 0;
        dbg("named struct/class: " + lastClassType);
        classOffset = 0;
        pushScope();
    }
#line 4157 "src/parser.tab.c"
    break;

  case 115: /* struct_or_class_specifier: struct_or_class IDENTIFIER LCURLY $@1 struct_or_class_member_list RCURLY  */
#line 2409 "src/parser.y"
    { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        popScope();
        (yyval.node) = (yyvsp[-1].node); 
        typeSize[lastClassType] = classOffset;   // NEW: store computed size
        lastClassType.clear(); 
    }
#line 4169 "src/parser.tab.c"
    break;

  case 116: /* struct_or_class: STRUCT  */
#line 2421 "src/parser.y"
    { 
        dbg("struct_or_class -> STRUCT");
        (yyval.node) = new Node(); 
        lastUsage = "public";
    }
#line 4179 "src/parser.tab.c"
    break;

  case 117: /* struct_or_class: CLASS  */
#line 2427 "src/parser.y"
    { 
        dbg("struct_or_class -> CLASS");
        (yyval.node) = new Node(); 
        lastUsage = "private";
    }
#line 4189 "src/parser.tab.c"
    break;

  case 118: /* struct_or_class_member_list: %empty  */
#line 2437 "src/parser.y"
    { 
        dbg("struct_or_class_member_list -> <empty>");
        dbg("lastClassType: " + lastClassType);
        (yyval.node) = new Node(); 
    }
#line 4199 "src/parser.tab.c"
    break;

  case 119: /* struct_or_class_member_list: struct_or_class_member_list struct_or_class_member  */
#line 2443 "src/parser.y"
    { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        dbg("lastClassType: " + lastClassType);
        Node* n = (yyvsp[-1].node); 
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; 
    }
#line 4211 "src/parser.tab.c"
    break;

  case 120: /* struct_or_class_member: access_specifier_label  */
#line 2454 "src/parser.y"
    { 
        dbg("struct_or_class_member -> access_specifier_label");
        dbg("lastClassType: " + lastClassType);
        lastUsage = string((yyvsp[0].node)->place);
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4222 "src/parser.tab.c"
    break;

  case 121: /* struct_or_class_member: external_declaration  */
#line 2461 "src/parser.y"
    { 
        dbg("struct_or_class_member -> member_declaration");
        dbg("lastClassType: " + lastClassType);
        dbg("");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4233 "src/parser.tab.c"
    break;

  case 122: /* access_specifier_label: PUBLIC COLON  */
#line 2471 "src/parser.y"
    { 
        dbg("access_specifier_label -> PUBLIC :");
        dbg("lastClassType: " + lastClassType);
        Node* n=new Node(); 
        n->place = "public";
        (yyval.node) = n; 
    }
#line 4245 "src/parser.tab.c"
    break;

  case 123: /* access_specifier_label: PRIVATE COLON  */
#line 2479 "src/parser.y"
    { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); 
        n->place = "private";
        (yyval.node) = n; 
    }
#line 4256 "src/parser.tab.c"
    break;

  case 124: /* access_specifier_label: PROTECTED COLON  */
#line 2486 "src/parser.y"
    { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); 
        n->place = "protected";
        (yyval.node) = n; 
    }
#line 4267 "src/parser.tab.c"
    break;

  case 125: /* parameter_list: parameter_declaration  */
#line 2634 "src/parser.y"
                                { 
            dbg("parameter_list -> parameter_declaration");
            (yyval.node) = (yyvsp[0].node); 
        }
#line 4276 "src/parser.tab.c"
    break;

  case 126: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 2639 "src/parser.y"
        {
            dbg("parameter_list -> parameter_list , parameter_declaration");
            Node* n = (yyvsp[-2].node);
            n->syn.insert(n->syn.end(), (yyvsp[0].node)->syn.begin(), (yyvsp[0].node)->syn.end()); 
            (yyval.node) = n;
        }
#line 4287 "src/parser.tab.c"
    break;

  case 127: /* parameter_declaration: return_type IDENTIFIER  */
#line 2650 "src/parser.y"
        {
            dbg("parameter_declaration -> return_type IDENTIFIER");
            Node* n = new Node();
            n->syn.push_back(string((yyvsp[-1].str))); 
            n->syn.push_back(string((yyvsp[0].str)));
            (yyval.node) = n;
        }
#line 4299 "src/parser.tab.c"
    break;

  case 128: /* statement: labeled_statement  */
#line 2661 "src/parser.y"
                            { 
        dbg("statement -> labeled_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4307 "src/parser.tab.c"
    break;

  case 129: /* statement: compound_statement  */
#line 2664 "src/parser.y"
                             { 
        dbg("statement -> compound_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4315 "src/parser.tab.c"
    break;

  case 130: /* statement: expression_statement  */
#line 2667 "src/parser.y"
                               { 
        dbg("statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4323 "src/parser.tab.c"
    break;

  case 131: /* statement: selection_statement  */
#line 2670 "src/parser.y"
                              { 
        dbg("statement -> selection_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4331 "src/parser.tab.c"
    break;

  case 132: /* statement: iteration_statement  */
#line 2673 "src/parser.y"
                              { 
        dbg("statement -> iteration_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4339 "src/parser.tab.c"
    break;

  case 133: /* statement: jump_statement  */
#line 2676 "src/parser.y"
                         { 
        dbg("statement -> jump_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4347 "src/parser.tab.c"
    break;

  case 134: /* labeled_statement: IDENTIFIER COLON  */
#line 2761 "src/parser.y"
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
#line 4362 "src/parser.tab.c"
    break;

  case 135: /* compound_statement: LCURLY RCURLY  */
#line 2775 "src/parser.y"
                        {
            dbg("compound_statement -> { }");
          Node* n = new Node();
          (yyval.node) = n;
      }
#line 4372 "src/parser.tab.c"
    break;

  case 136: /* $@5: %empty  */
#line 2781 "src/parser.y"
    {
        currentScope += "$";
        pushScope();
    }
#line 4381 "src/parser.tab.c"
    break;

  case 137: /* compound_statement: LCURLY $@5 statement_list RCURLY  */
#line 2784 "src/parser.y"
                            {
            dbg("compound_statement -> { statement_list }");
          Node* n = (yyvsp[-1].node);
          popScope();
          currentScope.pop_back();
          (yyval.node) = n;
      }
#line 4393 "src/parser.tab.c"
    break;

  case 138: /* statement_list: block_item  */
#line 2795 "src/parser.y"
                     { 
        dbg("statement_list -> block_item");
        (yyval.node) = (yyvsp[0].node); }
#line 4401 "src/parser.tab.c"
    break;

  case 139: /* statement_list: statement_list block_item  */
#line 2798 "src/parser.y"
                                    {
            dbg("statement_list -> statement_list block_item");
          Node* n = (yyvsp[-1].node);
          if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 4412 "src/parser.tab.c"
    break;

  case 140: /* block_item: statement  */
#line 2808 "src/parser.y"
                { 
        dbg("block_item -> statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4420 "src/parser.tab.c"
    break;

  case 141: /* block_item: declaration  */
#line 2811 "src/parser.y"
                  { 
        dbg("block_item -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4428 "src/parser.tab.c"
    break;

  case 142: /* expression_statement: SEMICOLON  */
#line 2817 "src/parser.y"
                    { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4436 "src/parser.tab.c"
    break;

  case 143: /* expression_statement: expression SEMICOLON  */
#line 2820 "src/parser.y"
                               { 
        dbg("expression_statement -> expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4444 "src/parser.tab.c"
    break;

  case 144: /* selection_statement: IF LROUND expression RROUND statement  */
#line 2826 "src/parser.y"
                                                                  {
          dbg("selection_statement -> if ( expression ) statement");
          Node* e = (yyvsp[-2].node);
          Node* s1 = (yyvsp[0].node);
          Node* n = new Node();
          
          n->code = e->code;
          int falseJumpIndex = n->code.size();
          n->code.push_back("if " + e->place + "==false goto __");
          vector<int> falseList = makeList(falseJumpIndex);
          
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          
          string Lend = newLabel();
          n->code.push_back(Lend + ":");
          backpatch(n->code, falseList, Lend);
          
          (yyval.node) = n;
      }
#line 4468 "src/parser.tab.c"
    break;

  case 145: /* selection_statement: IF LROUND expression RROUND statement ELSE statement  */
#line 2845 "src/parser.y"
                                                           {
          dbg("selection_statement -> if ( expression ) statement else statement");
          Node* e = (yyvsp[-4].node);
          Node* s1 = (yyvsp[-2].node);
          Node* s2 = (yyvsp[0].node);
          Node* n = new Node();
          
          n->code = e->code;
          
          int falseJumpIndex = n->code.size();
          n->code.push_back("if " + e->place + "==false goto __");
          vector<int> falseList = makeList(falseJumpIndex);
          
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          
          int endJumpIndex = n->code.size();
          n->code.push_back("goto __");
          vector<int> endList = makeList(endJumpIndex);
          
          string Lfalse = newLabel();
          n->code.push_back(Lfalse + ":");
          backpatch(n->code, falseList, Lfalse);
          
          n->code.insert(n->code.end(), s2->code.begin(), s2->code.end());
          
          string Lend = newLabel();
          n->code.push_back(Lend + ":");
          backpatch(n->code, endList, Lend);
          (yyval.node) = n;
      }
#line 4503 "src/parser.tab.c"
    break;

  case 146: /* selection_statement: switch_head LCURLY case_list RCURLY  */
#line 2875 "src/parser.y"
                                          {
        dbg("selection_statement -> switch_head { case_list }");
        Node* switchExpr = (yyvsp[-3].node);
        Node* cases = (yyvsp[-1].node);
        Node* n = new Node();
        
        n->code = switchExpr->code;
        n->code.insert(n->code.end(), cases->syn.begin(), cases->syn.end());
        n->code.push_back("goto __");
        n->code.insert(n->code.end(), cases->code.begin(), cases->code.end());
        
        string exitLabel = newLabel();
        n->code.push_back(exitLabel + ":");

        vector<int> exitList;
        for(size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "goto __") {
                exitList.push_back(i);
            }
        }

        backpatch(n->code,exitList,exitLabel);
        (yyval.node) = n;
      }
#line 4532 "src/parser.tab.c"
    break;

  case 147: /* switch_head: SWITCH LROUND expression RROUND  */
#line 2902 "src/parser.y"
                                      {
        dbg("switch_head -> SWITCH ( expression )");
        Node* e = (yyvsp[-1].node);
        Node* n = new Node();
        n->code = e->code;
        n->place = e->place;
        (yyval.node) = n;
      }
#line 4545 "src/parser.tab.c"
    break;

  case 148: /* case_list: %empty  */
#line 2913 "src/parser.y"
       {
        dbg("case_list -> <empty>");
        Node* n = new Node();
        (yyval.node) = n;
      }
#line 4555 "src/parser.tab.c"
    break;

  case 149: /* case_list: case_list case_item  */
#line 2918 "src/parser.y"
                          {
        dbg("case_list -> case_list case_item");
        Node* prev = (yyvsp[-1].node);
        Node* curr = (yyvsp[0].node);
        prev->syn.insert(prev->syn.end(), curr->syn.begin(), curr->syn.end());
        prev->code.insert(prev->code.end(), curr->code.begin(), curr->code.end());
        (yyval.node) = prev;
      }
#line 4568 "src/parser.tab.c"
    break;

  case 150: /* case_item: CASE constant_expression statement  */
#line 2929 "src/parser.y"
                                         {
        dbg("case_item -> CASE constant_expression : statement");
        Node* caseVal = (yyvsp[-1].node);
        Node* stmt = (yyvsp[0].node);
        Node* n = new Node();
        
        string caseLabel = newLabel();
        n->syn.push_back("if " + (yyvsp[(-2) - (3)].node)->place + " == " + caseVal->place + " goto " + caseLabel);
        
        n->code.push_back(caseLabel + ":");
        n->code.insert(n->code.end(), stmt->code.begin(), stmt->code.end());
        
        for (size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break;") {
                n->code[i] = "goto __";
            }
        }
        
        (yyval.node) = n;
      }
#line 4593 "src/parser.tab.c"
    break;

  case 151: /* case_item: DEFAULT statement  */
#line 2949 "src/parser.y"
                        {
        dbg("case_item -> DEFAULT : statement");
        Node* stmt = (yyvsp[0].node);
        Node* n = new Node();
        
        string defaultLabel = newLabel();
        n->syn.push_back("goto " + defaultLabel);
        
        n->code.push_back(defaultLabel + ":");
        n->code.insert(n->code.end(), stmt->code.begin(), stmt->code.end());
        
        for (size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break;") {
                n->code[i] = "goto __";
            }
        }
        // n->code.push_back("goto __");        
        (yyval.node) = n;
      }
#line 4617 "src/parser.tab.c"
    break;

  case 152: /* iteration_statement: WHILE LROUND expression RROUND statement  */
#line 2972 "src/parser.y"
                                               {
        dbg("iteration_statement -> WHILE ( expression ) statement");
        Node* cond = (yyvsp[-2].node); 
        Node* body = (yyvsp[0].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
        int jumpIndex = n->code.size();
        n->code.push_back("if " + cond->place + "==false goto __");
        vector<int> falseList = makeList(jumpIndex);
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, falseList, Lend);
        (yyval.node) = n;
    }
#line 4644 "src/parser.tab.c"
    break;

  case 153: /* iteration_statement: UNTIL LROUND expression RROUND statement  */
#line 2994 "src/parser.y"
                                               {
        dbg("iteration_statement -> UNTIL ( expression ) statement");
        Node* cond = (yyvsp[-2].node); 
        Node* body = (yyvsp[0].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
        int jumpIndex = n->code.size();
        n->code.push_back("if " + cond->place + "==true goto __");
        vector<int> falseList = makeList(jumpIndex);
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, falseList, Lend);
        (yyval.node) = n;
    }
#line 4671 "src/parser.tab.c"
    break;

  case 154: /* iteration_statement: DO statement WHILE LROUND expression RROUND SEMICOLON  */
#line 3016 "src/parser.y"
                                                            {
        dbg("iteration_statement -> DO statement WHILE ( expression ) ;");
        Node* body = (yyvsp[-5].node);
        Node* cond = (yyvsp[-2].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
        
        int jumpIndex = n->code.size();
        n->code.push_back("if " + cond->place + "==true goto " + Lbegin);
        (yyval.node) = n;
    }
#line 4692 "src/parser.tab.c"
    break;

  case 155: /* iteration_statement: FOR LROUND for_init_statement expression_statement RROUND statement  */
#line 3032 "src/parser.y"
                                                                          {
        dbg("iteration_statement -> FOR ( for_init_statement expression_statement ) statement");
        Node* init = (yyvsp[-3].node);
        Node* cond = (yyvsp[-2].node);
        Node* body = (yyvsp[0].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        if(init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
        n->code.push_back(Lbegin + ":");
        
        vector<int> falseList;
        if (cond && cond->place != "") {
            n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
            int jumpIndex = n->code.size();
            n->code.push_back("if " + cond->place + "==false goto __");
            falseList = makeList(jumpIndex);
        }
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        if (!falseList.empty())
            backpatch(n->code,falseList,Lend);

        (yyval.node) = n;
    }
#line 4726 "src/parser.tab.c"
    break;

  case 156: /* iteration_statement: FOR LROUND for_init_statement expression_statement expression RROUND statement  */
#line 3061 "src/parser.y"
                                                                                     {
        dbg("iteration_statement -> FOR ( for_init_statement expression_statement expression ) statement");
        Node* init = (yyvsp[-4].node);
        Node* cond = (yyvsp[-3].node);
        Node* iter = (yyvsp[-2].node);
        Node* body = (yyvsp[0].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
        n->code.push_back(Lbegin + ":");
        
        vector<int> falseList;
        if (cond && cond->place != "") {
            n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
            int jumpIndex = n->code.size();
            n->code.push_back("if " + cond->place + "==false goto __");
            falseList = makeList(jumpIndex);
        }
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        if (iter) n->code.insert(n->code.end(), iter->code.begin(), iter->code.end());
        n->code.push_back("goto " + Lbegin);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        if (!falseList.empty())
            backpatch(n->code, falseList, Lend);
        (yyval.node) = n;
    }
#line 4761 "src/parser.tab.c"
    break;

  case 157: /* for_init_statement: expression_statement  */
#line 3094 "src/parser.y"
                               { 
        dbg("for_init_statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4769 "src/parser.tab.c"
    break;

  case 158: /* for_init_statement: declaration  */
#line 3098 "src/parser.y"
    { 
        dbg("for_init_statement -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4777 "src/parser.tab.c"
    break;

  case 159: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 3105 "src/parser.y"
                                    {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string((yyvsp[-1].str)));
          (yyval.node) = n;
      }
#line 4788 "src/parser.tab.c"
    break;

  case 160: /* jump_statement: CONTINUE SEMICOLON  */
#line 3111 "src/parser.y"
                             {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); 
          n->code.push_back("continue;"); 
          (yyval.node) = n;
      }
#line 4799 "src/parser.tab.c"
    break;

  case 161: /* jump_statement: BREAK SEMICOLON  */
#line 3117 "src/parser.y"
                          {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); 
          n->code.push_back("break;"); 
          (yyval.node) = n;
      }
#line 4810 "src/parser.tab.c"
    break;

  case 162: /* jump_statement: RETURN SEMICOLON  */
#line 3123 "src/parser.y"
                           {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); 
          if(lastFnType != "void")
              yyerror("Return statement must return a value.");
          n->code.push_back("return;"); 
          (yyval.node) = n;
      }
#line 4823 "src/parser.tab.c"
    break;

  case 163: /* jump_statement: RETURN expression SEMICOLON  */
#line 3132 "src/parser.y"
    {
        dbg("jump_statement -> RETURN expression ;");
        Node* expr = (yyvsp[-1].node);
        if(expr == nullptr)
            yyerror("Return statement must return a value.");
        
        Node* n = new Node();
        if(lastClassType == "")
        {
            dbg("Return type: " + expr->type + ", Expected type: " + funcTable[currentFunction].returnType);

            dbg("");
            dbg("lastDeclType: " + lastDeclType);
            dbg("currentFunction: " + currentFunction);
            dbg("");
            if(expr->type != funcTable[currentFunction].returnType){
                yyerror("Return type mismatch in function '" + currentFunction + "'.");
            }
            dbg("Function '" + currentFunction + "' has return statement returning '" + expr->place + "'.");
            n->code = expr->code;
            n->code.push_back("return " + expr->place);
        }
        else
        {
            dbg("3");
            dbg(currentFunction);
            dbg("Return type: " + expr->type + ", Expected type: " + classTable[lastClassType][currentFunction].method.returnType);
            if(expr->type != classTable[lastClassType][currentFunction].method.returnType){
                yyerror("Return type mismatch in method '" + currentFunction + "'.");
            }
            dbg("Method '" + currentFunction + "' has return statement returning '" + expr->place + "'.");
            n->code = expr->code;
            n->code.push_back("return " + expr->place);
        }
        (yyval.node) = n;
    }
#line 4864 "src/parser.tab.c"
    break;

  case 164: /* $@6: %empty  */
#line 3173 "src/parser.y"
    {
        dbg("external_declaration -> type_specifier");
        lastDeclType = string((yyvsp[0].str));
        lastFnType = lastDeclType;
    }
#line 4874 "src/parser.tab.c"
    break;

  case 165: /* external_declaration: type_specifier $@6 external  */
#line 3179 "src/parser.y"
    { 
        dbg("external_declaration -> type_specifier external");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4883 "src/parser.tab.c"
    break;

  case 166: /* $@7: %empty  */
#line 3184 "src/parser.y"
    {
        dbg("external_declaration -> type_specifier pointer_list");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
        lastFnType = lastDeclType;
        dbg("");
        dbg("lastDeclType in external_declaration: " + lastDeclType);
        dbg("");
    }
#line 4896 "src/parser.tab.c"
    break;

  case 167: /* external_declaration: type_specifier pointer_list $@7 external  */
#line 3193 "src/parser.y"
    { 
        dbg("external_declaration -> type_specifier pointer_list external");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4905 "src/parser.tab.c"
    break;

  case 168: /* external_declaration: struct_or_class_specifier SEMICOLON  */
#line 3198 "src/parser.y"
    { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        (yyval.node) = (yyvsp[-1].node); 
    }
#line 4914 "src/parser.tab.c"
    break;

  case 169: /* external_declaration: TYPEDEF return_type IDENTIFIER SEMICOLON  */
#line 3202 "src/parser.y"
                                               {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string((yyvsp[-1].str))] = typeSize[string((yyvsp[-2].str))];
        (yyval.node) = new Node();
    }
#line 4924 "src/parser.tab.c"
    break;

  case 170: /* external_declaration: declare  */
#line 3207 "src/parser.y"
              {
        dbg("external_declaration -> declare");
        globalCode.insert(globalCode.begin(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end());
        (yyval.node) = new Node();
    }
#line 4934 "src/parser.tab.c"
    break;

  case 171: /* $@8: %empty  */
#line 3216 "src/parser.y"
    {
        dbg("declaration_specifiers -> const type_specifier");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
    }
#line 4943 "src/parser.tab.c"
    break;

  case 172: /* declare: CONST type_specifier $@8 init_declarator_list SEMICOLON  */
#line 3221 "src/parser.y"
    {
        dbg("declaration_specifiers -> const type_specifier init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 4952 "src/parser.tab.c"
    break;

  case 173: /* $@9: %empty  */
#line 3226 "src/parser.y"
    {
        dbg("declaration_specifiers -> static const type_specifier");
        lastDeclType = string((yyvsp[-2].str))+string((yyvsp[-1].str))+string((yyvsp[0].str));
    }
#line 4961 "src/parser.tab.c"
    break;

  case 174: /* declare: STATIC CONST type_specifier $@9 init_declarator_list SEMICOLON  */
#line 3231 "src/parser.y"
    {
        dbg("declaration_specifiers -> static const type_specifier init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 4970 "src/parser.tab.c"
    break;

  case 175: /* $@10: %empty  */
#line 3236 "src/parser.y"
    {
        dbg("declaration_specifiers -> static type_specifier");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
    }
#line 4979 "src/parser.tab.c"
    break;

  case 176: /* declare: STATIC type_specifier $@10 init_declarator_list SEMICOLON  */
#line 3241 "src/parser.y"
    {
        dbg("declaration_specifiers -> static type_specifier init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 4988 "src/parser.tab.c"
    break;

  case 177: /* $@11: %empty  */
#line 3249 "src/parser.y"
    {
        dbg("");
        dbg("lastFnType in external: " + lastFnType);
        dbg("");
        dbg("external -> IDENTIFIER ( )");
        string fname = string((yyvsp[-2].str));

        if(lastClassType == "")
        {
            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            
            if(funcTable.find(fname) != funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string(lastFnType) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;

            funcTable[fname].returnType = string(lastFnType);
            funcTable[fname].paramCount = 0;
            dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");
        }// dbg("Function '" + fname + "' with " + to_string(funcTable[fname].paramCount) + " parameters declared.");
        else
        {
            if(classTable[lastClassType].find(string((yyvsp[-2].str))) != classTable[lastClassType].end())
                yyerror("Method redeclaration: " + fname);
            classTable[lastClassType][string((yyvsp[-2].str))].kind = "function";
            classTable[lastClassType][string((yyvsp[-2].str))].type = lastFnType;
            classTable[lastClassType][string((yyvsp[-2].str))].place = string((yyvsp[-2].str));
            funcInfo f;
            f.place = string((yyvsp[-2].str));
            f.returnType = lastFnType;
            f.paramCount = 0;
            f.original = string((yyvsp[-2].str));
            if(string(lastFnType) == "void") f.hasReturn = false;
            else f.hasReturn = true;
            classTable[lastClassType][string((yyvsp[-2].str))].method = f;
            dbg("1");
            dbg("Method '" + fname + "' with return type '" + f.returnType + "' declared.");
            dbg("2");
        }
        currentFunction = fname;
        localTemp = 0; localLabel = 0;

        pushScope();
    }
#line 5039 "src/parser.tab.c"
    break;

  case 178: /* external: IDENTIFIER LROUND RROUND $@11 compound_statement  */
#line 3296 "src/parser.y"
    {
        dbg("external -> IDENTIFIER ( ) compound_statement");
        Node* n = new Node();
        n->place = string((yyvsp[-4].str));
        n->type = lastFnType;
        n->argCount = 0;
        n->kind = "function";
        string fname = string((yyvsp[-4].str));

        if(lastClassType != "")
            fname = lastClassType + "." + fname;
        if((yyvsp[0].node)->code.back().substr(0,6) != "return")
        {
            yyerror("Missing return statement in function '" + fname + "'.");
        }
        n->code.push_back(fname + ":");
        if((yyvsp[0].node)) n->code.insert(n->code.end(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end());
        popScope();
        currentFunction = "global";
        lastFnType="int";
        (yyval.node) = n;
    }
#line 5066 "src/parser.tab.c"
    break;

  case 179: /* $@12: %empty  */
#line 3319 "src/parser.y"
    {
        dbg("");
        dbg("lastDeclType in external: " + lastFnType);
        dbg("");
        dbg("external -> IDENTIFIER ( parameter_list )");
        string fname = string((yyvsp[-3].str));
        
        if(lastClassType == "")
        {
            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            
            for (int i=0;i<(yyvsp[-1].node)->syn.size();i+=2)
            {
                fname += "_" + (yyvsp[-1].node)->syn[i];
            }

            if(funcTable.find(fname) != funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string(lastFnType) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;

            funcTable[fname].returnType = string(lastFnType); 
            funcTable[fname].paramCount = (yyvsp[-1].node)->syn.size()/2;
            dbg("");
            dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");

            for (int i=0;i<(yyvsp[-1].node)->syn.size();i+=2){
                funcTable[fname].paramTypes.push_back((yyvsp[-1].node)->syn[i]);
                dbg("Parameter: " + (yyvsp[-1].node)->syn[i+1] + " of type " + (yyvsp[-1].node)->syn[i]);
            }
            dbg("");
        }
        else
        {
            for (int i=0;i<(yyvsp[-1].node)->syn.size();i+=2)
            {
                fname += "_" + (yyvsp[-1].node)->syn[i];
            }
            string methodName = fname;
            if(classTable[lastClassType].find(methodName) != classTable[lastClassType].end())
                yyerror("Method redeclaration: " + lastClassType + "." + methodName);
            classTable[lastClassType][methodName].kind = "function";
            classTable[lastClassType][methodName].type = lastFnType;
            classTable[lastClassType][methodName].place = methodName;

            funcInfo f;
            f.place = methodName;
            f.original = string((yyvsp[-3].str));
            f.returnType = lastFnType;
            f.paramCount = (yyvsp[-1].node)->syn.size()/2;
            if(string(lastFnType) == "void") f.hasReturn = false;
            else f.hasReturn = true;

            for (int i=0;i<(yyvsp[-1].node)->syn.size();i+=2)
            {
                f.paramTypes.push_back((yyvsp[-1].node)->syn[i]);
                dbg("Parameter: " + (yyvsp[-1].node)->syn[i+1] + " of type " + (yyvsp[-1].node)->syn[i]);
            }
            classTable[lastClassType][methodName].method = f;
        }
        currentFunction = fname;
        localTemp = 0; localLabel = 0;
        pushScope();

        for(int i=1;i<(yyvsp[-1].node)->syn.size();i+=2)
        {
            string pname = (yyvsp[-1].node)->syn[i];
            string ptype = (yyvsp[-1].node)->syn[i-1];
            bool ok = declareSymbol(pname,ptype);
            Symbol* sym = lookupSymbol(pname);
            string w = lastClassType + "."+ currentFunction + currentScope + "." +pname;
            sym->printName = w;
            if(!ok) yyerror("Duplicate parameter name '" + pname + "' in function '" + fname + "'.");
        }
    }
#line 5148 "src/parser.tab.c"
    break;

  case 180: /* external: IDENTIFIER LROUND parameter_list RROUND $@12 compound_statement  */
#line 3397 "src/parser.y"
    {
        dbg("external -> IDENTIFIER ( parameter_list ) compound_statement");
        Node* n = new Node();
        string fname = string((yyvsp[-5].str));
        for (int i=0;i<(yyvsp[-3].node)->syn.size();i+=2)
        {
            fname += "_" + (yyvsp[-3].node)->syn[i];
        }

        n->place = fname;
        n->type = lastFnType;

        n->argCount = (yyvsp[-3].node)->syn.size()/2;
        n->kind = "function";
        popScope(); 

        if(lastClassType != "")
            fname = lastClassType + "." + fname;

        if((yyvsp[0].node)->code.back().substr(0,6) != "return")
        {
            yyerror("Missing return statement in function '" + fname + "'.");
        }
        n->code.push_back(fname + ":");

        if((yyvsp[0].node)) n->code.insert(n->code.end(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end());
        finalRoot = n;
        currentFunction = "global";

        lastFnType="int";
        (yyval.node) = n;
    }
#line 5185 "src/parser.tab.c"
    break;

  case 181: /* external: init_declarator_list SEMICOLON  */
#line 3430 "src/parser.y"
        { 
            dbg("external -> init_declarator_list ;");
            globalCode.insert(globalCode.begin(),(yyvsp[-1].node)->code.begin(),(yyvsp[-1].node)->code.end());
            (yyval.node) = new Node();
        }
#line 5195 "src/parser.tab.c"
    break;

  case 182: /* return_type: type_specifier pointer_opt  */
#line 3527 "src/parser.y"
    { 
        dbg("return_type -> type_specifier pointer_opt");
        (yyval.str) = strdup( (string((yyvsp[-1].str)) + string((yyvsp[0].str))).c_str() );
    }
#line 5204 "src/parser.tab.c"
    break;


#line 5208 "src/parser.tab.c"

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

#line 3533 "src/parser.y"



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
        globalCode.push_back("");
        finalRoot->code.insert(finalRoot->code.begin(),globalCode.begin(),globalCode.end());
        string indent="";
        for(int i=0;i<finalRoot->code.size();i++) {
            if(finalRoot->code[i].back()==':') indent="";
            else indent="    ";
            cout<<indent<<finalRoot->code[i]<<"\n";
        }
    }

    return 0;
}
