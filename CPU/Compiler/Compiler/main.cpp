#include <stdio.h>
#include <string.h>
#include <cassert>


const char LOG_FILES_NAME [] = "LogFiles.txt";

const char FILES_PROGRAMM_NAME []  = "../../Programm/code.txt";

const char FILES_COMPILER_PROGRAMM_NAME [] = "../../Compiler Programm/LOL.txt";

const char VERSION_NUMBER [] = "../../SYSTEM/Version.txt";



char* ReadFiles (const char* name_files, int *number_of_char);

int Compiler (const char* name_files, char* my_buffer, int number_of_char);

int CorrectionNumber (char* my_buffer, int* number_of_char);

int VersionProgramm (const char* name_files_version, const char* name_files);

int ReadFunction (char* function_str, const char* my_buffer, int number_of_char, int* i);

int PrintFiles ();



#define DEF_CMD(function_name, number, declaration_cmd, specification) \
if (strcmp(parameter, #function_name) == 0) \
{ \
    declaration_cmd\
    return number; \
}



int SwitchFunction (char* parameter, const char* my_buffer, int number_of_char, int* i) {
    char parameter_reg [20] = "";
    
#include "../../SYSTEM/Comand.h"
    
    return -1;
}


int main()
{
    
    int number_of_char = 0;
    
    char* my_buffer = ReadFiles (FILES_PROGRAMM_NAME, &number_of_char);
    printf ("%s\nnumber %i\n===========\n", my_buffer, number_of_char);
    
    Compiler (FILES_COMPILER_PROGRAMM_NAME, my_buffer, number_of_char);
    
    
    
    return 0;
}




int VersionProgramm (const char* name_files_version, const char* name_files) {
    FILE *files = fopen (name_files_version, "rt");
    
    
    if (files == NULL)
    {
        assert(files != NULL);
    }
    
    fseek (files, 0, SEEK_END);
    int number_of_char = ftell(files);
    
    char* file_validation = new char [number_of_char];
    
    fseek (files, 0, SEEK_SET);
    fscanf(files, "%s", file_validation);
    fclose (files);
    
    
    files = fopen (name_files, "wt");
    
    
    if (files == NULL)
    {
        assert(files != NULL);
    }
    fprintf (files, "%s\n", file_validation);
    
    fclose (files);
    return 0;
}



int CorrectionNumber (char* my_buffer, int* number_of_char) {
    for (int i = 0; i < *number_of_char; ++i) {
        if (my_buffer [i] == '\n') {
            --*number_of_char;
        }
    }
    return 0;
}



int ReadFunction (char* function_str, const char* my_buffer, int number_of_char, int* i) {
    
    int j = 0;
    
    while ((my_buffer [*i] != '\0') && (my_buffer [*i] != '\r') && (my_buffer [*i] != '\n') && (my_buffer [*i] != ' ') && (*i < number_of_char)) {
        function_str [j] = my_buffer [*i];
        ++j;
        ++*i;
    }
    
    function_str [j] = '\0';
    return 0;
}



int PrintFiles (FILE *files, int number_function, char* function_str) {
    if (number_function != -1)
    {
        fprintf (files, "%i\n", number_function);
    } else {
        fprintf (files, "%s\n", function_str);
    }
    return 0;
}



int Compiler (const char* name_files, char* my_buffer, int number_of_char) {
    
    VersionProgramm (VERSION_NUMBER, name_files);
    
    
    FILE *files = fopen (name_files, "at");
    if (files == NULL)
    {
        assert(files != NULL);
    }
    
    
    //CorrectionNumber (my_buffer, &number_of_char); // WINDA!!!!!!!!!!
    
    
    char function_str [20] = "";
    int number_function = -1;
    
    
    for (int i = 0; i < number_of_char; ++i) {
        
        
        ReadFunction (function_str, my_buffer, number_of_char, &i);
        
        
        number_function = SwitchFunction (function_str, my_buffer, number_of_char, &i);
        printf("%i) => {[%s] == NUMBER CODE [%i]}\n", i,function_str, number_function);\
        
        if ((function_str [0] != '\0') && (function_str [0] != '\r') && (function_str [0] != '\n') && (function_str [0] != ' '))
        {
            PrintFiles (files, number_function, function_str);
        }
        
        if (i >= number_of_char) {
            fclose (files);
            return 0;
        }
        
        while ((my_buffer [i] == '\n') && (my_buffer [i + 1] == '\n')) {
            ++i;
        }
        
    }
    
    fclose (files);
    
    return 0;
}


char* ReadFiles (const char* name_files, int *number_of_char) {
    
    
    FILE *files = fopen (name_files, "rt");
    
    
    if (files == NULL)
    {
        assert(files != NULL);
    }
    
    fseek (files, 0, SEEK_END);
    *number_of_char = ftell(files);
    
    char* file_validation = new char [++*number_of_char];
    
    
    fseek (files, 0, SEEK_SET);
    fread (file_validation, sizeof (char), *number_of_char, files);
    fclose (files);
    file_validation [*number_of_char - 1] = '\0';
    return file_validation;
}

