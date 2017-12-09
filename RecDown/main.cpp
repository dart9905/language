//
//  main.cpp
//  RecDown
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


/*========================
 ОПАСНО БЛЯ
*/
const char* STR = NULL;
int POS = 0;
//========================



char* GetG0 (const char* pSTR); //ГЛАВНЫЙ БОСС

char* GetE (void); //НАЧАЛЬНИК ПО СЛОЖЕНИЮ И ВЫЧЕТАНИЮ

char* GetT (void); //ЗАМ ПО УМНОЖЕНИЮ И ДЕЛЕНИЮ

char* GetP (void);//ИНСПЕКТОР ГАДЖЕТ ПО СКОБКАМ

char* GetN (void);//КОПАТЕЛЬ-СОБИРАЕТЛЬ ЦИФР В ЧИСЛА


char* GetF1(void);//ОПРЕДЕЛИТЬ ДОП ФУНКЦИЙ


char* GetF1(char* str_fun, char* val_s);//ДОП ФУНКЦИИ


int DtoS (char* str, double var);


int main() {
    
    printf("%s\n", GetG0("5/5/5*5-5*(200-100)"));
    return 0;
}



char* GetG0 (const char* pSTR) {
    
    STR = pSTR;
    //pSTR = "";
    
    char* val_s = GetE();
    
    assert(val_s);
    assert(STR[POS] == '\0');
    
    return val_s;
}



char* GetE (void) {
    char* val_s = GetT();
    assert(val_s);
    
    double val_d1 = strtod(val_s, NULL);
    double val_d2;
    
    while (STR [POS] == '+' || STR [POS] == '-') {
        char op = STR [POS];
        ++POS;
        
        char* val_s2 = GetT();
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



char* GetT(void) {
    
    char* val_s = GetP();
    assert(val_s);
    
    double val_d1 = strtod(val_s, NULL);
    double val_d2;
    
    while (STR [POS] == '*' || STR [POS] == '/') {
        
        char op = STR [POS];
        ++POS;
        
        char* val_s2 = GetP();
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



char* GetP (void) {
    if (STR [POS] =='(') {
        ++POS;
        
        char* val_s = GetE();
        
        assert(STR [POS] == ')');
        ++POS;
        
        return val_s;
    } else
        if ((('a' <= STR [POS]) && (STR [POS] <= 'z')) || (('A' <= STR [POS]) && (STR [POS] <= 'Z'))) {
            
            char* str_fun = GetF1();
            
            char* val_s = GetE();
            assert(STR [POS] == ')');
            
            ++POS;
            
            val_s = GetF2(str_fun, val_s);
            
            delete str_fun;
            
            return val_s;
        } else
            return GetN();
    return NULL;
}



char* GetN (void) {
    char* val_s = new char [CELL_SIZE_DATA];
    char str [CELL_SIZE_DATA] = "";
    int i = 0;
    
    if (((STR [POS] == '+') || (STR [POS] == '-')) && ('0' <= STR [POS + 1] && STR [POS + 1] <= '9')) {
        str [i] = STR [POS];
        ++POS;
        ++i;
    }
    
    while ('0' <= STR [POS] && STR [POS] <= '9') {
        str [i] = STR [POS];
        ++POS;
        ++i;
    }
    
    if (STR [POS] == '.') {
        while ('0' <= STR [POS] && STR [POS] <= '9') {
            str [i] = STR [POS];
            ++i;
            ++POS;
        }
        
    }
    str [i] = '\0';
    
    memcpy(val_s, str, strlen(str));
    return val_s;
}



char* GetF1(void) {
    
}


char* GetF1(char* str_fun, char* val_s) {
    
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
