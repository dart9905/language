#define STARTP_COMMAND(program_status) \
   if ((program_status == StartProgram) && (programm [1 + *position_number] != 22)) {


#define SEARCH_TAGST_COMMAND(program_status) \
   if (program_status == SearchTagsProgram) {


#define END_COMMAND }

#define NEXT_P (++(*position_number))

#define BACK_P (-—(*position_number))

#define POP_S(EL) DATA_TYPE EL = name_stack->Pop(name_stack)

#define PUSH_S(EL) name_stack->Push(name_stack, (EL))

#define COLON_N 22

#define POS *position_number




#define DEF_REG(reg_name, number_reg, number) \
   if (strcmp(parameter_reg, #reg_name) == 0) \
   { \
\
      int* j = new int;\
      *j = 0;\
      for (int i = number_reg; i > 0;) { \
         parameter_reg [*j] = (char)(48 + i % 10);\
         i = i / 10;\
         ++(*j);\
      } \
\
      parameter_reg [*j] = '\n';\
      ++(*j);\
      for (int i = number; i > 0;) { \
         parameter_reg [*j] = (char)(48 + i % 10);\
         i = i / 10;\
         ++(*j);\
      } \
\
      parameter [*j] = '\0';\
      for (int i = 0; *j > 0 ; ++i) {\
         parameter [i] = parameter_reg [--(*j)];\
      }\
      delete j;\
\
      return -1;\
   }


#define DECLARATION_COMMAND(number) \
   if (my_buffer [*i] == ' ') \
   {\
      ++(*i);\
      ReadFunction (parameter_reg, my_buffer, number_of_char, i);\
      DEF_REG( ax, 1, number)\
      DEF_REG( bx, 2, number)\
      DEF_REG( cx, 3, number)\
      DEF_REG( dx, 4, number)\
      do { \
         --(*i);\
      } while (my_buffer [*i] != ' '); \
   }
       

#define DECLARATION_COMMAND2(number) \
if ((my_buffer [*i] == ' ') && (my_buffer [*i+1] == '[')) \
{\
    (*i) += 1;\
    ReadFunction (parameter_reg, my_buffer, number_of_char, i);\
    parameter_reg [strlen(parameter_reg) - 1] = '\0';\
    int* j = new int;\
    *j = 0;\
    for (int i = strlen(parameter_reg) - 1; i > 0;) { \
        parameter_reg [*j] = parameter_reg [i];\
        --i;\
        ++(*j);\
    } \
    \
    parameter_reg [*j] = '\n';\
    ++(*j);\
    for (int i = number; i > 0;) { \
        parameter_reg [*j] = (char)(48 + i % 10);\
        i = i / 10;\
        ++(*j);\
    } \
    \
    parameter [*j] = '\0';\
    for (int i = 0; *j > 0 ; ++i) {\
        parameter [i] = parameter_reg [--(*j)];\
    }\
    delete j;\
    \
    return -1;\
    do { \
        --(*i);\
    } while (my_buffer [*i] != ' '); \
}



#define IF_JUMP(number) \
   POP_S(x);\
   POP_S(y);\
   PUSH_S(y);\
   PUSH_S(x);\
   NEXT_P;\
\
   if (number) {\
      for (int i = 0; i < code_length; ++i) {\
         if (goto_data_name [i] == programm [POS]) {\
            POS = 1 + goto_data_position [i];\
            return 0;\
         }\
      }\
   } else {\
      return 0;\
   }


#define BEGIN_CODE \
   if ((*program_status == WaitingProgram) && (programm [1 + POS] != COLON_N)) { \
      *program_status = StartProgram; \
      printf("Start\n");\
   } \
   return 0;


#define PUSH_CODE \
   STARTP_COMMAND(*program_status)\
\
      NEXT_P;\
      PUSH_S(programm [POS]);\
\
      return 0;\
\
   END_COMMAND \
   NEXT_P;\
   return 0;


#define PUSH_REG_CODE \
   STARTP_COMMAND(*program_status)\
\
      NEXT_P;\
\
      PUSH_S(data->reg [(int)programm [POS]]);\
\
      return 0;\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define POP_CODE \
   STARTP_COMMAND(*program_status) \
\
      printf ("\n%lg\n", name_stack->Pop(name_stack));\
\
      return 0;\
\
   END_COMMAND


#define ADD_CODE \
   STARTP_COMMAND(*program_status)\
\
      POP_S(x);\
      POP_S(y);\
      PUSH_S(x + y);\
\
      return 0;\
\
   END_COMMAND


#define MOV_CODE \
   STARTP_COMMAND(*program_status)\
\
      NEXT_P;\
      data->reg [(int)programm [*position_number]] = name_stack->Pop(name_stack);\
      PUSH_S(data->reg [(int)programm [POS]]);\
\
      return 0;\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define MUL_CODE \
   STARTP_COMMAND(*program_status)\
\
      POP_S(x);\
      POP_S(y);\
      PUSH_S(x * y);\
\
      return 0;\
\
   END_COMMAND


#define SUB_CODE\
   STARTP_COMMAND(*program_status)\
\
      POP_S(y);\
      POP_S(x);\
      PUSH_S(x - y);\
\
      return 0;\
\
   END_COMMAND


#define END_CODE\
   STARTP_COMMAND(*program_status)\
\
      *program_status = EndProgram;\
\
      printf("\nEND\n");\
      return EndProgram;\
\
   END_COMMAND


#define SQRT_CODE\
   STARTP_COMMAND(*program_status)\
\
   POP_S(x);\
   if (x >= 0) {\
      x = sqrt(x);\
   }\
   PUSH_S(x);\
\
   return 0;\
\
   END_COMMAND


#define OUT_CODE\
   STARTP_COMMAND(*program_status)\
   name_stack->Out(name_stack);\
   return 0;\
   END_COMMAND


#define DIV_CODE \
   STARTP_COMMAND(*program_status) \
\
      POP_S(y);\
      POP_S(x);\
\
      if (y != 0) {\
         PUSH_S( x / y );\
      }\
\
      return 0;\
\
   END_COMMAND


#define POP_REG_CODE \
   STARTP_COMMAND(*program_status)\
\
      NEXT_P;\
      data->reg [(int)programm [POS]] = name_stack->Pop(name_stack);\
\
      return 0;\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define JMP_CODE \
   STARTP_COMMAND(*program_status)\
\
      NEXT_P;\
      for (int i = 0; i < code_length; ++i) {\
         if (goto_data_name [i] == programm [POS]) {\
            POS = 1 + goto_data_position [i];\
            return 0;\
         }\
      }\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define JE_CODE \
   STARTP_COMMAND(*program_status)\
\
      IF_JUMP(x == y)\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define JNE_CODE \
   STARTP_COMMAND(*program_status)\
\
      IF_JUMP(x != y)\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define JA_CODE \
   STARTP_COMMAND(*program_status)\
\
      IF_JUMP(x > y)\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define JAE_CODE \
   STARTP_COMMAND(*program_status)\
\
      IF_JUMP(x >= y)\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define JB_CODE\
   STARTP_COMMAND(*program_status)\
\
      IF_JUMP(x < y)\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define JBE_CODE \
   STARTP_COMMAND(*program_status)\
\
      IF_JUMP(x <= y)\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define RET_CODE \
   STARTP_COMMAND(*program_status)\
\
      POS = (int)(label_history->Pop(label_history));\
\
      return 0;\
\
   END_COMMAND


#define COLON_CODE \
   SEARCH_TAGST_COMMAND(*program_status)\
\
      --(*position_number);\
      goto_data_name [*position_number_goto] = programm [*position_number];\
      goto_data_position [*position_number_goto] = POS;\
      ++(*position_number_goto);\
      NEXT_P;\
\
      return 0;\
\
   END_COMMAND\
   STARTP_COMMAND(*program_status)\
\
   END_COMMAND\
   return 0;


#define CALL_CODE \
   STARTP_COMMAND(*program_status)\
\
      NEXT_P;\
      for (int i = 0; i < code_length; ++i) {\
         if (goto_data_name [i] == programm [POS]) {\
            label_history->Push(label_history, POS);\
            POS = 1 + goto_data_position [i];\
            return 0;\
         }\
      }\
\
   END_COMMAND\
   NEXT_P;\
   return 0;


#define DPOP_CODE \
   STARTP_COMMAND(*program_status) \
\
      POP_S(x);\
\
      return 0;\
\
   END_COMMAND

#define IN_CODE \
STARTP_COMMAND(*program_status) \
\
   DATA_TYPE x = 0;\
   scanf("%lg",&x);\
   PUSH_S(x);\
\
   return 0;\
\
END_COMMAND

       

#define PUSH_OP_CODE \
    STARTP_COMMAND(*program_status)\
\
        NEXT_P;\
\
        PUSH_S(data->op [(int)programm [POS]]);\
\
        return 0;\
\
    END_COMMAND\
    NEXT_P;\
    return 0;

       
       
#define POP_OP_CODE \
    STARTP_COMMAND(*program_status)\
\
        NEXT_P;\
\
        data->op [(int)programm [POS]] = name_stack->Pop(name_stack);\
\
        return 0;\
\
    END_COMMAND\
    NEXT_P;\
    return 0;







DEF_CMD( BEGIN, 1 ,,   BEGIN_CODE)


DEF_CMD( PUSH,  2 ,   DECLARATION_COMMAND2(26)  DECLARATION_COMMAND(3),  PUSH_CODE)


DEF_CMD( PUSH,  3 ,,   PUSH_REG_CODE)


DEF_CMD( POP,   4 ,   DECLARATION_COMMAND2(27)  DECLARATION_COMMAND(13), POP_CODE)


DEF_CMD( ADD,   5 ,,   ADD_CODE)


DEF_CMD( MOV,   6 ,     DECLARATION_COMMAND(6),  MOV_CODE)


DEF_CMD( MUL,   7 ,,   MUL_CODE)


DEF_CMD( SUB,   8 ,,   SUB_CODE)


DEF_CMD( END,   9 ,,   END_CODE)


DEF_CMD( SQRT,  10,,  SQRT_CODE)


DEF_CMD( OUT,   11,,  OUT_CODE)


DEF_CMD( DIV,   12,,  DIV_CODE)


DEF_CMD( POP,   13,,  POP_REG_CODE)


DEF_CMD( JMP,   14,,  JMP_CODE)


DEF_CMD( JE,    15,,  JE_CODE)


DEF_CMD( JNE,   16,;,  JNE_CODE)


DEF_CMD( JA,    17,,  JA_CODE)


DEF_CMD( JAE,   18,,  JAE_CODE)


DEF_CMD( JB,    19,,  JB_CODE)


DEF_CMD( JBE,   20,;,  JBE_CODE)


DEF_CMD( RET,   21,;,  RET_CODE)


DEF_CMD( :, 22,;, COLON_CODE)


DEF_CMD( CALL,  23,;,  CALL_CODE)


DEF_CMD( DPOP,  24,;,  DPOP_CODE)


DEF_CMD( IN,  25,;,  IN_CODE)
       

DEF_CMD( PUSH,  26 ,,   PUSH_OP_CODE)
       
       
DEF_CMD( POP,   27,,  POP_OP_CODE)


