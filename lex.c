#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/* removed useless def here*/
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

DPair* findDelimP(char a, DPair* arr_delim) {
  do {
    if (arr_delim->pair[0] == a) {
      return arr_delim;
    }
    arr_delim++;
  } while ((arr_delim - 1)->end != true);
  return NULL;
}

char* readTill(char** src_line, char end_char) {
  size_t bufsize = 1, offset = 0;
  char* buffer = NULL;
  if (*src_line == NULL)
    return NULL;
  while (**src_line != '\0' && **src_line != end_char) {
    if (offset == bufsize - 1) {
      bufsize *= 2;
      char* new_buf = realloc(buffer, bufsize);
      if (new_buf == NULL && buffer) {
        free(buffer);
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
      if (new_list == NULL && list) {
        free(list);
        return NULL;
      }
      list = new_list;
    }
    list[offset++] = nextTok(&src_cpy, src_pair);
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

int main(void) {
  char* src = "This is, \"in a thing\", and out";
  DPair them_pairs[] = {{.pair = {'\"', '\"'}, .tok_type = LIT, .end = true}};
  Tok* final = NULL;
  unsigned long finalInd = 0;
  final = tokArr(src, them_pairs);
  do {
    printf("%d:(\"%s\"), ", final[finalInd].type, final[finalInd].token);
    finalInd++;
  } while (final[finalInd - 1].end != true);
  deInit(final);
  return 0;
}
