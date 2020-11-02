#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "Reading_from_file.h"
#include "Enums.h"

const int FINDING       = 0;
const int WRITING       = 1;
const int DISASSEMBLING = 2;

#define DEFINE_COMMANDS(name, number, args, coding, discoding) \
        case number:                                           \
                                                               \
            discoding;                                         \
                                                               \
            break;

char *read_codes       (size_t *length);

void disassembling     (FILE *dis, char *program, size_t length);

long long count_labels (FILE *dis, char *program, size_t length, long long **labels);

void write_labels      (FILE *dis, char *program, size_t length, long long *labels);

void disassembling (FILE *dis, char *program, size_t length, long long *labels, long long n_labels);

void start_dis         ();

char *read_codes   (size_t *length)
{
    *length        = 0;
    size_t n_lines = 0;
    char *program  = (char*) reading_file("second.xex", length, &n_lines);
    if (!program)
    {
        printf("No memory access denied\n");
        return NULL;
    }

    return program;
}

long long count_labels (FILE *dis, char *program, size_t length, long long **labels_null)
{
    char *program_copy = program;

    long long  n_labels = 0;
    long long *labels   = *labels_null;

    int i = FINDING;

    for (int rip = 0; rip < (int)(length/sizeof(char)) - 1; rip++)
    {
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

    *labels_null = (long long*) calloc((size_t)n_labels + 1, sizeof(long long));
    for (long long j = 0; j <= n_labels; j++)
        (*labels_null)[j] = -1;

    return n_labels;
}

void write_labels (FILE *dis, char *program, size_t length, long long *labels)
{
    char *program_copy = program;

    long long  n_labels = 0;

    int i = WRITING;

    for (int rip = 0; rip < (int)(length/sizeof(char)) - 1; rip++)
    {
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
}

void disassembling (FILE *dis, char *program, size_t length, long long *labels, long long n_labels)
{
    char *program_copy = program;

    unsigned int i = DISASSEMBLING;

    for (int rip = 0; rip < (int)(length/sizeof(char)) - 1; rip++)
    {
        for (long int j = 0; j < n_labels; j++)
        {
            if (rip == labels[j])
            {
                fprintf(dis, "\%ld:\n", j);
                break;
            }
        }

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

}

void start_dis()
{
    size_t length = 0;
    char  *codes  = read_codes(&length);

    FILE *dis = fopen("disassemble.txt", "wb");

    if (codes)
    {
       long long *labels = NULL;

       long long num_labels = count_labels(dis, codes, length, &labels);
       write_labels(dis, codes, length, labels);
       disassembling(dis, codes, length, labels, num_labels);

       free(labels);
    }

    free(codes);
    fclose(dis);
}

#undef DEFINE_COMMANDS