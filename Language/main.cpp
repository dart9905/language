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
const char* CODE_FILES1 = "../resources/code.txt";

const long int LI = 1000000000;
typedef char* TYPE_TREE;

#include "../resources/tree.h"
#include "../resources/read.h"
#include "../resources/write.h"





int DtoS (char* str, double var);

int CreateCode (Tree_t* Tree, Cell_t* cell);

Cell_t* CreateCodeRec (Tree_t* Tree, Cell_t* cell);




int main() {
    
    char str [] = "";
    Tree_t* Tree = TreeConstruct(str);
    
    long int number_of_char = 0;
    char* my_buffer = ReadFiles (TREE_FILES , &number_of_char);
    
    Tree->cell = GetG0(Tree, my_buffer);
    Tree->position_first_cell = Tree->cell;
    TreeDump(Tree, Tree->cell);
    
    TreePrintFile(Tree, Tree->position_first_cell);
    
    TreeDestructor(Tree);
    
    return 0;
}



int CreateCode (Tree_t* Tree, Cell_t* cell) {
    TreeGoRound(Tree, cell, CreateCodeRec, FROM_BELOW);
    return 0;
}



Cell_t* CreateCodeRec (Tree_t* Tree, Cell_t* cell) {
    
    return cell->prev;
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
