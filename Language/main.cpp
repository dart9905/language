//
//  main.cpp
//  Language
//
//  Created by macbook on 28.11.2017.
//  Copyright © 2017 macbook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <math.h>



const char* TREE_FILES = "../resources/save.txt";
const char* TREE_FILES1 = "../resources/save1.txt";
const long int LI = 1000000000;
typedef char* TYPE_TREE;
#include "../resources/tree.h"




char* GetG0 (Tree_t* Tree, const char* pSTR); //ГЛАВНЫЙ БОСС

char* GetE (Tree_t* Tree, const char* pSTR, int* pPOS); //НАЧАЛЬНИК ПО СЛОЖЕНИЮ И ВЫЧЕТАНИЮ

char* GetT (Tree_t* Tree, const char* pSTR, int* pPOS); //ЗАМ ПО УМНОЖЕНИЮ И ДЕЛЕНИЮ

char* GetP (Tree_t* Tree, const char* pSTR, int* pPOS);//ИНСПЕКТОР ГАДЖЕТ ПО СКОБКАМ

char* GetN (Tree_t* Tree, const char* pSTR, int* pPOS);//КОПАТЕЛЬ-СОБИРАЕТЛЬ ЦИФР В ЧИСЛА


char* GetF1(Tree_t* Tree, const char* pSTR, int* pPOS);//ОПРЕДЕЛИТЬ ДОП ФУНКЦИЙ


char* GetF2(Tree_t* Tree, const char* pSTR, int* pPOS, char* str_fun, char* val_s);//ДОП ФУНКЦИИ


int DtoS (char* str, double var);


int main() {
    
    char str [] = "";
    Tree_t* Tree = TreeConstruct(str);
    //Cell_t* dcell_new = CellNew(dTree);
    
    long int number_of_char = 0;
    char* my_buffer = ReadFiles (TREE_FILES , &number_of_char);
    
    printf("%s\n", GetG0(Tree, my_buffer));
    
    
    return 0;
}



char* GetG0 (Tree_t* Tree, const char* pSTR) {
    
    int* pPOS;
    *pPOS = 0;
    //pSTR = "";
    
    char* val_s = GetE(Tree, pSTR, pPOS);
    
    assert(val_s);
    assert(pSTR[*pPOS] == '\0');
    
    return val_s;
}



char* GetE (Tree_t* Tree, const char* pSTR, int* pPOS) {
    char* val_s = GetT(Tree, pSTR, pPOS);
    assert(val_s);
    
    double val_d1 = strtod(val_s, NULL);
    double val_d2;
    
    while (pSTR [*pPOS] == '+' || pSTR [*pPOS] == '-') {
        char op = pSTR [*pPOS];
        ++*pPOS;
        
        char* val_s2 = GetT(Tree, pSTR, pPOS);
        assert(val_s2);
        val_d2 = strtod(val_s2, NULL);
        
        if (op == '+')
            val_d1 += val_d2;
        else
            val_d1 -= val_d2;
        DtoS(val_s, val_d1);
    }
    
    
    return val_s;
}



char* GetT(Tree_t* Tree, const char* pSTR, int* pPOS) {
    
    char* val_s = GetP(Tree, pSTR, pPOS);
    assert(val_s);
    
    double val_d1 = strtod(val_s, NULL);
    double val_d2;
    
    while (pSTR [*pPOS] == '*' || pSTR [*pPOS] == '/') {
        
        char op = pSTR [*pPOS];
        ++*pPOS;
        
        char* val_s2 = GetP(Tree, pSTR, pPOS);
        assert(val_s2);
        val_d2 = strtod(val_s2, NULL);
        
        if (op == '*')
            val_d1 *= val_d2;
        else
            val_d1 /= val_d2;
        
        DtoS(val_s, val_d1);
    }
    
    
    return val_s;
}



char* GetP (Tree_t* Tree, const char* pSTR, int* pPOS) {
    if (pSTR [*pPOS] =='(') {
        ++*pPOS;
        
        char* val_s = GetE(Tree, pSTR, pPOS);
        
        assert(pSTR [*pPOS] == ')');
        ++*pPOS;
        
        return val_s;
    } else
        if ((('a' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'z')) || (('A' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'Z'))) {
            
            char* str_fun = GetF1(Tree, pSTR, pPOS);
            assert(pSTR [*pPOS] == '(');
            ++*pPOS;
            
            char* val_s = GetE(Tree, pSTR, pPOS);
            assert(pSTR [*pPOS] == ')');
            
            ++*pPOS;
            
            val_s = GetF2(Tree, pSTR, pPOS, str_fun, val_s);
            
            delete str_fun;
            
            return val_s;
        } else
            return GetN(Tree, pSTR, pPOS);
    return NULL;
}



