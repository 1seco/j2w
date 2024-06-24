#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
/* removed useless def here*/
DPair* findDelimP(char a, DPair* arr_delim) {
  do {
    if (arr_delim->pair[0] == a) {
      return arr_delim;
    }
    arr_delim++;
  } while ((arr_delim - 1)->end != true);
  return NULL;
}

Tok nextTok(char** src_line, DPair* src_pair) {
  Tok local_tok;
  DPair* DelmP = NULL;
  while (**src_line == ' ') {
    (*src_line)++;
  }
  if ((DelmP = findDelimP(**src_line, src_pair)) != NULL) {
    (*src_line)++;
    local_tok.token = readTill(src_line, DelmP->pair[1]);
    local_tok.type = DelmP->tok_type;
    (*src_line)++;
  } else {
    local_tok.token = readTill(src_line, ' ');
    local_tok.type = IDT;
  }
  return local_tok;
}

Tok* tokArr(char* src_str, DPair* src_pair) {
  Tok* list = NULL;
  size_t tok_size = sizeof(Tok), bufsize = 1, offset = 0;
  if (src_str == NULL) {
    return NULL;
  }
  while (*src_str != '\0') {
    if (offset == bufsize - 1) {
      bufsize *= 2;
      Tok* new_list = realloc(list, bufsize * tok_size);
      if (new_list == NULL && list) {
        free(list);
        return NULL;
      }
      list = new_list;
    }
    list[offset++] = nextTok(&src_str, src_pair);
  }
  if (offset < bufsize - 1) {
    Tok* new_list = realloc(list, offset * tok_size);
    if (new_list != NULL) {
      list = new_list;
    }
  }
  list[offset - 1].end = true;
  return list;
}

void deInit(Tok* array) {
  unsigned long index = 0;
  do {
    free(array[index++].token);
  } while (array[index - 1].end != true);
  free(array);
}
