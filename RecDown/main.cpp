//
//  main.cpp
//  RecDown
//
//  Created by macbook on 28.11.2017.
//  Copyright © 2017 macbook. All rights reserved.
//

#include <stdio.h>
//#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <math.h>


/*========================
 ОПАСНО БЛЯ
*/
const char* STR = NULL;
int POS = 0;
//========================



int GetG0 (const char* pSTR); //ГЛАВНЫЙ БОСС

int GetE (void); //НАЧАЛЬНИК ПО СЛОЖЕНИЮ И ВЫЧЕТАНИЮ

int GetT (void); //ЗАМ ПО УМНОЖЕНИЮ И ДЕЛЕНИЮ

int GetP (void);//ИНСПЕКТОР ГАДЖЕТ ПО СКОБКАМ

int GetN (void);//КОПАТЕЛЬ-СОБИРАЕТЛЬ ЦИФР В ЧИСЛА


int main() {
    printf("%i", GetG0("5*(10/2)-((((1))))"));
    printf("\n");
    return 0;
}



int GetG0 (const char* pSTR) {
    
    STR = pSTR;
    pSTR = 0;
    
    int val = GetE();
    assert(STR[POS] == 0);
    
    return val;
}



int GetE (void) {
    int val = GetT();
    
    while (STR [POS] == '+' || STR [POS] == '-') {
        
        int op = STR [POS];
        ++POS;
        
        int val2 = GetT();
        
        if (op == '+')
            val += val2;
        else
            val -= val2;
    }
    
    
    return val;
}



int GetT(void) {
    
    int val = GetP();
    
    while (STR [POS] == '*' || STR [POS] == '/') {
        
        int op = STR [POS];
        ++POS;
        
        int val2 = GetP();
        
        if (op == '*')
            val *= val2;
        else
            val /= val2;
    }
    
    
    return val;
    
    return 0;
}



int GetP (void) {
    if (STR [POS] =='(') {
        ++POS;
        
        int val = GetE();
        
        assert(STR [POS] == ')');
        ++POS;
        
        return val;
    } else
        return GetN();
}



int GetN (void) {
    int val = 0;
    while ('0' <= STR [POS] && STR [POS] <='9') {
        val = val * 10 + STR [POS] - '0';
        ++POS;
    }
    return val;
}

