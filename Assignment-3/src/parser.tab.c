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
        string printName;
        vector<string> syn;
        string place;
        string type;
        string kind;
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
        string printName;
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
    unordered_map<string,string> typeDefTable;

    unordered_map<string,int> typeSize = {
        {"int", 4}, {"char", 1}, {"bool", 1}, {"double", 8}, {"string", 8}, {"nullptr", 8}
    };
    
    vector<string> errors;
    static string currentFunction = "";
    static int globalTemp = 0, globalLabel = 0;
    static int localTemp = 0, localLabel = 0;
    static int classOffset = 0;
    static string lastDeclType = "int";
    static string lastClassType = "";
    static string lastUsage = "";
    static string lastFnType = "int";
    static string currentScope = "";
    static string switchType = "";
    static string switchVar = "";
    static bool inloop = false;
    static bool inFunction = false;

    vector<string> globalCode;

    Node* finalRoot = nullptr;

    string newTemp() {
        if (currentFunction == "") {
            return "global.t" + to_string(++globalTemp);
        } else {
            return currentFunction + ".t" + to_string(++localTemp);
        }
    }
    string newLabel() {
        if (currentFunction == "") {
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
        if(from.back()=='*' && to=="bool") return true;
        return false;
    }

    extern int yylex();
    extern int yyparse();


#line 414 "src/parser.tab.c"

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
  YYSYMBOL_LOGICAL_NOT = 25,               /* LOGICAL_NOT  */
  YYSYMBOL_LOGICAL_AND = 26,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 27,                /* LOGICAL_OR  */
  YYSYMBOL_PLUS_EQUAL = 28,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 29,               /* MINUS_EQUAL  */
  YYSYMBOL_STAR_EQUAL = 30,                /* STAR_EQUAL  */
  YYSYMBOL_DIV_EQUAL = 31,                 /* DIV_EQUAL  */
  YYSYMBOL_MOD_EQUAL = 32,                 /* MOD_EQUAL  */
  YYSYMBOL_AND_EQUAL = 33,                 /* AND_EQUAL  */
  YYSYMBOL_OR_EQUAL = 34,                  /* OR_EQUAL  */
  YYSYMBOL_XOR_EQUAL = 35,                 /* XOR_EQUAL  */
  YYSYMBOL_LEFT_SHIFT_EQ = 36,             /* LEFT_SHIFT_EQ  */
  YYSYMBOL_RIGHT_SHIFT_EQ = 37,            /* RIGHT_SHIFT_EQ  */
  YYSYMBOL_LROUND = 38,                    /* LROUND  */
  YYSYMBOL_RROUND = 39,                    /* RROUND  */
  YYSYMBOL_LCURLY = 40,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 41,                    /* RCURLY  */
  YYSYMBOL_LSQUARE = 42,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 43,                   /* RSQUARE  */
  YYSYMBOL_SEMICOLON = 44,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 45,                     /* COLON  */
  YYSYMBOL_COMMA = 46,                     /* COMMA  */
  YYSYMBOL_DOT = 47,                       /* DOT  */
  YYSYMBOL_QUESTION_MARK = 48,             /* QUESTION_MARK  */
  YYSYMBOL_IF = 49,                        /* IF  */
  YYSYMBOL_ELSE = 50,                      /* ELSE  */
  YYSYMBOL_SWITCH = 51,                    /* SWITCH  */
  YYSYMBOL_CASE = 52,                      /* CASE  */
  YYSYMBOL_DEFAULT = 53,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 54,                     /* WHILE  */
  YYSYMBOL_DO = 55,                        /* DO  */
  YYSYMBOL_FOR = 56,                       /* FOR  */
  YYSYMBOL_GOTO = 57,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 58,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 59,                     /* BREAK  */
  YYSYMBOL_RETURN = 60,                    /* RETURN  */
  YYSYMBOL_UNTIL = 61,                     /* UNTIL  */
  YYSYMBOL_VOID = 62,                      /* VOID  */
  YYSYMBOL_INT = 63,                       /* INT  */
  YYSYMBOL_DOUBLE = 64,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 65,                      /* CHAR  */
  YYSYMBOL_BOOL = 66,                      /* BOOL  */
  YYSYMBOL_LONG = 67,                      /* LONG  */
  YYSYMBOL_TRUE = 68,                      /* TRUE  */
  YYSYMBOL_FALSE = 69,                     /* FALSE  */
  YYSYMBOL_NULLPTR = 70,                   /* NULLPTR  */
  YYSYMBOL_TILDE = 71,                     /* TILDE  */
  YYSYMBOL_STATIC = 72,                    /* STATIC  */
  YYSYMBOL_CONST = 73,                     /* CONST  */
  YYSYMBOL_SIZEOF = 74,                    /* SIZEOF  */
  YYSYMBOL_STRING_LITERAL = 75,            /* STRING_LITERAL  */
  YYSYMBOL_CLASS = 76,                     /* CLASS  */
  YYSYMBOL_STRUCT = 77,                    /* STRUCT  */
  YYSYMBOL_PUBLIC = 78,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 79,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 80,                 /* PROTECTED  */
  YYSYMBOL_IDENTIFIER = 81,                /* IDENTIFIER  */
  YYSYMBOL_INVALID_IDENTIFIER = 82,        /* INVALID_IDENTIFIER  */
  YYSYMBOL_DECIMAL_LITERAL = 83,           /* DECIMAL_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 84,            /* DOUBLE_LITERAL  */
  YYSYMBOL_EXPONENT_LITERAL = 85,          /* EXPONENT_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 86,         /* CHARACTER_LITERAL  */
  YYSYMBOL_LOWER_THAN_ELSE = 87,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 88,                  /* $accept  */
  YYSYMBOL_primary_expression = 89,        /* primary_expression  */
  YYSYMBOL_constant = 90,                  /* constant  */
  YYSYMBOL_postfix_expression = 91,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 92,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 93,          /* unary_expression  */
  YYSYMBOL_unary_operator = 94,            /* unary_operator  */
  YYSYMBOL_cast_expression = 95,           /* cast_expression  */
  YYSYMBOL_cast_type = 96,                 /* cast_type  */
  YYSYMBOL_cast_type_specifier = 97,       /* cast_type_specifier  */
  YYSYMBOL_multiplicative_expression = 98, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 99,       /* additive_expression  */
  YYSYMBOL_shift_expression = 100,         /* shift_expression  */
  YYSYMBOL_relational_expression = 101,    /* relational_expression  */
  YYSYMBOL_equality_expression = 102,      /* equality_expression  */
  YYSYMBOL_and_expression = 103,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 104,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 105,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 106,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 107,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 108,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 109,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 110,      /* assignment_operator  */
  YYSYMBOL_expression = 111,               /* expression  */
  YYSYMBOL_constant_expression = 112,      /* constant_expression  */
  YYSYMBOL_declaration = 113,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 114,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 115,     /* init_declarator_list  */
  YYSYMBOL_pointer_opt = 116,              /* pointer_opt  */
  YYSYMBOL_pointer_list = 117,             /* pointer_list  */
  YYSYMBOL_init_declarator = 118,          /* init_declarator  */
  YYSYMBOL_initializer = 119,              /* initializer  */
  YYSYMBOL_initializer_list = 120,         /* initializer_list  */
  YYSYMBOL_square_list = 121,              /* square_list  */
  YYSYMBOL_type_specifier = 122,           /* type_specifier  */
  YYSYMBOL_translation_unit = 123,         /* translation_unit  */
  YYSYMBOL_struct_or_class_specifier = 124, /* struct_or_class_specifier  */
  YYSYMBOL_125_1 = 125,                    /* $@1  */
  YYSYMBOL_struct_or_class = 126,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 127, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 128,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 129,   /* access_specifier_label  */
  YYSYMBOL_parameter_list = 130,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 131,    /* parameter_declaration  */
  YYSYMBOL_statement = 132,                /* statement  */
  YYSYMBOL_labeled_statement = 133,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 134,       /* compound_statement  */
  YYSYMBOL_135_5 = 135,                    /* $@5  */
  YYSYMBOL_statement_list = 136,           /* statement_list  */
  YYSYMBOL_block_item = 137,               /* block_item  */
  YYSYMBOL_expression_statement = 138,     /* expression_statement  */
  YYSYMBOL_selection_statement = 139,      /* selection_statement  */
  YYSYMBOL_switch_head = 140,              /* switch_head  */
  YYSYMBOL_141_6 = 141,                    /* $@6  */
  YYSYMBOL_case_list = 142,                /* case_list  */
  YYSYMBOL_case_item = 143,                /* case_item  */
  YYSYMBOL_iteration_statement = 144,      /* iteration_statement  */
  YYSYMBOL_145_7 = 145,                    /* $@7  */
  YYSYMBOL_146_8 = 146,                    /* $@8  */
  YYSYMBOL_147_9 = 147,                    /* $@9  */
  YYSYMBOL_148_10 = 148,                   /* $@10  */
  YYSYMBOL_149_11 = 149,                   /* $@11  */
  YYSYMBOL_for_start = 150,                /* for_start  */
  YYSYMBOL_for_init_statement = 151,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 152,           /* jump_statement  */
  YYSYMBOL_external_declaration = 153,     /* external_declaration  */
  YYSYMBOL_154_12 = 154,                   /* $@12  */
  YYSYMBOL_155_13 = 155,                   /* $@13  */
  YYSYMBOL_declare = 156,                  /* declare  */
  YYSYMBOL_157_14 = 157,                   /* $@14  */
  YYSYMBOL_158_15 = 158,                   /* $@15  */
  YYSYMBOL_159_16 = 159,                   /* $@16  */
  YYSYMBOL_external = 160,                 /* external  */
  YYSYMBOL_161_17 = 161,                   /* $@17  */
  YYSYMBOL_162_18 = 162,                   /* $@18  */
  YYSYMBOL_return_type = 163               /* return_type  */
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
#define YYLAST   947

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  331

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   342


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
      85,    86,    87
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   427,   427,   468,   473,   478,   487,   499,   510,   518,
     526,   534,   542,   553,   558,   630,   688,   795,   905,   928,
     956,   979,  1004,  1007,  1025,  1044,  1096,  1110,  1127,  1130,
    1133,  1136,  1139,  1142,  1149,  1153,  1174,  1182,  1185,  1188,
    1191,  1194,  1197,  1200,  1220,  1223,  1239,  1256,  1277,  1280,
    1300,  1320,  1323,  1339,  1359,  1362,  1377,  1392,  1407,  1426,
    1429,  1444,  1463,  1466,  1485,  1488,  1508,  1511,  1530,  1533,
    1552,  1555,  1573,  1578,  1621,  1627,  1678,  1681,  1684,  1687,
    1690,  1693,  1696,  1699,  1702,  1705,  1708,  1715,  1720,  1733,
    1742,  1758,  1765,  1770,  1775,  1784,  1790,  1801,  1807,  1815,
    1820,  1829,  1932,  2050,  2151,  2262,  2367,  2552,  2561,  2572,
    2594,  2608,  2636,  2639,  2642,  2645,  2648,  2651,  2657,  2679,
    2684,  2700,  2699,  2722,  2728,  2739,  2744,  2755,  2762,  2772,
    2780,  2787,  2936,  2940,  2951,  2963,  2966,  2969,  2972,  2975,
    2978,  2985,  2999,  3005,  3004,  3031,  3034,  3044,  3047,  3053,
    3056,  3062,  3084,  3117,  3145,  3145,  3158,  3163,  3174,  3200,
    3223,  3223,  3259,  3259,  3296,  3296,  3331,  3331,  3373,  3373,
    3421,  3430,  3433,  3441,  3447,  3453,  3459,  3467,  3509,  3508,
    3521,  3520,  3534,  3540,  3546,  3555,  3554,  3565,  3564,  3575,
    3574,  3588,  3587,  3663,  3662,  3843,  3947
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
  "BITWISE_OR", "BITWISE_XOR", "LEFT_SHIFT", "RIGHT_SHIFT", "LOGICAL_NOT",
  "LOGICAL_AND", "LOGICAL_OR", "PLUS_EQUAL", "MINUS_EQUAL", "STAR_EQUAL",
  "DIV_EQUAL", "MOD_EQUAL", "AND_EQUAL", "OR_EQUAL", "XOR_EQUAL",
  "LEFT_SHIFT_EQ", "RIGHT_SHIFT_EQ", "LROUND", "RROUND", "LCURLY",
  "RCURLY", "LSQUARE", "RSQUARE", "SEMICOLON", "COLON", "COMMA", "DOT",
  "QUESTION_MARK", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT", "WHILE",
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "UNTIL", "VOID",
  "INT", "DOUBLE", "CHAR", "BOOL", "LONG", "TRUE", "FALSE", "NULLPTR",
  "TILDE", "STATIC", "CONST", "SIZEOF", "STRING_LITERAL", "CLASS",
  "STRUCT", "PUBLIC", "PRIVATE", "PROTECTED", "IDENTIFIER",
  "INVALID_IDENTIFIER", "DECIMAL_LITERAL", "DOUBLE_LITERAL",
  "EXPONENT_LITERAL", "CHARACTER_LITERAL", "LOWER_THAN_ELSE", "$accept",
  "primary_expression", "constant", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "cast_type", "cast_type_specifier",
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
  "selection_statement", "switch_head", "$@6", "case_list", "case_item",
  "iteration_statement", "$@7", "$@8", "$@9", "$@10", "$@11", "for_start",
  "for_init_statement", "jump_statement", "external_declaration", "$@12",
  "$@13", "declare", "$@14", "$@15", "$@16", "external", "$@17", "$@18",
  "return_type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-264)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     228,    76,  -264,  -264,  -264,  -264,  -264,  -264,  -264,   124,
      76,  -264,  -264,    35,    87,     1,    -8,  -264,  -264,    35,
      37,    76,  -264,  -264,  -264,    74,     3,  -264,  -264,  -264,
      93,  -264,    74,    80,  -264,    34,    34,  -264,     3,    -4,
     -20,    36,  -264,  -264,  -264,  -264,    34,    10,    39,    42,
    -264,   821,   174,   821,    12,  -264,    34,   116,  -264,   112,
    -264,  -264,  -264,  -264,  -264,   841,   841,  -264,  -264,   504,
    -264,  -264,  -264,  -264,   106,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,    28,   338,   821,  -264,    20,   168,   175,
      31,   195,   137,   125,   146,   167,   -17,  -264,  -264,  -264,
       0,  -264,   115,  -264,  -264,   157,   162,   821,  -264,   821,
     867,  -264,   821,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,   176,    35,  -264,    21,   538,  -264,  -264,    51,
     821,   136,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,   821,  -264,   821,   821,   821,   821,   821,
     821,   821,   821,   821,   821,   821,   821,   821,   821,   821,
     821,   821,   821,   821,   184,  -264,    76,  -264,  -264,   821,
    -264,   187,  -264,  -264,   186,   189,   197,  -264,  -264,  -264,
     821,  -264,  -264,   821,   204,   205,  -264,    22,  -264,    26,
    -264,  -264,  -264,  -264,  -264,    20,    20,   168,   168,   175,
     175,   175,   175,    31,    31,   195,   137,   125,   146,   167,
     166,   207,  -264,   184,  -264,  -264,   -14,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,   821,  -264,   821,  -264,
     340,  -264,  -264,   821,  -264,  -264,  -264,   211,  -264,   212,
    -264,  -264,   164,   208,   213,   700,   217,   141,    76,   206,
     126,  -264,    34,  -264,  -264,  -264,  -264,   258,  -264,  -264,
    -264,   219,  -264,   222,  -264,  -264,   821,   223,   821,   619,
     224,  -264,  -264,  -264,   134,   821,    76,  -264,  -264,  -264,
    -264,   148,  -264,  -264,  -264,   422,    84,   821,   109,   215,
    -264,  -264,   122,  -264,  -264,   -16,  -264,  -264,   720,   619,
     233,  -264,   229,  -264,  -264,   821,   619,  -264,   740,   226,
    -264,   619,   821,   619,   619,  -264,  -264,   123,   619,  -264,
     127,  -264,  -264,   619,  -264,  -264,   230,  -264,   619,  -264,
    -264
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   118,   112,   114,   116,   113,   117,   115,     0,
       0,   124,   123,   178,     0,     0,     0,   119,   184,    98,
       0,     0,   189,   185,   100,   180,     0,     1,   120,   182,
       0,   196,    97,     0,   187,     0,     0,    99,     0,   101,
       0,     0,    95,   179,   121,   183,     0,   101,     0,     0,
     181,     0,     0,     0,   102,   195,     0,   103,   125,     0,
     190,   186,    30,    31,    29,     0,     0,    28,    33,     0,
      11,    12,    10,    32,     0,     5,     2,     6,     9,     8,
       7,    13,     3,    22,    34,     0,    44,    48,    51,    54,
      59,    62,    64,    66,    68,    70,    72,    74,   104,   191,
       0,   132,     0,    34,    89,     0,     0,     0,    96,     0,
       0,   188,     0,    23,    24,    43,    37,    39,    41,    38,
      42,    40,     0,    98,    87,     0,     0,    18,    19,     0,
       0,     0,    76,    80,    81,    77,    78,    79,    84,    86,
      85,    82,    83,     0,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   193,     0,   134,   111,     0,
     106,     0,   105,   122,     0,     0,     0,   126,   127,   128,
       0,    36,     4,     0,     0,     0,    15,     0,    20,     0,
      17,    75,    45,    46,    47,    49,    50,    52,    53,    56,
      55,    57,    58,    60,    61,    63,    65,    67,    69,    71,
       0,   143,   192,     0,   133,   108,     0,   110,   129,   130,
     131,    35,    88,    26,    27,    16,     0,    14,     0,   142,
       0,   194,   107,     0,    21,    73,   149,     0,   154,     0,
     164,   170,     0,     0,     0,     0,     0,     0,     0,     2,
       0,   148,     0,    91,   147,   135,   136,     0,   145,   137,
     138,     0,   139,     0,   140,   109,     0,     0,     0,     0,
       0,   174,   175,   176,     0,     0,     0,    92,    93,   141,
     150,     0,   144,   146,   156,     0,     0,     0,     0,     0,
     173,   177,     0,    94,    90,     0,   172,   171,     0,     0,
       0,   160,     0,   162,   153,     0,     0,   157,     0,   151,
     155,     0,     0,     0,     0,   159,   166,     0,     0,   161,
       0,   163,   158,     0,   168,   152,     0,   167,     0,   165,
     169
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -264,  -264,  -264,  -264,  -264,   -52,  -264,   -68,   147,  -264,
      71,    72,    29,    70,   119,   120,   121,   142,   118,  -264,
     -51,     2,  -264,   -50,  -104,    -3,  -264,   -31,   163,    -7,
     231,  -264,  -264,  -264,    -1,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,   131,   150,  -264,  -148,  -264,  -264,    49,
    -263,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,     4,  -264,  -264,  -264,  -264,
    -264,  -264,   247,  -264,  -264,   287
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    81,    82,    83,   187,    84,    85,    86,   122,   123,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   124,   143,   250,   105,   251,   252,    40,    31,    41,
      42,   170,   216,    54,    13,    14,    15,    58,    16,   110,
     177,   178,   100,   101,   254,   255,   256,   230,   257,   258,
     259,   260,   261,   267,   295,   307,   262,   311,   313,   269,
     323,   328,   263,   298,   264,    17,    26,    38,    18,    36,
      46,    35,    43,   164,   213,   102
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      19,   103,   104,   171,    48,    49,    25,    51,    22,    23,
     162,    24,    32,   113,   114,    59,   212,   144,    28,   125,
      34,    51,   297,   106,    55,   304,    56,   232,   145,   146,
     147,   163,   233,   103,    52,   308,   305,   306,    53,   165,
     127,   128,    24,    24,    37,    29,   166,   152,   153,   154,
     155,    19,    53,    98,   107,   103,   104,    62,    63,    64,
     182,   225,   125,    65,    66,   231,   129,   183,   226,   227,
     130,    67,   183,    30,   184,   131,    68,   192,   193,   194,
     189,     2,    37,    60,    39,    56,    61,    27,    56,    69,
     186,     1,     2,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   172,   221,   210,   179,    47,    32,    57,    33,    70,
      71,    72,    73,   299,    45,    74,    75,   109,   103,     2,
     183,   188,    76,    44,    77,    78,    79,    80,     3,     4,
       5,     6,     7,     8,   126,   191,     2,   159,   301,     3,
       4,     5,     6,     7,     8,   183,   111,   158,    56,     9,
      10,   303,   324,    11,    12,    19,   326,   160,   183,   183,
     280,   215,   183,   183,   148,   149,   103,   235,   291,     2,
     183,   199,   200,   201,   202,   222,     3,     4,     5,     6,
       7,     8,   294,   161,    56,   274,   167,    21,   150,   151,
     168,   314,   169,     3,     4,     5,     6,     7,     8,   156,
     157,   228,   183,    99,   276,   180,   286,   190,   288,   195,
     196,   281,   197,   198,   211,   292,   203,   204,   234,   253,
     217,   218,     1,     2,   219,   265,     3,     4,     5,     6,
       7,     8,   220,   223,   224,   270,   277,   278,   229,   266,
     268,   279,   271,   103,   104,   275,   253,   272,   317,   284,
     285,   287,   320,     2,    62,    63,    64,   312,   290,   302,
      65,    66,   310,   185,   329,   293,   318,   205,    67,   206,
     209,   207,   296,    68,   253,    50,   181,   108,    20,   300,
       3,     4,     5,     6,     7,     8,    69,   214,   211,   282,
       9,    10,   236,   208,    11,    12,   283,   237,     0,   238,
       0,     0,   239,   240,   241,   242,   243,   244,   245,   246,
       3,     4,     5,     6,     7,     8,    70,    71,    72,    73,
     247,   248,    74,    75,     0,     0,     0,     0,     0,   249,
       0,    77,    78,    79,    80,     2,    62,    63,    64,   132,
       0,     0,    65,    66,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,    68,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,     0,     0,    69,     0,
     211,     0,     0,     0,   236,     0,     0,     0,     0,   237,
       0,   238,     0,     0,   239,   240,   241,   242,   243,   244,
     245,   246,     3,     4,     5,     6,     7,     8,    70,    71,
      72,    73,   247,   248,    74,    75,     0,     0,     0,   289,
       0,   249,     0,    77,    78,    79,    80,     2,    62,    63,
      64,     0,     0,     0,    65,    66,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,    68,     0,   309,
       0,     0,     0,     0,     0,     0,   315,     0,     0,     0,
      69,   319,     0,   321,   322,     0,   236,     0,   325,     0,
       0,     0,     0,   327,     0,     0,     0,     0,   330,     0,
       0,     0,     0,     0,     3,     4,     5,     6,     7,     8,
      70,    71,    72,    73,   247,   248,    74,    75,     0,     0,
       0,     0,     0,    76,     0,    77,    78,    79,    80,   115,
      62,    63,    64,     0,     0,     0,    65,    66,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,    68,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    69,   115,    62,    63,    64,     0,     0,     0,
      65,    66,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,    68,     0,     0,   116,   117,   118,   119,
     120,   121,    70,    71,    72,    73,   112,     0,    74,    75,
       0,     0,     0,     0,     0,    76,     0,    77,    78,    79,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,   117,   118,   119,   120,   121,    70,    71,    72,    73,
       0,     0,    74,    75,     0,     0,     0,     0,     0,    76,
       0,    77,    78,    79,    80,    62,    63,    64,     0,     0,
       0,    65,    66,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,    68,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    69,     0,   211,
       0,     0,     0,   236,     0,     0,     0,     0,   237,     0,
     238,     0,     0,   239,   240,   241,   242,   243,   244,   245,
     246,     0,     0,     0,     0,     0,     0,    70,    71,    72,
      73,     0,     0,    74,    75,     0,     0,     0,     0,     0,
     249,     0,    77,    78,    79,    80,    62,    63,    64,     0,
       0,     0,    65,    66,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,    68,    62,    63,    64,     0,
       0,     0,    65,    66,     0,     0,     0,     0,    69,     0,
      67,     0,     0,     0,   273,    68,    62,    63,    64,     0,
       0,     0,    65,    66,     0,     0,     0,     0,    69,     0,
      67,     0,     0,     0,   236,    68,     0,     0,    70,    71,
      72,    73,     0,     0,    74,    75,     0,     0,    69,   316,
       0,    76,     0,    77,    78,    79,    80,     0,    70,    71,
      72,    73,     0,     0,    74,    75,     0,     0,     0,     0,
       0,    76,     0,    77,    78,    79,    80,     0,    70,    71,
      72,    73,     0,     0,    74,    75,     0,     0,     0,     0,
       0,    76,     0,    77,    78,    79,    80,    62,    63,    64,
       0,     0,     0,    65,    66,     0,     0,     0,     0,     0,
       0,    67,     0,     0,     0,     0,    68,    62,    63,    64,
       0,     0,     0,    65,    66,     0,     0,     0,     0,    69,
       0,    67,     0,     0,     0,     0,    68,     0,     0,     0,
       0,     1,     2,     0,     0,     0,     0,     0,     0,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
      71,    72,    73,     0,     0,    74,    75,     0,     0,     0,
       0,     0,    76,     0,    77,    78,    79,    80,   173,    70,
      71,    72,    73,     0,     0,    74,    75,     0,     0,     0,
       0,     0,    76,     0,    77,    78,    79,    80,     0,     3,
       4,     5,     6,     7,     8,     0,     0,     0,     0,     9,
      10,     0,     0,    11,    12,   174,   175,   176
};