char* GetN (Tree_t* Tree, const char* pSTR, int* pPOS) {
    char* val_s = new char [CELL_SIZE_DATA];
    char str [CELL_SIZE_DATA] = "";
    int i = 0;
    
    if (((pSTR [*pPOS] == '+') || (pSTR [*pPOS] == '-')) && ('0' <= pSTR [*pPOS + 1] && pSTR [*pPOS + 1] <= '9')) {
        str [i] = pSTR [*pPOS];
        ++*pPOS;
        ++i;
    }
    
    while ('0' <= pSTR [*pPOS] && pSTR [*pPOS] <= '9') {
        str [i] = pSTR [*pPOS];
        ++*pPOS;
        ++i;
    }
    
    if (pSTR [*pPOS] == '.') {
        while ('0' <= pSTR [*pPOS] && pSTR [*pPOS] <= '9') {
            str [i] = pSTR [*pPOS];
            ++i;
            ++*pPOS;
        }
        
    }
    str [i] = '\0';
    
    memcpy(val_s, str, strlen(str));
    return val_s;
}



char* GetF1(Tree_t* Tree, const char* pSTR, int* pPOS) {
    
    char* val_s = new char [CELL_SIZE_DATA];
    char str [CELL_SIZE_DATA] = "";
    int i = 0;
    
    while (((('a' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'z')) || (('A' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'Z')))
           && (pSTR [*pPOS] != '(')) {
        
        if (('A' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'Z')) {
            str [i] = pSTR [*pPOS] + ('A' - 'a');
        } else
            str [i] = pSTR [*pPOS];
        
        ++i;
        ++*pPOS;
    }
    
    str [i] = '\0';
    
    memcpy(val_s, str, strlen(str));
    return val_s;
}


char* GetF2(Tree_t* Tree, const char* pSTR, int* pPOS, char* str_fun, char* val_s) {
    assert(str_fun);
    assert(val_s);
    
    if (strcmp(str_fun, "sin") == 0) {
        DtoS (val_s ,sin(strtod(val_s, NULL)));
    }
    if (strcmp(str_fun, "cos") == 0) {
        DtoS (val_s ,cos(strtod(val_s, NULL)));
    }
    if (strcmp(str_fun, "tg") == 0) {
        DtoS (val_s ,sin(strtod(val_s, NULL)) / cos(strtod(val_s, NULL)));
    }
    if (strcmp(str_fun, "ctg") == 0) {
        DtoS (val_s , cos(strtod(val_s, NULL)) / sin(strtod(val_s, NULL)));
    }
    if (strcmp(str_fun, "sqrt") == 0) {
        DtoS (val_s ,sqrt(strtod(val_s, NULL)));
    }
    
    return val_s;
}



int DtoS (char* str, double var) {
    
    int i = 0;
    assert(str);
    str [0] = '\0';
    
    if (var < 0) {
        var = (-1) * var;
        str [i] = '-';
        ++i;
    }
    
    long int maxd = 1;
    long int maxp = 1;
    long int j = 0;
    long int pov = var;
    long int div = var * LI - pov * LI;
    long int longdiv = LI;
    
    
    
    while((j == 0) && (div > 0))
    {
        div = div / 10;
        j = div % 10;
        longdiv = longdiv / 10;
    }
    
    longdiv = longdiv / 10;
    
    while (maxp <= pov) maxp = maxp * 10;
    maxp = maxp / 10;
    
    while (maxd <= div) maxd = maxd * 10;
    maxd = maxd / 10;
    
    while (maxp > 0) {
        str [i] = pov / maxp + '0';
        if (pov > 0)
            pov = pov - (pov / maxp) * maxp;
        maxp = maxp / 10;
        ++i;
    }
    if (maxd > 0) {
        str [i] = '.';
        ++i;
        
        while (longdiv != maxd) {
            str [i] = '0';
            ++i;
            longdiv = longdiv / 10;
        }
        
        while (div > 0) {
            str [i] = div / maxd + '0';
            div = div - (div / maxd) * maxd;
            maxd = maxd / 10;
            ++i;
        }
    }
    if (i == 0) {
        str [i] = '0';
        ++i;
    }
    str [i] = '\0';
    
    return 0;
    
}
