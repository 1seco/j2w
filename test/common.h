#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef enum { LIT, IDT } TType;
typedef enum { TODO, EVENT, SCHED } TaskType;
typedef enum { WD, MD, YD, IN } RepeatType;


typedef struct {
  char pair[2];
  TType tok_type;
  bool end;
} DPair;

typedef struct {
  TType type;
  char* token;
  bool end;
} Tok;

char* readTill(char** src_string, char* end_char);
char** splitStr(char* src, char* dividers);
#endif
