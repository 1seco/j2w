#include "lex.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
  sched,
  event,
  todo
} TaskType

typedef struct {
  TaskType task_type;
  struct tm start_dt;
  struct tm end_dt;
  char* title;
  char* tag;
} UniversalType;

schedSet()

int switchARooOrSmnthIdk(Tok* line) {
  if (strcmp(line->token, "sched")) {

  } else if (strcmp(line->token, "event")) {

  } else if (strcmp(line->token), "todo") {
  }
  return 1;
}
