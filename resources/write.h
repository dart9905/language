int CreatASS (Tree_t* Tree, Cell_t* cell, const char* str);

Cell_t* CreatASSRet(Tree_t* Tree, Cell_t* cell, struct t_stack* stack, FILE* file);

#define DEF_CMD(functionT, declaration_cmd) \
if (strcmp(cell->data, #functionT) == 0) \
{ \
declaration_cmd\
}

int SWITCH_ADD (Cell_t* cell, struct t_stack* stack, FILE* file) {
    
#include "../resources/Comand.h"
    
    return 0;
}


#undef DEF_CMD




int CreatASS (Tree_t* Tree, Cell_t* cell, const char* str) {
    
    FILE* file = fopen(str, "wt");
    
    t_stack stack;
    stack.Construct (&stack, 10);
    
    CreatASSRet (Tree, cell, &stack, file);
    
    fclose(file);
    stack.Destructor(&stack);
    
    return 0;
}



Cell_t* CreatASSRet (Tree_t* Tree, Cell_t* cell, struct t_stack* stack , FILE* file) {
    
    assert(Tree);
    
    if (cell->nextl != NULL) {
        cell = CreatASSRet (Tree, cell->nextl, stack, file);
    }
    if (cell->nextr != NULL) {
        cell = CreatASSRet (Tree, cell->nextr, stack, file);
    }
    
    SWITCH_ADD (cell, stack, file);// функция обязательна должна возвращать pos_prev указатель на предыдующую ветку дерева!!!!!!!!
    
    return cell->prev;
}
