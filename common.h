#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef enum { TOKEN_LIT = 0, TOKEN_IDENT } TokenType;
typedef enum { TASK_TODO = 0, TASK_EVENT, TASK_SCHED } TaskType;
typedef enum {
  REPEATTYPE_WD = 0,
  REPEATTYPE_MD,
  REPEATTYPE_YD,
  REPEATTYPE_IN
} RepeatType;

typedef struct {
  char pair[2];
  TokenType tok_type;
  bool end;
} DPair;

typedef struct {
  TokenType type;
  char* token;
  bool end;
} Tok;

void* arrayInator(void* pointer, size_t memsize, size_t newsize);
