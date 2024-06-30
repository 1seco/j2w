#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef enum { LIT, IDT } TType;
typedef enum { TODO, EVENT, SCHED } TaskType;
typedef enum { WD, MN, IN } RepeatType;

typedef struct {
  unsigned short tm_mday : 5;
  unsigned short tm_mon : 4;
  unsigned short tm_year : 16;
  unsigned short tm_hour : 5;
  unsigned short tm_min : 6;
} minimal_tm;

typedef struct {
  minimal_tm time;
  bool is_repeat[5];
} Date;

typedef struct {
  Date* array;
  size_t len;
} DateArray;

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
