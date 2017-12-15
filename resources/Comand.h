#define GOTO + 100


#define GOTO_WHILE \
    if (cell->prev != NULL)\
        if (strcmp(cell->prev->data, "while") == 0) {\
            stack->Push(stack, stack->Peek(stack) + 1);\
            fprintf(file, "%i :\n", stack->Peek(stack) GOTO);\
        }\


#define DEF_ADD \
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
    fprintf(file, "ADD\n");


#define SUB_DEF \
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    fprintf(file, "SUB\n");


#define DIV_DEF \
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    fprintf(file, "DIV\n");


#define MUL_DEF \
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
    fprintf(file, "MUL\n");


#define EQU_DEF \
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"POP %s\n", cell->nextr->data);\
    }\


#define DEF_IF fprintf(file, "%i :\n", stack->Pop (stack) GOTO);


#define MOR_DEF \
    GOTO_WHILE\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "JBE %i\n", stack->Peek(stack) GOTO);


#define LES_DEF \
    GOTO_WHILE\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "JAE %i\n", stack->Peek(stack) GOTO);


#define EQUEQU_DEF \
    GOTO_WHILE\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "JNE %i\n", stack->Peek(stack) GOTO);


#define LESEQU_DEF \
    GOTO_WHILE\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "JA %i\n", stack->Peek(stack) GOTO);


#define MOREQU_DEF \
    GOTO_WHILE\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "JB %i\n", stack->Peek(stack) GOTO);


#define DEF_WHI \
    fprintf(file, "CALL %i\n", stack->Peek(stack) - 1 GOTO);\
    fprintf(file, "%i :\n", stack->Pop(stack) GOTO);\
    stack->Pop(stack);





DEF_CMD( while, DEF_WHI )
DEF_CMD( if, DEF_IF )
DEF_CMD( +, DEF_ADD )
DEF_CMD( -, SUB_DEF )
DEF_CMD( /, DIV_DEF )
DEF_CMD( *, MUL_DEF )
DEF_CMD( =, EQU_DEF )
DEF_CMD( >, MOR_DEF)
DEF_CMD( <, LES_DEF)
DEF_CMD( ==, EQUEQU_DEF)
DEF_CMD( <=, LESEQU_DEF)
DEF_CMD( >=, MOREQU_DEF)
DEF_CMD( , )






#undef GOTO
#undef GOTO_WHILE
#undef DEF_WHI
#undef DEF_IF
#undef DEF_ADD
#undef SUB_DEF
#undef DIV_DEF
#undef MUL_DEF
#undef EQU_DEF
#undef MOR_DEF
#undef LES_DEF
#undef EQUEQU_DEF
#undef LESEQU_DEF
#undef MOREQU_DEF
