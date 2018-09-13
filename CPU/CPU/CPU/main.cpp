#include <stdio.h>
#include <string.h>
#include <cassert>
#include <math.h>


const int OPERATIVE = 50;

typedef double DATA_TYPE;

const char LOG_FILES_NAME [] = "LogFiles.txt";
const char FILES_COMPILER_PROGRAMM_NAME [] = "../../Compiler Programm/LOL.txt";
const char VERSION_NUMBER [] = "../../SYSTEM/Version.txt";


enum ProgramStatusConst {
    WaitingProgram = 0,
    StartProgram = 1,
    EndProgram = 2,
    SearchTagsProgram = 3
};


struct resources {
    DATA_TYPE reg [4];
    DATA_TYPE op [OPERATIVE];
    int comparison [2];
};





#include "../../SYSTEM/Stack/Stack.h"

/*******************************************************************CAT
 #include "../../SYSTEM/CAT/cat.h"

#define CAT(number, function_name) \
if (*program_status == StartProgram) {\
printf("\n----\n%i) %s\n----\n", *position_number, #function_name);\
Cat (number);\
}
 
//=>  CAT(number, #function_name)\
********************************************************************/

#define DEF_CMD(function_name, number, declaration, specification) \
case number: {\
specification;\
break;\
};




int SwitchFunction (DATA_TYPE* programm, int* program_status, struct t_stack *label_history, int* position_number, struct t_stack *name_stack, struct resources* data, int* goto_data_name, int* goto_data_position, int*position_number_goto, const int code_length) {
    char parameter[0];
    char* parameter_reg;
    FILE *files = fopen (LOG_FILES_NAME, "at");
    fprintf(files, "==========Command==========\n\n");
    
    fprintf(files, "Status: %i\n\n", *program_status);
    
    fprintf(files, "Position: %i\n\n", *position_number);
    
    fprintf(files, "programm [%i] = %lg\n", *position_number, programm [*position_number]);
    
    fprintf(files, "\n===========================\n\n");
    fclose(files);
    
    switch ((int)(programm [*position_number])) {
        #include "../../SYSTEM/Comand.h"
    }
    
    return 0;
}





int CODING (DATA_TYPE* programm, int program_status, int* position_number, struct t_stack *name_stack,
            struct resources* data, int* goto_data_name, int* goto_data_position, int* position_number_goto, const int code_length);

int VersionProgramm (const char* name_files_version, const char* name_files);

DATA_TYPE* ReadProgramm (const char* name_files, int* code_length);





int main ()
{
    FILE *files = fopen (LOG_FILES_NAME, "wt");
    
    if (VersionProgramm (VERSION_NUMBER, FILES_COMPILER_PROGRAMM_NAME) != 0) {
        printf("ERROR version programm");
        return 0;
    }
    DATA_TYPE* RAM = new DATA_TYPE [10];
    
    
    int code_length = -1, position_number_1 = 0, program_status = 0, position_number_goto = 0;
    DATA_TYPE* programm = ReadProgramm (FILES_COMPILER_PROGRAMM_NAME, &code_length);
    
    
    
    t_stack mystack;
    mystack.BUG = mystack.Construct(&mystack, 10);
    
    resources data;
    
    
    int goto_data_name [code_length];
    int goto_data_position [code_length];
    for (int i = 0; i < code_length; ++i) {
        goto_data_name [i] = 0;
        goto_data_position [i] = 0;
    }
    
    
    CODING (programm, SearchTagsProgram, &position_number_1, &mystack, &data, goto_data_name, goto_data_position, &position_number_goto, code_length);
    
    CODING (programm, WaitingProgram, &position_number_1, &mystack, &data, goto_data_name, goto_data_position, &position_number_goto, code_length);
    
    //assert(0);
    mystack.Destructor(&mystack);
    delete [] RAM;
    return 0;
}


int CODING (DATA_TYPE* programm, int program_status, int* position_number, struct t_stack *name_stack,
            struct resources* data, int* goto_data_name, int* goto_data_position, int* position_number_goto, const int code_length) {
    
    *position_number = 0;
    *position_number_goto = 0;
    int status_end = 0;
    
    t_stack label_history;
    label_history.BUG = label_history.Construct(&label_history, 10);
    
    while (*position_number < code_length) {
        /*
        if (program_status != SearchTagsProgram)
            printf ("code[%i] == %lg\n", *position_number,programm [*position_number]);
        */
        status_end = SwitchFunction (programm, &program_status, &label_history, position_number, name_stack, data,
                        goto_data_name, goto_data_position, position_number_goto, code_length);
        if (status_end == EndProgram)
            return 0;
        ++(*position_number);
        
    }
    label_history.Destructor(&label_history);
    return 0;
}


DATA_TYPE* ReadProgramm (const char* name_files, int* code_length) {
    FILE *files = fopen (name_files, "rt");
    
    
    fseek (files, 0, SEEK_END);
    *code_length = ftell(files);
    
    DATA_TYPE* programm = new DATA_TYPE [*code_length];
    
    fseek (files, 0, SEEK_SET);
    
    
    
    char* version = new char [10];
    fscanf(files, "%s", version);
    delete [] version;
    
    
    for (int i = 0; feof (files) == 0; ++i) {
        fscanf(files, "%lg", &(programm [i]));
        *code_length = i + 1;
    }
    --*code_length;
    
    fclose (files);
    
    return programm;
}


int VersionProgramm (const char* name_files_version, const char* name_files) {
    FILE *files = fopen (name_files_version, "rt");
    
    
    if (files == NULL)
    {
        assert(files != NULL);
    }
    
    fseek (files, 0, SEEK_END);
    int number_of_char = ftell(files);
    
    char* file_validation_original = new char [number_of_char];
    char* file_validation = new char [number_of_char];
    
    fseek (files, 0, SEEK_SET);
    fscanf(files, "%s", file_validation_original);
    fclose (files);
    
    
    files = fopen (name_files, "rt");
    
    
    if (files == NULL)
    {
        assert(files != NULL);
    }
    fscanf(files, "%s", file_validation);
    
    fclose (files);
    
    
    if (strcmp(file_validation_original, file_validation) == 0) {
        return 0;
    } else {
        return 1;
    }
}
