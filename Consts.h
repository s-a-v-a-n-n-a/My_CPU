#pragma once

#define DEFINE_COMMANDS(name, number, arg, coding, discoding) \
        COM_##name,

typedef enum commands_for_processor
{
    #include "Commands.h"
} commands;

#undef DEFINE_COMMANDS

const char *LISTING_FILE         = "listing.txt";
const char *EXECUTABLE_FILE      = "binary.xex";
const char *ASSEMBLING_FILE_NAME = "loop.xax";
const char *DISASSEMBLING_FILE   = "disassemble.txt";

const int START_NUMBER  = 2;
const int REGISTER_NUM  = 4;
const int RAM_MEMORY    = 1000;

const int ONLY_VAL      = 0;
const int REG_RAX       = 1;
const int REG_RBX       = 2;
const int REG_RCX       = 3;
const int REG_RDX       = 4;
const int NO_REG_JUMP   = 5;
const int ADDRSS        = 6;
const int NOTHING       = 7;