static const yytype_int16 yycheck[] =
{
       1,    53,    53,   107,    35,    36,    13,    11,     9,    10,
      27,     8,    19,    65,    66,    46,   164,    85,    14,    69,
      21,    11,   285,    11,    44,    41,    46,    41,     8,     9,
      10,    48,    46,    85,    38,   298,    52,    53,    42,    39,
      12,    13,     8,     8,     8,    44,    46,    16,    17,    18,
      19,    52,    42,    51,    42,   107,   107,     6,     7,     8,
      39,    39,   112,    12,    13,   213,    38,    46,    46,    43,
      42,    20,    46,    81,   126,    47,    25,   145,   146,   147,
     130,     5,     8,    44,    81,    46,    44,     0,    46,    38,
      39,     4,     5,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   109,   180,   163,   110,    81,   123,    81,    81,    68,
      69,    70,    71,    39,    44,    74,    75,    11,   180,     5,
      46,   129,    81,    40,    83,    84,    85,    86,    62,    63,
      64,    65,    66,    67,    38,   143,     5,    22,    39,    62,
      63,    64,    65,    66,    67,    46,    44,    20,    46,    72,
      73,    39,    39,    76,    77,   166,    39,    21,    46,    46,
      44,   169,    46,    46,     6,     7,   228,   228,    44,     5,
      46,   152,   153,   154,   155,   183,    62,    63,    64,    65,
      66,    67,    44,    26,    46,   245,    81,    73,    23,    24,
      43,   305,    40,    62,    63,    64,    65,    66,    67,    14,
      15,    45,    46,    39,    73,    39,   266,    81,   268,   148,
     149,   252,   150,   151,    40,   275,   156,   157,   226,   230,
      43,    45,     4,     5,    45,   233,    62,    63,    64,    65,
      66,    67,    45,    39,    39,    81,   247,   248,    41,    38,
      38,    45,    44,   305,   305,    38,   257,    44,   308,    40,
      38,    38,   312,     5,     6,     7,     8,    38,    44,    54,
      12,    13,    39,   126,    44,   276,    50,   158,    20,   159,
     162,   160,   285,    25,   285,    38,   123,    56,     1,   287,
      62,    63,    64,    65,    66,    67,    38,   166,    40,    41,
      72,    73,    44,   161,    76,    77,   257,    49,    -1,    51,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    83,    84,    85,    86,     5,     6,     7,     8,    11,
      -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    25,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    38,    -1,
      40,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    49,
      -1,    51,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,   269,
      -1,    81,    -1,    83,    84,    85,    86,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    25,    -1,   299,
      -1,    -1,    -1,    -1,    -1,    -1,   306,    -1,    -1,    -1,
      38,   311,    -1,   313,   314,    -1,    44,    -1,   318,    -1,
      -1,    -1,    -1,   323,    -1,    -1,    -1,    -1,   328,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    83,    84,    85,    86,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    38,    -1,    74,    75,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    83,    84,    85,    86,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    40,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,
      51,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,
      81,    -1,    83,    84,    85,    86,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    25,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    38,    -1,
      20,    -1,    -1,    -1,    44,    25,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    38,    -1,
      20,    -1,    -1,    -1,    44,    25,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    74,    75,    -1,    -1,    38,    39,
      -1,    81,    -1,    83,    84,    85,    86,    -1,    68,    69,
      70,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    86,    -1,    68,    69,
      70,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    83,    84,    85,    86,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    25,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    38,
      -1,    20,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      -1,     4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    86,    41,    68,
      69,    70,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    83,    84,    85,    86,    -1,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    72,
      73,    -1,    -1,    76,    77,    78,    79,    80
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    62,    63,    64,    65,    66,    67,    72,
      73,    76,    77,   122,   123,   124,   126,   153,   156,   122,
     163,    73,   122,   122,     8,   117,   154,     0,   153,    44,
      81,   116,   117,    81,   122,   159,   157,     8,   155,    81,
     115,   117,   118,   160,    40,    44,   158,    81,   115,   115,
     160,    11,    38,    42,   121,    44,    46,    81,   125,   115,
      44,    44,     6,     7,     8,    12,    13,    20,    25,    38,
      68,    69,    70,    71,    74,    75,    81,    83,    84,    85,
      86,    89,    90,    91,    93,    94,    95,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,    39,
     130,   131,   163,    93,   108,   112,    11,    42,   118,    11,
     127,    44,    38,    93,    93,     5,    62,    63,    64,    65,
      66,    67,    96,    97,   109,   111,    38,    12,    13,    38,
      42,    47,    11,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,   110,    95,     8,     9,    10,     6,     7,
      23,    24,    16,    17,    18,    19,    14,    15,    20,    22,
      21,    26,    27,    48,   161,    39,    46,    81,    43,    40,
     119,   112,   109,    41,    78,    79,    80,   128,   129,   153,
      39,   116,    39,    46,    93,    96,    39,    92,   109,   111,
      81,   109,    95,    95,    95,    98,    98,    99,    99,   100,
     100,   100,   100,   101,   101,   102,   103,   104,   105,   106,
     111,    40,   134,   162,   131,   109,   120,    43,    45,    45,
      45,    95,   109,    39,    39,    39,    46,    43,    45,    41,
     135,   134,    41,    46,   109,   108,    44,    49,    51,    54,
      55,    56,    57,    58,    59,    60,    61,    72,    73,    81,
     111,   113,   114,   122,   132,   133,   134,   136,   137,   138,
     139,   140,   144,   150,   152,   109,    38,   141,    38,   147,
      81,    44,    44,    44,   111,    38,    73,   122,   122,    45,
      44,   115,    41,   137,    40,    38,   111,    38,   111,   132,
      44,    44,   111,   122,    44,   142,   113,   138,   151,    39,
     109,    39,    54,    39,    41,    52,    53,   143,   138,   132,
      39,   145,    38,   146,   112,   132,    39,   111,    50,   132,
     111,   132,   132,   148,    39,   132,    39,   132,   149,    44,
     132
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    89,    89,    89,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      92,    92,    93,    93,    93,    93,    93,    93,    94,    94,
      94,    94,    94,    94,    95,    95,    96,    97,    97,    97,
      97,    97,    97,    97,    98,    98,    98,    98,    99,    99,
      99,   100,   100,   100,   101,   101,   101,   101,   101,   102,
     102,   102,   103,   103,   104,   104,   105,   105,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   111,   111,   112,
     113,   114,   114,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   118,   118,   118,   118,   119,   120,   120,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   123,
     123,   125,   124,   126,   126,   127,   127,   128,   128,   129,
     129,   129,   130,   130,   131,   132,   132,   132,   132,   132,
     132,   133,   134,   135,   134,   136,   136,   137,   137,   138,
     138,   139,   139,   139,   141,   140,   142,   142,   143,   143,
     145,   144,   146,   144,   147,   144,   148,   144,   149,   144,
     150,   151,   151,   152,   152,   152,   152,   152,   154,   153,
     155,   153,   153,   153,   153,   157,   156,   158,   156,   159,
     156,   161,   160,   162,   160,   160,   163
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     3,     2,     2,
       1,     3,     1,     2,     2,     2,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     2,     2,     3,     1,     3,     1,     0,     2,
       1,     1,     2,     2,     3,     4,     4,     3,     1,     3,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     6,     1,     1,     0,     2,     1,     1,     2,
       2,     2,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     0,     4,     1,     2,     1,     1,     1,
       2,     5,     7,     4,     0,     5,     0,     2,     3,     2,
       0,     6,     0,     6,     0,     8,     0,     7,     0,     8,
       1,     1,     1,     3,     2,     2,     2,     3,     0,     3,
       0,     4,     2,     4,     1,     0,     5,     0,     6,     0,
       5,     0,     5,     0,     6,     2,     2
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
#line 428 "src/parser.y"
    {
        dbg("primary_expression -> IDENTIFIER");
        Node* n = new Node();
        string name = string((yyvsp[0].str));
        dbg(name);
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
            dbg(n->printName + " " + sym->printName);
        }
        // dbg("n->place is " + n->place + ", n->name is " + name);
        (yyval.node) = n;
    }
