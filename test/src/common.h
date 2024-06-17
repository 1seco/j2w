#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef enum { LIT, IDT } TType;
typedef enum { TODO, EVENT, SCHED } TaskType;
typedef enum { WD, MD, YD, IN } RepeatType;

typedef struct {
  RepeatType repeat_type;
  unsigned* repeat_val;
} RepeatPair;

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

typedef struct {
  TaskType task_type;
  struct tm start_dt;
  struct tm end_dt;
  RepeatPair repeat_pair;
  char* title;
  char* tag;
} UniversalType;

typedef struct {
  RepeatPair day_num;
  bool init;
} DayEntry;

typedef struct {
  DayEntry* Array;
  size_t size;
  size_t capacity;
} DayArray;

void* arrayInator(void* pointer, size_t memsize, size_t newsize) {
  void* temp = NULL;
  temp = realloc(pointer, memsize);
  if (temp != NULL) {
    pointer = temp;
    return pointer;
  }
  return NULL;
}
#endif
