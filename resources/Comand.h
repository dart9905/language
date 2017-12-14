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
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextl->data);\
    }\
\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"PUSH %s\n", cell->nextr->data);\
    }\
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
    }


#define MOR_DEF


#define LES_DEF


#define EQUEQU_DEF


#define LESEQU_DEF


#define MOREQU_DEF






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