#line 1992 "src/parser.tab.c"
    break;

  case 3: /* primary_expression: constant  */
#line 469 "src/parser.y"
    { 
        dbg("primary_expression -> constant");
        (yyval.node) = (yyvsp[0].node);
    }
#line 2001 "src/parser.tab.c"
    break;

  case 4: /* primary_expression: LROUND expression RROUND  */
#line 474 "src/parser.y"
    {
        dbg("primary_expression -> ( expression )");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2010 "src/parser.tab.c"
    break;

  case 5: /* primary_expression: STRING_LITERAL  */
#line 479 "src/parser.y"
    {
        dbg("constant -> STRING_LITERAL");
        (yyval.node) = new Node(string((yyvsp[0].str)), "char*", "rvalue");
    }
#line 2019 "src/parser.tab.c"
    break;

  case 6: /* constant: DECIMAL_LITERAL  */
#line 488 "src/parser.y"
    {
        dbg("constant -> DECIMAL_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "int", "const");
        n->argCount = stoi(string((yyvsp[0].str)));
        dbg("");
        dbg("Integer constant value: " + to_string(n->argCount));
        dbg("");
        n->kind = "rvalue";
        n->printName = string((yyvsp[0].str));
        (yyval.node) = n;
    }
#line 2035 "src/parser.tab.c"
    break;

  case 7: /* constant: CHARACTER_LITERAL  */
#line 500 "src/parser.y"
    {
        dbg("constant -> CHARACTER_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "char", "const");
        dbg("");
        dbg("Character constant value: " + string(1, (yyvsp[0].str)[1]));
        dbg("");
        n->printName = string(1, (yyvsp[0].str)[1]);
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2050 "src/parser.tab.c"
    break;

  case 8: /* constant: EXPONENT_LITERAL  */
#line 511 "src/parser.y"
    {
        dbg("constant -> EXPONENT_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "double", "const");
        n->kind = "rvalue";
        n->printName = string((yyvsp[0].str));
        (yyval.node) = n;
    }
#line 2062 "src/parser.tab.c"
    break;

  case 9: /* constant: DOUBLE_LITERAL  */
#line 519 "src/parser.y"
    {
        dbg("constant -> DOUBLE_LITERAL");
        Node* n = new Node(string((yyvsp[0].str)), "double", "const");
        n->kind = "rvalue";
        n->printName = string((yyvsp[0].str));
        (yyval.node) = n;
    }
#line 2074 "src/parser.tab.c"
    break;

  case 10: /* constant: NULLPTR  */
#line 527 "src/parser.y"
    {
        dbg("constant -> NULLPTR");
        Node* n = new Node("0", "nullptr", "const");
        n->kind = "rvalue";
        n->printName = "nullptr";
        (yyval.node) = n;
    }
#line 2086 "src/parser.tab.c"
    break;

  case 11: /* constant: TRUE  */
#line 535 "src/parser.y"
    {
        dbg("constant -> TRUE");
        Node* n = new Node("1", "bool", "const");
        n->kind = "rvalue";
        n->printName = "true";
        (yyval.node) = n;
    }
#line 2098 "src/parser.tab.c"
    break;

  case 12: /* constant: FALSE  */
#line 543 "src/parser.y"
    {
        dbg("constant -> FALSE");
        Node* n = new Node("0", "bool", "const");
        n->kind = "rvalue";
        n->printName = "false";
        (yyval.node) = n;
    }
#line 2110 "src/parser.tab.c"
    break;

  case 13: /* postfix_expression: primary_expression  */
#line 554 "src/parser.y"
    { 
        dbg("postfix_expression -> primary_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 2119 "src/parser.tab.c"
    break;

  case 14: /* postfix_expression: postfix_expression LSQUARE expression RSQUARE  */
#line 559 "src/parser.y"
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
            
            n->code = base->code;
            n->code.insert(n->code.end(), idx->code.begin(), idx->code.end());
            
            string type = base->type.substr(0, base->type.size()-base->syn.size());
            string offset = newTemp();
            
            // Handle array parameters (which don't have dimension info in syn)
            if(base->syn.empty()){
                // For arrays passed as parameters, just do simple pointer arithmetic
                n->code.push_back(offset + " = " + idx->printName + " * " + to_string(typeSize[type]));
                n->place = newTemp();
                n->printName = n->place;
                n->code.push_back(n->place + " = " + base->printName + " + " + offset);
                n->type = type;
                n->kind = base->kind;
                n->place = "*" + n->place;
                n->printName = "*" + n->printName;
            }
            // Handle regular arrays with dimension information
            else {
                int p = 1;
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
                n->code.push_back(offset + " = " + idx->printName + " * " + to_string(p));
                n->code.push_back(offset + " = " + offset +" * "+to_string(typeSize[type]));
                n->place = newTemp();
                n->printName = n->place;
                n->code.push_back(n->place + " = " + base->printName + " + " + offset);
                n->type = base->type.substr(0,base->type.size()-1);
                n->kind = base->kind;
                n->syn = vector<string>(base->syn.begin()+1, base->syn.end());
                
                if(n->syn.empty()){
                    n->place = "*" + n->place;
                    n->printName = "*" + n->printName;
                }
            }
        }   
        (yyval.node) = n;
    }
#line 2195 "src/parser.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression LROUND RROUND  */
#line 631 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression ( )");
        Node* fun = (yyvsp[-2].node);
        dbg("2123");
        dbg(fun->place);

        string funcName = fun->place;
        
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
            string pname = funcTable[funcName].printName;
            int i = 0;
            while(i<pname.size() && pname[i] != '.') i++;
            bool flg = false;
            dbg(to_string(i));
            if(i<pname.size()){
                flg = true;
                pname = funcName;
                i = 0;
                while(i<pname.size() && pname[i] != '.') i++;
                pname = pname.substr(0,i);
                dbg("pname is: " + pname);
                Symbol* sybl = lookupSymbol(pname);
                if(sybl){
                    n->code.push_back("param " + sybl->printName);
                }
            }

            if(fun->type=="void"){
                if(flg)
                    n->code.push_back("call " + funcTable[funcName].printName + ", 1;");
                else
                    n->code.push_back("call " + funcTable[funcName].printName + ", 0;");
            }
            else{
                n->place = newTemp();
                if(flg)
                    n->code.push_back(n->place + " = call " + funcTable[funcName].printName + ", 1;");
                else
                    n->code.push_back(n->place + " = call " + funcTable[funcName].printName + ", 0;");
            }
        }
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2257 "src/parser.tab.c"
    break;

  case 16: /* postfix_expression: postfix_expression LROUND argument_expression_list RROUND  */
#line 689 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression ( argument_expression_list )");
        Node* fun = (yyvsp[-3].node);
        dbg("133");
        dbg(fun->place);
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
        check_func_access(s);
        Node* n = new Node();
        if(!s)
        {
            if(original!="printf" && original!="scanf" && original!="malloc" && original!="free")
                yyerror("Function '" + original + "' with given argument types not found.");
            else{
                n->code = fun->code;
                n->type = "int";
                n->code.insert(n->code.end(), args->code.begin(), args->code.end());
                n->argCount = args->argCount;
                if(original=="malloc"){
                    if(args->argCount!=1 || args->syn[0]!="int"){
                        yyerror("malloc expects a single integer argument.");
                    }
                    n->place = newTemp();
                    n->code.push_back(n->place + " = call malloc, " + to_string(args->argCount));
                    n->type = "void*";
                }
                else if(original=="free"){
                    if(args->argCount!=1 || args->syn[0].back()!='*'){
                        yyerror("free expects a single pointer argument.");
                    }
                    n->code.push_back("call free, " + to_string(args->argCount));
                    n->type = "void";
                }
                else{
                    n->place = newTemp();
                    n->code.push_back(n->place + " = call " + original + ", " + to_string(args->argCount));
                }
            }
        }
        else
        {
            if (s->paramCount != args->argCount) {
                yyerror("Call to function '" + original + "' with incorrect number of arguments.");
            }
            for(int i=0; i<args->argCount; i++){
                if(s->paramTypes[i]!=args->syn[i]){
                    yyerror("Type mismatch in argument " + to_string(i+1) + " of function '" + original + "'.");
                }
            }
            dbg(funcTable[name].printName);
            n->code = fun->code;
            n->type = s->returnType;
            string pname = funcTable[name].printName;
            int i = 0;
            while(i<pname.size() && pname[i] != '.') i++;
            bool flg = false;
            dbg(to_string(i));
            if(i<pname.size()){
                flg = true;
                pname = name;
                i = 0;
                while(i<pname.size() && pname[i] != '.') i++;
                pname = pname.substr(0,i);
                dbg("pname is: " + pname);
                Symbol* sybl = lookupSymbol(pname);
                if(sybl){
                    n->code.push_back("param " + sybl->printName);
                }
            }
            n->code.insert(n->code.end(), args->code.begin(), args->code.end());
            
            if(s->returnType=="void") {
                n->type = "";
                if(flg)
                    n->code.push_back("call " + funcTable[name].printName + ", " + to_string(args->argCount + 1));
                else
                    n->code.push_back("call " + funcTable[name].printName + ", " + to_string(args->argCount));
            }
            else{
                n->place = newTemp();
                n->kind = "rvalue";
                dbg("mnb");
                dbg(funcTable[name].printName);
                if(flg)
                    n->code.push_back(n->place + " = call " + funcTable[name].printName + ", " + to_string(args->argCount + 1));
                else
                    n->code.push_back(n->place + " = call " + funcTable[name].printName + ", " + to_string(args->argCount));
            }
        }
        n->kind = "rvalue";
        n->printName = n->place;
        (yyval.node) = n;
    }
#line 2368 "src/parser.tab.c"
    break;

  case 17: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 795 "src/parser.y"
                                            {
        dbg("postfix_expression -> postfix_expression . IDENTIFIER");
        Node* obj = (yyvsp[-2].node);
        Node* n = new Node();
        if(obj)
        {
            string currentType = obj->type;
            dbg("currentname is " + obj->printName);
            if(classTable.find(currentType) == classTable.end()){
                yyerror("Dot operator can not be applied here.");
            }

            // int idx=0;
            // for(int i=0;i<obj->place.size();i++){
            //     if(obj->place[i]=='$') idx = i;
            // }
            // obj->place.erase(0,idx+1);

            string stars = "";
            int i=0;
            dbg("currentType is " + currentType);
            while(i<obj->printName.size() && obj->printName[i]=='*'){
                stars += '*';
                i++;
            }
            string nm = stars + obj->place + "." + string((yyvsp[0].str));

            dbg("2ss12121");
            dbg(nm);
            dbg("");
            Symbol* s = lookupSymbol(nm);
            funcInfo* f = lookupFunction(nm);
            memberInfo* m = lookupClassMember(currentType,string((yyvsp[0].str)));

            if(!s)
                dbg("YES");

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
                    n->printName = s->printName;
                    n->place = s->name;
                    n->type = s->type;
                    n->kind = s->kind;
                }
            }

            // else if(m){
            //     n->type = m->type;
            //     n->kind = m->kind;
            //     n->place = nm;
            //     n->printName = m->printName;
            // }
            else{
                yyerror("No member or function named '" + nm+"'.");
            }

            n->code = obj->code;
            dbg("1");
        }// n->code.push_back(n->place + " = " + nm);
        (yyval.node) = n;
    }
#line 2442 "src/parser.tab.c"
    break;

  case 18: /* postfix_expression: postfix_expression INCREMENT  */
#line 906 "src/parser.y"
    {
        dbg("postfix_expression -> postfix_expression ++");
        Node* v = (yyvsp[-1].node);
        if(v->kind.find("rvalue")!=string::npos){
            yyerror("Cannot apply increment to rvalue.");
        }
        if(!check_unary_comp(v->type,"++")){
            yyerror("Invalid type '" + v->type + "' for increment.");
        }
        if(v->kind.find("const")!=string::npos){
            yyerror("Cannot modify a const value.");
        }
        Node* n = new Node();
        n->code = v->code;
        string old = newTemp();
        n->code.push_back(old + " = " + v->printName);          // load old value from address
        n->code.push_back(v->printName + " = " + old + " + 1;");      // store back incremented value
        n->place = old;
        n->type = v->type;
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2469 "src/parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression DECREMENT  */
#line 929 "src/parser.y"
    { 
        dbg("postfix_expression -> postfix_expression --");
        Node* v = (yyvsp[-1].node);

        if(v->kind.find("rvalue")!=string::npos){
            yyerror("Cannot apply decrement to rvalue.");
        }
        if(!check_unary_comp(v->type,"--")){
            yyerror("Invalid type '" + v->type + "' for decrement.");
        }
        if(v->kind.find("const")!=string::npos){
            yyerror("Cannot modify a const value.");
        }
        Node* n = new Node();
        n->code = v->code;
        string old = newTemp();
        n->code.push_back(old + " = " + v->printName);          // load old value from address
        n->code.push_back(v->printName + " = " + old + " - 1;");      // store back incremented value
        n->place = old;
        n->type = v->type;
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2497 "src/parser.tab.c"
    break;

  case 20: /* argument_expression_list: assignment_expression  */
#line 957 "src/parser.y"
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
        if(e->kind == "rvalue"){
            n->code.push_back("param " + e->place);
        }
        else{
            n->code.push_back("param " + e->printName);
        }
        n->type = e->type;
        dbg("");
        dbg("argcount is "+ to_string(n->argCount)+", type is "+n->type);
        dbg("");
        (yyval.node) = n;
    }
#line 2524 "src/parser.tab.c"
    break;

  case 21: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 980 "src/parser.y"
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
        if(e->kind == "rvalue"){
            n->code.push_back("param " + e->place);
        }
        else{
            n->code.push_back("param " + e->printName);
        }
        dbg("argcount is " + to_string(n->argCount) + ", type is " + e->type);
        dbg(e->place+"-"+e->printName);
        (yyval.node) = n;
    }
#line 2549 "src/parser.tab.c"
    break;

  case 22: /* unary_expression: postfix_expression  */
#line 1004 "src/parser.y"
                             { 
        dbg("unary_expression -> postfix_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2557 "src/parser.tab.c"
    break;

  case 23: /* unary_expression: INCREMENT unary_expression  */
#line 1007 "src/parser.y"
                                     {
          dbg("unary_expression -> ++ unary_expression");
          Node* v = (yyvsp[0].node);
          if(v->kind.find("rvalue")!=string::npos){
              yyerror("Cannot apply increment to rvalue.");
          }
          if(!check_unary_comp(v->type,"++")){
              yyerror("Invalid type '" + v->type + "' for increment.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->printName + " = " + v->printName + " + 1;");
          (yyval.node) = n;
      }
#line 2580 "src/parser.tab.c"
    break;

  case 24: /* unary_expression: DECREMENT unary_expression  */
#line 1026 "src/parser.y"
    {
        dbg("unary_expression -> -- unary_expression");
        Node* v = (yyvsp[0].node);
        if(v->kind.find("rvalue")!=string::npos){
            yyerror("Cannot apply decrement to rvalue.");
        }
        if(!check_unary_comp(v->type,"--")){
            yyerror("Invalid type '" + v->type + "' for decrement.");
        }
        if(v->kind.find("const")!=string::npos){
            yyerror("Cannot modify a const value.");
        }
        Node* n = new Node();
        n->code = v->code;
        n->place = v->place;
        n->code.push_back(v->printName + " = " + v->printName + " - 1;");
        (yyval.node) = n;
    }
#line 2603 "src/parser.tab.c"
    break;

  case 25: /* unary_expression: unary_operator cast_expression  */
#line 1045 "src/parser.y"
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
            if(rhs->kind.find("rvalue")!=string::npos){
                  yyerror("Cannot take address of rvalue.");
              }
            n->place = newTemp();
            n->code.push_back(n->place + " = &" + rhs->printName);
            n->type = rhs->type + "*";
            n->kind = "rvalue";
            n->printName = n->place;
        } else if (op == "*") 
        {
            n = (yyvsp[0].node);
            if(n->kind.find("rvalue")!=string::npos){
                yyerror("Cannot dereference a rvalue.");
            }
            n->type = rhs->type.substr(0, rhs->type.size() - 1);
            n->place = rhs->place;
            n->printName = "*" + rhs->printName;
        } else if (op == "+") {
            n->place = rhs->place;
            n->type = rhs->type;
            n->kind = "rvalue";
        } else if (op == "-") {
            n->place = newTemp();
            dbg(rhs->place+"---"+rhs->printName);
            n->code.push_back(n->place + " = 0 - " + rhs->printName);
            n->type = rhs->type;
            n->printName = n->place;
            n->kind = "rvalue";
        } else if (op == "~") {
            n->place = newTemp();
            n->code.push_back(n->place + " = ~" + rhs->printName);
            n->type = rhs->type;
            n->kind = "rvalue";
        } else if (op == "!") {
            n->place = newTemp();
            n->code.push_back(n->place + " = !" + rhs->printName);
            n->type = "bool";
            n->kind = "rvalue";
        }
        (yyval.node) = n;
    }
#line 2659 "src/parser.tab.c"
    break;

  case 26: /* unary_expression: SIZEOF LROUND unary_expression RROUND  */
#line 1097 "src/parser.y"
    {
        dbg("unary_expression -> sizeof ( unary_expression )");
        Node* n = new Node(); 
        n->place = newTemp(); 
        n->code = (yyvsp[-1].node)->code;
        string t = (yyvsp[-1].node)->type;
        if(t.back()=='*') t = "nullptr";
        n->code.push_back(n->place + " = " + to_string(typeSize[t]));
        n->type = "int";
        n->kind = "rvalue";
        n->printName = n->place;
        (yyval.node) = n;
    }
#line 2677 "src/parser.tab.c"
    break;

  case 27: /* unary_expression: SIZEOF LROUND cast_type RROUND  */
#line 1111 "src/parser.y"
    {
        dbg("unary_expression -> sizeof ( type_name )");
        Node* n = new Node(); 
        n->place = newTemp(); 
        string t = (yyvsp[-1].str);
        if(t.back()=='*') t = "nullptr";
        n->code.push_back(n->place + " = " + to_string(typeSize[t]));
        n->type = "int";
        n->kind = "rvalue";
        n->printName = n->place;
        (yyval.node) = n;
    }
#line 2694 "src/parser.tab.c"
    break;

  case 28: /* unary_operator: BITWISE_AND  */
#line 1127 "src/parser.y"
                      { 
        dbg("unary_operator -> &");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2702 "src/parser.tab.c"
    break;

  case 29: /* unary_operator: STAR  */
#line 1130 "src/parser.y"
               { 
        dbg("unary_operator -> *");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2710 "src/parser.tab.c"
    break;

  case 30: /* unary_operator: PLUS  */
#line 1133 "src/parser.y"
               { 
        dbg("unary_operator -> +");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2718 "src/parser.tab.c"
    break;

  case 31: /* unary_operator: MINUS  */
#line 1136 "src/parser.y"
                { 
        dbg("unary_operator -> -");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2726 "src/parser.tab.c"
    break;

  case 32: /* unary_operator: TILDE  */
#line 1139 "src/parser.y"
                { 
        dbg("unary_operator -> ~");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2734 "src/parser.tab.c"
    break;

  case 33: /* unary_operator: LOGICAL_NOT  */
#line 1142 "src/parser.y"
                      { 
        dbg("unary_operator -> !");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 2742 "src/parser.tab.c"
    break;

  case 34: /* cast_expression: unary_expression  */
#line 1149 "src/parser.y"
                           { 
        dbg("cast_expression -> unary_expression");
        dbg(lastDeclType);
        (yyval.node) = (yyvsp[0].node); }
#line 2751 "src/parser.tab.c"
    break;

  case 35: /* cast_expression: LROUND cast_type RROUND cast_expression  */
#line 1154 "src/parser.y"
    {
        dbg("cast_expression -> ( cast_type ) cast_expression");
        string a = (yyvsp[-2].str); Node* b = (yyvsp[0].node);
        dbg("ww");
        dbg("Casting from " + b->type + " to " + a);
        if(!check_casting(b->type,a)){
            yyerror("Unable to cast from '" + b->type + "' to '" + a + "'.");
        }
        Node* n = new Node();
        n->code = b->code;
        n->place = newTemp();
        n->printName = n->place;
        n->code.push_back(n->place + " = " + b->type + "_to_"+ a +" "+ b->printName);
        n->type = a;
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2773 "src/parser.tab.c"
    break;

  case 36: /* cast_type: cast_type_specifier pointer_opt  */
#line 1175 "src/parser.y"
    { 
        dbg("return_type -> type_specifier pointer_opt");
        (yyval.str) = strdup( (string((yyvsp[-1].str)) + string((yyvsp[0].str))).c_str() );
    }
#line 2782 "src/parser.tab.c"
    break;

  case 37: /* cast_type_specifier: VOID  */
#line 1182 "src/parser.y"
                 { 
        dbg("cast_type_specifier -> VOID");
        (yyval.str) = strdup("void"); }
#line 2790 "src/parser.tab.c"
    break;

  case 38: /* cast_type_specifier: CHAR  */
#line 1185 "src/parser.y"
                 { 
        dbg("cast_type_specifier -> CHAR");
        (yyval.str) = strdup("char"); }
#line 2798 "src/parser.tab.c"
    break;

  case 39: /* cast_type_specifier: INT  */
#line 1188 "src/parser.y"
                 { 
        dbg("cast_type_specifier -> INT");
        (yyval.str) = strdup("int"); }
#line 2806 "src/parser.tab.c"
    break;

  case 40: /* cast_type_specifier: LONG  */
#line 1191 "src/parser.y"
                 { 
        dbg("cast_type_specifier -> LONG");
        (yyval.str) = strdup("long"); }
#line 2814 "src/parser.tab.c"
    break;

  case 41: /* cast_type_specifier: DOUBLE  */
#line 1194 "src/parser.y"
                 { 
        dbg("cast_type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); }
#line 2822 "src/parser.tab.c"
    break;

  case 42: /* cast_type_specifier: BOOL  */
#line 1197 "src/parser.y"
                 { 
        dbg("cast_type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); }
#line 2830 "src/parser.tab.c"
    break;

  case 43: /* cast_type_specifier: TYPE_NAME  */
#line 1201 "src/parser.y"
    { 
        dbg("cast_type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str); 
        if(typeDefTable.find(string((yyvsp[0].str))) != typeDefTable.end()){
            (yyval.str) = strdup(typeDefTable[string((yyvsp[0].str))].c_str());
            dbg("Typedef found: " + string((yyval.str)));
        }
        else if(typeSize.find(string((yyvsp[0].str))) != typeSize.end()){
            dbg("User defined type found: " + string((yyvsp[0].str)));
        }
        else
        {
            yyerror("Unknown type '" + string((yyvsp[0].str)) + "'.");    
        }
    }
#line 2850 "src/parser.tab.c"
    break;

  case 44: /* multiplicative_expression: cast_expression  */
#line 1220 "src/parser.y"
                          { 
        dbg("multiplicative_expression -> cast_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2858 "src/parser.tab.c"
    break;

  case 45: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 1224 "src/parser.y"
    {
        dbg("multiplicative_expression -> multiplicative_expression * cast_expression");
        Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
        if(!check_compatibility(a->type,b->type,"*")){
            yyerror("Type incompatibility in multiply.");
        }
        Node* n = new Node();
        n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
        n->place = newTemp();
        n->code.push_back(n->place + " = " + a->printName + " * " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2878 "src/parser.tab.c"
    break;

  case 46: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 1240 "src/parser.y"
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
        n->code.push_back(n->place + " = " + a->printName + " / " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2899 "src/parser.tab.c"
    break;

  case 47: /* multiplicative_expression: multiplicative_expression MODULUS cast_expression  */
#line 1257 "src/parser.y"
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
        n->code.push_back(n->place + " = " + a->printName + " % " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2920 "src/parser.tab.c"
    break;

  case 48: /* additive_expression: multiplicative_expression  */
#line 1277 "src/parser.y"
                                    { 
        dbg("additive_expression -> multiplicative_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2928 "src/parser.tab.c"
    break;

  case 49: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 1281 "src/parser.y"
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
        n->code.push_back(n->place + " = " + a->printName + " + " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        if(n->type.back()=='*'){
            n->kind = "pointer";
        }
        (yyval.node) = n;
    }
#line 2952 "src/parser.tab.c"
    break;

  case 50: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 1300 "src/parser.y"
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
        n->code.push_back(n->place + " = " + a->printName + " - " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 2973 "src/parser.tab.c"
    break;

  case 51: /* shift_expression: additive_expression  */
#line 1320 "src/parser.y"
                              { 
        dbg("shift_expression -> additive_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2981 "src/parser.tab.c"
    break;

  case 52: /* shift_expression: shift_expression LEFT_SHIFT additive_expression  */
#line 1323 "src/parser.y"
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
          n->code.push_back(n->place + " = " + a->printName + " << " + b->printName);
          n->type = a->type; 
        n->printName = n->place;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3002 "src/parser.tab.c"
    break;

  case 53: /* shift_expression: shift_expression RIGHT_SHIFT additive_expression  */
#line 1339 "src/parser.y"
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
          n->code.push_back(n->place + " = " + a->printName + " >> " + b->printName);
          n->type = a->type; 
        n->printName = n->place;
        n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3023 "src/parser.tab.c"
    break;

  case 54: /* relational_expression: shift_expression  */
#line 1359 "src/parser.y"
                           { 
        dbg("relational_expression -> shift_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3031 "src/parser.tab.c"
    break;

  case 55: /* relational_expression: relational_expression GREATER_THAN shift_expression  */
#line 1362 "src/parser.y"
                                                              {
          dbg("relational_expression -> relational_expression > shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " > " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3051 "src/parser.tab.c"
    break;

  case 56: /* relational_expression: relational_expression LESS_THAN shift_expression  */
#line 1377 "src/parser.y"
                                                           {
          dbg("relational_expression -> relational_expression < shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " < " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
            n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3071 "src/parser.tab.c"
    break;

  case 57: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 1392 "src/parser.y"
                                                            {
            dbg("relational_expression -> relational_expression <= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " <= " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3091 "src/parser.tab.c"
    break;

  case 58: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 1407 "src/parser.y"
                                                               {
            dbg("relational_expression -> relational_expression >= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " >= " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
            n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3111 "src/parser.tab.c"
    break;

  case 59: /* equality_expression: relational_expression  */
#line 1426 "src/parser.y"
                                { 
        dbg("equality_expression -> relational_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3119 "src/parser.tab.c"
    break;

  case 60: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 1429 "src/parser.y"
                                                          {
            dbg("equality_expression -> equality_expression == relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in equality expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " == " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3139 "src/parser.tab.c"
    break;

  case 61: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 1444 "src/parser.y"
                                                              {
            dbg("equality_expression -> equality_expression != relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(a->type != b->type){
              yyerror("Type incompatibility in equality expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " != " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
            n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3159 "src/parser.tab.c"
    break;

  case 62: /* and_expression: equality_expression  */
#line 1463 "src/parser.y"
                              { 
        dbg("and_expression -> equality_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3167 "src/parser.tab.c"
    break;

  case 63: /* and_expression: and_expression BITWISE_AND equality_expression  */
#line 1466 "src/parser.y"
                                                         {
            dbg("and_expression -> and_expression & equality_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(!check_compatibility(a->type,b->type,"&")){
                yyerror("Type incompatibility in bitwise AND expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " & " + b->printName);
          n->type = a->type;
        n->printName = n->place;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3187 "src/parser.tab.c"
    break;

  case 64: /* exclusive_or_expression: and_expression  */
#line 1485 "src/parser.y"
                         { 
        dbg("exclusive_or_expression -> and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3195 "src/parser.tab.c"
    break;

  case 65: /* exclusive_or_expression: exclusive_or_expression BITWISE_XOR and_expression  */
#line 1489 "src/parser.y"
    {
        dbg("exclusive_or_expression -> exclusive_or_expression ^ and_expression");
        Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
        if(!check_compatibility(a->type,b->type,"^")){
            yyerror("Type incompatibility in bitwise XOR expression.");
        }
        n->code=a->code; 
        n->code.insert(n->code.end(), b->code.begin(), b->code.end());
        n->place=newTemp(); 
        n->code.push_back(n->place + " = " + a->printName + " ^ " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        (yyval.node) = n;
    }
#line 3215 "src/parser.tab.c"
    break;

  case 66: /* inclusive_or_expression: exclusive_or_expression  */
#line 1508 "src/parser.y"
                                  { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3223 "src/parser.tab.c"
    break;

  case 67: /* inclusive_or_expression: inclusive_or_expression BITWISE_OR exclusive_or_expression  */
#line 1511 "src/parser.y"
                                                                     {
            dbg("inclusive_or_expression -> inclusive_or_expression | exclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(!check_compatibility(a->type,b->type,"|")){
              yyerror("Type incompatibility in bitwise OR expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " | " + b->printName);
            n->type = a->type;
        n->printName = n->place;
            n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3243 "src/parser.tab.c"
    break;

  case 68: /* logical_and_expression: inclusive_or_expression  */
#line 1530 "src/parser.y"
                                  { 
        dbg("logical_and_expression -> inclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3251 "src/parser.tab.c"
    break;

  case 69: /* logical_and_expression: logical_and_expression LOGICAL_AND inclusive_or_expression  */
#line 1533 "src/parser.y"
                                                                     {
            dbg("logical_and_expression -> logical_and_expression && inclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
            if(a->type!="bool" || b->type!="bool"){
                yyerror("Type incompatibility in logical AND expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " && " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3271 "src/parser.tab.c"
    break;

  case 70: /* logical_or_expression: logical_and_expression  */
#line 1552 "src/parser.y"
                                 { 
        dbg("logical_or_expression -> logical_and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3279 "src/parser.tab.c"
    break;

  case 71: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 1555 "src/parser.y"
                                                                  {
            dbg("logical_or_expression -> logical_or_expression || logical_and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          if(a->type!="bool" || b->type!="bool"){
              yyerror("Type incompatibility in logical OR expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->printName + " || " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
            n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 3299 "src/parser.tab.c"
    break;

  case 72: /* conditional_expression: logical_or_expression  */
#line 1574 "src/parser.y"
    { 
        dbg("conditional_expression -> logical_or_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3308 "src/parser.tab.c"
    break;

  case 73: /* conditional_expression: logical_or_expression QUESTION_MARK expression COLON conditional_expression  */
#line 1578 "src/parser.y"
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
        n->code.push_back("ifFalse " + cond->place + " goto __");
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
        n->printName = n->place;
        (yyval.node) = n;
    }
#line 3352 "src/parser.tab.c"
    break;

  case 74: /* assignment_expression: conditional_expression  */
#line 1622 "src/parser.y"
    { 
        dbg("assignment_expression -> conditional_expression");
        Node* n = (yyvsp[0].node);
        (yyval.node) = n;
    }
#line 3362 "src/parser.tab.c"
    break;

  case 75: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 1628 "src/parser.y"
    {
        dbg("assignment_expression -> unary_expression assignment_operator assignment_expression");
        Node* left = (yyvsp[-2].node); 
        Node* right = (yyvsp[0].node);
        Node* n = new Node();
        if(right && left)
        {
            n->code = left->code; 
            n->code.insert(n->code.end(),right->code.begin(),right->code.end());
            string op = string((yyvsp[-1].str));
            string baseop = op.substr(0,op.size()-1);
            dbg("11:"+baseop);
            if (!check_compatibility(left->type,right->type,baseop)) {
                yyerror("Type incompatibility in assignment to '" + left->place + "'.");
            }
            if(left->kind.find("const")!=string::npos){
                yyerror("Cannot assign to const variable '" + left->place + "'.");
            }
            if(left->kind == "rvalue"){
                yyerror("Left side of assignment must be an lvalue.");
            }
            dbg("abcdefgh");
            if (op == "=") {
                if(right->kind == "rvalue"){
                    dbg(left->printName);
                    n->code.push_back(left->printName + " = " + right->place);
                }
                else{
                    n->code.push_back(left->printName + " = " + right->printName);
                }
            } 
            else {
                if(right->kind == "rvalue"){
                n->code.push_back(left->printName + " = " + left->printName + " " + baseop + " " + right->place);
                }
                else{
                n->code.push_back(left->printName + " = " + left->printName + " " + baseop + " " + right->printName);
                }
            }
            n->printName = left->printName;
            n->place = left->place;
            n->type = left->type;
        }
        (yyval.node) = n;
    }
#line 3412 "src/parser.tab.c"
    break;

  case 76: /* assignment_operator: ASSIGN  */
#line 1678 "src/parser.y"
                 { 
        dbg("assignment_operator -> =");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3420 "src/parser.tab.c"
    break;

  case 77: /* assignment_operator: STAR_EQUAL  */
#line 1681 "src/parser.y"
                     { 
        dbg("assignment_operator -> *=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3428 "src/parser.tab.c"
    break;

  case 78: /* assignment_operator: DIV_EQUAL  */
#line 1684 "src/parser.y"
                    { 
        dbg("assignment_operator -> /=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3436 "src/parser.tab.c"
    break;

  case 79: /* assignment_operator: MOD_EQUAL  */
#line 1687 "src/parser.y"
                    { 
        dbg("assignment_operator -> %=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3444 "src/parser.tab.c"
    break;

  case 80: /* assignment_operator: PLUS_EQUAL  */
#line 1690 "src/parser.y"
                     { 
        dbg("assignment_operator -> +=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3452 "src/parser.tab.c"
    break;

  case 81: /* assignment_operator: MINUS_EQUAL  */
#line 1693 "src/parser.y"
                      { 
        dbg("assignment_operator -> -=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3460 "src/parser.tab.c"
    break;

  case 82: /* assignment_operator: LEFT_SHIFT_EQ  */
#line 1696 "src/parser.y"
                        { 
        dbg("assignment_operator -> <<=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3468 "src/parser.tab.c"
    break;

  case 83: /* assignment_operator: RIGHT_SHIFT_EQ  */
#line 1699 "src/parser.y"
                         { 
        dbg("assignment_operator -> >>=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3476 "src/parser.tab.c"
    break;

  case 84: /* assignment_operator: AND_EQUAL  */
#line 1702 "src/parser.y"
                    { 
        dbg("assignment_operator -> &=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3484 "src/parser.tab.c"
    break;

  case 85: /* assignment_operator: XOR_EQUAL  */
#line 1705 "src/parser.y"
                    { 
        dbg("assignment_operator -> ^=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3492 "src/parser.tab.c"
    break;

  case 86: /* assignment_operator: OR_EQUAL  */
#line 1708 "src/parser.y"
                   { 
        dbg("assignment_operator -> |=");
        (yyval.str) = strdup((yyvsp[0].str)); }
#line 3500 "src/parser.tab.c"
    break;

  case 87: /* expression: assignment_expression  */
#line 1716 "src/parser.y"
    { 
        dbg("expression -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3509 "src/parser.tab.c"
    break;

  case 88: /* expression: expression COMMA assignment_expression  */
#line 1721 "src/parser.y"
        {
            dbg("expression -> expression , assignment_expression");
            Node* n = new Node();
            n->code = (yyvsp[-2].node)->code;
            n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
            n->place = (yyvsp[0].node)->place;
            (yyval.node) = n;
        }
#line 3522 "src/parser.tab.c"
    break;

  case 89: /* constant_expression: conditional_expression  */
#line 1734 "src/parser.y"
    { 
        dbg("constant_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3531 "src/parser.tab.c"
    break;

  case 90: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 1743 "src/parser.y"
    {
        dbg("declaration -> declaration_specifiers init_declarator_list ;");
        dbg(lastDeclType);
        if(lastDeclType.find("static")!=string::npos){ 
            globalCode.insert(globalCode.end(), (yyvsp[-1].node)->code.begin(), (yyvsp[-1].node)->code.end());
            (yyval.node) = new Node();
        }
        else{
            (yyval.node) = (yyvsp[-1].node);
        }
    }
#line 3547 "src/parser.tab.c"
    break;

  case 91: /* declaration_specifiers: type_specifier  */
#line 1759 "src/parser.y"
    {
        dbg("declaration_specifiers -> type_specifier");
        lastDeclType = string((yyvsp[0].str));
        dbg(lastDeclType);
        (yyval.str) = strdup(lastDeclType.c_str());
	}
#line 3558 "src/parser.tab.c"
    break;

  case 92: /* declaration_specifiers: STATIC type_specifier  */
#line 1765 "src/parser.y"
                            {
        dbg("declaration_specifiers -> static type_specifier");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
    }
#line 3568 "src/parser.tab.c"
    break;

  case 93: /* declaration_specifiers: CONST type_specifier  */
#line 1770 "src/parser.y"
                           {
        dbg("declaration_specifiers -> const type_specifier");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
	}
#line 3578 "src/parser.tab.c"
    break;

  case 94: /* declaration_specifiers: STATIC CONST type_specifier  */
#line 1775 "src/parser.y"
                                  {
        dbg("declaration_specifiers -> static const type_specifier");
        lastDeclType = string((yyvsp[-2].str))+string((yyvsp[-1].str))+string((yyvsp[0].str));
        (yyval.str) = strdup(lastDeclType.c_str());
    }
#line 3588 "src/parser.tab.c"
    break;

  case 95: /* init_declarator_list: init_declarator  */
#line 1785 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator");
        dbg(lastDeclType);
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3598 "src/parser.tab.c"
    break;

  case 96: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1791 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator_list , init_declarator");
        Node* n = (yyvsp[-2].node);
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        (yyval.node) = n;
    }
#line 3609 "src/parser.tab.c"
    break;

  case 97: /* pointer_opt: pointer_list  */
#line 1802 "src/parser.y"
    {
        dbg("pointer_opt -> pointer_list");
        (yyval.str) = (yyvsp[0].str);
    }
#line 3618 "src/parser.tab.c"
    break;

  case 98: /* pointer_opt: %empty  */
#line 1807 "src/parser.y"
    {
        dbg("pointer_opt -> <empty>");
        (yyval.str) = strdup("");
    }
#line 3627 "src/parser.tab.c"
    break;

  case 99: /* pointer_list: pointer_list STAR  */
#line 1816 "src/parser.y"
    {
        dbg("pointer_list -> pointer_list *");
        (yyval.str) = strdup((string("*")+string((yyvsp[-1].str))).c_str());
    }
#line 3636 "src/parser.tab.c"
    break;

  case 100: /* pointer_list: STAR  */
#line 1821 "src/parser.y"
    {
        dbg("pointer_list -> *");
        (yyval.str) = strdup("*");
    }
#line 3645 "src/parser.tab.c"
    break;

  case 101: /* init_declarator: IDENTIFIER  */
#line 1830 "src/parser.y"
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
        dbg("333"+n->place);
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }

        Symbol* sym = lookupSymbol(n->place);
        string w;
        if(lastClassType=="")
            w = lastClassType+currentFunction+currentScope+n->place;
        else
            w = lastClassType+"."+currentFunction+currentScope+n->place;
        sym->printName = w;
        
        if(lastClassType != "" && currentFunction == "")
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

        if(n->type == "void"){
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

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = currentFunction + currentScope + name;
                    sym->printName = w;

                    dbg("mmm");
                    dbg(w);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3752 "src/parser.tab.c"
    break;

  case 102: /* init_declarator: IDENTIFIER square_list  */
#line 1933 "src/parser.y"
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
        string w;
        if(lastClassType=="")
            w = lastClassType+currentFunction+currentScope+n->place;
        else
            w = lastClassType+"."+currentFunction+currentScope+n->place;
        sym->printName = w;
        

        if(lastClassType != "" && currentFunction == "")
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

        if(n->type =="void"){
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
                    dbg("zaz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = currentFunction + currentScope + name;
                    sym->printName = w;

                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3874 "src/parser.tab.c"
    break;

  case 103: /* init_declarator: pointer_list IDENTIFIER  */
#line 2051 "src/parser.y"
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
        string w;
        if(lastClassType=="")
            w = lastClassType+currentFunction+currentScope+n->place;
        else
            w = lastClassType+"."+currentFunction+currentScope+n->place;
        sym->printName = w;
       
        if(lastClassType != "" && currentFunction == "")
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

        if(n->type =="void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        if(classTable.find(lastDeclType) != classTable.end())
        {
            for(const auto& member : classTable[lastDeclType])
            {
                if(member.second.kind == "function")
                {
                    string name = stars + n->place + "." + member.first;
                    string original = stars + n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = stars + n->place + "." + f.place;
                    dbg("zzw");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = stars + n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = lastClassType+currentFunction+currentScope + name;
                    sym->printName = w;

                    dbg("mmm");
                    dbg(w);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 3978 "src/parser.tab.c"
    break;

  case 104: /* init_declarator: IDENTIFIER ASSIGN assignment_expression  */
#line 2152 "src/parser.y"
    {
        dbg("init_declarator -> IDENTIFIER = assignment_expression ");
        Node* n = new Node();
        string name = string((yyvsp[-2].str));
        n->place = name;
        n->type = lastDeclType;
        n->code = (yyvsp[0].node)->code;
        n->argCount = 0;
        n->kind = "";

        dbg(lastDeclType);
        dbg("333"+n->place);

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        dbg("Type of assignment expression: " + (yyvsp[0].node)->type);
        dbg("Type of variable: " + n->type);
        if(n->type != (yyvsp[0].node)->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
        Symbol* sym = lookupSymbol(n->place);
        string w;
        if(lastClassType=="")
            w = lastClassType+currentFunction+currentScope+n->place;
        else
            w = lastClassType+"."+currentFunction+currentScope+n->place;
        sym->printName = w;
        if((yyvsp[0].node)->kind == "rvalue"){
            n->code.push_back(w + " = " + (yyvsp[0].node)->place);
        }
        else{
            n->code.push_back(w + " = " + (yyvsp[0].node)->printName);
        }
        
        if(lastClassType != "" && currentFunction == "")
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

        if(n->type =="void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("nmnmn");
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

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = lastClassType+currentFunction+currentScope+name;
                    sym->printName = w;

                    dbg("mmm");
                    dbg(w);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 4092 "src/parser.tab.c"
    break;

  case 105: /* init_declarator: pointer_list IDENTIFIER ASSIGN assignment_expression  */
#line 2263 "src/parser.y"
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
        string w;
        if(lastClassType=="")
            w = lastClassType+currentFunction+currentScope+n->place;
        else
            w = lastClassType+"."+currentFunction+currentScope+n->place;
        sym->printName = w;
        n->code.push_back(w + " = " + (yyvsp[0].node)->printName);
       
        if(lastClassType != "" && currentFunction == "")
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

        if(n->type =="void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(lastDeclType) != classTable.end())
        {
            for(const auto& member : classTable[lastDeclType])
            {
                if(member.second.kind == "function")
                {
                    string name = stars + n->place + "." + member.first;
                    string original = stars + n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = stars + n->place + "." + f.place;
                    dbg("zzw");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else
                {
                    string name = stars + n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = lastClassType+currentFunction+currentScope + name;
                    sym->printName = w;

                    dbg("mmm");
                    dbg(w);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        (yyval.node) = n;
    }
#line 4200 "src/parser.tab.c"
    break;

  case 106: /* init_declarator: IDENTIFIER square_list ASSIGN initializer  */
#line 2368 "src/parser.y"
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
        string w;
        if(lastClassType=="")
            w = lastClassType+currentFunction+currentScope+n->place;
        else
            w = lastClassType+"."+currentFunction+currentScope+n->place;
        sym->printName = w;

        string tmp = newTemp();
        n->code.push_back(tmp + " = &" + sym->printName);
        for(int i = 0; i < (yyvsp[0].node)->argCount; i++)
        {
            n->code.push_back("*" + tmp + " = " + (yyvsp[0].node)->syn[i]);
            n->code.push_back(tmp + " = " + tmp + " + " + to_string(typeSize[(yyvsp[0].node)->type]));
        }
       
        if(lastClassType != "" && currentFunction == "")
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
        if(n->type =="void"){
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
#line 4318 "src/parser.tab.c"
    break;

  case 107: /* initializer: LCURLY initializer_list RCURLY  */
#line 2553 "src/parser.y"
    { 
        dbg("initializer -> { initializer_list }");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 4327 "src/parser.tab.c"
    break;

  case 108: /* initializer_list: assignment_expression  */
#line 2562 "src/parser.y"
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
#line 4342 "src/parser.tab.c"
    break;

  case 109: /* initializer_list: initializer_list COMMA assignment_expression  */
#line 2573 "src/parser.y"
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
#line 4364 "src/parser.tab.c"
    break;

  case 110: /* square_list: square_list LSQUARE constant_expression RSQUARE  */
#line 2595 "src/parser.y"
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
#line 4382 "src/parser.tab.c"
    break;

  case 111: /* square_list: LSQUARE constant_expression RSQUARE  */
#line 2609 "src/parser.y"
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
#line 4399 "src/parser.tab.c"
    break;

  case 112: /* type_specifier: VOID  */
#line 2636 "src/parser.y"
                 { 
        dbg("type_specifier -> VOID");
        (yyval.str) = strdup("void"); lastDeclType = "void"; }
#line 4407 "src/parser.tab.c"
    break;

  case 113: /* type_specifier: CHAR  */
#line 2639 "src/parser.y"
                 { 
        dbg("type_specifier -> CHAR");
        (yyval.str) = strdup("char"); lastDeclType = "char"; }
#line 4415 "src/parser.tab.c"
    break;

  case 114: /* type_specifier: INT  */
#line 2642 "src/parser.y"
                 { 
        dbg("type_specifier -> INT");
        (yyval.str) = strdup("int"); lastDeclType = "int"; }
#line 4423 "src/parser.tab.c"
    break;

  case 115: /* type_specifier: LONG  */
#line 2645 "src/parser.y"
                 { 
        dbg("type_specifier -> LONG");
        (yyval.str) = strdup("long"); lastDeclType = "long"; }
#line 4431 "src/parser.tab.c"
    break;

  case 116: /* type_specifier: DOUBLE  */
#line 2648 "src/parser.y"
                 { 
        dbg("type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); lastDeclType = "double"; }
#line 4439 "src/parser.tab.c"
    break;

  case 117: /* type_specifier: BOOL  */
#line 2651 "src/parser.y"
                 { 
        dbg("type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); lastDeclType = "bool"; }
#line 4447 "src/parser.tab.c"
    break;

  case 118: /* type_specifier: TYPE_NAME  */
#line 2658 "src/parser.y"
    { 
        dbg("type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str);
        if(typeDefTable.find(string((yyvsp[0].str))) != typeDefTable.end()){
            lastDeclType = typeDefTable[string((yyvsp[0].str))];
            (yyval.str) = strdup(lastDeclType.c_str());
        }
        else if(typeSize.find(string((yyvsp[0].str))) != typeSize.end()){
            lastDeclType = string((yyvsp[0].str));
            dbg("User defined type found: " + string((yyvsp[0].str)));
            (yyval.str) = strdup(lastDeclType.c_str());
        }
        else
        {
            yyerror("Unknown type '" + string((yyvsp[0].str)) + "'.");    
        }
    }
#line 4469 "src/parser.tab.c"
    break;

  case 119: /* translation_unit: external_declaration  */
#line 2680 "src/parser.y"
    { 
        dbg("translation_unit -> external_declaration");
        finalRoot = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); 
    }
#line 4478 "src/parser.tab.c"
    break;

  case 120: /* translation_unit: translation_unit external_declaration  */
#line 2685 "src/parser.y"
    {
        dbg("translation_unit -> translation_unit external_declaration");
        Node* a = (yyvsp[-1].node); Node* b = (yyvsp[0].node);
        if (b) 
        { 
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; (yyval.node) = a; 
        }
        else { finalRoot = b; (yyval.node) = b; }
    }
#line 4493 "src/parser.tab.c"
    break;

  case 121: /* $@1: %empty  */
#line 2700 "src/parser.y"
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
#line 4508 "src/parser.tab.c"
    break;

  case 122: /* struct_or_class_specifier: struct_or_class IDENTIFIER LCURLY $@1 struct_or_class_member_list RCURLY  */
#line 2711 "src/parser.y"
    { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        popScope();
        (yyval.node) = (yyvsp[-1].node); 
        typeSize[lastClassType] = classOffset;   // NEW: store computed size
        lastClassType.clear(); 
    }
#line 4520 "src/parser.tab.c"
    break;

  case 123: /* struct_or_class: STRUCT  */
#line 2723 "src/parser.y"
    { 
        dbg("struct_or_class -> STRUCT");
        (yyval.node) = new Node(); 
        lastUsage = "public";
    }
#line 4530 "src/parser.tab.c"
    break;

  case 124: /* struct_or_class: CLASS  */
#line 2729 "src/parser.y"
    { 
        dbg("struct_or_class -> CLASS");
        (yyval.node) = new Node(); 
        lastUsage = "private";
    }
#line 4540 "src/parser.tab.c"
    break;

  case 125: /* struct_or_class_member_list: %empty  */
#line 2739 "src/parser.y"
    { 
        dbg("struct_or_class_member_list -> <empty>");
        dbg("lastClassType: " + lastClassType);
        (yyval.node) = new Node(); 
    }
#line 4550 "src/parser.tab.c"
    break;

  case 126: /* struct_or_class_member_list: struct_or_class_member_list struct_or_class_member  */
#line 2745 "src/parser.y"
    { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        dbg("lastClassType: " + lastClassType);
        Node* n = (yyvsp[-1].node); 
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; 
    }
#line 4562 "src/parser.tab.c"
    break;

  case 127: /* struct_or_class_member: access_specifier_label  */
#line 2756 "src/parser.y"
    { 
        dbg("struct_or_class_member -> access_specifier_label");
        dbg("lastClassType: " + lastClassType);
        lastUsage = string((yyvsp[0].node)->place);
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4573 "src/parser.tab.c"
    break;

  case 128: /* struct_or_class_member: external_declaration  */
#line 2763 "src/parser.y"
    {
        dbg("struct_or_class_member -> external_declaration");
        dbg("lastClassType: " + lastClassType);
        dbg("");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 4584 "src/parser.tab.c"
    break;

  case 129: /* access_specifier_label: PUBLIC COLON  */
#line 2773 "src/parser.y"
    { 
        dbg("access_specifier_label -> PUBLIC :");
        dbg("lastClassType: " + lastClassType);
        Node* n=new Node(); 
        n->place = "public";
        (yyval.node) = n; 
    }
#line 4596 "src/parser.tab.c"
    break;

  case 130: /* access_specifier_label: PRIVATE COLON  */
#line 2781 "src/parser.y"
    { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); 
        n->place = "private";
        (yyval.node) = n; 
    }
#line 4607 "src/parser.tab.c"
    break;

  case 131: /* access_specifier_label: PROTECTED COLON  */
#line 2788 "src/parser.y"
    { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); 
        n->place = "protected";
        (yyval.node) = n; 
    }
#line 4618 "src/parser.tab.c"
    break;

  case 132: /* parameter_list: parameter_declaration  */
#line 2936 "src/parser.y"
                                { 
            dbg("parameter_list -> parameter_declaration");
            (yyval.node) = (yyvsp[0].node); 
        }
#line 4627 "src/parser.tab.c"
    break;

  case 133: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 2941 "src/parser.y"
        {
            dbg("parameter_list -> parameter_list , parameter_declaration");
            Node* n = (yyvsp[-2].node);
            n->syn.insert(n->syn.end(), (yyvsp[0].node)->syn.begin(), (yyvsp[0].node)->syn.end()); 
            (yyval.node) = n;
        }
#line 4638 "src/parser.tab.c"
    break;

  case 134: /* parameter_declaration: return_type IDENTIFIER  */
#line 2952 "src/parser.y"
        {
            dbg("parameter_declaration -> return_type IDENTIFIER");
            Node* n = new Node();
            n->syn.push_back(string((yyvsp[-1].str))); 
            n->syn.push_back(string((yyvsp[0].str)));
            (yyval.node) = n;
        }
#line 4650 "src/parser.tab.c"
    break;

  case 135: /* statement: labeled_statement  */
#line 2963 "src/parser.y"
                            { 
        dbg("statement -> labeled_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4658 "src/parser.tab.c"
    break;

  case 136: /* statement: compound_statement  */
#line 2966 "src/parser.y"
                             { 
        dbg("statement -> compound_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4666 "src/parser.tab.c"
    break;

  case 137: /* statement: expression_statement  */
#line 2969 "src/parser.y"
                               { 
        dbg("statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4674 "src/parser.tab.c"
    break;

  case 138: /* statement: selection_statement  */
#line 2972 "src/parser.y"
                              { 
        dbg("statement -> selection_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4682 "src/parser.tab.c"
    break;

  case 139: /* statement: iteration_statement  */
#line 2975 "src/parser.y"
                              { 
        dbg("statement -> iteration_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4690 "src/parser.tab.c"
    break;

  case 140: /* statement: jump_statement  */
#line 2978 "src/parser.y"
                         { 
        dbg("statement -> jump_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4698 "src/parser.tab.c"
    break;

  case 141: /* labeled_statement: IDENTIFIER COLON  */
#line 2985 "src/parser.y"
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
#line 4713 "src/parser.tab.c"
    break;

  case 142: /* compound_statement: LCURLY RCURLY  */
#line 2999 "src/parser.y"
                        {
            dbg("compound_statement -> { }");
          Node* n = new Node();
          (yyval.node) = n;
      }
#line 4723 "src/parser.tab.c"
    break;

  case 143: /* $@5: %empty  */
#line 3005 "src/parser.y"
    {
        currentScope += ".";
        pushScope();
    }
#line 4732 "src/parser.tab.c"
    break;

  case 144: /* compound_statement: LCURLY $@5 statement_list RCURLY  */
#line 3009 "src/parser.y"
    {
        dbg("compound_statement -> { statement_list }");
        Node* n = (yyvsp[-1].node);
        popScope();
        currentScope.pop_back();
        (yyval.node) = n;
        if(!inloop)
        { 
            for(size_t i = 0; i < n->code.size(); i++) {
                if(n->code[i]=="break"){
                    yyerror("Incorrect usage of 'break'");
                }
                if(n->code[i]=="continue"){
                    yyerror("Incorrect usage of 'continue'");
                }
            }
        }
    }
#line 4755 "src/parser.tab.c"
    break;

  case 145: /* statement_list: block_item  */
#line 3031 "src/parser.y"
                     { 
        dbg("statement_list -> block_item");
        (yyval.node) = (yyvsp[0].node); }
#line 4763 "src/parser.tab.c"
    break;

  case 146: /* statement_list: statement_list block_item  */
#line 3034 "src/parser.y"
                                    {
            dbg("statement_list -> statement_list block_item");
          Node* n = (yyvsp[-1].node);
          if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 4774 "src/parser.tab.c"
    break;

  case 147: /* block_item: statement  */
#line 3044 "src/parser.y"
                { 
        dbg("block_item -> statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4782 "src/parser.tab.c"
    break;

  case 148: /* block_item: declaration  */
#line 3047 "src/parser.y"
                  { 
        dbg("block_item -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4790 "src/parser.tab.c"
    break;

  case 149: /* expression_statement: SEMICOLON  */
#line 3053 "src/parser.y"
                    { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4798 "src/parser.tab.c"
    break;

  case 150: /* expression_statement: expression SEMICOLON  */
#line 3056 "src/parser.y"
                               { 
        dbg("expression_statement -> expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4806 "src/parser.tab.c"
    break;

  case 151: /* selection_statement: IF LROUND expression RROUND statement  */
#line 3062 "src/parser.y"
                                                                  {
          dbg("selection_statement -> if ( expression ) statement");
          Node* e = (yyvsp[-2].node);
          if(e->type != "bool"){
              yyerror("Condition expression must be of type bool.");
          }
          Node* s1 = (yyvsp[0].node);
          Node* n = new Node();
          
          n->code = e->code;
          int falseJumpIndex = n->code.size();
          n->code.push_back("ifFalse " + e->place + " goto __");
          vector<int> falseList = makeList(falseJumpIndex);
          
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          
          string Lend = newLabel();
          n->code.push_back(Lend + ":");
          backpatch(n->code, falseList, Lend);
          
          (yyval.node) = n;
      }
#line 4833 "src/parser.tab.c"
    break;

  case 152: /* selection_statement: IF LROUND expression RROUND statement ELSE statement  */
#line 3084 "src/parser.y"
                                                           {
          dbg("selection_statement -> if ( expression ) statement else statement");
          Node* e = (yyvsp[-4].node);
            if(e->type != "bool"){
                yyerror("Condition expression must be of type bool.");
            }
          Node* s1 = (yyvsp[-2].node);
          Node* s2 = (yyvsp[0].node);
          Node* n = new Node();
          
          n->code = e->code;
          
          int falseJumpIndex = n->code.size();
          n->code.push_back("ifFalse " + e->place + " goto __");
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
#line 4871 "src/parser.tab.c"
    break;

  case 153: /* selection_statement: switch_head LCURLY case_list RCURLY  */
#line 3117 "src/parser.y"
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
        inloop=false;
      }
#line 4901 "src/parser.tab.c"
    break;

  case 154: /* $@6: %empty  */
#line 3145 "src/parser.y"
            {inloop=true;}
#line 4907 "src/parser.tab.c"
    break;

  case 155: /* switch_head: SWITCH $@6 LROUND assignment_expression RROUND  */
#line 3145 "src/parser.y"
                                                               {
        dbg("switch_head -> SWITCH ( expression )");
        Node* e = (yyvsp[-1].node);
        Node* n = new Node();
        n->code = e->code;
        n->place = e->place;
        switchType = e->type;
        switchVar = e->printName;
        (yyval.node) = n;
      }
#line 4922 "src/parser.tab.c"
    break;

  case 156: /* case_list: %empty  */
#line 3158 "src/parser.y"
       {
        dbg("case_list -> <empty>");
        Node* n = new Node();
        (yyval.node) = n;
      }
#line 4932 "src/parser.tab.c"
    break;

  case 157: /* case_list: case_list case_item  */
#line 3163 "src/parser.y"
                          {
        dbg("case_list -> case_list case_item");
        Node* prev = (yyvsp[-1].node);
        Node* curr = (yyvsp[0].node);
        prev->syn.insert(prev->syn.end(), curr->syn.begin(), curr->syn.end());
        prev->code.insert(prev->code.end(), curr->code.begin(), curr->code.end());
        (yyval.node) = prev;
      }
#line 4945 "src/parser.tab.c"
    break;

  case 158: /* case_item: CASE constant_expression statement  */
#line 3174 "src/parser.y"
                                         {
        dbg("case_item -> CASE constant_expression : statement");
        Node* caseVal = (yyvsp[-1].node);

        if(caseVal->type != switchType){
            yyerror("Type mismatch in case label.");
        }
        Node* stmt = (yyvsp[0].node);
        Node* n = new Node();
        
        string caseLabel = newLabel();
        if(!caseVal->code.empty()){
            n->syn.insert(n->syn.end(), caseVal->code.begin(), caseVal->code.end());
        }
        n->syn.push_back("if " + switchVar + " == " + caseVal->place + " goto " + caseLabel);
        n->code.push_back(caseLabel + ":");
        n->code.insert(n->code.end(), stmt->code.begin(), stmt->code.end());
        
        for (size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
            }
        }
        
        (yyval.node) = n;
      }
#line 4976 "src/parser.tab.c"
    break;

  case 159: /* case_item: DEFAULT statement  */
#line 3200 "src/parser.y"
                        {
        dbg("case_item -> DEFAULT : statement");
        Node* stmt = (yyvsp[0].node);
        Node* n = new Node();
        
        string defaultLabel = newLabel();
        n->syn.push_back("goto " + defaultLabel);
        
        n->code.push_back(defaultLabel + ":");
        n->code.insert(n->code.end(), stmt->code.begin(), stmt->code.end());
        
        for (size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
            }
        }
        // n->code.push_back("goto __");        
        (yyval.node) = n;
      }
#line 5000 "src/parser.tab.c"
    break;

  case 160: /* $@7: %empty  */
#line 3223 "src/parser.y"
                                     {inloop=true;}
#line 5006 "src/parser.tab.c"
    break;

  case 161: /* iteration_statement: WHILE LROUND expression RROUND $@7 statement  */
#line 3223 "src/parser.y"
                                                             {
        dbg("iteration_statement -> WHILE ( expression ) statement");
        Node* cond = (yyvsp[-3].node); 
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* body = (yyvsp[0].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
        int jumpIndex = n->code.size();
        n->code.push_back("ifFalse " + cond->place + " goto __");
        vector<int> falseList = makeList(jumpIndex);
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);

        for(size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
                falseList.push_back(i);
            }
            if (n->code[i] == "continue") {
                n->code[i] = "goto " + Lbegin;
            }
        }
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, falseList, Lend);
        (yyval.node) = n;
        inloop=false;
    }
#line 5047 "src/parser.tab.c"
    break;

  case 162: /* $@8: %empty  */
#line 3259 "src/parser.y"
                                     {inloop=true;}
#line 5053 "src/parser.tab.c"
    break;

  case 163: /* iteration_statement: UNTIL LROUND expression RROUND $@8 statement  */
#line 3259 "src/parser.y"
                                                             {
        dbg("iteration_statement -> UNTIL ( expression ) statement");
        Node* cond = (yyvsp[-3].node); 
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* body = (yyvsp[0].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
        int jumpIndex = n->code.size();
        n->code.push_back("if " + cond->place + " goto __");
        vector<int> falseList = makeList(jumpIndex);
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);

        for(size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
                falseList.push_back(i);
                dbg("Found break at line " + to_string(i));
            }
            if (n->code[i] == "continue") {
                n->code[i] = "goto " + Lbegin;
            }
        }
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, falseList, Lend);
        (yyval.node) = n;
        inloop=false;
    }
#line 5095 "src/parser.tab.c"
    break;

  case 164: /* $@9: %empty  */
#line 3296 "src/parser.y"
        {inloop=true;}
#line 5101 "src/parser.tab.c"
    break;

  case 165: /* iteration_statement: DO $@9 statement WHILE LROUND expression RROUND SEMICOLON  */
#line 3296 "src/parser.y"
                                                                          {
        dbg("iteration_statement -> DO statement WHILE ( expression ) ;");
        Node* body = (yyvsp[-5].node);
        Node* cond = (yyvsp[-2].node);
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());

        vector<int> falseList;
        for(size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
                falseList.push_back(i);
            }
            if (n->code[i] == "continue") {
                n->code[i] = "goto " + Lbegin;
            }
        }
        
        int jumpIndex = n->code.size();
        n->code.push_back("if " + cond->place + " goto " + Lbegin);

        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, falseList, Lend);
        (yyval.node) = n;
        inloop=false;
    }
#line 5141 "src/parser.tab.c"
    break;

  case 166: /* $@10: %empty  */
#line 3331 "src/parser.y"
                                                                     {inloop=true;}
#line 5147 "src/parser.tab.c"
    break;

  case 167: /* iteration_statement: for_start LROUND for_init_statement expression_statement RROUND $@10 statement  */
#line 3331 "src/parser.y"
                                                                                              {
        dbg("iteration_statement -> FOR ( for_init_statement expression_statement ) statement");
        Node* init = (yyvsp[-4].node);
        Node* cond = (yyvsp[-3].node);
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* body = (yyvsp[0].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        if(init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
        n->code.push_back(Lbegin + ":");
        
        vector<int> falseList;
        if (cond && cond->place != "") {
            n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
            int jumpIndex = n->code.size();
            n->code.push_back("ifFalse " + cond->place + " goto __");
            falseList = makeList(jumpIndex);
        }

        for(size_t i = 0; i < body->code.size(); i++) {
            if (body->code[i] == "break") {
                body->code[i] = "goto __";
                falseList.push_back(n->code.size() + i);
            }
            if (body->code[i] == "continue") {
                body->code[i] = "goto " + Lbegin;
            }
        }
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code,falseList,Lend);
        (yyval.node) = n;
        inloop=false;
        popScope();
    }
#line 5194 "src/parser.tab.c"
    break;

  case 168: /* $@11: %empty  */
#line 3373 "src/parser.y"
                                                                                {inloop=true;}
#line 5200 "src/parser.tab.c"
    break;

  case 169: /* iteration_statement: for_start LROUND for_init_statement expression_statement expression RROUND $@11 statement  */
#line 3373 "src/parser.y"
                                                                                                        {
        dbg("iteration_statement -> FOR ( for_init_statement expression_statement expression ) statement");
        Node* init = (yyvsp[-5].node);
        Node* cond = (yyvsp[-4].node);
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* iter = (yyvsp[-3].node);
        Node* body = (yyvsp[0].node);
        Node* n = new Node();
        
        string Lbegin = newLabel();
        if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
        n->code.push_back(Lbegin + ":");
        
        vector<int> falseList;
        if (cond && cond->place != "") {
            n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
            int jumpIndex = n->code.size();
            n->code.push_back("ifFalse " + cond->place + " goto __");
            falseList = makeList(jumpIndex);
        }

        for(size_t i = 0; i < body->code.size(); i++) {
            if (body->code[i] == "break") {
                body->code[i] = "goto __";
                falseList.push_back(n->code.size() + i);
            }
            if (body->code[i] == "continue") {
                body->code[i] = "goto " + Lbegin;
            }
        }
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        if (iter) n->code.insert(n->code.end(), iter->code.begin(), iter->code.end());
        n->code.push_back("goto " + Lbegin);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        if (!falseList.empty())
            backpatch(n->code, falseList, Lend);
        (yyval.node) = n;
        inloop=false;
        popScope();
    }
#line 5250 "src/parser.tab.c"
    break;

  case 170: /* for_start: FOR  */
#line 3421 "src/parser.y"
          {
        dbg("for_start -> FOR");
        pushScope();
        Node* n = new Node();
        (yyval.node) = n;
    }
#line 5261 "src/parser.tab.c"
    break;

  case 171: /* for_init_statement: expression_statement  */
#line 3430 "src/parser.y"
                               { 
        dbg("for_init_statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 5269 "src/parser.tab.c"
    break;

  case 172: /* for_init_statement: declaration  */
#line 3434 "src/parser.y"
    { 
        dbg("for_init_statement -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 5277 "src/parser.tab.c"
    break;

  case 173: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 3441 "src/parser.y"
                                    {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string((yyvsp[-1].str)));
          (yyval.node) = n;
      }
#line 5288 "src/parser.tab.c"
    break;

  case 174: /* jump_statement: CONTINUE SEMICOLON  */
#line 3447 "src/parser.y"
                             {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); 
          n->code.push_back("continue"); 
          (yyval.node) = n;
      }
#line 5299 "src/parser.tab.c"
    break;

  case 175: /* jump_statement: BREAK SEMICOLON  */
#line 3453 "src/parser.y"
                          {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); 
          n->code.push_back("break"); 
          (yyval.node) = n;
      }
#line 5310 "src/parser.tab.c"
    break;

  case 176: /* jump_statement: RETURN SEMICOLON  */
#line 3459 "src/parser.y"
                           {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); 
          if(lastFnType != "void")
              yyerror("Return statement must return a value.");
          n->code.push_back("return"); 
          (yyval.node) = n;
      }
#line 5323 "src/parser.tab.c"
    break;

  case 177: /* jump_statement: RETURN expression SEMICOLON  */
#line 3468 "src/parser.y"
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
            n->code.push_back("return " + expr->printName);
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
            n->code.push_back("return " + expr->printName);
        }
        (yyval.node) = n;
    }
#line 5364 "src/parser.tab.c"
    break;

  case 178: /* $@12: %empty  */
#line 3509 "src/parser.y"
    {
        dbg("external_declaration -> type_specifier");
        lastDeclType = string((yyvsp[0].str));
        dbg("lastDeclType in external_declaration: " + lastDeclType);
        lastFnType = lastDeclType;
    }
#line 5375 "src/parser.tab.c"
    break;

  case 179: /* external_declaration: type_specifier $@12 external  */
#line 3516 "src/parser.y"
    { 
        dbg("external_declaration -> type_specifier external");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 5384 "src/parser.tab.c"
    break;

  case 180: /* $@13: %empty  */
#line 3521 "src/parser.y"
    {
        dbg("external_declaration -> type_specifier pointer_list");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
        lastFnType = lastDeclType;
        dbg("");
        dbg("lastDeclType in external_declaration: " + lastDeclType);
        dbg("");
    }
#line 5397 "src/parser.tab.c"
    break;

  case 181: /* external_declaration: type_specifier pointer_list $@13 external  */
#line 3530 "src/parser.y"
    { 
        dbg("external_declaration -> type_specifier pointer_list external");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 5406 "src/parser.tab.c"
    break;

  case 182: /* external_declaration: struct_or_class_specifier SEMICOLON  */
#line 3535 "src/parser.y"
    { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        dbg("..ll");
        (yyval.node) = (yyvsp[-1].node); 
    }
#line 5416 "src/parser.tab.c"
    break;

  case 183: /* external_declaration: TYPEDEF return_type IDENTIFIER SEMICOLON  */
#line 3540 "src/parser.y"
                                               {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string((yyvsp[-1].str))] = typeSize[string((yyvsp[-2].str))];
        typeDefTable[string((yyvsp[-1].str))] = string((yyvsp[-2].str));
        (yyval.node) = new Node();
    }
#line 5427 "src/parser.tab.c"
    break;

  case 184: /* external_declaration: declare  */
#line 3546 "src/parser.y"
              {
        dbg("external_declaration -> declare");
        globalCode.insert(globalCode.begin(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end());
        (yyval.node) = new Node();
    }
#line 5437 "src/parser.tab.c"
    break;

  case 185: /* $@14: %empty  */
#line 3555 "src/parser.y"
    {
        dbg("declaration_specifiers -> const type_specifier");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
    }
#line 5446 "src/parser.tab.c"
    break;

  case 186: /* declare: CONST type_specifier $@14 init_declarator_list SEMICOLON  */
#line 3560 "src/parser.y"
    {
        dbg("declaration_specifiers -> const type_specifier init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 5455 "src/parser.tab.c"
    break;

  case 187: /* $@15: %empty  */
#line 3565 "src/parser.y"
    {
        dbg("declaration_specifiers -> static const type_specifier");
        lastDeclType = string((yyvsp[-2].str))+string((yyvsp[-1].str))+string((yyvsp[0].str));
    }
#line 5464 "src/parser.tab.c"
    break;

  case 188: /* declare: STATIC CONST type_specifier $@15 init_declarator_list SEMICOLON  */
#line 3570 "src/parser.y"
    {
        dbg("declaration_specifiers -> static const type_specifier init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 5473 "src/parser.tab.c"
    break;

  case 189: /* $@16: %empty  */
#line 3575 "src/parser.y"
    {
        dbg("declaration_specifiers -> static type_specifier");
        lastDeclType = string((yyvsp[-1].str))+string((yyvsp[0].str));
    }
#line 5482 "src/parser.tab.c"
    break;

  case 190: /* declare: STATIC type_specifier $@16 init_declarator_list SEMICOLON  */
#line 3580 "src/parser.y"
    {
        dbg("declaration_specifiers -> static type_specifier init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 5491 "src/parser.tab.c"
    break;

  case 191: /* $@17: %empty  */
#line 3588 "src/parser.y"
    {
        dbg("");
        dbg("lastFnType in external: " + lastFnType);
        dbg("");
        dbg("external -> IDENTIFIER ( )");
        string fname = string((yyvsp[-2].str));

        inFunction = true;
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
            funcTable[fname].printName = fname;
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
            f.printName = lastClassType + "." + string((yyvsp[-2].str));
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
#line 5545 "src/parser.tab.c"
    break;

  case 192: /* external: IDENTIFIER LROUND RROUND $@17 compound_statement  */
#line 3638 "src/parser.y"
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
        n->code.push_back("");
        currentFunction = "";
        lastFnType="int";
        inFunction = false;
        (yyval.node) = n;
    }
#line 5574 "src/parser.tab.c"
    break;

  case 193: /* $@18: %empty  */
#line 3663 "src/parser.y"
    {
        dbg("");
        dbg("lastDeclType in external: " + lastFnType);
        dbg("");
        dbg("external -> IDENTIFIER ( parameter_list )");
        string fname = string((yyvsp[-3].str));
        inFunction = true;
        
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
            funcTable[fname].printName = fname;
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
            f.printName = lastClassType + "." + methodName;
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
            dbg("Parameter declare: " + pname + " of type " + ptype);
            dbg(lastDeclType);

            string stars = "";
            string q = "";
            for(char c : ptype)
            {
                if(c == '*')
                    stars += '*';
                else
                    q += c;
            }
            dbg("q: " + q);
            dbg("stars: " + stars);
            if(classTable.find(q) != classTable.end())
            {
                dbg("abcd");
                for(const auto& member : classTable[q])
                {
                    if(member.second.kind == "function")
                    {
                        string name = stars + pname + "." + member.first;
                        string original = stars + pname + "." + member.second.method.original;
                        if(lookupSymbol(original) == nullptr)
                            declareSymbol(original, "function","function",vector<string>(),true);
                        dbg(original);
                        funcInfo f = member.second.method;
                        f.place = stars + pname + "." + f.place;
                        dbg("zz");
                        dbg(f.place);
                        funcTable[name] = f;
                        dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                    }
                    else
                    {
                        string name = stars + pname + "." + member.first;
                        bool ok = declareSymbol(name, member.second.type, member.second.kind);

                        if (!ok) {
                            yyerror("Duplicate declaration of '" + name + "' in same scope.");
                        }

                        Symbol* sym = lookupSymbol(name);
                        string w;
                        if(lastClassType == "")
                            w = currentFunction + currentScope + "." + name;
                        else
                            w = lastClassType + "." + currentFunction + currentScope + "." + name;
                        sym->printName = w;

                        dbg("mmm");
                        dbg(w);
                        dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                    }
                }
            }
            string w;
            if(lastClassType == "")
                w = currentFunction + currentScope + "." + pname;
            else
                w = lastClassType + "." + currentFunction + currentScope + "." + pname;
            sym->printName = w;
            if(!ok) yyerror("Duplicate parameter name '" + pname + "' in function '" + fname + "'.");
        }
    }
#line 5719 "src/parser.tab.c"
    break;

  case 194: /* external: IDENTIFIER LROUND parameter_list RROUND $@18 compound_statement  */
#line 3804 "src/parser.y"
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

        dbg("");
        dbg("fname: " + fname);
        dbg("lastFnType in external: " + lastFnType);
        dbg("");

        if((yyvsp[0].node)->code.back().substr(0,6) != "return")
        {
            yyerror("Missing return statement in function '" + fname + "'.");
        }
        n->code.push_back(fname + ":");

        if((yyvsp[0].node)) n->code.insert(n->code.end(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end());
        finalRoot = n;
        n->code.push_back("");
        currentFunction = "";
        inFunction = false;

        lastFnType="int";
        (yyval.node) = n;
    }
#line 5763 "src/parser.tab.c"
    break;

  case 195: /* external: init_declarator_list SEMICOLON  */
#line 3844 "src/parser.y"
    { 
        dbg("external -> init_declarator_list ;");
        Node* n = new Node();
        if(lastClassType == "")
            globalCode.insert(globalCode.begin(),(yyvsp[-1].node)->code.begin(),(yyvsp[-1].node)->code.end());
        else
        {
            n->code.insert(n->code.end(),(yyvsp[-1].node)->code.begin(),(yyvsp[-1].node)->code.end());
            n->code.push_back("");
        } 
        (yyval.node) = n;
    }
#line 5780 "src/parser.tab.c"
    break;

  case 196: /* return_type: type_specifier pointer_opt  */
#line 3948 "src/parser.y"
    { 
        dbg("return_type -> type_specifier pointer_opt");
        (yyval.str) = strdup( (string((yyvsp[-1].str)) + string((yyvsp[0].str))).c_str() );
    }
#line 5789 "src/parser.tab.c"
    break;


#line 5793 "src/parser.tab.c"

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

#line 3954 "src/parser.y"



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
