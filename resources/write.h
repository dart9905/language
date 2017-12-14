int CreatASS (Tree_t* Tree, Cell_t* cell, const char* str);

Cell_t* CreatASSRet(Tree_t* Tree, Cell_t* cell, FILE* file);

#define DEF_CMD(functionT, declaration_cmd) \
if (strcmp(cell->data, #functionT) == 0) \
{ \
declaration_cmd\
}

int SWITCH_ADD (Cell_t* cell, FILE* file) {
    
#include "../resources/Comand.h"
    
    return 0;
}


#undef DEF_CMD




int CreatASS (Tree_t* Tree, Cell_t* cell, const char* str) {
    
    FILE* file = fopen(str, "wt");
    
    CreatASSRet (Tree, cell, file);
    
    fclose(file);
    
    return 0;
}



Cell_t* CreatASSRet (Tree_t* Tree, Cell_t* cell, FILE* file) {
    
    assert(Tree);
    
    if (cell->nextl != NULL) {
        cell = CreatASSRet (Tree, cell->nextl, file);
    }
    if (cell->nextr != NULL) {
        cell = CreatASSRet (Tree, cell->nextr, file);
    }
    
    SWITCH_ADD (cell, file);// функция обязательна должна возвращать pos_prev указатель на предыдующую ветку дерева!!!!!!!!
    
    return cell->prev;
}
