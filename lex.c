#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_CHAR '\0'

typedef enum { LIT, IDT } TType;

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

DPair* findCharII(char a, DPair* arr_delim) {
  do {
    if (arr_delim->pair[0] == a){
      arr_delim++;
      return arr_delim;
    }
  }
  while(arr_delim->end != true);
  return NULL;
}

char* readTill(char** src_line, char end_char) {
  size_t bufsize = 1, offset = 0;
  char* buffer = NULL;
  while (**src_line != '\0' && **src_line != end_char) {
    if (offset == bufsize - 1) {
      bufsize *= 2;
      char* new_buf = realloc(buffer, bufsize);
      if (new_buf == NULL && !buffer) {
        return NULL;
      }
      buffer = new_buf;
    }
    buffer[offset++] = **src_line;
    (*src_line)++;
  }
  if (offset < bufsize - 1) {
    char* new_buf = realloc(buffer, offset + 1);
    if (new_buf != NULL) {
      buffer = new_buf;
    }
  }
  buffer[offset] = '\0';
  return buffer;
}

Tok nextTok(char** src_line, DPair* src_pair) {
  Tok local_tok;
  char* check;
  DPair* var_pair = NULL;
  while (**src_line == ' ') {
    src_line++;
  }
  if ((var_pair = findCharII(**src_line, src_pair)) != NULL) {
    (*src_line)++;
    if ((check = readTill(src_line, var_pair->pair[1])) != NULL){
      local_tok.token = check;
      local_tok.type = var_pair->tok_type;
    }
    local_tok.type = var_pair->tok_type;
  } else {
    local_tok.token = readTill(src_line, ' ');
    local_tok.type = IDT;
  }
  return local_tok;
}

Tok* tokArr(char* src_line, DPair* src_pair) {
  Tok* list = NULL;
  char* src_cpy = src_line;
  size_t tok_size = sizeof(Tok), bufsize = 1, offset = 0;
  if (src_cpy == NULL) {
    return NULL;
  }
  while (*src_cpy != '\0') {
    if (offset == bufsize - 1) {
      bufsize *= 2;
      Tok* new_list = realloc(list, bufsize * tok_size);
      if (new_list == NULL && !list) {
        return NULL;
      }
      list = new_list;
    }
    list[offset++] = nextTok(&src_cpy, src_pair);
    src_cpy++;
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

int main(void) {
  char* src = "This is outside, \"this is inside\", and back outside";
  DPair them_pairs[] = {
    {
    .pair = {'\"', '\"'},
    .tok_type = LIT,
    .end = true
    }
  };
  Tok* final = NULL;
  final = tokArr(src, them_pairs);
  for (unsigned index = 0; final[index].end != true; index++) {
    printf("%d( %s )\n", final[index].type, final[index].token);
  }
  return 0;
}
