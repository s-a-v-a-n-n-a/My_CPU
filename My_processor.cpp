#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "PolyStack.h"
#include "Assembler.h"
#include "Disassembler.h"

#define COMPILATING

#define DEFINE_COMMANDS(name, number, args, coding, discoding) \
        case number:                                           \
            printf("%s\n", #name);                             \
                                                               \
            coding;                                            \
                                                               \
            break;


typedef struct Processor_on_stack Processor;

struct Processor_on_stack{
    Stack  *stack;
    Stack  *funcs;
    double  registers[4];
    double *ram;
};

const char *EXECUTABLE_FILE = "second.xex";
const char *NAME            = "SquareSolving.xax";

char *read_program     (size_t *length);

void  start_perfomance (char *program, size_t length);

int main (int argc, const char **argv)
{
    int        com   = 0;
    assembl_er error = ASM_OK;

    #ifdef COMPILATING
    if (argc > 1)
    {
        error = processing(argv[1]);
        com = 1;
    }
    else
    {
        error = processing(NAME);
    }

    start_dis();
    #endif

    if (error == ASM_OK)
    {
        size_t length = 0;
        char  *prog   = read_program(&length);
        if (prog)
            start_perfomance(prog, length);

        if (com)
            system("pause");
    }
    else
        system("pause");
    system("pause");
    return 0;
}

char *read_program (size_t *length)
{
    *length        = 0;
    size_t n_lines = 0;
    char *program  = (char*) reading_file(EXECUTABLE_FILE, length, &n_lines, 0);
    if (!program)
    {
        printf("No memory access denied\n");
        return NULL;
    }

    return program;
}

void start_perfomance (char *program, size_t length)
{
    char *program_copy = program;

    Processor proc = {0};
    proc.stack = stack_new(2);
    proc.funcs = stack_new(2);
    proc.ram   = (double*) calloc(1000, sizeof(double));

    for (int i = 0; i < 4; i++)
    {
        proc.registers[i] = 0;                                               //   /\  | || |      ||     /\    ||
    }                                                                       //   //\\  \||/       ||    //\\   ||
                                                                                //..\\  ||        ||   //..\\  ||
    for (long long rip = 0; rip < (long long)(length/sizeof(char)) - 1; rip++) // ()//  //         \\ // () || ||
    {
        printf("%04x\n", rip);
        char val = *program_copy;

        char mode = 0;

        double val_earl = 0;
        double val_last = 0;

        long long jump  = 0;

        program_copy++;

        switch ((int)val)
        {
            #include "Commands.h"

            default:

                break;
        }
    }

    stack_destruct(&proc.funcs);
    stack_destruct(&proc.stack);
    free(program);
}

#undef DEFINE_COMMANDS
