#ifndef LEX_H
#define LEX_H

#include "common.h"
Tok* tokArr(char* src_line, DPair* src_pair);
void deInit(Tok* array);

#endif
