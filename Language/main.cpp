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




Cell_t* GetG0 (Tree_t* Tree, const char* pSTR); //ГЛАВНЫЙ БОСС

Cell_t* GetE (Tree_t* Tree, const char* pSTR, int* pPOS); //НАЧАЛЬНИК ПО СЛОЖЕНИЮ И ВЫЧЕТАНИЮ

Cell_t* GetT (Tree_t* Tree, const char* pSTR, int* pPOS); //ЗАМ ПО УМНОЖЕНИЮ И ДЕЛЕНИЮ

Cell_t* GetS (Tree_t* Tree, const char* pSTR, int* pPOS); //БРИГАДИР ПО СТЕПЕНЯМ

Cell_t* GetP (Tree_t* Tree, const char* pSTR, int* pPOS);//ИНСПЕКТОР ГАДЖЕТ ПО СКОБКАМ

Cell_t* GetN (Tree_t* Tree, const char* pSTR, int* pPOS);//КОПАТЕЛЬ-СОБИРАЕТЛЬ ЦИФР В ЧИСЛА

Cell_t* GetF1(Tree_t* Tree, const char* pSTR, int* pPOS);//ОПРЕДЕЛИТЬ ДОП ФУНКЦИЙ

char* GetF2(Tree_t* Tree, const char* pSTR, int* pPOS, char* str_fun, char* val_s);//ДОП ФУНКЦИИ

Cell_t* Creat_Cell (Tree_t* Tree, Cell_t* cell1, Cell_t* cell2, Cell_t* cell3, char* str);

int DtoS (char* str, double var);




int main() {
    
    char str [] = "";
    Tree_t* Tree = TreeConstruct(str);
    //Cell_t* dcell_new = CellNew(dTree);
    
    long int number_of_char = 0;
    char* my_buffer = ReadFiles (TREE_FILES , &number_of_char);
    
    Tree->cell = GetG0(Tree, my_buffer);
    //Tree->cell->nextl->prev = Tree->cell;
    Tree->position_first_cell = Tree->cell;
    TreeDump(Tree, Tree->cell);
    //assert(0);
    TreeDestructor(Tree);
    
    return 0;
}



Cell_t* GetG0 (Tree_t* Tree, const char* pSTR) {
    
    int POS;
    POS = 0;
    //pSTR = "";
    
    Cell_t* cell_new = GetE(Tree, pSTR, &POS);
    
    assert(cell_new);
    //assert(0);
    assert(pSTR[POS] == '\0');
    
    return cell_new;
}



Cell_t* GetE (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Cell_t* cell_new = GetT(Tree, pSTR, pPOS);
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [2];
    
    assert(cell_new);
    
    if (pSTR [*pPOS] == '+' || pSTR [*pPOS] == '-') {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        
        cell_new2 = GetE(Tree, pSTR, pPOS);
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new, cell_new2, cell_new3, op);
        
    }
    return cell_new3;
}



Cell_t* GetT(Tree_t* Tree, const char* pSTR, int* pPOS) {
    Cell_t* cell_new = GetS(Tree, pSTR, pPOS);
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [2];
    
    assert(cell_new);
    
    if (pSTR [*pPOS] == '*' || pSTR [*pPOS] == '/') {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        
        cell_new2 = GetT(Tree, pSTR, pPOS);
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new, cell_new2, cell_new3, op);
        
    }
    
    return cell_new3;
}



Cell_t* GetS (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Cell_t* cell_new = GetP(Tree, pSTR, pPOS);
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [2];
    
    assert(cell_new);
    
    if (pSTR [*pPOS] == '^') {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        
        cell_new2 = GetS(Tree, pSTR, pPOS);
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new, cell_new2, cell_new3, op);
        
    }
    
    return cell_new3;
    
}




Cell_t* GetP (Tree_t* Tree, const char* pSTR, int* pPOS) {
    if (pSTR [*pPOS] =='(') {
        
        ++*pPOS;
        
        Cell_t* cell_new = GetE(Tree, pSTR, pPOS);
        
        assert(pSTR [*pPOS] == ')');
        ++*pPOS;
        
        return cell_new;
    } else
        if ((('a' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'z')) || (('A' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'Z'))) {
            
            Cell_t* cell_new = GetF1(Tree, pSTR, pPOS);
            assert(cell_new);
            
            if (pSTR [*pPOS] == '(') {
                
                ++*pPOS;
                
                cell_new->nextl = GetE(Tree, pSTR, pPOS);
                
                if (pSTR [*pPOS] == ',') {
                    ++*pPOS;
                    cell_new->nextr = GetE(Tree, pSTR, pPOS);
                    cell_new->nextr->prev = cell_new;
                }
                
                assert(pSTR [*pPOS] == ')');
                ++*pPOS;
                
                assert(cell_new->nextl);
                
                cell_new->nextl->prev = cell_new;
                
            }
            
            
            return cell_new;
        } else
            return GetN(Tree, pSTR, pPOS);
    printf("NULL\n");
    return NULL;
}



Cell_t* GetN (Tree_t* Tree, const char* pSTR, int* pPOS) {
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
    
    Cell_t* cell_new = CellNew(Tree);
    cell_new->data = val_s;
    
    return cell_new;
}



Cell_t* GetF1(Tree_t* Tree, const char* pSTR, int* pPOS) {
    
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
    
    Cell_t* cell_new = CellNew(Tree);
    cell_new->data = val_s;
    
    return cell_new;
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



Cell_t* Creat_Cell (Tree_t* Tree, Cell_t* cell1, Cell_t* cell2, Cell_t* cell3, char* str) {
    assert(Tree);
    assert(str);
    
    cell3 = CellNew (Tree);
    cell3->data = str;
    cell3->nextl = cell1;
    cell3->nextr = cell2;
    cell3->nextl->prev = cell3;
    cell3->nextr->prev = cell3;
    
    return cell3;
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
