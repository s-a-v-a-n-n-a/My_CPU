#include <stdio.h>
#include <stdlib.h>

size_t get_size_of_file (FILE *file);

char  *get_the_text     (FILE *file, size_t *length);

size_t get_num_lines    (char *buf, size_t length);

char  *reading_file     (FILE *file, size_t *length, size_t *num_lines);


size_t get_size_of_file(FILE* file)
{
    assert(file != NULL);

    long int length = 0;

    if (!fseek(file, 0, SEEK_END))
        length = ftell(file);
    length++;

    fseek(file, 0, SEEK_SET);

    return length;
}

char *get_the_text(FILE* file, size_t* length)
{
    assert(file != NULL && *length != 0);

    char* buffer = (char*) calloc(*length, sizeof(char));
    long int obj = fread(buffer, sizeof(char), *length, file);

    assert((size_t)obj == *length - 1);

    if (buffer[obj] != '\n')
    {
        (*length)++;
        buffer[*length - 2] = '\n';
    }

    buffer[*length - 1] = '\0';

    return buffer;
}

size_t get_num_lines(char* buf, size_t length)
{
    assert(buf != NULL);

    long int n_lines = 0;
    char* ptr        = NULL;
    size_t len_tmp   = 0;

    do
    {
        ptr = strchr(buf, '\n');

        if (ptr != NULL)
        {
            len_tmp += ptr - buf + 1;

            if (len_tmp < length)
                n_lines++;

            buf = ptr + 1;
        }

    }while (ptr != NULL && len_tmp < length);

    return n_lines;
}

char *reading_file (const char *file_name, size_t *length, size_t *num_lines)
{
    FILE* input = fopen(file_name, "rb");
    if (!input)
        return NULL;

    *length       = get_size_of_file(input);
    char *first   = get_the_text    (input, length);

    *num_lines = get_num_lines (first, *length);
    
    fclose(input);

    return first;
}
