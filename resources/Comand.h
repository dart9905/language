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
    fprintf(file, "ADD\n");\
    return 0;


#define SUB_DEF \
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    fprintf(file, "SUB\n");\
    return 0;


#define DIV_DEF \
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
\
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    fprintf(file, "DIV\n");\
    return 0;


#define MUL_DEF \
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
    fprintf(file, "MUL\n");\
    return 0;


#define EQU_DEF \
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"POP %s\n", cell->nextr->data);\
    }\
    return 0;


#define DEF_IF \
    fprintf(file, "%i :\n", stack->Pop (stack) GOTO);\
    return 0;


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
    fprintf(file, "JBE %i\n", stack->Peek(stack) GOTO);\
    return 0;


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
    fprintf(file, "JAE %i\n", stack->Peek(stack) GOTO);\
    return 0;


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
    fprintf(file, "JNE %i\n", stack->Peek(stack) GOTO);\
    return 0;


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
    fprintf(file, "JA %i\n", stack->Peek(stack) GOTO);\
    return 0;


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
    fprintf(file, "JB %i\n", stack->Peek(stack) GOTO);\
    return 0;


#define DEF_WHI \
    fprintf(file, "CALL %i\n", stack->Peek(stack) - 1 GOTO);\
    fprintf(file, "%i :\n", stack->Pop(stack) GOTO);\
    stack->Pop(stack);\
    return 0;


#define DEF_END \
    fprintf(file,"END\n");\
    return 0;


#define DEF_BEG \
    fprintf(file,"BEGIN\n");\
    return 0;


#define DEF_REA \
if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
    fprintf(file,"IN\n", cell->nextl->data);\
    fprintf(file,"POP %s\n", cell->nextl->data);\
}\
return 0;


#define DEF_PRI \
if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
    fprintf(file,"PUSH %s\n", cell->nextl->data);\
    fprintf(file,"POP\n", cell->nextl->data);\
}\
return 0;





DEF_CMD( while, DEF_WHI )
DEF_CMD( if, DEF_IF )
DEF_CMD( begin, DEF_BEG )
DEF_CMD( end, DEF_END )
DEF_CMD( read, DEF_REA )
DEF_CMD( print, DEF_PRI )
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
//DEF_CMD( ;, return 0;)






#undef DEF_REA
#undef DEF_PRI
#undef DEF_END
#undef DEF_BEG
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
